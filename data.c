#include "data.h"
#include <string.h>
#include <stdlib.h>

struct data{
	char* key;
	int* value;
};

Data nullValCreate(const char*key){
	Data d = malloc(sizeof(struct data));
	d->key=strdup(key);
	d->value = NULL;
	return d;
}

int dataVal(Data d){
	if(d->value)
		return 1;
	else return 0;
}

int getDataVal(Data d){
	if(d->value)
		return *(d->value);
	else return 0;
}

char* getDataKey(Data d){
	return d->key;
}

Data dataCreate(const char *key, int value){
	Data d = malloc(sizeof(struct data));
	d->key=strdup(key);
	d->value = malloc(sizeof(int));
	*(d->value)=value;
	return d;
}

Data dataCopy(const Data old){
	Data new;
	if(dataVal(old))
		new=dataCreate(old->key,*(old->value));
	else
		new=nullValCreate(old->key);
	return new;
}

void dataDelete(Data d){
	free(d->key);
	if(d->value)
		free(d->value);
	free(d);
}