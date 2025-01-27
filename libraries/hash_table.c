#include <stdio.h>
#include <stdlib.h>

#define TABLE_SIZE 10

typedef struct HashTable {
    int key;
    int value;
    struct HashTable* next;
} HashTable;

int hashFunction(int key) {
    return key % TABLE_SIZE;
}

HashTable* createTable() {
    HashTable* table[TABLE_SIZE] = { NULL };
    return table;
}

void insert(HashTable* table[], int key, int value) {
    int hashIndex = hashFunction(key);
    HashTable* newNode = (HashTable*)malloc(sizeof(HashTable));
    newNode->key = key;
    newNode->value = value;
    newNode->next = table[hashIndex];
    table[hashIndex] = newNode;
}

int search(HashTable* table[], int key) {
    int hashIndex = hashFunction(key);
    HashTable* temp = table[hashIndex];
    while (temp != NULL) {
        if (temp->key == key) {
            return temp->value;
        }
        temp = temp->next;
    }
    return -1;  // Not found
}

void delete(HashTable* table[], int key) {
    int hashIndex = hashFunction(key);
    HashTable* temp = table[hashIndex];
    HashTable* prev = NULL;

    if (temp != NULL && temp->key == key) {
        table[hashIndex] = temp->next;
        free(temp);
        return;
    }

    while (temp != NULL && temp->key != key) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Key not found\n");
        return;
    }

    prev->next = temp->next;
    free(temp);
}

void displayTable(HashTable* table[]) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        printf("Table[%d]: ", i);
        HashTable* temp = table[i];
        while (temp != NULL) {
            printf("Key: %d, Value: %d -> ", temp->key, temp->value);
            temp = temp->next;
        }
        printf("NULL\n");
    }
}
   
