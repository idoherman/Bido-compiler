cmake_minimum_required(VERSION 3.26)
project(CompilerProject C)

set(CMAKE_C_STANDARD 11)

add_executable(CompilerProject main.c
        Token.c
        Token.h
        HashMap.c
        HashMap.h
        MyString.c
        MyString.h
        Error_Handler.c
        Error_Handler.h
        Abstract_Syntax_Tree.c
        Abstract_Syntax_Tree.h
        Parser.c
        Parser.h
        Parse_Stack.c
        Parse_Stack.h
        Parse_Table.c
        Parse_Table.h
        Parse_tree.c
        Parse_tree.h
        Symbol_Table.c
        Symbol_Table.h
        Code_Generation.c
        Code_Generation.h
        Code_Generation_Base.c
        Code_Generation_Base.h
        Lexer.c
        Lexer.h
)
