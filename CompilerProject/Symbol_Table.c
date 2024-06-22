#include "Symbol_Table.h"

SymbolTable* create_symbol_table()
{
    SymbolTable* table = (SymbolTable*) malloc(sizeof(SymbolTable));
    table->head = NULL;
    table->scope_level = -1;
    return table;
}


Symbol* create_symbol(char* name, Data_Type type, int scope_level)
{
    Symbol* symbol = (Symbol*) malloc(sizeof(Symbol));
    symbol->name = (char*) malloc((str_length(name) + 1) * sizeof(char));
    str_copy(name, symbol->name);
    symbol->type = type;
    symbol->scope_level = scope_level;
    symbol->next = NULL;
    return symbol;
}

void add_symbol(SymbolTable* table, char* name, Data_Type type)
{
    Symbol* symbol = create_symbol(name, type, table->scope_level);
    symbol->next = table->head;
    table->head = symbol;
}

// Function that finds the variable in the symbol table with his name.
Symbol* find_symbol(SymbolTable* table, char* name)
{
    Symbol* current = table->head;
    while (current != NULL) {
        if (str_compare(current->name, name)) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

// function that adds 1 to the scope level when you entered another scope.
void enter_scope(SymbolTable* table)
{
    table->scope_level++;
}

// function that deletes the variables that defined in a specific scope.
void exit_scope(SymbolTable* table)
{
    Symbol* current = table->head;
    while (current != NULL && current->scope_level == table->scope_level) {
        Symbol* to_free = current;
        current = current->next;
        free(to_free->name);
        free(to_free);
    }
    table->head = current;
    table->scope_level--;
}

char* data_type_to_str(Data_Type type, Error* errors)
{
    switch (type) {
        case DATA_INT:
            return "int";
        case DATA_BOOL:
            return "bool";
        case DATA_CHAR:
            return "char";
        case DATA_TEXT:
            return "text";
        default:
            unexpected_data_type_error(errors);
            return NULL;
    }
}

