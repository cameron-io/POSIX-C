#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
   int key;
   int value;
} Record;

#define SIZE 20

Record* table[SIZE];
Record* null_terminator;

int ht_hash(int key) {
   return key % SIZE;
}

void ht_init() {
    null_terminator = (Record*) malloc(sizeof(Record));
    null_terminator->value = -1;
    null_terminator->key = -1;
}

void ht_insert(int key, int value) {
    int bucket_index = ht_hash(key);
    Record* record = (Record*) malloc(sizeof(Record));
    record->value = value;  
    record->key = key;

    while (table[bucket_index] != NULL && table[bucket_index]->key != -1) {
        bucket_index++;
        bucket_index %= SIZE;
    }
    table[bucket_index] = record;
}

Record* ht_query(int key) {
    int bucket_index = ht_hash(key);
 
    while(table[bucket_index] != NULL) {
        if(table[bucket_index]->key == key)
            return table[bucket_index];
        bucket_index++;
        bucket_index %= SIZE;
    }

    return NULL;
}

Record* ht_delete(Record* record) {
    int key = record->key;
    int bucket_index = ht_hash(key);

    while (table[bucket_index] != NULL) {
        if (table[bucket_index]->key == key) {
            Record* deleted_record = table[bucket_index];
            table[bucket_index] = null_terminator;
            return deleted_record;
        }
        bucket_index++;
        bucket_index %= SIZE;
    }
    return NULL;
}

void print_table() {
    for (int i = 0; i < SIZE; i++) {
        if (table[i] != NULL)
            printf(" (%d, %d) ", table[i]->key, table[i]->value);
        else
            printf(" () ");
    }
    printf("\n");
}

int main() {
    ht_init();

    ht_insert(1, 20);
    ht_insert(2, 70);
    ht_insert(42, 80);
    ht_insert(4, 25);
    ht_insert(12, 44);
    ht_insert(14, 32);
    ht_insert(17, 11);
    ht_insert(13, 78);
    ht_insert(37, 97);

    print_table();

    // Query
    Record* record = ht_query(37);
    printf("Record 37 query  : %d\n", record->value);

    // Delete Record
    ht_delete(record);

    // Follow-Up Query
    record = ht_query(37);
    printf("Record 37 deleted: %s\n", (record == NULL) ? "true" : "false" );
}