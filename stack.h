#ifndef INC_STACK_H
#define INC_STACK_H

#include "data.h"

typedef struct stack** Stack;

Stack stackCreate(void);

/*pushes Data onto stack; makes copy of Data*/
int stackPush(Stack, const Data);

/*returns Data from top of stack*/
Data stackPop(Stack);

/*returns true if empty*/
int stackEmpty(Stack);

void stackDestroy(Stack);

#endif