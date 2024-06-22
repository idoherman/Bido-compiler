#include "Code_Generation_Base.h"

#define MAX_DATA_SEGMENT_LEN MAX_TOKENS_IN_CODE
#define MAX_STACK_SEGMENT_LEN 100
#define MAX_CODE_SEGMENT_LEN (MAX_TOKEN_LENGTH * MAX_TOKENS_IN_CODE * 10)
#define MAX_LAST_DEFINITION_LEN 20
#define DEFAULT_INT_VAL 0
#define DEFAULT_CHAR_VAL "'$'"
#define DEFAULT_TEXT_VAL "21 DUP ('$')"
#define DEFAULT_BOOL_VAL 0





char* calculate_expr(SymbolTable* symbol_table, Register* registers, Parse_Tree* command, Error* errors);



int generate_code_from_statement(SymbolTable* symbol_table , Register* registers,
                                 Parse_Tree* command, Error* errors);



void write_to_file(const char* file_path, const char* code, char* mode, Error* errors);
int code_generation(SymbolTable* symbol_table, Register* registers, Parse_Tree* root,
                    char* assembly_file_path, Error* errors);