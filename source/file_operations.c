#include "../include/file_operations.h"

void file_add_record(int fd, const int pos, const char *key)
{
	llrbt_insert(fd, pos, key);
}

void file_search_record(int fd, const int root_pos, const char *key)
{
	char number[max_number_length] = { 0 };
	int pos, pos_value;
	struct node tmp;
	pos	= llrbt_search(fd, root_pos, key);
	pos_value = read_position(fd, pos);
	if(pos_value == -1) {
		write(1, "0\n", 2);
		return;
	}
	read_node_from_file(fd, &tmp, pos_value);
	number_to_str(tmp.rc.counter, number);
	write(1, number, sizeof(number));
	write(1, "\n", 1);
}

void file_print_content(int fd, const int pos)
{
	char number[max_number_length] = { 0 };
	struct node tmp;
	int pos_record, end;
	end = lseek(fd, 0, SEEK_END);
	lseek(fd, 0, SEEK_SET);
	pos_record = 4;
	for( ; pos_record != end;) {
		read_node_from_file(fd, &tmp, pos_record);
		write(1, tmp.rc.str, max_str_record);
		write(1, " + ",  3);
		number_to_str(tmp.rc.counter, number);
		write(1, number, sizeof(number));
		write(1, "\n", 1);
		pos_record += sizeof(struct node);
	}
}
