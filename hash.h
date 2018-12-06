#ifndef INC_HASH_H
#define INC_HASH_H

#define INIT_SIZE (7)
#define LOAD_FACTOR (0.5)
#define PRIME (37)
#define GROWTH_FACTOR (2)
#include "data.h"

typedef struct hash** Hash;

/*inserts Data into table. takes key (i.e. variable name) as third argument*/
void hashInsert(Hash, Data, const char*);

/*return Data at hash if found, 0 if not*/
Data hashSearch(Hash, const char*);

Hash hashCreate(void);

void hashDestroy(Hash);

#endif