#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
   void* key;
   void* value;
} Record;

#define SIZE 10

Record* table[SIZE];
Record* null_terminator;

int ht_hash(char* key) {
   return strlen(key) % SIZE;
}

void ht_init() {
    null_terminator = (Record*) malloc(sizeof(Record));
    null_terminator->value = (void*) NULL;
    null_terminator->key = (void*) NULL;
}

void ht_insert(char* key, char* value) {
    int bucket_index = ht_hash(key);
    Record* record = (Record*) malloc(sizeof(Record));
    record->value = (void*) value;
    record->key = (void*) key;

    while (table[bucket_index] && table[bucket_index]->key) {
        bucket_index++;
    }
    table[bucket_index] = record;
}

Record* ht_query(char* key) {
    int bucket_index = ht_hash(key);
 
    while(table[bucket_index]) {
        if(table[bucket_index]->key == key)
            return table[bucket_index];
        bucket_index++;
    }

    return NULL;
}

Record* ht_delete(char* key) {
    int bucket_index = ht_hash(key);

    while (table[bucket_index]) {
        if (table[bucket_index]->key == key) {
            Record* deleted_record = table[bucket_index];
            table[bucket_index] = null_terminator;
            return deleted_record;
        }
        bucket_index++;
    }
    return NULL;
}

void print_table() {
    printf("[\n");
    for (int i = 0; i < SIZE; i++) {
        if (table[i] && table[i]->key)
            printf("    {\"%s\": \"%s\"}\n", table[i]->key, table[i]->value);
        else
            printf("    {\"\": \"\"}\n");
    }
    printf("]\n");
}

int main() {
    ht_init();

    ht_insert("Dodge", "Auburn Hills, Michigan");
    ht_insert("Ford", "Dearborn, Michigan");
    ht_insert("Chevrolet", "Detroit, Michigan");
    ht_insert("Ferrari", "Maranello, Italy");
    ht_insert("Lamborghini", "Bolognese, Italy");
    ht_insert("Porsche", "Stuttgart, Germany");

    print_table();

    // Query
    char* key = "Dodge";
    Record* record = ht_query(key);
    printf("Record \"%s\" query  : \"%s\"\n", key, record->value);

    // Delete Record
    ht_delete(key);

    // Follow-Up Query
    record = ht_query(key);
    printf("Record \"%s\" deleted: \"%s\"\n", key, (!record) ? "true" : "false" );

    print_table();
}