#include "Token.h"
#define TABLE_SIZE 256

// Node structure for the linked list (for separate chaining)
typedef struct Node {
    char key[MAX_TOKEN_LENGTH]; // the value of the token
    Token* value; // the token
    struct Node* next;
} Node;

// Hash map structure
typedef struct {
    Node** table;
} HashMap;


HashMap* create_hash_map();
unsigned int hash(const char* key);
void add(HashMap* hash_map, char* key, Token* value);
Token* get(HashMap* hash_map, char* key);
void removeKey(HashMap* hash_map, const char* key);
HashMap* make_hash_map_tokens(char** bido_tokens_str);
void freeHashMap(HashMap* hashMap);
