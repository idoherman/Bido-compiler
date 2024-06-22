#include "stdio.h"
#include "Error_Handler.h"


typedef struct AST {
    Token* token;
    struct AST* left;
    struct AST* right;
} AST;
