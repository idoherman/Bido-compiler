#include "Symbol_Table.h"
#define RULES 40

int variable_type_to_data_type(Token* token , Error* errors);
int variable_value_to_data_type(Token* token, Error* errors);
int check_equal_cmp_op(const char* str);
int check_cmp_op(const char* str);
int check_add_op(char ch);
int check_mult_op(char ch);
int check_unary_op(char ch);
int check_both_integer(Parse_Tree* tree1, Parse_Tree* tree2, Error* errors);
int check_if_both_int_or_bool(Data_Type type1, Data_Type type2);

// Rules:
int rule_10(SymbolTable* symbol_table, Parse_Tree* tree, Error* errors);
int rule_11(SymbolTable* symbol_table, Parse_Tree* tree, Error* errors);
int rule_12(SymbolTable* symbol_table, Parse_Tree* tree, Error* errors);
int rule_16(Parse_Tree* tree, Error* errors);
int rule_18(Parse_Tree* tree, Error* errors);
int rule_20(Parse_Tree* tree, Error* errors);
int rule_22(Parse_Tree* tree, Error* errors);
int rule_24(Parse_Tree* tree, Error* errors);
int rule_26(Parse_Tree* tree, Error* errors);
int rule_28(Parse_Tree* tree, Error* errors);
int rule_31(Parse_Tree* tree, Error* errors);
int rule_33(Parse_Tree* tree, Error* errors);
int rule_35(Parse_Tree* tree, Error* errors);
int get_son_rules(Parse_Tree* tree);
int rule_37(Parse_Tree* tree);
int rule_39(SymbolTable* symbol_table, Parse_Tree* tree, Error* errors);
int rule_40(Parse_Tree* tree, Error* errors);
int the_rest_rules(int rule, Error* errors);

// Semantic Analysis Functions:
int semantic_analysis(SymbolTable* symbol_table, Parse_Tree* tree, int rule_index, Error* errors);
void scope_in_and_scope_out(SymbolTable* table , Token* token);

// Syntax Analysis Functions:
int reduce_action(Parse_Table* parse_table, SymbolTable* symbol_table, Parse_Stack* parse_stack,
                  Action** cur_action, Token* cur_token, Error* errors);
void shift_action(SymbolTable* symbol_table, Parse_Stack* parse_stack,
                  Action* cur_action, Token* cur_token, Error* errors);
void check_and_change_if_unary_op(Token_Type last_type, Token* cur_token);
//Parse_Tree* syntax_analysis_parser_function(Token* code_tokens, int tokens_amount, Error* errors);
Parse_Tree* syntax_analysis_parser_function(Token* code_tokens,
            SymbolTable* symbol_table, int tokens_amount, Error* errors);
