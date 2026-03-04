#include "../include/record.h"

void init_record(struct record *rc)
{
	int i;
	rc->counter = 0;
	for(i = 0; i < string_length; i++) {
		(rc->str)[i] = 0;
	}
}
