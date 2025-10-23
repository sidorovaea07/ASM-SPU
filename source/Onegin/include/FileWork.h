#ifndef filework
#define filework

#include "StrFunc.h"
#include "StructOnE.h"

size_t FileSize(FILE *fp);
char* ReadFile(const char* myfile, size_t* ReadSize);
FILE* OpenFile(const char *myfile, const char *mode);
int PrintToFile(ptrs* ptrsarr, size_t linescnt);

#endif