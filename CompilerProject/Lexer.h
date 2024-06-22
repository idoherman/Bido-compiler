#include "Error_Handler.h"

Token* token_already_exist(HashMap* exist_tokens, char* str);
Token* make_new_token(char* str, int line, int token_in_line, Error* errors);
int is_not_white_space(char ch);
Token* lexical_analyser(char* code, int* count_tokens, HashMap* exist_tokens, Error* errors);
int change_first_int_func_type(Token* code_tokens, int count_tokens, Error* errors);

