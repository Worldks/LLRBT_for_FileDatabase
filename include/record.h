#ifndef RECORD_H_SENTRY
#define	RECORD_H_SENTRY

enum { string_length = 60 };
enum { max_str_record = 60 };

struct record {
	char str[string_length];
	unsigned int counter;
};

void init_record(struct record *rc);

#endif
