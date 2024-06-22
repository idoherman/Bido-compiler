#include "Code_Generation.h"


char* read_file_to_string(const char* filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return NULL;
    }

    // Seek to the end of the file to determine the file size
    fseek(file, 0, SEEK_END);
    long filesize = ftell(file);
    rewind(file); // Rewind to the beginning of the file

    // Allocate memory for the file content + null terminator
    char *content = (char*) malloc((filesize + 1) * sizeof(char));
    if (content == NULL) {
        perror("Error allocating memory");
        fclose(file);
        return NULL;
    }

    // Read the file content into the allocated memory
    size_t bytes_read = fread(content, 1, filesize, file);

    // Null-terminate the string
    content[bytes_read] = '\0';

    // Close the file
    fclose(file);

    return content;
}


int main(int argc, char *argv[])
{
    char* code = read_file_to_string(argv[1]);
//    char* code = read_file_to_string("C:\\ort_homeworks\\MyProject\\CompilerProject\\compiler_files\\bido_file_example_1.txt");

// const cant change the order without changing the token type enum.
    char* bido_tokens_str[BIDO_TOKENS_AMOUNT] = {"function", "<", "main", ">",
                                                 "returns", "int", "gets",
                                                 "(", ")", "{", "}",
                                                 "char", "text", "bool",
                                                 "is", "true", "false",
                                                 "if", "not", "and", "or",
                                                 ".", "=", "!=", ">=", "<=",
                                                 "+", "-", "*", "/", "%",
                                                 "&", "|", "^", "!", "return"};


    HashMap* tokens_dict = make_hash_map_tokens(bido_tokens_str);
    Error* errors = init_errors_node();

    int count_tokens = 0;
    Token* code_tokens = lexical_analyser(code, &count_tokens, tokens_dict, errors);
    change_first_int_func_type(code_tokens, count_tokens, errors);
    free(code);
    if (check_errors_exists(errors)) {
        printf("\n Lexical Errors!!!!!!");
        return 0; // stop the compilation.
    }

    print_code_tokens(code_tokens, count_tokens);     // code_tokens
    printf("\n\nAmount of tokens: %d \n \n", count_tokens);        // amount of tokens

    int count_tokens_include_dollar = count_tokens + 1;
    Token* code_tokens_include_dollar = (Token*) realloc(code_tokens, count_tokens_include_dollar * sizeof(Token));
    code_tokens_include_dollar[count_tokens_include_dollar - 1] = *make_token_from_str("$", TOKEN_DOLLAR , -1, -1);
    SymbolTable* symbol_table = create_symbol_table();
    Parse_Tree* tree = syntax_analysis_parser_function(code_tokens_include_dollar,
               symbol_table, count_tokens_include_dollar, errors);

    if (check_errors_exists(errors)) {
        return 0;
    }
//    if (tree) {
//        print_parse_tree(tree, errors);
//    }

    char* assembly_file_path = argv[2];
//    char* assembly_file_path = "C:\\ort_homeworks\\MyProject\\CompilerProject\\compiler_files\\bido_code_after_compilation_1.txt";
    Register* registers = init_free_registers();
    int check_code_gen = code_generation(symbol_table, registers,  tree,
    assembly_file_path, errors);
    if (check_code_gen == 0) {
        if (check_errors_exists(errors)) {
            return 0;
        }
        printf("\nThere is errors without any error message!!!\n");
    }
    else {
        printf("\nThe Compilation Process succeeded :) (:\n");
    }
    return 0;
}


