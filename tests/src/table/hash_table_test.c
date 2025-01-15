#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "hash_table.h"

int
main() {
    ht_init();

    ht_insert("Dodge", "Auburn Hills, Michigan");
    ht_insert("Ford", "Dearborn, Michigan");
    ht_insert("Chevrolet", "Detroit, Michigan");
    ht_insert("Ferrari", "Maranello, Italy");
    ht_insert("Lamborghini", "Bolognese, Italy");
    ht_insert("Porsche", "Stuttgart, Germany");

    print_table();

    // Query Bucket Collision
    char* key1 = "Porsche";
    Record* record1 = ht_query(key1);
    assert(strcmp((char*)record1->value, "Stuttgart, Germany") == 0);
    printf("GET\t\"%s\" \t: \"%s\"\n", key1, (char*)record1->value);

    char* key2 = "Dodge";
    Record* record2 = ht_query(key2);
    assert(strcmp((char*)record2->value, "Auburn Hills, Michigan") == 0);
    printf("GET\t\"%s\" \t: \"%s\"\n", key2, (char*)record2->value);

    // Delete Record
    ht_delete(key2);

    // Follow-Up Query
    record2 = ht_query(key2);
    assert(!record2);
    printf("DELETE\t\"%s\"\n", key2);

    print_table();
}
