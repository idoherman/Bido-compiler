#include "HashMap.h"
#define MAX_ERRORS 1000
#define MAX_ERROR_LENGTH 150

static int ERRORS_AMOUNT = 0;

enum error_types {
    LEXICAL_ERROR,
    SYNTAX_ERROR,
    SEMANTIC_ERROR,
    CODE_GENERATION_ERROR,
    STACK_ERROR,
    FILE_ERROR
};

typedef struct Error {
    char* value;
    int type;
} Error;


Error* init_errors_node();

// File Errors:
void cant_open_the_file_error(const char* file_path, Error* errors);

// Lexical Analysis Errors:
void token_has_no_type_error(char* str, int line, int token_in_line, Error* errors);
void token_len_over_limit_error(char* str, int line, int token_in_line, Error* errors);

// Syntax Analysis Errors:
void syntax_analysis_error_func(Error* errors);
void stack_full_error(Error* errors);
void stack_empty_error(Error* errors);
void error_token_none_type(Token* token, Error* errors);
void error_unknown_token_type(Token* token, Error* errors);
void syntax_analysis_error_action_table(Token* token, Error* errors);
void error_unexpected_index_rule(Error* errors);
void syntax_analysis_error_unexpected_action_type(Error* errors);
void unexpected_non_terminal_type_error(Error* errors);
void unexpected_tree_is_terminal_value(Error* errors);

// Semantic Analysis Errors:
void variable_name_never_declared(int line, Error* errors);
void unexpected_data_type_error(Error* errors);
void unexpected_token_type_error(int line, Error* errors);
void must_be_an_integer_type_error(int line, int token_in_line, Error* errors);
void variable_already_declared_error(int line, int token_in_line, Error* errors);
void type_mismatch_error(int line, int token_in_line, Error* errors);
void expected_or_op_error(int line, int token_in_line, Error* errors);
void expected_xor_op_error(int line, int token_in_line, Error* errors);
void expected_and_op_error(int line, int token_in_line, Error* errors);
void expected_equal_cmp_op_error(int line, int token_in_line, Error* errors);
void variables_can_not_be_compare_error(int line, Error* errors);
void expected_cmp_op_error(int line, int token_in_line, Error* errors);
void expected_add_op_error(int line, int token_in_line, Error* errors);
void must_be_a_number_type_error(int line, int token_in_line, Error* errors);
void expected_mult_op_error(int line, int token_in_line, Error* errors);
void expected_unary_op_error(int line ,int token_in_line, Error* errors);

// Code Generation Errors:
void unexpected_num_of_sons_error(Error* errors);
void must_be_if_stmt_error(Error* errors);
void function_main_returns_int_error(Error* errors);
void code_generation_error(Error* errors);

// Check if exists and print the errors:
void print_errors(Error* errors);
int check_errors_exists(Error* errors);
