#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
   void* key;
   void* value;
} Record;

#define NUM_BUCKETS 10
#define BUCKET_DEPTH 5

Record* table[NUM_BUCKETS][BUCKET_DEPTH];
Record* null_terminator;

int ht_hash(char* key) {
   return strlen(key) % NUM_BUCKETS;
}

void ht_init() {
    null_terminator = (Record*) malloc(sizeof(Record));
    null_terminator->value = (void*) NULL;
    null_terminator->key = (void*) NULL;

    for (int i = 0; i < NUM_BUCKETS; i++) {
        for (int j = 0; j < BUCKET_DEPTH; j++) {
            table[i][j] = null_terminator;
        }
    }
}

void ht_insert(char* key, char* value) {
    int bucket_index = ht_hash(key);
    Record* record = (Record*) malloc(sizeof(Record));
    record->value = (void*) value;
    record->key = (void*) key;

    int i = 0;
    while (table[bucket_index][i]->key) {
        i++;
    }
    table[bucket_index][i] = record;
}

Record* ht_query(char* key) {
    int bucket_index = ht_hash(key);

    int i = 0;
    while(table[bucket_index][i]) {
        if(table[bucket_index][i]->key == key)
            return table[bucket_index][i];
        i++;
    }
    return NULL;
}

Record* ht_delete(char* key) {
    int bucket_index = ht_hash(key);

    int i = 0;
    while (table[bucket_index][i]) {
        if (table[bucket_index][i]->key == key) {
            Record* deleted_record = table[bucket_index][i];
            table[bucket_index][i] = null_terminator;
            free(deleted_record);
            return NULL;
        }
        i++;
    }
    return NULL;
}

void print_table() {
    printf("[\n");
    for (int i = 0; i < NUM_BUCKETS; i++) {
        printf("    [");
        for (int j = 0; j < BUCKET_DEPTH; j++) {
            if (table[i][j] && table[i][j]->key)
                printf("\033[1;36m{\"%s\": \"%s\"}\033[0m", table[i][j]->key, table[i][j]->value);
            else
                printf("nil");
            if (j < BUCKET_DEPTH - 1) printf(", ");
        }
        printf("]\n");
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
    printf("Record \"%s\" deleted: %s\n", key, (!record) ? "true" : "false" );

    print_table();
}