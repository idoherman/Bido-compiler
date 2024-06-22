#include "MyString.h"



int str_length(char* str)
{
    int counter = 0;
    while(*str) {
        counter++;
        str++;
    }
    return counter;
}

void str_copy(char* source, char* destination)
{
    while(*source) {
        *destination = *source;
        source++;
        destination++;
    }
    *destination = '\0';
}

int str_compare(const char* str, const char* str2)
{
    while(*str && *str2) {
        if (*str != * str2) {
            return 0;
        }
        str++;
        str2++;
    }
    return !(*str) && !(*str2);
}

int is_letter(char ch)
{
    return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z');
}

int is_digit(char ch)
{
    return ch >= '0' && ch <='9';
}

int check_variable(const char* str)
{
    if(!is_letter(*str)) {
        return 0;
    }
    while (*str) {
        if (!is_letter(*str) && *str != '_' && !is_digit(*str)) {
            return 0;
        }
        str++;
    }
    return 1;
}

int check_int_number(const char* str)
{
    while (*str) {
        if(!is_digit(*str)) {
            return 0;
        }
        str++;
    }
    return 1;
}


int check_char(const char* str)
{
    if(*str != '\'') {
        return 0;
    }
    str += 2;
    if (*str != '\'') {
        return 0;
    }
    return 1;
}

int check_string(const char* str)
{
    if (*str != '\"') {
        return 0;
    }
    str++;

    while(*str) {
        if (*str == '\"' && !(*(str + 1))) {
            return 1;
        }
        str++;
    }
    return 0;
}
