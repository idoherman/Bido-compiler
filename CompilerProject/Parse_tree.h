#include "Lexer.h"
#define NUM_OF_TERMINALS 30
#define NUM_OF_NON_TERMINALS 23

typedef enum Terminals {
    FUNCTION,         // "function"
    LESS_THAN,        // "<"
    MAIN,             // "main"
    GREATER_THAN,     // ">"
    RETURNS,          // "returns"
    INT_TYPE,         // "int"
    GETS,             // "gets"
    LEFT_PAREN,       // "("
    RIGHT_PAREN,      // ")"
    LEFT_BRACE,       // "{"
    RETURN,           // "return"
    DOT,              // "."
    RIGHT_BRACE,      // "}"
    VARIABLE_TYPE,    // "VARIABLE_TYPE"
    VARIABLE_NAME,    // "VARIABLE_NAME"
    IS,               // "is"
    IF,               // "if"
    NOT,              // "not"
    OR,               // "or"
    AND,              // "and"
    BITWISE_OR,       // "|"
    BITWISE_XOR,      // "^"
    BITWISE_AND,      // "&"
    EQUAL_CMP_OP,     // "EQUAL_CMP_OP"
    CMP_OP,           // "CMP_OP"
    ADD_OP,           // "ADD_OP"
    MULT_OP,          // "MULT_OP"
    UNARY_OP,         // "UNARY_OP"
    VARIABLE_VALUE,   // "VARIABLE_VALUE"
    DOLLAR            // "$"
} Terminals;

typedef enum Non_Terminals {
    PROG_PRIME,        // "prog'"
    PROG,              // "prog"
    BLOCK,             // "block"
    STMT,              // "stmt"
    BLOCK_STMT,        // "block_stmt"
    DECLARE_STMT,      // "declare_stmt"
    ASSIGNMENT_STMT,   // "assignment_stmt"
    IF_STMT,           // "if_stmt"
    IF_NOT_STMT,       // "if_not_stmt"
    EXPR,              // "expr"
    EXPR12,            // "expr12"
    EXPR11,            // "expr11"
    EXPR10,            // "expr10"
    EXPR9,             // "expr9"
    EXPR8,             // "expr8"
    EXPR7,             // "expr7"
    EXPR6,             // "expr6"
    EXPR5,             // "expr5"
    EXPR4,             // "expr4"
    EXPR3,             // "expr3"
    EXPR2,             // "expr2"
    EXPR1,             // "expr1"
    CONST              // "const"
} Non_Terminals;

typedef enum Is_Terminal {
    NON_TERMINAL,
    TERMINAL
} Is_Terminal;

typedef enum Data_Type {
    DATA_INT,
    DATA_BOOL,
    DATA_CHAR,
    DATA_TEXT
 } Data_Type;

typedef struct Parse_Tree {
    Token* token;   // if it's terminal so token, else NULL for non terminal
    Is_Terminal is_terminal; // terminal = 1, non = 0, -1 for init
    Non_Terminals non_terminal_type;  // if it's terminal so -1 else 0-22
    int state;
    int num_of_sons;
    struct Parse_Tree** sons;
    Data_Type data_type;
} Parse_Tree;

Parse_Tree* init_parse_tree();
Parse_Tree* make_parse_tree(Token* token, Is_Terminal is_terminal, int non_terminal_type, int state);
void make_father_of_sons(Parse_Tree* father, Parse_Tree** sons, int num_of_sons);
void change_data_type(Parse_Tree* tree, Data_Type data_type);
Non_Terminals get_non_terminal_type(int rule, Error* errors);
char* get_string_from_non_terminal_type(Parse_Tree* tree, Error* errors);
void print_parse_tree_helper(Parse_Tree* tree, int depth, Error* errors);
void print_parse_tree(Parse_Tree* tree, Error* errors);

