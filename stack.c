#include <stdlib.h>
#include <string.h>
#include "stack.h"

/*stack is pointer to pointer to first element
of a linked list*/
struct stack{
	Data d;
	/*next item in stack or NULL if last item*/
	struct stack *next;
};

Stack stackCreate(void){
	Stack s = malloc(sizeof(struct stack*));
	*s = NULL;
	return s;
}

/*returns 1 on success, 0 on failure*/
int stackPush(Stack s,const Data d){
	struct stack *new = malloc(sizeof(struct stack));
	new->next = *s;
	/*copy data so that input data can be freed*/
	new->d=dataCopy(d);
	/*if duplication failed*/
	if(new->d==NULL){
		free(new);
		return 0;
	}
	*s = new;
	return 1;
}

Data stackPop(Stack s){
	if(*s==NULL){
		/*empty stack*/
		return NULL;
	} else{
		Data d = (*s)->d;
		struct stack *temp = *s;
		*s=(*s)->next;
		free(temp);
		return d;
	}
}

/*return true if empty*/
int stackEmpty(Stack s){
	return (*s)==0;
}

void stackDestroy(Stack s){
	while(*s){
		dataDelete(stackPop(s));
	}
	free(s);
}