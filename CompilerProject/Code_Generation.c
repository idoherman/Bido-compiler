#include "Code_Generation.h"

static int next = 0;
static int next_block = 0;
static int help_str = 0;
char data_segment[MAX_DATA_SEGMENT_LEN] = {};
char stack_segment[MAX_STACK_SEGMENT_LEN] = {};
char code_segment[MAX_CODE_SEGMENT_LEN] = {};
char* not_null = "Not NULL";

void add_variable_to_data_segment(char* line)
{
    static int last_index = 0;
    while (*line) {
        data_segment[last_index] = *line;
        last_index++;
        line++;
    }
    data_segment[last_index] = '\n';
    last_index++;
    data_segment[last_index] = '\0'; // for last definition.
}

void init_data_segment()
{
    add_variable_to_data_segment("DATA SEGMENT");
}

void end_data_segment()
{
    add_variable_to_data_segment("DATA ENDS \n");
}

void add_variable_to_stack_segment(char* line)
{
    static int last_index = 0;
    while (*line) {
        stack_segment[last_index] = *line;
        last_index++;
        line++;
    }
    stack_segment[last_index] = '\n';
    last_index++;
    stack_segment[last_index] = '\0'; // for last definition.
}

void init_stack_segment()
{
    add_variable_to_stack_segment("SSEG SEGMENT STACK   ; Stack definition.");
    add_variable_to_stack_segment("DW 100H DUP(?)");
    add_variable_to_stack_segment("SSEG ENDS \n");
}

void add_variable_to_code_segment(char* line)
{
    static int last_index = 0;
    while (*line) {
        code_segment[last_index] = *line;
        last_index++;
        line++;
    }
    code_segment[last_index] = '\n';
    last_index++;
    code_segment[last_index] = '\0'; // for last definition.
}

char* add_line_to_code_segment_with_realloc(char* line)
{
    add_variable_to_code_segment(line);
    free(line);
    return (char*) malloc((MAX_TOKEN_LENGTH * 2 + MAX_LAST_DEFINITION_LEN) * sizeof(char));
}


void init_code_segment()
{
    add_variable_to_code_segment("CODE SEGMENT");
    add_variable_to_code_segment("ASSUME CS:CODE, DS:DATA, SS:SSEG");
    add_variable_to_code_segment("START: MOV AX, DATA");
    add_variable_to_code_segment("\tMOV DS, AX");
    add_variable_to_code_segment("\tMOV ES, AX \n");
}

void end_code_segment()
{
    add_variable_to_code_segment("\nMOV AH, 4CH       ; End of code.");
    add_variable_to_code_segment("INT 21H");

    add_variable_to_code_segment("CODE ENDS");
    add_variable_to_code_segment("END START \n");
}

char* push_reg(char* reg_name, char** line)
{
    sprintf(*line, "\tpush %s", reg_name);
    add_variable_to_code_segment(*line);
    free(*line);
    return not_null;
}

void pop_to_two_registers(char* name1, char* name2, char** line)
{
    sprintf(*line, "\tpop %s", name2);
    add_variable_to_code_segment(*line);
    sprintf(*line, "\tpop %s", name1);
    add_variable_to_code_segment(*line);
}

void pop_to_two_registers_opposite(char* name1, char* name2, char** line)
{
    sprintf(*line, "\tpop %s", name1);
    add_variable_to_code_segment(*line);
    sprintf(*line, "\tpop %s", name2);
    add_variable_to_code_segment(*line);
}

char* cmp_and_push_bool(char* reg1, char* reg2, char* jump_type, char** line)
{
    sprintf(*line, "\tcmp %s, %s", reg1, reg2);
    add_variable_to_code_segment(*line);
    sprintf(*line, "\t%s next%d", jump_type, next);
    add_variable_to_code_segment(*line);
    sprintf(*line, "\tmov %s, 0", reg1);
    add_variable_to_code_segment(*line);
    sprintf(*line, "\tjmp next%d", next + 1);
    add_variable_to_code_segment(*line);
    sprintf(*line, "next%d: mov %s, 1", next++, reg1);
    add_variable_to_code_segment(*line);
    sprintf(*line, "next%d: push %s", next++, reg1);
    add_variable_to_code_segment(*line);
    free(*line);
    return not_null;
}

char* check_true_or_true(Register reg1, Register reg2, char** line)
{
    sprintf(*line, "\tcmp %s, %s", reg1.name, "0");
    add_variable_to_code_segment(*line);
    sprintf(*line, "\tjne next%d", next);
    add_variable_to_code_segment(*line);
    sprintf(*line, "\tcmp %s, %s", reg2.name, "0");
    add_variable_to_code_segment(*line);
    sprintf(*line, "\tjne next%d", next);
    add_variable_to_code_segment(*line);
    sprintf(*line, "\tmov %s, %d", reg1.name, 0);
    add_variable_to_code_segment(*line);
    sprintf(*line, "\tjmp next%d ", next + 1);
    add_variable_to_code_segment(*line);
    sprintf(*line, "next%d: mov %s, %d", next++, reg1.name, 1);
    add_variable_to_code_segment(*line);
    sprintf(*line, "next%d: push %s", next++, reg1.name);
    add_variable_to_code_segment(*line);
    free(*line);
    return not_null;
}

void change_quotes_to_single_quote(char* expr)
{
    int len = str_length(expr);
    *expr = '\'';
    *(expr + len - 1) = '\'';
}

void define_known_str(char* expr, char* reg_name, char** line)
{
    int dollars_left = MAX_TOKEN_LENGTH + 1 - (str_length(expr) - 2);
    change_quotes_to_single_quote(expr);
    sprintf(*line, "str_for_help%d db %s, %d dup ('$')", help_str, expr, dollars_left);
    add_variable_to_data_segment(*line);
    sprintf(*line, "\tlea %s, str_for_help%d", reg_name, help_str++);
    add_variable_to_code_segment(*line);
}

char* cmp_equal_str_asm(char* reg_name, char** line)
{
    sprintf(*line, "\tmov cx, %d", MAX_TOKEN_LENGTH);
    add_variable_to_code_segment(*line);
    sprintf(*line, "\tcld   ; df = 0."); // df = 0.
    add_variable_to_code_segment(*line);
    sprintf(*line, "\trepe cmpsb");
    add_variable_to_code_segment(*line);
    sprintf(*line, "\tjne next%d", next);
    add_variable_to_code_segment(*line);
    sprintf(*line, "\tmov %s, %d", reg_name, 1);
    add_variable_to_code_segment(*line);
    sprintf(*line, "\tjmp next%d", next + 1);
    add_variable_to_code_segment(*line);
    sprintf(*line, "next%d:mov %s, %d", next++, reg_name, 0);
    add_variable_to_code_segment(*line);
    sprintf(*line, "next%d: push %s", next++, reg_name);
    add_variable_to_code_segment(*line);
    return not_null;
}

char* cmp_not_equal_str_asm(char* reg_name, char** line)
{
    sprintf(*line, "\tmov cx, %d", MAX_TOKEN_LENGTH);
    add_variable_to_code_segment(*line);
    sprintf(*line, "\tcld   ; df = 0."); // df = 0.
    add_variable_to_code_segment(*line);
    sprintf(*line, "\trepe cmpsb");
    add_variable_to_code_segment(*line);
    sprintf(*line, "\tjne next%d", next);
    add_variable_to_code_segment(*line);
    sprintf(*line, "\tmov %s, %d", reg_name, 0);
    add_variable_to_code_segment(*line);
    sprintf(*line, "\tjmp next%d", next + 1);
    add_variable_to_code_segment(*line);
    sprintf(*line, "next%d:mov %s, %d", next++, reg_name, 1);
    add_variable_to_code_segment(*line);
    sprintf(*line, "next%d: push %s", next++, reg_name);
    add_variable_to_code_segment(*line);
    return not_null;
}


void copy_str_in_asm(char* dest, char** line)
{
    sprintf(*line, "\tlea di, %s", dest);
    add_variable_to_code_segment(*line);
    sprintf(*line, "\tmov cx, %d", MAX_TOKEN_LENGTH);
    add_variable_to_code_segment(*line);
    sprintf(*line, "\tcld   ; df = 0."); // df = 0.
    add_variable_to_code_segment(*line);
    sprintf(*line, "\trep movsb");
    add_variable_to_code_segment(*line);
}

char* expr12(SymbolTable* symbol_table, Register* registers, Parse_Tree* command, Error* errors)
{
    char* expr11 = calculate_expr(symbol_table, registers, command->sons[0], errors);
    if (expr11 == NULL) {
        return NULL;
    }
    if (command->num_of_sons == 3) {
        if (calculate_expr(symbol_table, registers, command->sons[2], errors) == NULL) {
            return NULL;
        }
        char* line = (char*) malloc((MAX_TOKEN_LENGTH * 2 + MAX_LAST_DEFINITION_LEN) * sizeof(char));
        Parse_Tree* son0 = command->sons[0];
        Parse_Tree* son1 = command->sons[1];
        Parse_Tree* son2 = command->sons[2];

        if (!check_if_both_int_or_bool(son0->data_type, son2->data_type)) {
            free(line);
            return NULL; // push 1 or 0
        }

        Register reg1 = get_reg(registers);
        Register reg2 = get_reg(registers);
        pop_to_two_registers(reg1.name, reg2.name, &line);

        if (son1->token->type == TOKEN_OR) {
            return check_true_or_true(reg1, reg2, &line);
        }
        else {
            expected_equal_cmp_op_error(son1->token->line, son1->token->token_in_line, errors);
            free(line);
            return NULL;
        }
    }
    else if (command->num_of_sons == 1) {
        return expr11;
    }
    else {
        unexpected_num_of_sons_error(errors);
        return NULL;
    }
}

char* check_true_and_true(Register reg1, Register reg2, char** line)
{
    sprintf(*line, "\tcmp %s, %s", reg1.name, "0");
    add_variable_to_code_segment(*line);
    sprintf(*line, "\tje next%d", next);
    add_variable_to_code_segment(*line);
    sprintf(*line, "\tcmp %s, %s", reg2.name, "0");
    add_variable_to_code_segment(*line);
    sprintf(*line, "\tje next%d", next);
    add_variable_to_code_segment(*line);
    sprintf(*line, "\tmov %s, %d", reg1.name, 1);
    add_variable_to_code_segment(*line);
    sprintf(*line, "jmp next%d ", next + 1);
    add_variable_to_code_segment(*line);
    sprintf(*line, "next%d: mov %s, %d", next++, reg1.name, 0);
    add_variable_to_code_segment(*line);
    sprintf(*line, "next%d: push %s", next++, reg1.name);
    add_variable_to_code_segment(*line);
    free(*line);
    return not_null;
}

char* expr11(SymbolTable* symbol_table, Register* registers, Parse_Tree* command, Error* errors)
{
    char* expr10 = calculate_expr(symbol_table, registers, command->sons[0], errors);
    if (expr10 == NULL) {
        return NULL;
    }
    if (command->num_of_sons == 3) {
        if (calculate_expr(symbol_table, registers, command->sons[2], errors) == NULL) {
            return NULL;
        }
        char* line = (char*) malloc((MAX_TOKEN_LENGTH * 2 + MAX_LAST_DEFINITION_LEN) * sizeof(char));
        Parse_Tree* son0 = command->sons[0];
        Parse_Tree* son1 = command->sons[1];
        Parse_Tree* son2 = command->sons[2];

        if (!check_if_both_int_or_bool(son0->data_type, son2->data_type)) {
            free(line);
            return NULL;
        }

        Register reg1 = get_reg(registers);
        Register reg2 = get_reg(registers);
        pop_to_two_registers(reg1.name, reg2.name, &line);

        if (son1->token->type == TOKEN_AND) {
            return check_true_and_true(reg1, reg2, &line);
        }
        else {
            expected_equal_cmp_op_error(son1->token->line, son1->token->token_in_line, errors);
            free(line);
            return NULL;
        }
    }
    else if (command->num_of_sons == 1) {
        return expr10;
    }
    else {
        unexpected_num_of_sons_error(errors);
        return NULL;
    }
}

char* expr8_9_10(SymbolTable* symbol_table, Register* registers, Parse_Tree* command, Error* errors)
{
    char* expr = calculate_expr(symbol_table, registers, command->sons[0], errors);
    if (expr == NULL) {
        return NULL;
    }
    if (command->num_of_sons == 3) {
        if (calculate_expr(symbol_table, registers, command->sons[2], errors) == NULL) {
            return NULL;
        }
        char* line = (char*) malloc((MAX_TOKEN_LENGTH * 2 + MAX_LAST_DEFINITION_LEN) * sizeof(char));
        Parse_Tree* son0 = command->sons[0];
        Parse_Tree* son1 = command->sons[1];
        Parse_Tree* son2 = command->sons[2];

        if (!check_both_integer(son0, son2, errors)) {
            free(line);
            return NULL;
        }
        Register reg1 = get_reg(registers);
        Register reg2 = get_reg(registers);
        pop_to_two_registers(reg1.name, reg2.name, &line);
//        pop_to_two_registers_opposite(reg1.name, reg2.name, &line);

        if (son1->token->type == TOKEN_OR_OP && command->non_terminal_type == EXPR10) {
            sprintf(line, "\tor %s, %s", reg1.name, reg2.name); // '|'
            add_variable_to_code_segment(line);
            return push_reg(reg1.name, &line);
        }
        else if (son1->token->type == TOKEN_XOR_OP && command->non_terminal_type == EXPR9) {
            sprintf(line, "\txor %s, %s", reg1.name, reg2.name); // '^'
            add_variable_to_code_segment(line);
            return push_reg(reg1.name, &line);
        }
        else if (son1->token->type == TOKEN_AND_OP && command->non_terminal_type == EXPR8) {
            sprintf(line, "\txor %s, %s", reg1.name, reg2.name);
            add_variable_to_code_segment(line);
            return push_reg(reg1.name, &line);
        }
        else {
        type_mismatch_error(son1->token->line, son1->token->token_in_line, errors);
            free(line);
        return NULL;
        }
    }
    else if (command->num_of_sons == 1) {
        return expr;
    }
    else {
        unexpected_num_of_sons_error(errors);
        return NULL;
    }
}


char* expr7(SymbolTable* symbol_table, Register* registers, Parse_Tree* command, Error* errors)
{
    char* expr6 = calculate_expr(symbol_table, registers, command->sons[0], errors);
    if (expr6 == NULL) {
        return NULL;
    }
    if (command->num_of_sons == 3) {
        char* expr7 = calculate_expr(symbol_table, registers, command->sons[2], errors);
        if (expr7 == NULL) {
            return NULL;
        }
        char* line = (char*) malloc((MAX_TOKEN_LENGTH * 2 + MAX_LAST_DEFINITION_LEN) * sizeof(char));
        Parse_Tree* son0 = command->sons[0];
        Parse_Tree* son1 = command->sons[1];
        Parse_Tree* son2 = command->sons[2];

        if (son0->data_type == DATA_TEXT && son2->data_type == DATA_TEXT) {
            Register reg = get_reg(registers);
            if (str_compare("Not NULL", expr6)) {
                sprintf(line, "\tpop si");
                add_variable_to_code_segment(line);
            }
            else {
                define_known_str(expr6, "si", &line);
            }
            if (str_compare("Not NULL", expr7)) {
                sprintf(line, "\tpop di");
                add_variable_to_code_segment(line);
            }
            else {
                define_known_str(expr7, "di", &line);
            }
            if (son1->token->type == TOKEN_EQUAL) { // str1 = str2
                return cmp_equal_str_asm(reg.name, &line);
            }
            else if (son1->token->type == TOKEN_NEQ) {  // str1 != str2
                return cmp_not_equal_str_asm(reg.name, &line);
            }
        }

        Register reg1 = get_reg(registers);
        Register reg2 = get_reg(registers);
        pop_to_two_registers(reg1.name, reg2.name, &line);

        switch (son1->token->type) {
            case TOKEN_EQUAL: // reg1 = reg2
                return cmp_and_push_bool(reg1.name, reg2.name, "je", &line);

            case TOKEN_NEQ: // reg1 != reg2
                return cmp_and_push_bool(reg1.name, reg2.name, "jne", &line);

            default:
                expected_equal_cmp_op_error(son1->token->line, son1->token->token_in_line, errors);
                free(line);
                return NULL;
        }
    }
    else if (command->num_of_sons == 1) {
        return expr6;
    }
    else {
        unexpected_num_of_sons_error(errors);
        return NULL;
    }
}

char* expr6(SymbolTable* symbol_table, Register* registers, Parse_Tree* command, Error* errors)
{
    char* expr5 = calculate_expr(symbol_table, registers, command->sons[0], errors);
    if (expr5 == NULL) {
        return NULL;
    }
    if (command->num_of_sons == 3) {
        if (calculate_expr(symbol_table, registers, command->sons[2], errors) == NULL) {
            return NULL;
        }
        char* line = (char*) malloc((MAX_TOKEN_LENGTH * 2 + MAX_LAST_DEFINITION_LEN) * sizeof(char));
        Parse_Tree* son0 = command->sons[0];
        Parse_Tree* son1 = command->sons[1];
        Parse_Tree* son2 = command->sons[2];
        if ((son0->data_type != DATA_INT && son0->data_type != DATA_BOOL)
            || (son2->data_type != DATA_INT && son2->data_type != DATA_BOOL)) {
            unexpected_data_type_error(errors);
            free(line);
            return NULL;
        }

        Register reg1 = get_reg(registers);
        Register reg2 = get_reg(registers);
        pop_to_two_registers(reg1.name, reg2.name, &line);

        switch (son1->token->type) {
            case TOKEN_LT: // reg1 '<' reg2
                return cmp_and_push_bool(reg1.name, reg2.name, "jb", &line);

            case TOKEN_GT: // reg1 '>' reg2
                return cmp_and_push_bool(reg1.name, reg2.name, "ja", &line);

            case TOKEN_GTE: // reg1 '>=' reg2
                return cmp_and_push_bool(reg1.name, reg2.name, "jae", &line);

            case TOKEN_LTE: // reg1 '<=' reg2
                return cmp_and_push_bool(reg1.name, reg2.name, "jbe", &line);

            default:
                expected_cmp_op_error(son1->token->line, son1->token->token_in_line, errors);
                free(line);
                return NULL;
        }
    }
    else if (command->num_of_sons == 1) {
        return expr5;
    }
    else {
        unexpected_num_of_sons_error(errors);
        return NULL;
    }
}

char* expr5(SymbolTable* symbol_table, Register* registers, Parse_Tree* command, Error* errors)
{
    char* expr4 = calculate_expr(symbol_table, registers, command->sons[0], errors);
    if (command->num_of_sons == 1) {
        return expr4;
    }
    else {
        unexpected_num_of_sons_error(errors);
        return NULL;
    }
}

char* expr4(SymbolTable* symbol_table, Register* registers, Parse_Tree* command, Error* errors)
{
    char* expr3 = calculate_expr(symbol_table, registers, command->sons[0], errors);
    if (expr3 == NULL) {
        return NULL;
    }
    if (command->num_of_sons == 3) {
        if (calculate_expr(symbol_table, registers, command->sons[2], errors) == NULL) {
            return NULL;
        }
        char* line = (char*) malloc((MAX_TOKEN_LENGTH * 2 + MAX_LAST_DEFINITION_LEN) * sizeof(char));
        Parse_Tree* son0 = command->sons[0];
        Parse_Tree* son1 = command->sons[1];
        Parse_Tree* son2 = command->sons[2];
        if (son0->data_type != DATA_INT || son2->data_type != DATA_INT) {
            unexpected_data_type_error(errors);
            free(line);
            return NULL;
        }

        pop_to_two_registers(AX, BX, &line);
//        pop_to_two_registers_opposite(AX, BX, &line);
        switch (son1->token->type) {
            case TOKEN_PLUS:
                sprintf(line, "\tadd %s, %s", AX, BX);
                add_variable_to_code_segment(line);
                return push_reg(AX, &line);

            case TOKEN_MINUS:
                sprintf(line, "\tsub %s, %s", AX, BX);
                add_variable_to_code_segment(line);
                return push_reg(AX, &line);

            default:
                expected_add_op_error(son1->token->line, son1->token->token_in_line, errors);
                free(line);
                return NULL;
        }
    }
    else if (command->num_of_sons == 1) {
        return expr3;
    }
    else {
        unexpected_num_of_sons_error(errors);
        return NULL;
    }
}

char* expr3(SymbolTable* symbol_table, Register* registers, Parse_Tree* command, Error* errors)
{
    char* expr2 = calculate_expr(symbol_table, registers, command->sons[0], errors);
    if (expr2 == NULL) {
        return NULL;
    }
    if (command->num_of_sons == 3) {
        if (calculate_expr(symbol_table, registers, command->sons[2], errors) == NULL) {
            return NULL;
        }
        char* line = (char*) malloc((MAX_TOKEN_LENGTH * 2 + MAX_LAST_DEFINITION_LEN) * sizeof(char));
        Parse_Tree* son0 = command->sons[0];
        Parse_Tree* son1 = command->sons[1];
        Parse_Tree* son2 = command->sons[2];
        if (son0->data_type != DATA_INT || son2->data_type != DATA_INT) {
            unexpected_data_type_error(errors);
            free(line);
            return NULL;
        }

        pop_to_two_registers(AX, BX, &line);
//        pop_to_two_registers_opposite(AX, BX, &line);
        switch (son1->token->type) {
            case TOKEN_MULT:
                sprintf(line, "\timul bl");
                add_variable_to_code_segment(line);
                return push_reg(AX, &line);

            case TOKEN_DIV:
                sprintf(line, "\tidiv bl");
                add_variable_to_code_segment(line);
                sprintf(line, "\tand %s, 00FFH", AX);
                add_variable_to_code_segment(line);
                return push_reg(AX, &line);

            case TOKEN_MOD:
                sprintf(line, "\tidiv bl");
                add_variable_to_code_segment(line);
                sprintf(line, "\tand %s, 0FF00H", AX);
                add_variable_to_code_segment(line);
                return push_reg(AX, &line);

            default:
                expected_mult_op_error(son1->token->line, son1->token->token_in_line, errors);
                free(line);
                return NULL;
        }
    }
    else if (command->num_of_sons == 1) {
        return expr2;
    }
    else {
        unexpected_num_of_sons_error(errors);
        return NULL;
    }
}

char* expr2(SymbolTable* symbol_table, Register* registers, Parse_Tree* command, Error* errors)
{
    if (command->num_of_sons == 2) {
        Parse_Tree* son0 = command->sons[0];
        Parse_Tree* son1 = command->sons[1];
        if (calculate_expr(symbol_table, registers, son1, errors) == NULL) {
            return NULL;
        }
        Register reg = get_reg(registers);
        char* line = (char*) malloc((MAX_TOKEN_LENGTH * 2 + MAX_LAST_DEFINITION_LEN) * sizeof(char));
        sprintf(line, "\tpop %s", reg.name);
        add_variable_to_code_segment(line);

        if (son1->data_type == DATA_INT && son0->token->type == TOKEN_MINUS_UNARY_OP) {
            sprintf(line, "\txor %s, 0ffffH", reg.name);
            add_variable_to_code_segment(line);
            sprintf(line, "\tadd %s, 1", reg.name);
            add_variable_to_code_segment(line);
            return push_reg(reg.name, &line);
        }
        else if ((son1->data_type == DATA_INT || son1->data_type == DATA_BOOL)
                 && son0->token->type == TOKEN_NOT_UNARY_OP) {
            return cmp_and_push_bool(reg.name, "0", "jz", &line);
        }
        else {
            type_mismatch_error(son0->token->line, son0->token->token_in_line, errors);
            free(line);
            return NULL;
        }
    }
    else if (command->num_of_sons == 1) {
        return calculate_expr(symbol_table, registers, command->sons[0], errors);;
    }
    else {
        unexpected_num_of_sons_error(errors);
        return NULL;
    }
}

char* expr1(SymbolTable* symbol_table, Register* registers, Parse_Tree* command, Error* errors)
{
    if (command->num_of_sons == 3) {
        return calculate_expr(symbol_table, registers, command->sons[1], errors);
    }
    else if (command->num_of_sons == 1) {
        return calculate_expr(symbol_table, registers, command->sons[0], errors);
    }
    else {
        unexpected_num_of_sons_error(errors);
        return NULL;
    }
}

char* mov_and_push_val(Register* registers, char* val, char** line)
{
    Register reg = get_reg(registers);
    sprintf(*line, "\tmov %s, %s", reg.name, val);
    add_variable_to_code_segment(*line);
    sprintf(*line, "\tpush %s", reg.name);
    add_variable_to_code_segment(*line);
    free(*line);
    return not_null;
}

char* const_rules(Parse_Tree* command, Register* registers, Error* errors)
{
    char* expr = (char*) malloc((MAX_TOKEN_LENGTH + 3) * sizeof(char));
    char* line = (char*) malloc((MAX_TOKEN_LENGTH * 2 + MAX_LAST_DEFINITION_LEN) * sizeof(char));
    Parse_Tree* son0 = command->sons[0];
    switch (son0->token->type) {
        case TOKEN_VARIABLE:
            sprintf(expr, "[%s]", son0->token->value);
            switch (son0->data_type) {
                case DATA_INT:
                case DATA_BOOL:
                case DATA_CHAR:
                    return mov_and_push_val(registers, expr, &line);

                case DATA_TEXT:
                    sprintf(line, "\tlea si, %s", son0->token->value);
                    add_variable_to_code_segment(line);
                    return push_reg("si", &line);

                default:
                    unexpected_data_type_error(errors);
                    free(line);
                    return NULL;
            }
        case TOKEN_INT_NUMBER:
        case TOKEN_CHAR_LITERAL:
            sprintf(expr, "%s", son0->token->value);
            return mov_and_push_val(registers, expr, &line);

        case TOKEN_TRUE:
            sprintf(expr, "%d", 1);
            return mov_and_push_val(registers, expr, &line);

        case TOKEN_FALSE:
            sprintf(expr, "%d", 0);
            return mov_and_push_val(registers, expr, &line);

        case TOKEN_TEXT_LITERAL:
            free(line);
            return son0->token->value;

        default:
            unexpected_token_type_error(son0->token->line, errors);
            free(line);
            return NULL;
    }
}


char* calculate_expr(SymbolTable* symbol_table, Register* registers, Parse_Tree* command, Error* errors)
{
    switch (command->non_terminal_type) {

        case EXPR: // "expr"
            return calculate_expr(symbol_table, registers, command->sons[0], errors);

        case EXPR12: // "expr12"
            return expr12(symbol_table, registers, command, errors);

        case EXPR11: // "expr11"
            return expr11(symbol_table, registers, command, errors);

        case EXPR10: // "expr10"
        case EXPR9: // "expr9"
        case EXPR8: // "expr8"
            return expr8_9_10(symbol_table, registers, command, errors);

        case EXPR7: // "expr7"
            return expr7(symbol_table, registers, command, errors);

        case EXPR6: // "expr6"
            return expr6(symbol_table, registers, command, errors);

        case EXPR5: // "expr5"
            return expr5(symbol_table, registers, command, errors);

        case EXPR4: // "expr4"
            return expr4(symbol_table, registers, command, errors);

        case EXPR3: // "expr3"
            return expr3(symbol_table, registers, command, errors);

        case EXPR2: // "expr2"
            return expr2(symbol_table, registers, command, errors);

        case EXPR1: // "expr1"
            return expr1(symbol_table, registers, command, errors);

        case CONST: // "const"
            return const_rules(command, registers, errors);

        default:
            unexpected_non_terminal_type_error(errors);
            return NULL;
    }
}

int block_rules(SymbolTable* symbol_table, Register* registers,
                Parse_Tree* command, Error* errors)
{
    int check1, check2;
    if (command->num_of_sons == 3) {
        check1 = generate_code_from_statement(symbol_table, registers,
                                              command->sons[0], errors);
        check2 = generate_code_from_statement(symbol_table, registers,
                                              command->sons[2], errors);
        return check1 && check2;
    }
    else if (command->num_of_sons == 2) {
        check1 = generate_code_from_statement(symbol_table, registers,
                                              command->sons[0], errors);
        check2 = generate_code_from_statement(symbol_table, registers,
                                              command->sons[1], errors);
        return check1 && check2;
    }

    else if (command->num_of_sons == 0) {
        return 1;
    }
    else {
        unexpected_num_of_sons_error(errors);
        return 0;
    }
}

// declare_stmt -> VARIABLE_TYPE < VARIABLE_NAME >
int declare_stmt_without_expr(Parse_Tree* command, Error* errors)
{
    char* declare_line = (char*) malloc((MAX_TOKEN_LENGTH + MAX_LAST_DEFINITION_LEN) * sizeof(char));
    Parse_Tree* son0 = command->sons[0];
    Parse_Tree* son2 = command->sons[2];

    switch (son0->data_type) {
        case DATA_INT:
            sprintf(declare_line, "%s DW %d", son2->token->value, DEFAULT_INT_VAL);
            add_variable_to_data_segment(declare_line);
            free(declare_line); // Free the allocated memory
            return 1;
        case DATA_BOOL:
            sprintf(declare_line, "%s DW %d", son2->token->value, DEFAULT_BOOL_VAL);
            add_variable_to_data_segment(declare_line);
            free(declare_line); // Free the allocated memory
            return 1;
        case DATA_CHAR:
            sprintf(declare_line, "%s DW %s", son2->token->value, DEFAULT_CHAR_VAL); // %c for char value
            add_variable_to_data_segment(declare_line);
            free(declare_line); // Free the allocated memory
            return 1;
        case DATA_TEXT:
            sprintf(declare_line, "%s DB %s", son2->token->value, DEFAULT_TEXT_VAL);
            add_variable_to_data_segment(declare_line);
            free(declare_line); // Free the allocated memory
            return 1;
        default:
            unexpected_data_type_error(errors);
            free(declare_line); // Free the allocated memory
            return 0;
    }
}


// VARIABLE_TYPE < VARIABLE_NAME > is expr
int declare_stmt_with_expr(SymbolTable* symbol_table, Register* registers,
                           Parse_Tree* command, Error* errors)
{
    declare_stmt_without_expr(command, errors);
    Parse_Tree* son2 = command->sons[2];
    Parse_Tree* son5 = command->sons[5];
    char* line = (char*) malloc((MAX_TOKEN_LENGTH * 2 + MAX_LAST_DEFINITION_LEN) * sizeof(char));
    Register reg = get_reg(registers);

    if (son5->data_type != DATA_TEXT) {
        if (calculate_expr(symbol_table, registers, son5, errors) == NULL) {
            free(line);
            return 0;
        }
        sprintf(line, "\tpop %s", reg.name);
        add_variable_to_code_segment(line);
        sprintf(line, "\tmov [%s], %s", son2->token->value, reg.name);
        add_variable_to_code_segment(line);
    }
    else {
        char* expr = calculate_expr(symbol_table, registers, son5, errors);
        if (expr == NULL) {
            free(line);
            return 0;
        }
        if (str_compare(expr, "Not NULL")) {
            sprintf(line, "\tpop si");
            add_variable_to_code_segment(line);
        }
        else {
            define_known_str(expr, "si", &line);
        }
        copy_str_in_asm(son2->token->value, &line);
    }
    free(line);
    return 1;
}

// declare_stmt -> VARIABLE_TYPE < VARIABLE_NAME > is expr
int assignment_stmt(SymbolTable* symbol_table, Register* registers,
                    Parse_Tree* command, Error* errors)
{
    Parse_Tree* son0 = command->sons[0];
    Parse_Tree* son2 = command->sons[2];
    char* line = (char*) malloc((MAX_TOKEN_LENGTH * 2 + MAX_LAST_DEFINITION_LEN) * sizeof(char));
    Register reg = get_reg(registers);

    if (son2->data_type != DATA_TEXT) {
        if (calculate_expr(symbol_table, registers, son2, errors) == NULL) {
            free(line);
            return 0;
        }
        sprintf(line, "\tpop %s", reg.name);
        add_variable_to_code_segment(line);
        sprintf(line, "\tmov [%s], %s", son0->token->value, reg.name);
        add_variable_to_code_segment(line);
    }
    else {
        char* expr = calculate_expr(symbol_table, registers, son2, errors);
        if (expr == NULL) {
            free(line);
            return 0;
        }
        if (str_compare(expr, "Not NULL")) {
            sprintf(line, "\tpop si");
            add_variable_to_code_segment(line);
        }
        else {
//            change_quotes_to_single_quote(expr);
//            sprintf(line, "str_for_help%d db %s, '$'", help_str, expr);
//            add_variable_to_data_segment(line);
//            sprintf(line, "\tlea si, str_for_help%d", help_str++);
//            add_variable_to_code_segment(line);
            define_known_str(expr, "si", &line);
        }
        copy_str_in_asm(son0->token->value, &line);
    }
    free(line);
    return 1;
}

// if_stmt -> if ( expr ) { block }
int if_stmt(SymbolTable* symbol_table, Register* registers, Parse_Tree* command,
            int is_if_not, Error* errors)
{
    if (command->non_terminal_type != IF_STMT) {
        must_be_if_stmt_error(errors);
        return 0;
    }
    char* line = (char*) malloc((MAX_TOKEN_LENGTH * 2 + MAX_LAST_DEFINITION_LEN) * sizeof(char));
    if (calculate_expr(symbol_table, registers, command->sons[2], errors) == NULL) {
        free(line);
        return 0;
    }
    Register reg = get_reg(registers);
    sprintf(line, "\tpop %s", reg.name);
    add_variable_to_code_segment(line);
    sprintf(line, "\tcmp %s, %d", reg.name, 0);
    add_variable_to_code_segment(line);
    sprintf(line, "\tje next_block%d", next_block);
    add_variable_to_code_segment(line);
    int check = generate_code_from_statement(symbol_table, registers, command->sons[5], errors);
    // #TODO maybe check the check.
    if (is_if_not) {
        sprintf(line, "\tjmp next_block%d", next_block + 1);
        add_variable_to_code_segment(line);
    }
    sprintf(line, "next_block%d: ", next_block++);
    add_variable_to_code_segment(line);
    return check;
}

// if_not_stmt -> if_stmt if not { block }
int if_not_stmt(SymbolTable* symbol_table, Register* registers, Parse_Tree* command, Error* errors)
{

    int check_if = if_stmt(symbol_table, registers, command->sons[0], 1, errors);
    if (check_if) {
        char* line = (char*) malloc((MAX_TOKEN_LENGTH * 2 + MAX_LAST_DEFINITION_LEN) * sizeof(char));
//        sprintf(line, "next_block%d: ", next_block++);
//        add_variable_to_code_segment(line);
        int check_block = generate_code_from_statement(symbol_table,
                             registers, command->sons[4], errors);
        sprintf(line, "next_block%d: ", next_block++);
        add_variable_to_code_segment(line);
        free(line);
        return check_if && check_block; // #TODO check why is always true.
    }
    else {
        return check_if;
    }
}

int generate_code_from_statement(SymbolTable* symbol_table, Register* registers,
                                Parse_Tree* command, Error* errors)
{
    if (command->is_terminal == NON_TERMINAL) {
        switch (command->non_terminal_type) {
//            case PROG_PRIME:
//                return generate_code_from_statement(symbol_table, registers,
//                                    command->sons[0], errors);

            case PROG:
                return generate_code_from_statement(symbol_table, registers,
                                    command->sons[10], errors);
            case BLOCK: // "block"
                return block_rules(symbol_table, registers, command, errors);

            case STMT: // "stmt"
            case BLOCK_STMT: // "block_stmt"
                return generate_code_from_statement(symbol_table, registers,
                                    command->sons[0], errors);
            case DECLARE_STMT: // "declare_stmt"
                if (command->num_of_sons == 4) {
                    return declare_stmt_without_expr(command, errors);
                }
                else if (command->num_of_sons == 6) {
                    return declare_stmt_with_expr(symbol_table, registers, command, errors);
                }
                else {
                    printf("\n *******************************************");
                    printf("* don't need to get here ever never!!! *");
                    printf("*******************************************");
                    unexpected_num_of_sons_error(errors);
                    return 0;
                }

            case ASSIGNMENT_STMT: // "assignment_stmt"
                return assignment_stmt(symbol_table, registers, command, errors);

            case IF_STMT: // "if_stmt"
                return if_stmt(symbol_table, registers, command, 0, errors);

            case IF_NOT_STMT: // "if_not_stmt"
                return if_not_stmt(symbol_table, registers, command, errors);

            default:
                if (command->non_terminal_type >= 0 && command->non_terminal_type <=8) {
                    return 1;
                }
                unexpected_non_terminal_type_error(errors);
                return 0;
        }
    }
    return 1;
}

int define_return_value(Parse_Tree* ret_val, Error* errors)
{
    char* line = (char*) malloc((MAX_TOKEN_LENGTH * 2 + MAX_LAST_DEFINITION_LEN) * sizeof(char));
    sprintf(line, "ret_msg db 'The return value is: ', '$'  ; The return message.");
    add_variable_to_data_segment(line);
    sprintf(line, "\nReturn: mov ah, 09h    ; Prints the return message.");
    add_variable_to_code_segment(line);
    sprintf(line, "\tlea %s, ret_msg", DX);
    add_variable_to_code_segment(line);
    sprintf(line, "\tint 21h");
    add_variable_to_code_segment(line);
    if (ret_val->data_type != DATA_INT) {
        function_main_returns_int_error(errors);
        return 0;
    }
    if (ret_val->token->type == TOKEN_VARIABLE) {
        sprintf(line, "\tmov %s, [%s]", AX, ret_val->token->value);
        add_variable_to_code_segment(line);
    }
    else if (ret_val->token->type == TOKEN_INT_NUMBER) {
        sprintf(line, "\tmov %s, %s", AX, ret_val->token->value);
        add_variable_to_code_segment(line);
    }

    sprintf(line, "\tmov bl, %d", 10);
    add_variable_to_code_segment(line);
    sprintf(line, "\tmov %s, %d", CX, 0);
    add_variable_to_code_segment(line);
    sprintf(line, "\tcmp %s, %d", AX, 0);
    add_variable_to_code_segment(line);
    sprintf(line, "\tjns Stack_Num");
    add_variable_to_code_segment(line);
    sprintf(line, "\tneg %s", AX);
    add_variable_to_code_segment(line);
    sprintf(line, "\tpush %s", AX);
    add_variable_to_code_segment(line);
    sprintf(line, "\tmov dl, '-'    ;     Print the minus.");
    add_variable_to_code_segment(line);
    sprintf(line, "\tmov ah, %d", 2);
    add_variable_to_code_segment(line);
    sprintf(line, "\tint 21h");
    add_variable_to_code_segment(line);
    sprintf(line, "\tpop %s", AX);
    add_variable_to_code_segment(line);

    sprintf(line, "\nStack_Num:     ; Enter the number into stack in digits");
    add_variable_to_code_segment(line);
    sprintf(line, "\tdiv bl");
    add_variable_to_code_segment(line);
    sprintf(line, "\tadd ah, '0'    ; Make the digit as ascii digit.");
    add_variable_to_code_segment(line);
    sprintf(line, "\txor %s, %s", DX, DX);
    add_variable_to_code_segment(line);
    sprintf(line, "\tmov dl, ah");
    add_variable_to_code_segment(line);
    sprintf(line, "\tpush %s", DX);
    add_variable_to_code_segment(line);
    sprintf(line, "\tand %s, 00ffh", AX);
    add_variable_to_code_segment(line);
    sprintf(line, "\tinc %s", CX);
    add_variable_to_code_segment(line);
    sprintf(line, "\tcmp al, %d", 0);
    add_variable_to_code_segment(line);
    sprintf(line, "\tjne Stack_Num");
    add_variable_to_code_segment(line);

    sprintf(line, "\nPrint:  pop %s", DX);
    add_variable_to_code_segment(line);
    sprintf(line, "\tmov ah, %d", 2);
    add_variable_to_code_segment(line);
    sprintf(line, "\tint 21h");
    add_variable_to_code_segment(line);
    sprintf(line, "\tloop Print");
    add_variable_to_code_segment(line);

    return 1;
}

void write_to_file(const char* file_path, const char* code, char* mode, Error* errors)
{
    FILE* file = fopen(file_path, mode); // a -> append mode
    if (file != NULL) {
        fprintf(file, "%s\n", code);
        fclose(file);
    }
    else {
        cant_open_the_file_error(file_path, errors);
    }
}

int code_generation(SymbolTable* symbol_table, Register* registers, Parse_Tree* root,
                    char* assembly_file_path, Error* errors)
{
    init_data_segment();
    init_stack_segment();
    init_code_segment();
    int check_success = generate_code_from_statement(symbol_table, registers, root, errors);
    int check_return = define_return_value((root->sons[12])->sons[0], errors);

    if (check_success && check_return) {
        end_data_segment();
        write_to_file(assembly_file_path, data_segment, "w", errors);
        write_to_file(assembly_file_path, stack_segment, "a", errors);
        end_code_segment();
        write_to_file(assembly_file_path, code_segment, "a", errors);
        return 1;
    }
    else {
        code_generation_error(errors);
        return 0;
    }
}

