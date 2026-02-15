#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ST.h"
#include "Item.h"

// Symbol Table structure: two parallel arrays
// The array index corresponds to the unique vertex ID (0, 1, ..., V-1)
struct symbletable {
    City *items;     // Array storing the city data at the corresponding index
    int *hash_table; // Hash Table for fast lookup: maps (Hash) -> Vertex Index
    int maxN;        // Maximum number of elements (V)
};

// Private Hash function (Horner's method for strings)
static int hash(char *str, int M) {
    int h = 0, a = 127;
    for (; *str != '\0'; str++) {
        h = (a * h + *str) % M;
    }
    return h;
}

ST STinit(int MAXN) {
    ST st = malloc(sizeof(struct symbletable));
    if (st == NULL) return NULL;

    st->maxN = MAXN;

    // Array to store Items at the exact vertex index
    st->items = malloc(MAXN * sizeof(City));
    // Hash table containing indices. Larger size to reduce collisions (e.g., MAXN * 2)
    st->hash_table = malloc((MAXN * 2) * sizeof(int));

    if (st->items == NULL || st->hash_table == NULL) {
        free(st->items);
        free(st->hash_table);
        free(st);
        return NULL;
    }

    int i;
    for (i = 0; i < MAXN; i++) st->items[i] = NULL;
    for (i = 0; i < MAXN * 2; i++) st->hash_table[i] = -1; // -1 indicates "empty"

    return st;
}

// Inserts a city at the specified index and updates the Hash Table
void STinsert(ST st, City c, int index) {
    if (st == NULL || c == NULL || index < 0 || index >= st->maxN) return;

    // Saves the Item in the direct access array
    st->items[index] = c;

    char *name = ITEMgetname(c);
    int i = hash(name, st->maxN * 2);

    // Inserts into the Hash Table using Linear Probing for collisions
    while (st->hash_table[i] != -1) {
        i = (i + 1) % (st->maxN * 2);
    }
    st->hash_table[i] = index;
}

// Retrieves a city given its numerical index (direct access O(1))
City STget(ST st, int index) {
    if (st == NULL || index < 0 || index >= st->maxN) return NULL;
    return st->items[index];
}

// Returns the numerical index of a city given its Item (via Hash O(1))
int STgetIndex(ST st, City c) {
    if (st == NULL || c == NULL) return -1;

    char *name = ITEMgetname(c);
    int i = hash(name, st->maxN * 2);

    while (st->hash_table[i] != -1) {
        // Checks if the city found in the hash table matches the target
        if (ITEMcmp(st->items[st->hash_table[i]], c) == 0) {
            return st->hash_table[i];
        }
        i = (i + 1) % (st->maxN * 2);
    }

    return -1; // Not found
}

// Searches and returns the complete Item
City STsearch(ST st, City c) {
    int index = STgetIndex(st, c);
    if (index == -1) return NULL;
    return st->items[index];
}

// Displays all the elements currently in the Symbol Table
void STprint(ST st) {
    if (st == NULL) return;
    int i;
    for (i = 0; i < st->maxN; i++) {
        if (st->items[i] != NULL) {
            printf("Index %d: ", i);
            ITEMdisplay(st->items[i]);
        }
    }
}

// Frees the allocated memory for the Symbol Table and its items
void STfree(ST st) {
    if (st == NULL) return;
    int i;
    for (i = 0; i < st->maxN; i++) {
        if (st->items[i] != NULL) {
            ITEMfree(st->items[i]);
        }
    }
    free(st->items);
    free(st->hash_table);
    free(st);
}