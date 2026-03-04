#ifndef UTILS_H_SENTRY
#define UTILS_H_SENTRY
#include <errno.h>
#include <stdio.h>

void check_write_call(int returned_counter, const char *function);
void check_read_call(int returned_counter, const char *function);

#endif
