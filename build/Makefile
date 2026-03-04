CC = gcc
CFLAGS = -Wall -g -ansi -pedantic

record: ../source/record.c ../include/record.h
	$(CC) $(CFLAGS) -c $< -o $@
my_string: ../source/my_string.c ../include/my_string.h
	$(CC) $(CFLAGS) -c $< -o $@
file_operations: ../source/file_operations.c ../include/file_operations.h
	$(CC) $(CFLAGS) -c $< -o $@
utils: ../source/utils.c ../include/utils.h
	$(CC) $(CFLAGS) -c $< -o $@
llrbt_for_file: ../source/llrbt_for_file.c ../include/llrbt_for_file.h
	$(CC) $(CFLAGS) -c $< -o $@
prog: ../source/main.c file_operations record my_string utils llrbt_for_file
	$(CC) $(CFLAGS) $^ -o prog

clear_obj:
	rm file_operations record my_string llrbt_for_file utils
run:
	./prog
