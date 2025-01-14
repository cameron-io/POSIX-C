#ifndef HASH_TABLE_H
#define HASH_TABLE_H

typedef struct {
   void* key;
   void* value;
} Record;

int ht_hash(char* key);
void ht_init();
void ht_insert(char* key, char* value);
Record* ht_query(char* key);
Record* ht_delete(char* key);
void print_table();

#endif