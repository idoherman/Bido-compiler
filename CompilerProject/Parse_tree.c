#include "Parse_tree.h"

Parse_Tree* init_parse_tree()
{
    Parse_Tree* parse_tree = (Parse_Tree*) malloc(sizeof(Parse_Tree));
    parse_tree->token = NULL;
    parse_tree->is_terminal = -1; // no one of the options - terminal/non terminal.
    parse_tree->non_terminal_type = -1;
    parse_tree->state = -1; // no state exist.
    parse_tree->num_of_sons = 0;
    parse_tree->sons = NULL;
    parse_tree->data_type = -1; // no data type exist.
    return parse_tree;
}

Parse_Tree* make_parse_tree(Token* token, Is_Terminal is_terminal, int non_terminal_type, int state)
{
    Parse_Tree* parse_tree = init_parse_tree();
    parse_tree->token = token;
    parse_tree->is_terminal = is_terminal;
    parse_tree->non_terminal_type = non_terminal_type;
    parse_tree->state = state;
    return parse_tree;
}

void make_father_of_sons(Parse_Tree* father, Parse_Tree** sons, int num_of_sons)
{
    father->sons = sons;
    father->num_of_sons = num_of_sons;
}

void change_data_type(Parse_Tree* tree, Data_Type data_type)
{
    tree->data_type = data_type;
}

Non_Terminals get_non_terminal_type(int rule, Error* errors)
{
    switch (rule) {
        case 0:
            return PROG_PRIME;
        case 1:
            return PROG;
        case 2:
        case 3:
        case 4:
            return BLOCK;
        case 5:
        case 6:
            return STMT;
        case 7:
        case 8:
            return BLOCK_STMT;
        case 9:
        case 10:
            return DECLARE_STMT;
        case 11:
            return ASSIGNMENT_STMT;
        case 12:
            return IF_STMT;
        case 13:
            return IF_NOT_STMT;
        case 14:
            return EXPR;
        case 15:
        case 16:
            return EXPR12;
        case 17:
        case 18:
            return EXPR11;
        case 19:
        case 20:
            return EXPR10;
        case 21:
        case 22:
            return EXPR9;
        case 23:
        case 24:
            return EXPR8;
        case 25:
        case 26:
            return EXPR7;
        case 27:
        case 28:
            return EXPR6;
        case 29:
            return EXPR5;
        case 30:
        case 31:
            return EXPR4;
        case 32:
        case 33:
            return EXPR3;
        case 34:
        case 35:
            return EXPR2;
        case 36:
        case 37:
            return EXPR1;
        case 38:
        case 39:
            return CONST;
        default:
            error_unexpected_index_rule(errors); // the rule is out of the index rules.
            return -1; // Or some other error indicator
    }
}

char* get_string_from_non_terminal_type(Parse_Tree* tree, Error* errors)
{
    switch (tree->non_terminal_type) {
        case PROG_PRIME:
            return "prog'";
        case PROG:
            return "prog";
        case BLOCK:
            return "block";
        case STMT:
            return "stmt";
        case BLOCK_STMT:
            return "block_stmt";
        case DECLARE_STMT:
            return "declare_stmt";
        case ASSIGNMENT_STMT:
            return "assignment_stmt";
        case IF_STMT:
            return "if_stmt";
        case IF_NOT_STMT:
            return "if_not_stmt";
        case EXPR:
            return "expr";
        case EXPR12:
            return "expr12";
        case EXPR11:
            return "expr11";
        case EXPR10:
            return "expr10";
        case EXPR9:
            return "expr9";
        case EXPR8:
            return "expr8";
        case EXPR7:
            return "expr7";
        case EXPR6:
            return "expr6";
        case EXPR5:
            return "expr5";
        case EXPR4:
            return "expr4";
        case EXPR3:
            return "expr3";
        case EXPR2:
            return "expr2";
        case EXPR1:
            return "expr1";
        case CONST:
            return "const";
        default:
            unexpected_non_terminal_type_error(errors);
            return NULL;
    }
}


void print_parse_tree_helper(Parse_Tree* tree, int depth, Error* errors)
{
    if (!tree) return;

    for (int i = 0; i < depth; i++) {
        printf("  ");  // Indentation for tree structure
    }

    if (tree->is_terminal == TERMINAL) {
        printf("Terminal: %s\n", tree->token ? tree->token->value : "NULL");
    } else if (tree->is_terminal == NON_TERMINAL) {
        printf("Non-Terminal: %s\n", get_string_from_non_terminal_type(tree, errors));
    } else {
        printf("Uninitialized Node\n");
    }

    for (int i = 0; i < tree->num_of_sons; i++) {
        print_parse_tree_helper(tree->sons[i], depth + 1, errors);
    }
}

void print_parse_tree(Parse_Tree* tree, Error* errors)
{
    printf("The parse tree look like: \n \n ");
    print_parse_tree_helper(tree, 0, errors);
}
