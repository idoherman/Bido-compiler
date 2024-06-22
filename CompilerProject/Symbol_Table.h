#include "Parse_Table.h"

typedef struct Symbol {
    char* name;          // Variable name
    Data_Type type;          // Variable type
    int scope_level;     // the level of the variable definition scope
    struct Symbol* next;
} Symbol;

// symbol table
typedef struct SymbolTable {
    Symbol* head;        // Head of the symbol list
    int scope_level;     // the level of the current scope
} SymbolTable;


SymbolTable* create_symbol_table();
Symbol* create_symbol(char* name, Data_Type type, int scope_level);
void add_symbol(SymbolTable* table, char* name, Data_Type type);
Symbol* find_symbol(SymbolTable* table, char* name);
void enter_scope(SymbolTable* table);
void exit_scope(SymbolTable* table);
char* data_type_to_str(Data_Type type, Error* errors);

