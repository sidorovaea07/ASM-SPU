#ifndef ptrswork
#define ptrswork
#include "StrFunc.h"
#include "StructOnE.h"

ptrs *CreatePtrArr(size_t linescnt, char * buff);
size_t LinesCnt(char * buff);
int PtrsPrint(ptrs* ptrsarr, size_t linescnt);

#endif