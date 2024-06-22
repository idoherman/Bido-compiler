#include "HashMap.h"

// Initialize hash map
HashMap* create_hash_map()
{
    HashMap* hash_map = (HashMap*) malloc(sizeof(HashMap));
    hash_map->table = (Node**) malloc(TABLE_SIZE * sizeof(Node *));
    for (int i = 0; i < TABLE_SIZE; i++) {
        hash_map->table[i] = NULL;
    }
    return hash_map;
}

// Hash function
unsigned int hash(const char* key)
{
    return *key;
}


// Add key-value pair to hash map
void add(HashMap* hash_map, char* key, Token* value)
{
    unsigned int index = hash(key);
    Node* newNode = (Node*) malloc(sizeof(Node));
    str_copy(key, newNode->key);
    newNode->value = value;
    newNode->next = hash_map->table[index];
    hash_map->table[index] = newNode;
}

// Get value associated with key
Token* get(HashMap* hash_map, char* key)
{
    unsigned int index = hash(key);
    Node* current = hash_map->table[index];
    while (current) {
        if (str_compare(current->key, key)) {
            return current->value;
        }
        current = current->next;
    }
    return NULL;
}

// Remove key-value pair from hash map
void removeKey(HashMap* hash_map, const char *key)
{
    unsigned int index = hash(key);
    Node* current = hash_map->table[index];
    Node* prev = NULL;
    while (current) {
        if (str_compare(current->key, key)) {
            if (prev) {
                prev->next = current->next;
            } else {
                hash_map->table[index] = current->next;
            }
            free(current->key);
            free(current->value);
            free(current);
            return;
        }
        prev = current;
        current = current->next;
    }
}

HashMap* make_hash_map_tokens(char** bido_tokens_str)
{
    int i;
    HashMap* hash_map = create_hash_map();
    for (i = 0; i < BIDO_TOKENS_AMOUNT; i++) {
        Token* token = make_token_from_str(bido_tokens_str[i], i, 0, 0); // Assuming TOKEN_TYPE is a placeholder for the actual token type
        add(hash_map, token->value, token);
    }
    return hash_map;
}

// Free hash map memory
void freeHashMap(HashMap* hashMap)
{
    for (int i = 0; i < TABLE_SIZE; i++) {
        Node* current = hashMap->table[i];
        while (current) {
            Node* temp = current;
            current = current->next;
            free(temp->key);
            free(temp->value);
            free(temp);
        }
    }
    free(hashMap->table);
    free(hashMap);
}
