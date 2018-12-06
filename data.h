#ifndef INC_DATA_H
#define INC_DATA_H

typedef struct data* Data;

Data dataCreate(const char *key, int value);

/*duplicate Data object (creates copy of all internal parts)*/
Data dataCopy(const Data old);

/*creates data object with no initial value (i.e. NULL)*/
Data nullValCreate(const char *key);

/*return 1 if there is a value stored, 0 otherwise (i.e. null pointer)*/
int dataVal(Data);

/*return value. if no value, returns 0*/
int getDataVal(Data);

char* getDataKey(Data);

void dataDelete(Data);

#endif