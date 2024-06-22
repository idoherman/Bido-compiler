#include "Token.h"


Token* init_token()
{
    Token* token = (Token*) malloc(sizeof(Token));
    token->type = TOKEN_NONE_TYPE;
    token->value[0] = '\0';
    token->line = -1;
    token->token_in_line = -1;
    return token;
}

Token* init_code_tokens()
{
    return (Token*) malloc(MAX_TOKENS_IN_CODE * sizeof(Token));
}

Token* make_token_from_str(char* str, int typ, int line, int token_in_line)
{
    Token* token = init_token();
    str_copy(str, token->value);
    token->type = typ;
    token->line = line;
    token->token_in_line = token_in_line;
    return token;
}

Token* duplicate_token(Token* token, int line, int tok_in_line)
{
    Token* new_token = (Token*) malloc(sizeof(Token));
    str_copy(token->value, new_token->value);
    new_token->type = token->type;
    new_token->line = line;
    new_token->token_in_line = tok_in_line;
    return new_token;
}

void print_code_tokens(Token* code_tokens, int count_tokens)
{
    int i;
    for (i = 0; i < count_tokens; i++) {
        printf("%s \t", code_tokens[i].value);
    }
}
