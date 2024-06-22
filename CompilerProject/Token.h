#include "MyString.h"
#define BIDO_TOKENS_AMOUNT 36
#define BLANK 32
#define MAX_TOKENS_IN_CODE 1000
#define MAX_TOKEN_LENGTH 20


typedef enum Token_Type {
    TOKEN_NONE_TYPE = -1,
    TOKEN_FUNCTION, // the save words are - 0-36
    TOKEN_LT, // '<'
    TOKEN_MAIN,
    TOKEN_GT, // '>'
    TOKEN_RETURNS,
    TOKEN_INT,      // 5   new -> the in of variable type
    TOKEN_GETS,
    TOKEN_LPAREN, // '('
    TOKEN_RPAREN, // ')'
    TOKEN_LBRACE, // '{'
    TOKEN_RBRACE, // '}'    -- 10
    TOKEN_CHAR,
    TOKEN_TEXT,
    TOKEN_BOOL,
    TOKEN_IS,
    TOKEN_TRUE,       // 15
    TOKEN_FALSE,
    TOKEN_IF,
    TOKEN_NOT,
    TOKEN_AND,
    TOKEN_OR,      // 20
    TOKEN_DOT, // '.'
    TOKEN_EQUAL, // '='
    TOKEN_NEQ, // '!='
    TOKEN_GTE, // '>='
    TOKEN_LTE, // '<='      -- 25
    TOKEN_PLUS, // '+'
    TOKEN_MINUS, // '-'
    TOKEN_MULT, // '*'
    TOKEN_DIV, // '/'
    TOKEN_MOD, // '%'      --30
    TOKEN_AND_OP, // '&'
    TOKEN_OR_OP, // '|'
    TOKEN_XOR_OP, // '^'
    TOKEN_NOT_UNARY_OP, // '!'
    TOKEN_RETURN_END,       // 35
    TOKEN_INT_FUNC,       //  -> the int of return func
    TOKEN_VARIABLE, // not save word
    TOKEN_INT_NUMBER,
    TOKEN_CHAR_LITERAL,
    TOKEN_TEXT_LITERAL,     // 40
    TOKEN_PLUS_UNARY_OP,
    TOKEN_MINUS_UNARY_OP,
    TOKEN_DOLLAR   // $  // 43
} Token_Type;



typedef struct Token {
    Token_Type type;
    char value[MAX_TOKEN_LENGTH];
    int line;
    int token_in_line;
} Token;

Token* init_token();
Token* init_code_tokens();
Token* make_token_from_str(char* str, int typ, int line, int token_in_line);
Token* duplicate_token(Token* token, int line, int tok_in_line);
void print_code_tokens(Token* code_tokens, int count_tokens);


