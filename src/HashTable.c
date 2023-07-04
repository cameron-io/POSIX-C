#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define SIZE 20

typedef struct {
   int key;
   int data;
} Record;

Record* hash_table[SIZE];
Record* null_terminator;

int hash(int key) {
   return key % SIZE;
}

void init() {
    null_terminator = (Record*) malloc(sizeof(Record));
    null_terminator->data = -1;
    null_terminator->key = -1;
}

void insert(int key, int data) {
    int hash_index = hash(key);
    Record* record = (Record*) malloc(sizeof(Record));
    record->data = data;  
    record->key = key;

    while(hash_table[hash_index] != NULL && hash_table[hash_index]->key != -1) {
        ++hash_index;
        hash_index %= SIZE;
    }
    hash_table[hash_index] = record;
}

Record *query(int key) {
    int hash_index = hash(key);  
 
    while(hash_table[hash_index] != NULL) {        
        if(hash_table[hash_index]->key == key)
            return hash_table[hash_index];
        ++hash_index;
        hash_index %= SIZE;
    }    
    return NULL;
}

Record* delete(Record* record) {
    int key = record->key;
    int hash_index = hash(key);

    while (hash_table[hash_index] != NULL) {	
        if (hash_table[hash_index]->key == key) {
            Record* temp = hash_table[hash_index];
            hash_table[hash_index] = null_terminator;
            return temp;
        }
        hash_index++;
        hash_index %= SIZE;
    }
    return NULL;
}

void print_all() {
    for (int i = 0; i < SIZE; i++) {
        if (hash_table[i] != NULL)
            printf(" (%d, %d) ", hash_table[i]->key, hash_table[i]->data);
        else
            printf(" () ");
    }
    printf("\n");
}

int main() {
    init();

    insert(1, 20);
    insert(2, 70);
    insert(42, 80);
    insert(4, 25);
    insert(12, 44);
    insert(14, 32);
    insert(17, 11);
    insert(13, 78);
    insert(37, 97);

    print_all();
    Record* record = query(37);

    if(record != NULL)
        printf("Element found: %d\n", record->data);
    else
        printf("Element not found\n");

    delete(record);
    record = query(37);

    if(record != NULL)
        printf("Element found: %d\n", record->data);
    else
        printf("Element not found\n");
}