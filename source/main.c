#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "../include/llrbt_for_file.h"
#include "../include/file_operations.h"

static const char error_args[] = "Error: uncorrect parametrs.\n"
"Usage: 1 - filename 2 - \"command\" (add, query, list) 3 - identificator.\n"
"identificator may have less than 60 characters.\n";

int main(int argc, char **argv)
{
	struct llrbt_for_file store;
	int equal, fd;
	if(argc < 3) {
		write(2, error_args, sizeof(error_args));
		return 1;
	}
	if(argc >= 4) {
		int length = str_length(argv[3]);
		if(length > 59) {
			write(2, error_args, sizeof(error_args));
			return 1;
		}
	}
	/* correct parametrs, we can work */
	fd = open(argv[1], O_RDWR|O_CREAT, 0666);
	if(fd == -1) {
		write(2, argv[1], sizeof(argv[1]));
		close(fd);
		return 2;
	}
	llrbt_init(fd, &store);
	equal = is_str_equal(argv[2], "list");
	if(equal) {
		file_print_content(fd, 4);
		close(fd);
		return 0;
	}
	equal = is_str_equal(argv[2], "add");
	if(equal && argc >= 4) {
		file_add_record(fd, store.root_counter_offset, argv[3]);
		close(fd);
		return 0;
	}
	equal = is_str_equal(argv[2], "query");
	if(equal && argc >= 4)
		file_search_record(fd, store.root_counter_offset, 
						argv[3]);
	close(fd);
	return 0;
}
