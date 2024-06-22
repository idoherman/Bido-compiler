#include "Lexer.h"


// if token exist return token else return NULL
Token* token_already_exist(HashMap* exist_tokens, char* str)
{
    Token* token = get(exist_tokens, str);
    return token;
}

Token* make_new_token(char* str, int line, int token_in_line, Error* errors)
{
    int typ = -100;
    if (str_length(str) > MAX_TOKEN_LENGTH - 1) {
        token_len_over_limit_error(str, line, token_in_line, errors);
        return NULL;
    }
    if (check_variable(str)) {
        typ = TOKEN_VARIABLE;
    }
    else if (check_int_number(str)) {
        typ = TOKEN_INT_NUMBER;
    }
    else if (check_char(str)) {
        typ = TOKEN_CHAR_LITERAL;
    }
    else if (check_string(str)) {
        typ = TOKEN_TEXT_LITERAL;
    }
    if (typ == -100) {
        token_has_no_type_error(str, line, token_in_line, errors);
        return NULL;
    }
    return make_token_from_str(str, typ, line, token_in_line);
}

int is_not_white_space(char ch)
{
    return ch != ' ' && ch != '\t' && ch != '\n' && ch != '\v';
}

Token* lexical_analyser(char* code, int* count_tokens, HashMap* exist_tokens, Error* errors)
{
    int length_of_token, line = 1, token_in_line = 1;
    Token* code_tokens = init_code_tokens();

    while (*code) {
        char* str = (char*) malloc((MAX_TOKEN_LENGTH + 1) * sizeof(char));
        length_of_token = 0;
        if (*code && is_not_white_space(*code)) {
            if (*code == '#') {
                while (*code && *code != '\n') {
                    code++;
                }
            }
            else {
                while (*code && is_not_white_space(*code)) {
                    if(length_of_token < MAX_TOKEN_LENGTH) {
                        str[length_of_token] = *code;
                    }
                    length_of_token++;
                    code++;
                }
                str[length_of_token++] = '\0';

                Token* token = token_already_exist(exist_tokens, str);

                if (!token) {
                    token = make_new_token(str, line, token_in_line, errors);
                }

                if (token) {
                    code_tokens[*count_tokens] =  *duplicate_token(token, line, token_in_line);
                    (*count_tokens)++;
                }

                token_in_line++;
            }
        }
        else {
            if (*code == '\n' || *code == '\v') {
                line++;
                token_in_line = 1;
            }
            free(str);
            code++;
        }
    }

    code_tokens = (Token*) realloc(code_tokens, *count_tokens * sizeof(Token));
    if (!code_tokens) {
        return NULL;
    }
    return code_tokens;
}

int change_first_int_func_type(Token* code_tokens, int count_tokens, Error* errors)
{
    if(count_tokens >= 6 && code_tokens[0].type == TOKEN_FUNCTION &&
       code_tokens[1].type == TOKEN_LT && code_tokens[2].type == TOKEN_MAIN &&
       code_tokens[3].type == TOKEN_GT && code_tokens[4].type == TOKEN_RETURNS &&
       code_tokens[5].type == TOKEN_INT) {
        code_tokens[5].type = TOKEN_INT_FUNC;
        // the change is because int func and int variable type are different for the syntax analysis
        return 1;
    }

    syntax_analysis_error_func(errors);
    return 0;
}
