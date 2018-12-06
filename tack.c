/*note, case insensitive database*/

/*the maximum input size for the command,
variable name, or number length*/
#define MAX_LEN (9)

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "hash.h"
#include "stack.h"


void upCase(char* s){
	while((*s++=toupper(*s)))
		;
}

int main(int argc, char**argv){
	Hash h = hashCreate();
	char c;
	char next[3][MAX_LEN+1];/*stores input: command, variable, value*/
	int spaces = 0;
	int pos = 0;
	int tblock = 0;
	Stack s = stackCreate();
	while((c = getchar())!=EOF){
		if(spaces==0 && pos==0){
			/*next input, set all strings to NULL before getting input*/
			for(int i = 0; i<3;i++)
				next[i][0]='\0';
		}
		if(pos==(MAX_LEN)){
			if(c!=' ' && c!='\n'){
				fprintf(stderr,"Bad Command or Name/Value too long. Truncating.\n");
				while((c=getchar())!='\n' && c!=' ')
					;
			}
		}
		if(spaces>2){
			fprintf(stderr,"Too many spaces. Skipping input.\n");
			spaces=0;
			pos=0;
			while((c=getchar())!='\n')
				;
		}
		else if(c==' '){
			next[spaces][pos]='\0';
			spaces++;
			pos=0;
		}
		else if(c=='\n'){
			next[spaces][pos]='\0';
			spaces=0;
			pos=0;
			char* comm = next[0];
			if(!strcmp("SET",comm)){
				if(!strcmp(next[1],"") || !strcmp(next[2],"")){
					/*do nothing, bad input*/
					printf("Insufficent arguments to SET\n");
				}else{
					int value = atoi(next[2]);
					upCase(next[1]);
					Data new=dataCreate(next[1],value);
					if(tblock){
						Data old=hashSearch(h,next[1]);
						if(old!=NULL){
							stackPush(s,old);
						}else{
							/*variable not previously stored*/
							Data zero=nullValCreate(next[1]);
							stackPush(s,zero);
							dataDelete(zero);
						}
					}
					hashInsert(h,new,next[1]);
					dataDelete(new);
				}	
			}else if(!strcmp("GET",comm)){
				if(!strcmp(next[1],"")){
					/*do nothing, bad input*/
					printf("Insufficent arguments to GET\n");
				}else{
					upCase(next[1]);
					Data old = hashSearch(h,next[1]);
					if(old && dataVal(old)){
						printf("%d\n",getDataVal(old));
					}else
						printf("NULL\n");
				}		
			}else if(!strcmp("END",comm)){
				hashDestroy(h);
				stackDestroy(s);
				return 0;
			}else if(!strcmp("BEGIN",comm)){
				tblock = 1;
				Data d = dataCreate("BEGIN",0);
				stackPush(s,d);
				dataDelete(d);
			}else if(!strcmp("ROLLBACK",comm)){
				Data d;
				while((d = stackPop(s))){
					if(!strcmp(getDataKey(d),"BEGIN")){
						dataDelete(d);
						break;
					}else{
						hashInsert(h,d,getDataKey(d));
						dataDelete(d);
					}
				}
				if(d==NULL)
					printf("INVALID ROLLBACK\n");
			}else if(!strcmp("COMMIT",comm)){
				stackDestroy(s);
				s=stackCreate();
			}else if(!strcmp("UNSET",comm)){
				if(!strcmp(next[1],"")){
					/*do nothing, bad input*/
					printf("Insufficent arguments to UNSET\n");
				}else{
					upCase(next[1]);
					Data old = hashSearch(h, next[1]);
					if(old!=NULL && dataVal(old)){
						if(tblock){
							stackPush(s,old);
						}
						Data zero=nullValCreate(next[1]);
						hashInsert(h,zero,next[1]);
						dataDelete(zero);
					}else{
						printf("Variable already NULL\n");
					}
				}
			}
			else
				fprintf(stderr,"Invalid command\n");
		}else{
			next[spaces][pos++]=c;
		}
	}
	/*exit without END*/
	hashDestroy(h);
	stackDestroy(s);
	return 0;		
}





