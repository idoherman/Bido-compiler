#include "Parse_Stack.h"
#define NUM_OF_STATES 85

typedef enum Action_Type {
    ERROR_ACTION,
    SHIFT_ACTION,
    REDUCE_ACTION,
    ACCEPT_ACTION
} Action_Type;

typedef struct Action {
    Action_Type type; // action type
    int state;  // if state -1 is the init default, if state = -2 is the accept place.
} Action;

typedef struct GoTo {
    int state;
} GoTo;

typedef struct Parse_Table {
    Action action_table[NUM_OF_STATES][NUM_OF_TERMINALS];
    GoTo goto_table[NUM_OF_STATES][NUM_OF_NON_TERMINALS];
} Parse_Table;

Parse_Table* init_parse_table();
Parse_Table* build_the_actual_table();
int get_terminal_type_from_token(Token* token, Error* errors);
Action* get_action(Parse_Table* table, Token* token, int row, Parse_Stack* st, Error* errors);
GoTo* get_goto(Parse_Table* table, int state, int rule, Error* errors);
