#include <stdio.h>
#include <malloc.h>

int str_length(char* str);
void str_copy(char* source, char* destination);
int str_compare(const char* str, const char* str2);

int is_letter(char ch);
int is_digit(char ch);

int check_variable(const char* str);
int check_int_number(const char* str);
int check_char(const char* str);
int check_string(const char* str);
