#include "Parse_Stack.h"

Parse_Stack* init_parse_stack()
{
    Parse_Stack* st = (Parse_Stack*) malloc(sizeof(Parse_Stack));
    st->offset = -1;
    return st;
}

int is_stack_empty(Parse_Stack* st)
{
    return st->offset == -1;
}

int is_stack_full(Parse_Stack* st)
{
    return st->offset == STACK_MAX_SIZE - 1;
}

void push_first_parse_stack(Parse_Stack* st, Parse_Tree* element, Error* errors)
{
    element->state = 0;
    push_parse_stack(st, element, errors);
}

void push_parse_stack(Parse_Stack* st, Parse_Tree* element, Error* errors)
{
    if (is_stack_full(st)) {
        stack_full_error(errors);
    }
    else {
        st->offset++;
        st->array[st->offset] = element;
    }
}

Parse_Tree* pop_parse_stack(Parse_Stack* st, Error* errors)
{
    if (is_stack_empty(st)) {
        stack_empty_error(errors);
        return NULL;
    }
    else {
        return st->array[st->offset--];
    }
}

Parse_Tree* top_parse_stack(Parse_Stack* st, Error* errors)
{
    if (is_stack_empty(st)) {
        stack_empty_error(errors);
        return NULL;
    }
    else {
        return st->array[st->offset];
    }
}
