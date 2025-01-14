#include "lib/table/hash_table.h"

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
    printf("Record \"%s\" query  : \"%s\"\n", key1, record1->value);

    char* key2 = "Dodge";
    Record* record2 = ht_query(key2);
    printf("Record \"%s\" query  : \"%s\"\n", key2, record2->value);

    // Delete Record
    ht_delete(key2);

    // Follow-Up Query
    record2 = ht_query(key2);
    printf("Record \"%s\" deleted: %s\n", key2, (!record2) ? "true" : "false" );

    print_table();
}
