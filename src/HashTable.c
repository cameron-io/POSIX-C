#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
   int key;
   int value;
} Record;

#define SIZE 20

Record* hash_table[SIZE];
Record* null_terminator;

int hash(int key) {
   return key % SIZE;
}

void init() {
    null_terminator = (Record*) malloc(sizeof(Record));
    null_terminator->value = -1;
    null_terminator->key = -1;
}

void insert(int key, int value) {
    int hash_index = hash(key);
    Record* record = (Record*) malloc(sizeof(Record));
    record->value = value;  
    record->key = key;

    while(hash_table[hash_index] != NULL && hash_table[hash_index]->key != -1) {
        hash_index++;
        hash_index %= SIZE;
    }
    hash_table[hash_index] = record;
}

Record* query(int key) {
    int hash_index = hash(key);
 
    while(hash_table[hash_index] != NULL) {
        if(hash_table[hash_index]->key == key)
            return hash_table[hash_index];
        hash_index++;
        hash_index %= SIZE;
    }

    return NULL;
}

Record* delete(Record* record) {
    int key = record->key;
    int hash_index = hash(key);

    while (hash_table[hash_index] != NULL) {
        if (hash_table[hash_index]->key == key) {
            Record* deleted_record = hash_table[hash_index];
            hash_table[hash_index] = null_terminator;
            return deleted_record;
        }
        hash_index++;
        hash_index %= SIZE;
    }
    return NULL;
}

void print_table() {
    for (int i = 0; i < SIZE; i++) {
        if (hash_table[i] != NULL)
            printf(" (%d, %d) ", hash_table[i]->key, hash_table[i]->value);
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

    print_table();

    // Query
    Record* record = query(37);
    printf("Record 37 query  : %d\n", record->value);

    // Delete Record
    delete(record);

    // Follow-Up Query
    record = query(37);
    printf("Record 37 deleted: %s\n", (record == NULL) ? "true" : "false" );
}