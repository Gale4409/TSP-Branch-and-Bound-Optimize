#include <stdio.h>
#include <stdlib.h>
#include "item.h"
#include <string.h>

struct city {
    char *name; int population; int altitude;
};

City ITEMinit (int N) {
    City c = malloc (sizeof(struct city));
    if (c == NULL) return NULL;
    c->name = calloc (N+1, sizeof(char));
    c->population = c->altitude = 0;
    return c;
}

City ITEMload (char *name, int population, int altitude) {
    City c = ITEMinit (strlen(name));
    if (c == NULL) return NULL;
    strcpy (c->name, name);
    c->population = population;
    c->altitude = altitude;
    return c;
}

char *ITEMgetname (City c) {
    if (c == NULL) return NULL;
    return c->name;
}

int ITEMcmp (City c1, City c2) { return strcmp (c1->name, c2->name); }

void ITEMdisplay (City c) {
    printf ("\nCity data:\n");
    printf(" - Name: %s\n", c->name);
    printf (" - Population: %d\n", c->population);
    printf (" - Altitude: %d\n", c->altitude);
}

void ITEMfree (City c) { free (c->name); free (c); }