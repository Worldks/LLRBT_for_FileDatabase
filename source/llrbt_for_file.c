#include "../include/llrbt_for_file.h"

static void init_node(struct node *node)
{
	init_record(&(node->rc));
	node->color = red;
	node->left = node->right = -1; /* leaf */
	node->rc.counter = 1;
}

void read_node_from_file(int fd, struct node *nd, int pos_nd)
{
	int count;
	lseek(fd, pos_nd, SEEK_SET);
	count = read(fd, nd, sizeof(struct node));
	check_read_call(count, "read_node_from_file()");
	lseek(fd, -sizeof(*nd), SEEK_CUR);
}

void write_node_in_file(int fd, struct node *nd, int pos_nd)
{
	int count;
	lseek(fd, pos_nd, SEEK_SET);
	count = write(fd, nd, sizeof(struct node));
	check_write_call(count, "write_node_in_file()");
	lseek(fd, -sizeof(*nd), SEEK_CUR);
}

int read_position(int fd, int pos_offset)
{
	int count, position;
	lseek(fd, pos_offset, SEEK_SET);
	count = read(fd, &position, sizeof(int));
	check_read_call(count, "read_position()");
	lseek(fd, -sizeof(int), SEEK_CUR);
	return position;
}

void write_position(int fd, int pos_offset, int pos_to_write)
{
	int count, position;
	position = pos_to_write;
	lseek(fd, pos_offset, SEEK_SET);
	count = write(fd, &position, sizeof(int));
	check_write_call(count, "write_position()");
	lseek(fd, -sizeof(int), SEEK_CUR);
}

static void color_flip(int fd, int pos)
{
	int pos_value, pos_right_children, pos_left_children;
	struct node tmp;
	init_node(&tmp);
	pos_value = read_position(fd, pos);
	read_node_from_file(fd, &tmp, pos_value);
	pos_right_children = tmp.right;
	pos_left_children = tmp.left;
	if(tmp.color == black)
		tmp.color = red;
	write_node_in_file(fd, &tmp, pos_value);
	read_node_from_file(fd, &tmp, pos_left_children);
	tmp.color = black;
	write_node_in_file(fd, &tmp, pos_left_children);
	read_node_from_file(fd, &tmp, pos_right_children);
	tmp.color = black;
	write_node_in_file(fd, &tmp, pos_right_children);
}

static void left_rotate(int fd, int pos)
{
	struct node tmp, tmp_right;
	int pos_value, pos_right_children;
	init_node(&tmp);
	init_node(&tmp_right);
	pos_value = read_position(fd, pos);
	read_node_from_file(fd, &tmp, pos_value);
	pos_right_children = tmp.right;
	read_node_from_file(fd, &tmp_right, tmp.right);
	
	tmp_right.color = tmp.color;
	tmp.color = red;
	tmp.right = tmp_right.left;
	tmp_right.left = pos_value;
	write_node_in_file(fd, &tmp, pos_value);
	write_node_in_file(fd, &tmp_right, pos_right_children);
	write_position(fd, pos, pos_right_children);
}

static void right_rotate(int fd, int pos)
{
	int pos_value, pos_left_children;
	enum node_color left_color;
	struct node tmp, tmp_left;
	init_node(&tmp);
	init_node(&tmp_left);
	pos_value = read_position(fd, pos);
	read_node_from_file(fd, &tmp, pos_value);
	pos_left_children = tmp.left;
	read_node_from_file(fd, &tmp_left, tmp.left);
	
	left_color = tmp_left.color;
	tmp_left.color = tmp.color;
	tmp.color = left_color;
	tmp.left = tmp_left.right;
	tmp_left.right = pos_value;
	write_node_in_file(fd, &tmp, pos_value);
	write_node_in_file(fd, &tmp_left, pos_left_children);
	write_position(fd, pos, pos_left_children);
}

static void fix_up(int fd, int pos)
{
	/* break the invariant
	 *	1. 2 red links left (right_rot, color_flip)											+
	 *	2. 1 red link right (left_rot)														+
	 *	3. 1 red link left, next red link right (left_rot, right_rot, colr_flip)			+
	 *	4. 1 red left and 1 red right (color flip)											+
	 * */
	int pos_value;
	struct node tmp, tmp_left, tmp_right;
	struct node tmp_left_left, tmp_left_right;
	init_node(&tmp);
	init_node(&tmp_left);
	init_node(&tmp_right);
	pos_value = read_position(fd, pos);
	read_node_from_file(fd, &tmp, pos_value);
	if(tmp.left != -1)
		read_node_from_file(fd, &tmp_left, tmp.left);
	if(tmp.right != -1)
		read_node_from_file(fd, &tmp_right, tmp.right);
	if(tmp.left == -1 && tmp.right == -1) {
		return;
	} else if(tmp.left != -1 && tmp.right != -1 
				   	&& tmp_left.color == red && tmp_right.color == red) {
		color_flip(fd, pos);
	} else if(tmp.left != -1 && tmp_left.color == red) {
			if(tmp_left.left != -1) {
				init_node(&tmp_left_left);
				read_node_from_file(fd, &tmp_left_left, tmp_left.left);
			}
			if(tmp_left.right != -1) {
				init_node(&tmp_left_right);
				read_node_from_file(fd, &tmp_left_right, tmp_left.right);
			}
			if(tmp_left.left != -1 && tmp_left_left.color == red) {
				right_rotate(fd, pos);
				color_flip(fd, pos);
				return;
			}
			if(tmp_left.right != -1 && tmp_left_right.color == red) {
				left_rotate(fd, pos_value+sizeof(tmp.rc)+sizeof(tmp.color));
				right_rotate(fd, pos);
				color_flip(fd, pos);
				return;
			}
	} else if(tmp.right != -1 && tmp_right.color == red)
		left_rotate(fd, pos);
}

void llrbt_init(int fd, struct llrbt_for_file *root)
{
	int count = -1;
	root->fd = fd;
	count = lseek(fd, 0, SEEK_END);
	if(count == 0) {
		count = -1;
		write(fd, &count, sizeof(count));
		lseek(fd, 0, SEEK_SET);
	}
	root->root_counter_offset = 0;
}

void llrbt_insert(int fd, int pos, const void *key)
{	/* *pos - offset of position witch pointer to recodr in file */
	/* need recursion and fix_up() function */
	struct node tmp;
	enum compare cmp;
	int pos_value;
	init_node(&tmp);
	pos_value = read_position(fd, pos);
	if(pos_value == -1) {
		pos_value = lseek(fd, 0, SEEK_END);
		str_copy(tmp.rc.str, (const char *)key);
		write_node_in_file(fd, &tmp, pos_value);
		write_position(fd, pos, pos_value);
		return;
	}
	read_node_from_file(fd, &tmp, pos_value);
	cmp = compare_strings((const char *)key, (tmp.rc).str);
	switch(cmp) {
		case equal:
			tmp.rc.counter++;
			write_node_in_file(fd, &tmp, pos_value);
			break;
		case less:
			pos_value = lseek(fd, sizeof(tmp.rc)+sizeof(tmp.color), SEEK_CUR);
			llrbt_insert(fd, pos_value, key);
			break;
		case greather:
			pos_value = lseek(fd, sizeof(tmp.rc)+sizeof(tmp.color)
							+sizeof(tmp.left), SEEK_CUR);
			llrbt_insert(fd, pos_value, key);
			break;
	}
	fix_up(fd, pos);
}

int llrbt_search(int fd, const int pos, const void *key)
{
	enum compare cmp;
	struct node tmp;
	int pos_value;

	pos_value = read_position(fd, pos);
	if(pos_value == -1) /* leaf */
		return pos;
	read_node_from_file(fd, &tmp, pos_value);
	cmp = compare_strings((const char *)key, (tmp.rc).str);
	switch(cmp) {
		case equal:
			return pos;
		case less:
			pos_value = lseek(fd, sizeof(tmp.rc)+sizeof(tmp.color), SEEK_CUR);
			return llrbt_search(fd, pos_value, key);
		case greather:
			pos_value = lseek(fd, sizeof(tmp.rc)+sizeof(tmp.color)
							+sizeof(tmp.left), SEEK_CUR);
			return llrbt_search(fd, pos_value, key);
	}
}

void llrbt_print(int fd, const int pos)
{
	char number[max_number_length] = { 0 };
	struct node tmp;
	int pos_value;
	pos_value = read_position(fd, pos);
	if(pos_value == -1)
		return;
	read_node_from_file(fd, &tmp, pos_value);
	if(tmp.left != -1)
		llrbt_print(fd, pos_value+sizeof(tmp.rc)+sizeof(tmp.color));
	if(tmp.right != -1)
		llrbt_print(fd, pos_value+sizeof(tmp.rc)+sizeof(tmp.color)
						+sizeof(tmp.left));
	write(1, tmp.rc.str, max_str_record);
	write(1, " : ",  3);
	number_to_str(tmp.rc.counter, number);
	write(1, number, sizeof(number));
	if(tmp.color == red)
		write(1, " red\n", 5);
	else 
		write(1, " black\n", 7);
}

void print_node_from_llrbt(int fd, int pos)
{
	char number[max_number_length] = { 0 };
	struct node tmp;
	int pos_value;
	pos_value = read_position(fd, pos);
	if(pos_value == -1) {
		write(1, "0\n", 2);
		return;
	}
	read_node_from_file(fd, &tmp, pos_value);
	write(1, tmp.rc.str, max_str_record);
	write(1, " : ",  3);
	number_to_str(tmp.rc.counter, number);
	write(1, number, sizeof(number));
	if(tmp.color == red)
		write(1, " red\n", 5);
	else 
		write(1, " black\n", 7);
}
