#include "../include/my_string.h"

enum compare compare_strings(const char *str_1, const char *str_2)
{
	int len_1, len_2, i;
	len_1 = str_length(str_1);
	len_2 = str_length(str_2);
	if(len_1 == len_2) {
		for(i = 0; (str_1[i] == str_2[i]) && (i < len_1); i++)
			{}
		if(i == len_1)
			return equal;
		goto compare;
	}
	if(len_1 < len_2)
		len_1 = len_2;
	for(i = 0; (str_1[i] == str_2[i]) && (i < len_1); i++) {
		if(i == len_1 - 1)
			return less;
	}

compare:
	if(str_1[i] < str_2[i])
		return less;
	else
		return greather;
}

int str_length(const char *str)
{
	int i;
	for(i = 0; str[i] != '\0'; i++)
		{}
	return i;
}

int is_str_equal(const char *str_1, const char *str_2)
{
	int len_1, len_2, i;
	len_1 = str_length(str_1);
	len_2 = str_length(str_2);
	if(len_1 != len_2)
		return 0;
	for(i = 0; (str_1[i] == str_2[i]) && (i < len_1); i++)
		{}
	if(i == len_1)
		return 1;
	else
		return 0;
}

void str_copy(char *dest, const char *src)
{
	int len, i;
	len = str_length(src);
	for(i = 0; i <= len; dest[i] = src[i], i++)
		{}
}

void number_to_str(int number, char *str)
{
	int i, j;
	char tmp_str[max_number_length] = { 0 };
	char tmp;
	i = 0;
	j = 0;
	if(number == 0) {
		*str = 0x30;
		*(str+1) = '\0';
		return;
	}
	while(number != 0) {
		tmp = number % 10;
		number = number/10;
		tmp = tmp + 0x30;
		*(tmp_str + i) = tmp;
		i++;
	}
	i--;
	while(j <= i) {
		*(str + j) = *(tmp_str + i -j);
		j++;
	}
	*(str + j) = '\0';
}
