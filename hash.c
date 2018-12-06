#include <stdlib.h>
#include <string.h>
#include "hash.h"

typedef struct elt{
	char* key;
	Data d;
}* Elt;

struct hash{
	size_t size;
	size_t numElts;
	struct elt **table;
};

static Hash internalHashCreate(size_t size);

static Elt eltCreate(const char* key, Data d){
	Elt e = malloc(sizeof(struct elt));
	e->key=strdup(key);
	e->d=dataCopy(d);
	return e;
}

static void eltDelete(Elt e){
	if(e==NULL)
		return;
	else{
		dataDelete(e->d);
		free(e->key);
		free(e);
	}
}

static unsigned long hashFunction(const char *s){
	unsigned long h=0;
	while(*s){
		h = h * PRIME + *s++;
	}
	return h;
}

static void grow(Hash h){
	Hash new = internalHashCreate((*h)->size * GROWTH_FACTOR);
	size_t i;
	Elt e;
	for(i=0;i<(*h)->size;i++){
		if((e=(*h)->table[i])!=NULL){
			hashInsert(new,e->d,e->key);
			eltDelete((*h)->table[i]);
		}
	}

	free((*h)->table);
	free(*h);
	
	*h=*new;
	
	free(new);
}

void hashInsert(Hash h, Data d, const char *key){
	Elt new = eltCreate(key, d);
	unsigned long hashNum=hashFunction(key) % (*h)->size;
	Elt e;
	while((e=(*h)->table[hashNum])!=NULL){
		if(!strcmp(e->key,key)){
			eltDelete((*h)->table[hashNum]);
			break;
		}
		else if(hashNum== (*h)->size - 1)
			hashNum=0;
		else
			hashNum++;
	}
	(*h)->table[hashNum]=new;
	(*h)->numElts++;
	
	/*increase size if load factor exceeded*/
	if((*h)->numElts >= (*h)->size*LOAD_FACTOR)
		grow(h);
}

/*return Data at hash if found, 0 if not*/
Data hashSearch(Hash h, const char *key){
	unsigned long hashNum=hashFunction(key) % (*h)->size;
	Elt e;
	while((e=(*h)->table[hashNum])!=NULL){
		if(!strcmp(e->key,key))
			return e->d;
		else if(hashNum== (*h)->size - 1)
			hashNum=0;
		else
			hashNum++;
	}
	return NULL;	
}

static Hash internalHashCreate(size_t size){
	Hash h=malloc(sizeof(struct hash*));
	*h=malloc(sizeof(struct hash));
	(*h)->size = size;
	(*h)->numElts=0;
	(*h)->table = malloc(sizeof(struct elt*)*(*h)->size);
	
	/*initalize all elts in table to null*/
	for(size_t i = 0; i<(*h)->size;i++){
		(*h)->table[i]=NULL;
	}
	return h;
}

Hash hashCreate(void){
	return internalHashCreate(INIT_SIZE);
}

void hashDestroy(Hash h){
	size_t i;
	for(i=0; i < (*h)->size; i++){
		eltDelete((*h)->table[i]);
	}
	free((*h)->table);
	free(*h);
	free(h);
}