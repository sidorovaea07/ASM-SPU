#ifndef strfunc
#define strfunc
#include "StructOnE.h"

size_t MyLen(char* s1, char* s2);
int AlphasCheck (char* s);
int mystrcmp(const char* s1, const char* s2);
int myputs (char* s);
int myrevstrcmp(const char* s1, const char* s2);
char* mystrchr (char* s, int c);
size_t mystrlen (const char* s);
char* mystrcat (char* s1, const char* s2);
char* mystrncat (char* s1, const char* s2, size_t n);
int myatoi(const char* nptr);
char* myfgets(char* str, int num, FILE* stream);
char* mystrdup(char* str);
int mygetline(char** lineptr, size_t* n, FILE* stream);  

#endif