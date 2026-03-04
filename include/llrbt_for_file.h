#ifndef LLRBT_FOR_FILE_H_SENTRY
#define LLRBT_FOR_FILE_H_SENTRY
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "record.h"
#include "utils.h"
#include "my_string.h"

enum node_color { red, black };

struct node {
	struct record rc;
	enum node_color color;
	int left;		/* offset in file */
	int right;		/* offset in file */
};

struct llrbt_for_file {
	int fd;
	int root_counter_offset;
					/* where root in file */
};

void read_node_from_file(int fd, struct node *nd, int pos_nd);
void write_node_in_file(int fd, struct node *nd, int pos_nd);
void write_position(int fd, int pos_offset, int pos_to_write);
int read_position(int fd, int pos_offset);
void llrbt_init(int fd, struct llrbt_for_file *root);
void llrbt_insert(int fd, int pos, const void *key);
int llrbt_search(int fd, const int pos, const void *key);
void llrbt_print(int fd, const int pos);
void print_node_from_llrbt(int fd, int pos);
#endif
