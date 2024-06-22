#include "Abstract_Syntax_Tree.h"

AST* init_ast(Token* token, AST* left, AST* right)
{
    AST* ast = (AST*) malloc(sizeof(AST));
    ast->token = token;
    ast->left = left;
    ast->right = right;
    return ast;
}


