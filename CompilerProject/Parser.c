#include "Parser.h"

int RULES_ARR[RULES] = {
        1,  // Rule 1: prog' -> prog
        15, // Rule 2: prog -> function < main > returns int gets ( ) { block return const . }
        3,  // Rule 3: block -> stmt . block
        2,  // Rule 4: block -> block_stmt block
        0,  // Rule 5: block -> ''
        1,  // Rule 6: stmt -> declare_stmt
        1,  // Rule 7: stmt -> assignment_stmt
        1,  // Rule 8: block_stmt -> if_stmt
        1,  // Rule 9: block_stmt -> if_not_stmt
        4,  // Rule 10: declare_stmt -> VARIABLE_TYPE < VARIABLE_NAME >
        6,  // Rule 11: declare_stmt -> VARIABLE_TYPE < VARIABLE_NAME > is expr
        3,  // Rule 12: assignment_stmt -> VARIABLE_NAME is expr
        7,  // Rule 13: if_stmt -> if ( expr ) { block }
        6,  // Rule 14: if_not_stmt -> if_stmt if not { block }
        1,  // Rule 15: expr -> expr12
        3,  // Rule 16: expr12 -> expr11 or expr12
        1,  // Rule 17: expr12 -> expr11
        3,  // Rule 18: expr11 -> expr10 and expr11
        1,  // Rule 19: expr11 -> expr10
        3,  // Rule 20: expr10 -> expr9 | expr10
        1,  // Rule 21: expr10 -> expr9
        3,  // Rule 22: expr9 -> expr8 ^ expr9
        1,  // Rule 23: expr9 -> expr8
        3,  // Rule 24: expr8 -> expr7 & expr8
        1,  // Rule 25: expr8 -> expr7
        3,  // Rule 26: expr7 -> expr6 EQUAL_CMP_OP expr7
        1,  // Rule 27: expr7 -> expr6
        3,  // Rule 28: expr6 -> expr5 CMP_OP expr6
        1,  // Rule 29: expr6 -> expr5
        1,  // Rule 30: expr5 -> expr4
        3,  // Rule 31: expr4 -> expr3 ADD_OP expr4
        1,  // Rule 32: expr4 -> expr3
        3,  // Rule 33: expr3 -> expr2 MULT_OP expr3
        1,  // Rule 34: expr3 -> expr2
        2,  // Rule 35: expr2 -> UNARY_OP expr2
        1,  // Rule 36: expr2 -> expr1
        3,  // Rule 37: expr1 -> ( expr )
        1,  // Rule 38: expr1 -> const
        1,  // Rule 39: const -> VARIABLE_NAME
        1   // Rule 40: const -> VARIABLE_VALUE
};

int variable_type_to_data_type(Token* token , Error* errors)
{
    switch (token->type) {
        case TOKEN_INT:
            return DATA_INT;
        case TOKEN_BOOL:
            return DATA_BOOL;
        case TOKEN_CHAR:
            return DATA_CHAR;
        case TOKEN_TEXT:
            return DATA_TEXT;
        default:
            unexpected_token_type_error(token->line, errors);
            return -1;
    }
}

int variable_value_to_data_type(Token* token, Error* errors)
{
    switch (token->type) {
        case TOKEN_INT_NUMBER:
            return DATA_INT;
        case TOKEN_TRUE:
        case TOKEN_FALSE:
            return DATA_BOOL;
        case TOKEN_CHAR_LITERAL:
            return DATA_CHAR;
        case TOKEN_TEXT_LITERAL:
            return DATA_TEXT;
        default:
            unexpected_token_type_error(token->line, errors);
            return -1;
    }
}

int check_equal_cmp_op(const char* str)
{
    return (*str == '=' && *(str + 1) == '\0') || (*str == '!' && *(str + 1) == '=');
}

int check_cmp_op(const char* str)
{
    return (*str == '>' || *str == '<') && (*(str + 1) == '=' || *(str + 1) == '\0');
}

int check_add_op(char ch)
{
    return ch == '+' || ch == '-';
}

int check_mult_op(char ch)
{
    return ch == '*' || ch == '/' || ch == '%';
}

int check_unary_op(char ch)
{
    return check_add_op(ch) || ch == '!';
}

int check_both_integer(Parse_Tree* tree1, Parse_Tree* tree2, Error* errors)
{
    if (tree1->data_type != DATA_INT) {
        must_be_an_integer_type_error(tree1->token->line,
                                      tree1->token->token_in_line, errors);
        return 0;
    }
    if (tree1->data_type != tree2->data_type) {
        must_be_an_integer_type_error(tree2->token->line,
                                      tree2->token->token_in_line, errors);
        return 0;
    }
    return 1;
}

int check_if_both_int_or_bool(Data_Type type1, Data_Type type2)
{
    return (type1 == DATA_INT || type1 == DATA_BOOL) &&
            (type2 == DATA_INT || type2 == DATA_BOOL);
}


// Rule 10: declare_stmt -> VARIABLE_TYPE < VARIABLE_NAME >
int rule_10(SymbolTable* symbol_table, Parse_Tree* tree, Error* errors)
{
    Parse_Tree* tree_son0 = tree->sons[0];
    Parse_Tree* tree_son2 = tree->sons[2];
    if (find_symbol(symbol_table, tree_son2->token->value) != NULL) {
        variable_already_declared_error(tree_son0->token->line,
                                        tree_son0->token->token_in_line, errors);
        return 0;
    }

    tree_son0->data_type = variable_type_to_data_type(tree_son0->token, errors);
    tree_son2->data_type = tree_son0->data_type;
    if (tree_son2->data_type == -1) {
        unexpected_data_type_error(errors);
        return 0;
    }
    add_symbol(symbol_table, tree_son2->token->value,tree_son2->data_type);
    return 1;
}

// Rule 11: declare_stmt -> VARIABLE_TYPE < VARIABLE_NAME > is expr
int rule_11(SymbolTable* symbol_table, Parse_Tree* tree, Error* errors)
{
    Parse_Tree* tree_son0 = tree->sons[0];
    Parse_Tree* tree_son2 = tree->sons[2];
    Parse_Tree* tree_son5 = tree->sons[5];
    tree_son0->data_type = variable_type_to_data_type(tree_son0->token, errors);
    tree_son2->data_type = tree_son0->data_type;

    if (tree_son2->data_type == -1 || tree_son2->data_type != tree_son5->data_type) {
        type_mismatch_error(tree_son0->token->line,
                            6, errors);  // 6 is the expr place because it is non_terminal type
        return 0;
    }

    Symbol* cur_symbol = find_symbol(symbol_table, tree_son2->token->value);
    if (cur_symbol != NULL) {
        variable_already_declared_error(tree_son2->token->line,
                        tree_son2->token->token_in_line, errors);
        return 0;
    }
    add_symbol(symbol_table, tree_son2->token->value,tree_son2->data_type);
    return 1;
}

// Rule 12: assignment_stmt -> VARIABLE_NAME is expr
int rule_12(SymbolTable* symbol_table, Parse_Tree* tree, Error* errors)
{
    Parse_Tree* tree_son0 = tree->sons[0];
    Parse_Tree* tree_son2 = tree->sons[2];
    Symbol* cur_symbol = find_symbol(symbol_table, tree_son0->token->value);

    if (cur_symbol == NULL) {
        variable_name_never_declared(tree_son0->token->line, errors);
        return 0;
    }
    if (cur_symbol->type != tree_son2->data_type) {

        return 0;
    }
    tree->data_type = tree_son0->data_type;
    return 1;
}

// Rule 16: expr12 -> expr11 or expr12
int rule_16(Parse_Tree* tree, Error* errors)
{
    Parse_Tree* tree_son0 = tree->sons[0];
    Parse_Tree* tree_son1 = tree->sons[1];
    Parse_Tree* tree_son2 = tree->sons[2];
    tree->data_type = DATA_BOOL;
    if (tree_son0->data_type == DATA_TEXT || tree_son0->data_type == DATA_CHAR) {
        type_mismatch_error(tree_son1->token->line, 1, errors);
        return 0;
    }
    else if (tree_son2->data_type == DATA_TEXT || tree_son0->data_type == DATA_CHAR) {
        type_mismatch_error(tree_son1->token->line, 3, errors);
        return 0;
    }
    return 1;
}

// Rule 18: expr11 -> expr10 and expr11
int rule_18(Parse_Tree* tree, Error* errors)
{
    Parse_Tree* tree_son0 = tree->sons[0];
    Parse_Tree* tree_son1 = tree->sons[1];
    Parse_Tree* tree_son2 = tree->sons[2];
    tree->data_type = DATA_BOOL;
    if (tree_son0->data_type == DATA_TEXT || tree_son0->data_type == DATA_CHAR) {
        type_mismatch_error(tree_son1->token->line, 1, errors);
        return 0;
    }
    else if (tree_son2->data_type == DATA_TEXT || tree_son0->data_type == DATA_CHAR) {
        type_mismatch_error(tree_son1->token->line, 3, errors);
        return 0;
    }
    return 1;
}

// Rule 20: expr10 -> expr9 | expr10
int rule_20(Parse_Tree* tree, Error* errors)
{
    Parse_Tree* tree_son0 = tree->sons[0];
    Parse_Tree* tree_son1 = tree->sons[1];
    Parse_Tree* tree_son2 = tree->sons[2];
    tree->data_type = tree_son0->data_type;
    if (tree_son1->token->type != TOKEN_OR_OP) {
        expected_or_op_error(tree_son1->token->line, tree_son1->token->token_in_line, errors);
        return 0;
    }
    return check_both_integer(tree_son0, tree_son2, errors);
}

// Rule 22: expr9 -> expr8 ^ expr9
int rule_22(Parse_Tree* tree, Error* errors)
{
    Parse_Tree* tree_son0 = tree->sons[0];
    Parse_Tree* tree_son1 = tree->sons[1];
    Parse_Tree* tree_son2 = tree->sons[2];
    tree->data_type = tree_son0->data_type;
    if (tree_son1->token->type != TOKEN_XOR_OP) {
        expected_xor_op_error(tree_son1->token->line,
                              tree_son1->token->token_in_line, errors);
        return 0;
    }
    return check_both_integer(tree_son0, tree_son2, errors);
}

// Rule 24: expr8 -> expr7 & expr8
int rule_24(Parse_Tree* tree, Error* errors)
{
    Parse_Tree* tree_son0 = tree->sons[0];
    Parse_Tree* tree_son1 = tree->sons[1];
    Parse_Tree* tree_son2 = tree->sons[2];
    tree->data_type = tree_son0->data_type;
    if (tree_son1->token->type != TOKEN_AND_OP) {
        expected_and_op_error(tree_son1->token->line,
                              tree_son1->token->token_in_line, errors);
        return 0;
    }
    return check_both_integer(tree_son0, tree_son2, errors);
}

// Rule 26: expr7 -> expr6 EQUAL_CMP_OP expr7
int rule_26(Parse_Tree* tree, Error* errors)
{
    Parse_Tree* tree_son0 = tree->sons[0];
    Parse_Tree* tree_son1 = tree->sons[1];
    Parse_Tree* tree_son2 = tree->sons[2];
    tree->data_type = DATA_BOOL; // Resulting type
    if (!check_equal_cmp_op(tree_son1->token->value)) {
        expected_equal_cmp_op_error(tree_son1->token->line, tree_son1->token->token_in_line, errors);
        return 0;
    }
    if (tree_son0->data_type != tree_son2->data_type &&
            !check_if_both_int_or_bool(tree_son0->data_type, tree_son2->data_type)) {
        variables_can_not_be_compare_error(tree_son1->token->line, errors);
        return 0;
    }
    return 1;
}

// Rule 28: expr6 -> expr5 CMP_OP expr6
int rule_28(Parse_Tree* tree, Error* errors)
{
    Parse_Tree* tree_son0 = tree->sons[0];
    Parse_Tree* tree_son1 = tree->sons[1];
    Parse_Tree* tree_son2 = tree->sons[2];
    tree->data_type = DATA_BOOL; // Resulting type
    if (!check_cmp_op(tree_son1->token->value)) {
        expected_cmp_op_error(tree_son1->token->line, tree_son1->token->token_in_line, errors);
        return 0;
    }
    if (!check_if_both_int_or_bool(tree_son0->data_type, tree_son2->data_type)) {
        variables_can_not_be_compare_error(tree_son0->token->line, errors);
        return 0;
    }
    return 1;
}

// Rule 31: expr4 -> expr3 ADD_OP expr4
int rule_31(Parse_Tree* tree, Error* errors)
{
    Parse_Tree* tree_son0 = tree->sons[0];
    Parse_Tree* tree_son1 = tree->sons[1];
    Parse_Tree* tree_son2 = tree->sons[2];
    tree->data_type = tree_son0->data_type; // Resulting type
    if (!check_add_op(*(tree_son1->token->value))) {
        expected_add_op_error(tree_son1->token->line, tree_son1->token->token_in_line, errors);
        return 0;
    }

    if (tree_son0->data_type != DATA_INT) {
        must_be_a_number_type_error(tree_son0->token->line, tree_son0->token->token_in_line, errors);
        return 0;
    }
    if (tree_son0->data_type != tree_son2->data_type) {
        // 3 is the place for expr4 that is non teminal type (no token)
        type_mismatch_error(tree_son1->token->line,3, errors);
        return 0;
    }
    return 1;
}

// Rule 33: expr3 -> expr2 MULT_OP expr3
int rule_33(Parse_Tree* tree, Error* errors)
{
    Parse_Tree* tree_son0 = tree->sons[0];
    Parse_Tree* tree_son1 = tree->sons[1];
    Parse_Tree* tree_son2 = tree->sons[2];
    tree->data_type = tree_son0->data_type;
    if (!check_mult_op(*(tree_son1->token->value))) {
        expected_mult_op_error(tree_son1->token->line, tree_son1->token->token_in_line, errors);
        return 0;
    }

    return check_both_integer(tree_son0, tree_son2, errors);
}

// Rule 35: expr2 -> UNARY_OP expr2
int rule_35(Parse_Tree* tree, Error* errors)
{
    Parse_Tree* tree_son0 = tree->sons[0];
    Parse_Tree* tree_son1 = tree->sons[1];
    tree->data_type = tree_son1->data_type;
    if (!check_unary_op(*(tree_son0->token->value))) {
        expected_unary_op_error(tree_son0->token->line, tree_son0->token->token_in_line, errors);
        return 0;
    }
    if (tree_son1->data_type == DATA_INT ||
           (tree_son1->data_type == DATA_BOOL && tree_son1->token->type == TOKEN_NOT_UNARY_OP)) {

        return 1;
    }
    // 1 is the place for expr2 that has no token because it non terminal type
    type_mismatch_error(tree_son0->token->line,2, errors);
    return 0;

}


int get_son_rules(Parse_Tree* tree)
{
    Parse_Tree* tree_son0 = tree->sons[0];
    tree->data_type = tree_son0->data_type;
    return 1;
}

// Rule 37: expr1 -> ( expr )
int rule_37(Parse_Tree* tree)
{
    Parse_Tree* tree_son1 = tree->sons[1];
    tree->data_type = tree_son1->data_type;
    return 1;
}

// Rule 39: const -> VARIABLE_NAME
int rule_39(SymbolTable* symbol_table, Parse_Tree* tree, Error* errors)
{
    Parse_Tree* tree_son0 = tree->sons[0];
    Symbol* cur_symbol = find_symbol(symbol_table, tree_son0->token->value);
    if (cur_symbol == NULL) {
        variable_name_never_declared(tree_son0->token->line, errors);
        return 0;
    }
    tree_son0->data_type = cur_symbol->type;
    tree->data_type = tree_son0->data_type;

    return 1;
}

// Rule 40: const -> VARIABLE_VALUE
int rule_40(Parse_Tree* tree, Error* errors)
{
    Parse_Tree* tree_son0 = tree->sons[0];
    tree_son0->data_type = variable_value_to_data_type(tree_son0->token, errors);
    tree->data_type = tree_son0->data_type;
    if (tree->data_type == -1) {
        unexpected_data_type_error(errors);
        return 0; // the variable value has no type.
    }
    return 1;
}


int the_rest_rules(int rule, Error* errors)
{
    if (rule >= 0 && rule <= 39) {
        return 1;
    }
    error_unexpected_index_rule(errors);
    return 0;
}

int semantic_analysis(SymbolTable* symbol_table, Parse_Tree* tree, int rule_index, Error* errors)
{

    switch (rule_index) {

        case 9: // Rule 10: declare_stmt -> VARIABLE_TYPE < VARIABLE_NAME >
            return rule_10(symbol_table, tree, errors);

        case 10: // Rule 11: declare_stmt -> VARIABLE_TYPE < VARIABLE_NAME > is expr
            return rule_11(symbol_table, tree, errors);

        case 11: // Rule 12: assignment_stmt -> VARIABLE_NAME is expr
            return rule_12(symbol_table, tree, errors);

        case 15: // Rule 16: expr12 -> expr11 or expr12
            return rule_16(tree, errors);

        case 17: // Rule 18: expr11 -> expr10 and expr11
            return rule_18(tree, errors);

        case 19: // Rule 20: expr10 -> expr9 | expr10
            return rule_20(tree, errors);

        case 21: // Rule 22: expr9 -> expr8 ^ expr9
            return rule_22(tree, errors);

        case 23: // Rule 24: expr8 -> expr7 & expr8
            return rule_24(tree, errors);

        case 25: // Rule 26: expr7 -> expr6 EQUAL_CMP_OP expr7
            return rule_26(tree, errors);

        case 27: // Rule 28: expr6 -> expr5 CMP_OP expr6
            return rule_28(tree, errors);

        case 30: // Rule 31: expr4 -> expr3 ADD_OP expr4
            return rule_31(tree, errors);

        case 32: // Rule 33: expr3 -> expr2 MULT_OP expr3
            return rule_33(tree, errors);

        case 34: // Rule 35: expr2 -> UNARY_OP expr2
            return rule_35(tree, errors);

        case 14:
        case 16:
        case 18:
        case 20:
        case 22:
        case 24:
        case 26:
        case 28:
        case 29:
        case 31:
        case 33:
        case 35:
        case 37:
            return get_son_rules(tree);


        case 36:
            return rule_37(tree);

        case 38: // Rule 39: const -> VARIABLE_NAME
            return rule_39(symbol_table, tree, errors);

        case 39: // Rule 40: const -> VARIABLE_VALUE
            return rule_40(tree, errors);

        default:
            return the_rest_rules(rule_index, errors);
    }

}

void scope_in_and_scope_out(SymbolTable* table , Token* token)
{
    if (token->type == TOKEN_LBRACE) {
        enter_scope(table);
    }
    else if(token->type == TOKEN_RBRACE) {
        exit_scope(table);
    }
}

int reduce_action(Parse_Table* parse_table, SymbolTable* symbol_table,
                  Parse_Stack* parse_stack, Action** cur_action, Token* cur_token, Error* errors)
{
    int j, amount_to_pop;
    Parse_Tree* cur_parse_tree;
    Parse_Tree** cur_tree_sons;
    GoTo* cur_go_to = NULL;

    while ((*cur_action)->type == REDUCE_ACTION) {
        int rule = (*cur_action)->state;
        amount_to_pop = RULES_ARR[rule];
        cur_tree_sons = (Parse_Tree**) malloc(amount_to_pop * sizeof(Parse_Tree*));
        for(j = amount_to_pop - 1; j >= 0; j--) {
//        for(j = 0; j < amount_to_pop; j++) {
            cur_tree_sons[j] = pop_parse_stack(parse_stack, errors);
            if (cur_tree_sons[j] == NULL) {
                stack_empty_error(errors);
                return 0;
            }
        }

        int state_to_search = top_parse_stack(parse_stack, errors)->state;
        cur_go_to = get_goto(parse_table, state_to_search, rule, errors);
        Non_Terminals non_terminal_type = get_non_terminal_type(rule, errors);
        cur_parse_tree = make_parse_tree(NULL, NON_TERMINAL, non_terminal_type, cur_go_to->state);
        make_father_of_sons(cur_parse_tree, cur_tree_sons, amount_to_pop);
        if (!semantic_analysis(symbol_table, cur_parse_tree, rule, errors)) {
            return 0;
        }
        push_parse_stack(parse_stack, cur_parse_tree, errors);

        cur_parse_tree = top_parse_stack(parse_stack, errors);
        state_to_search = cur_parse_tree->state;
        *cur_action = get_action(parse_table , cur_token, state_to_search, parse_stack, errors);
        // #ToDo maybe to unite the three lines above
        // #ToDo with the three line below the for after the cur token.

    }
    return 1;
}

void shift_action(SymbolTable* symbol_table, Parse_Stack* parse_stack,
                 Action* cur_action, Token* cur_token, Error* errors)
{
    scope_in_and_scope_out(symbol_table, cur_token);
    Parse_Tree* cur_parse_tree = make_parse_tree    // the -1 in line 71 is for terminals.
            (cur_token, TERMINAL, -1 ,cur_action->state);
    push_parse_stack(parse_stack, cur_parse_tree, errors);
}

// This function changes the +|- that is math plus op to unary op.
void check_and_change_if_unary_op(Token_Type last_type, Token* cur_token)
{
    if (last_type != TOKEN_INT_NUMBER && last_type != TOKEN_RPAREN) {
        if (cur_token->type == TOKEN_PLUS) {
            cur_token->type = TOKEN_PLUS_UNARY_OP;
        }
        else if (cur_token->type == TOKEN_MINUS) {
            cur_token->type = TOKEN_MINUS_UNARY_OP;
        }
    }
}

Parse_Tree* syntax_analysis_parser_function(Token* code_tokens,
                SymbolTable* symbol_table, int tokens_amount, Error* errors)
{
    int i, state_to_search;
    Token* cur_token = NULL;
    Action* cur_action = NULL;
    Parse_Table* parse_table = build_the_actual_table();
    Parse_Tree* parse_tree = init_parse_tree();
    Parse_Stack* parse_stack = init_parse_stack();
    push_first_parse_stack(parse_stack, parse_tree, errors);

    for (i = 0; i < tokens_amount; i++) {
        cur_token = &(code_tokens[i]);
        if (i > 0) {
            check_and_change_if_unary_op(code_tokens[i - 1].type, cur_token);
        }
        state_to_search = top_parse_stack(parse_stack, errors)->state;
        cur_action = get_action(parse_table , cur_token, state_to_search, parse_stack, errors);

        if (!reduce_action(parse_table, symbol_table, parse_stack, &cur_action, cur_token, errors)) {
            return NULL;
        }

        if (cur_action->type == ERROR_ACTION) {
            syntax_analysis_error_action_table(cur_token, errors);
            return NULL;
        }
        else if (cur_action->type == SHIFT_ACTION) {
            shift_action(symbol_table, parse_stack, cur_action, cur_token, errors);
        }
        else if (cur_action->type == ACCEPT_ACTION) {
            return pop_parse_stack(parse_stack, errors);
        }
        else {
            syntax_analysis_error_unexpected_action_type(errors);
        }
    }
    return NULL; // -> didn't get to the accept action.
}

