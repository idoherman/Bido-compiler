#include <stdio.h>
#include "Error_Handler.h"


Error* init_errors_node()
{
    int i;
    Error* errors = (Error*) malloc(MAX_ERRORS * sizeof(Error));
    for (i = 0; i < MAX_ERRORS; i++) {
        errors[i].value = (char*) malloc(MAX_ERROR_LENGTH * sizeof(char));
        *(errors[i].value) = '\0';
        errors[i].type = -1;
    }
    return errors;
}

// file errors
void cant_open_the_file_error(const char* file_path, Error* errors)
{
    sprintf(errors[ERRORS_AMOUNT].value, "Open File Error - "
             "The file: \" %s \" can not be open.", file_path);
    errors[ERRORS_AMOUNT].type = FILE_ERROR;
    ERRORS_AMOUNT++;
}


// Lexical Errors:
void token_has_no_type_error(char* str, int line, int token_in_line, Error* errors)
{

    sprintf(errors[ERRORS_AMOUNT].value, "Lexical Error - "
         "The token has no type (illegal token)."
         " The token is in line: %d in token: %d (%s).", line, token_in_line, str);
    errors[ERRORS_AMOUNT].type = LEXICAL_ERROR;
    ERRORS_AMOUNT++;
}

void token_len_over_limit_error(char* str, int line, int token_in_line, Error* errors)
{
    sprintf(errors[ERRORS_AMOUNT].value, "Lexical Error - "
             "The toke length is over the limit, in line: %d in token: %d (%s).", line, token_in_line, str);
    errors[ERRORS_AMOUNT].type = LEXICAL_ERROR;
    ERRORS_AMOUNT++;
}

void syntax_analysis_error_func(Error* errors)
{
    sprintf(errors[ERRORS_AMOUNT].value, "Syntax Analysis Error - "
         "The first line should look different (like the definition of main-function).");
    errors[ERRORS_AMOUNT].type = STACK_ERROR;
    ERRORS_AMOUNT++;
}

void stack_full_error(Error* errors)
{
    sprintf(errors[ERRORS_AMOUNT].value, "Stack Full Error - "
         "the parser stack is full and you are trying to push another element into it.");
    errors[ERRORS_AMOUNT].type = STACK_ERROR;
    ERRORS_AMOUNT++;
}

void stack_empty_error(Error* errors)
{
    sprintf(errors[ERRORS_AMOUNT].value, "Stack Empty Error - "
         "the parser stack is empty and you are trying to pop another element from it.");
    errors[ERRORS_AMOUNT].type = STACK_ERROR;
    ERRORS_AMOUNT++;
}

void error_token_none_type(Token* token, Error* errors)
{
    sprintf(errors[ERRORS_AMOUNT].value, "Token None Type Error - "
         "The token: %s in line: %d is none type - need to care in lexical analysis"
         , token->value, token->line);
    errors[ERRORS_AMOUNT].type = LEXICAL_ERROR;
    ERRORS_AMOUNT++;
}

void error_unknown_token_type(Token* token, Error* errors)
{
    sprintf(errors[ERRORS_AMOUNT].value, "Unknown Token Type Error - "
         "The token: %s in line: %d is unknown type - need to care in lexical analysis",
         token->value, token->line);
    errors[ERRORS_AMOUNT].type = LEXICAL_ERROR;
    ERRORS_AMOUNT++;
}

void syntax_analysis_error_action_table(Token* token, Error* errors)
{
    sprintf(errors[ERRORS_AMOUNT].value, "Syntax Analysis Error - "
         "The token: %s in line: %d can't be in that place according to the action table "
         , token->value, token->line);
    errors[ERRORS_AMOUNT].type = SYNTAX_ERROR;
    ERRORS_AMOUNT++;
}

void error_unexpected_index_rule(Error* errors)
{
    sprintf(errors[ERRORS_AMOUNT].value, "Syntax Analysis Error - "
         "The index of the rule is unexpected (not in range -> 0-39).");
    errors[ERRORS_AMOUNT].type = SYNTAX_ERROR;
    ERRORS_AMOUNT++;
}

void syntax_analysis_error_unexpected_action_type(Error* errors)
{
    sprintf(errors[ERRORS_AMOUNT].value, "Syntax Analysis Error - "
        "Unexpected action type (not in range -> 0-3).");
    errors[ERRORS_AMOUNT].type = SYNTAX_ERROR;
    ERRORS_AMOUNT++;
}

void unexpected_non_terminal_type_error(Error* errors)
{
    sprintf(errors[ERRORS_AMOUNT].value, "Syntax Analysis Error - "
         "Unexpected non terminal type (not in range -> 0-22).");
    errors[ERRORS_AMOUNT].type = SYNTAX_ERROR;
    ERRORS_AMOUNT++;
}

void unexpected_tree_is_terminal_value(Error* errors)
{
    sprintf(errors[ERRORS_AMOUNT].value, "Syntax Analysis Error - "
         "Unexpected is_terminal value (not in range -> 0-1).");
    errors[ERRORS_AMOUNT].type = SYNTAX_ERROR;
    ERRORS_AMOUNT++;
}

// Semantic Analysis Errors

void variable_name_never_declared(int line, Error* errors)
{
    sprintf(errors[ERRORS_AMOUNT].value, "Semantic Analysis Error - "
         "You can't assign a variable that never defined (in line: %d)", line);
    errors[ERRORS_AMOUNT].type = SEMANTIC_ERROR;
    ERRORS_AMOUNT++;
}

void unexpected_data_type_error(Error* errors)
{
    sprintf(errors[ERRORS_AMOUNT].value, "Semantic Analysis Error - "
         "Unexpected data type error (not in range 0 - 4).");
    errors[ERRORS_AMOUNT].type = SEMANTIC_ERROR;
    ERRORS_AMOUNT++;
}

void unexpected_token_type_error(int line, Error* errors)
{
    sprintf(errors[ERRORS_AMOUNT].value, "Semantic Analysis Error - "
        "Unexpected token type error in line: %d.", line);
    errors[ERRORS_AMOUNT].type = SEMANTIC_ERROR;
    ERRORS_AMOUNT++;
}

void must_be_an_integer_type_error(int line, int token_in_line, Error* errors)
{
    sprintf(errors[ERRORS_AMOUNT].value, "Semantic Analysis Error - The token must be an integer. "
         "The error is in line: %d, in token: %d from start of the line.", line, token_in_line);
    errors[ERRORS_AMOUNT].type = SEMANTIC_ERROR;
    ERRORS_AMOUNT++;
}

void variable_already_declared_error(int line, int token_in_line, Error* errors)
{
    sprintf(errors[ERRORS_AMOUNT].value, "Semantic Analysis Error - The token is already declared. "
         "The error is in line: %d, in token: %d from start of the line.", line, token_in_line);
    errors[ERRORS_AMOUNT].type = SEMANTIC_ERROR;
    ERRORS_AMOUNT++;
}

void type_mismatch_error(int line, int token_in_line, Error* errors)
{
    sprintf(errors[ERRORS_AMOUNT].value, "Semantic Analysis Error - "
         "The variables are not with the same type. "
         "The error is in line: %d, in token: %d from start of the line.", line, token_in_line);
    errors[ERRORS_AMOUNT].type = SEMANTIC_ERROR;
    ERRORS_AMOUNT++;
}

void expected_or_op_error(int line, int token_in_line, Error* errors)
{
    sprintf(errors[ERRORS_AMOUNT].value, "Semantic Analysis Error - "
         "Unexpected operation (the expected operation is: | (or operation)) "
         "The error is in line: %d, in token: %d from start of the line.", line, token_in_line);
    errors[ERRORS_AMOUNT].type = SEMANTIC_ERROR;
    ERRORS_AMOUNT++;
}

void expected_xor_op_error(int line, int token_in_line, Error* errors)
{
    sprintf(errors[ERRORS_AMOUNT].value, "Semantic Analysis Error - "
         "Unexpected operation (the expected operation is: ^ (xor operation)) "
         "The error is in line: %d, in token: %d from start of the line.", line, token_in_line);
    errors[ERRORS_AMOUNT].type = SEMANTIC_ERROR;
    ERRORS_AMOUNT++;
}

void expected_and_op_error(int line, int token_in_line, Error* errors)
{
    sprintf(errors[ERRORS_AMOUNT].value, "Semantic Analysis Error - "
         "Unexpected operation (the expected operation is: & (and operation)) "
         "The error is in line: %d, in token: %d from start of the line.", line, token_in_line);
    errors[ERRORS_AMOUNT].type = SEMANTIC_ERROR;
    ERRORS_AMOUNT++;
}

void expected_equal_cmp_op_error(int line, int token_in_line, Error* errors)
{
    sprintf(errors[ERRORS_AMOUNT].value, "Semantic Analysis Error - "
         "Unexpected equal compare operation (the expected operation is on of these: =, !=) "
         "The error is in line: %d, in token: %d from start of the line.", line, token_in_line);
    errors[ERRORS_AMOUNT].type = SEMANTIC_ERROR;
    ERRORS_AMOUNT++;
}

void variables_can_not_be_compare_error(int line, Error* errors)
{
    sprintf(errors[ERRORS_AMOUNT].value, "Semantic Analysis Error - "
        "The variables can not be compared. The error is in line: %d.", line);
    errors[ERRORS_AMOUNT].type = SEMANTIC_ERROR;
    ERRORS_AMOUNT++;
}

void expected_cmp_op_error(int line, int token_in_line, Error* errors)
{
    sprintf(errors[ERRORS_AMOUNT].value, "Semantic Analysis Error - "
        "Unexpected compare operation (the expected operation is on of these: >, <, >=, <=) "
        "The error is in line: %d, in token: %d from start of the line.", line, token_in_line);
    errors[ERRORS_AMOUNT].type = SEMANTIC_ERROR;
    ERRORS_AMOUNT++;
}

void expected_add_op_error(int line, int token_in_line, Error* errors)
{
    sprintf(errors[ERRORS_AMOUNT].value, "Semantic Analysis Error - "
         "Unexpected add operation (the expected operation is on of these: +, -) "
         "The error is in line: %d, in token: %d from start of the line.", line, token_in_line);
    errors[ERRORS_AMOUNT].type = SEMANTIC_ERROR;
    ERRORS_AMOUNT++;
}

void must_be_a_number_type_error(int line, int token_in_line, Error* errors)
{
    sprintf(errors[ERRORS_AMOUNT].value, "Semantic Analysis Error - "
        "The token in line: %d, in token: %d from start of the line must be a number"
        " (int). ", line, token_in_line);
    errors[ERRORS_AMOUNT].type = SEMANTIC_ERROR;
    ERRORS_AMOUNT++;
}

void expected_mult_op_error(int line, int token_in_line, Error* errors)
{
    sprintf(errors[ERRORS_AMOUNT].value, "Semantic Analysis Error - "
         "Unexpected mult operation (the expected operation is on of these: *, /, %%) "
         "The error is in line: %d, in token: %d from start of the line.", line, token_in_line);
    errors[ERRORS_AMOUNT].type = SEMANTIC_ERROR;
    ERRORS_AMOUNT++;
}

void expected_unary_op_error(int line ,int token_in_line, Error* errors)
{
    sprintf(errors[ERRORS_AMOUNT].value, "Semantic Analysis Error - "
         "Unexpected unary operation (the expected operation is on of these: +, -, !) "
         "The error is in line: %d, in token: %d from start of the line.", line, token_in_line);
    errors[ERRORS_AMOUNT].type = SEMANTIC_ERROR;
    ERRORS_AMOUNT++;
}

// Code Generation Errors
void unexpected_num_of_sons_error(Error* errors)
{
    sprintf(errors[ERRORS_AMOUNT].value, "Code Generation Error - "
             "Unexpected num of sons.");
    errors[ERRORS_AMOUNT].type = CODE_GENERATION_ERROR;
    ERRORS_AMOUNT++;
}

void must_be_if_stmt_error(Error* errors)
{
    sprintf(errors[ERRORS_AMOUNT].value, "Code Generation Error - "
                 "The non terminal type must be: IF_STMT");
    errors[ERRORS_AMOUNT].type = CODE_GENERATION_ERROR;
    ERRORS_AMOUNT++;
}

void function_main_returns_int_error(Error* errors)
{
    sprintf(errors[ERRORS_AMOUNT].value, "Code Generation Error - "
             "The main function must return int.");
    errors[ERRORS_AMOUNT].type = CODE_GENERATION_ERROR;
    ERRORS_AMOUNT++;
}

void code_generation_error(Error* errors)
{
    sprintf(errors[ERRORS_AMOUNT].value, "\nThere is Code Generation Error!!!");
    errors[ERRORS_AMOUNT].type = CODE_GENERATION_ERROR;
    ERRORS_AMOUNT++;
}

// Check if exists and print the errors:
void print_errors(Error* errors)
{
       int i;
       for(i = 0; i < ERRORS_AMOUNT; i++) {
           printf("%s \n", errors[i].value);
       }
}

int check_errors_exists(Error* errors)
{
    if(ERRORS_AMOUNT != 0) {
        print_errors(errors);
        return 1;   // there are a few errors.
    }
    return 0; // there are no errors.

}
