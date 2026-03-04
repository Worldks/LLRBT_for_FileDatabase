#ifndef MY_STRING_H_SENTRY
#define MY_STRING_H_SENTRY

enum { max_number_length = 12 };
enum compare { less, equal, greather };	/* equal - 1 => may use in if() */

int str_length(const char *str);
int is_str_equal(const char *str_1, const char *str_2);
void str_copy(char *dest, const char *src);
void number_to_str(int number, char *str);
enum compare compare_strings(const char *str_1, const char *str_2);

#endif
