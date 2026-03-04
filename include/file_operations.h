#ifndef FILE_OPERATIONS_H_SENTRY
#define FILE_OPERATIONS_H_SENTRY 
#include "my_string.h"
#include "record.h"
#include "llrbt_for_file.h"
#include <errno.h>
#include <stdio.h>

void file_print_content(int fd, const int pos);
void file_add_record(int fd, const int pos, const char *key);
void file_search_record(int fd, const int pos, const char *key);
#endif
