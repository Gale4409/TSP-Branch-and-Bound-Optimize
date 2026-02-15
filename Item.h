#ifndef ITEM_H
#define ITEM_H

typedef struct city *City;

City ITEMinit (int N); //N is the dimension of the string "city name"
City ITEMload (char *name, int population, int altitude);
char *ITEMgetname (City c);
int ITEMcmp (City c1, City c2);
void ITEMdisplay (City c);
void ITEMfree (City c);

#endif