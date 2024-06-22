#include "Parse_tree.h"
#define STACK_MAX_SIZE 1000

typedef struct Parse_Stack {
    Parse_Tree* array[STACK_MAX_SIZE];
    int offset;
} Parse_Stack;


Parse_Stack* init_parse_stack();
int is_stack_empty(Parse_Stack* st);
int is_stack_full(Parse_Stack* st);
void push_first_parse_stack(Parse_Stack* st, Parse_Tree* element, Error* errors);
void push_parse_stack(Parse_Stack* st, Parse_Tree* element, Error* errors);
Parse_Tree* pop_parse_stack(Parse_Stack* st, Error* errors);
Parse_Tree* top_parse_stack(Parse_Stack* st, Error* errors);
