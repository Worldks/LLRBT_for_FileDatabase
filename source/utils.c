#include "../include/utils.h"

void check_write_call(int returned_counter, const char *function)
{
	if(returned_counter == -1)
		perror(function);
}

void check_read_call(int returned_counter, const char *function)
{
	if(returned_counter == -1)
		perror(function);
}
