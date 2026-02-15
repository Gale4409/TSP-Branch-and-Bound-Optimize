# ifndef ST_H
# define ST_H

#include "Item.h"

typedef struct symbletable * ST ;

ST STinit (int MAXN) ;
void STinsert (ST st , City c, int index); //i'll pass to the ST the index where i want to find my item, i'll use 2 different array to do it with hash fx
City STget (ST st, int index);
int STgetIndex (ST st, City c);
City STsearch (ST st , City c);
void STprint (ST st);
void STfree (ST st);

#endif