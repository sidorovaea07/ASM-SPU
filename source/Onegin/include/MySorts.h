#ifndef bubblesorts
#define bubblesorts

#include "StrFunc.h"
#include "StructOnE.h"

struct ptrs* MySort(struct ptrs *ptrsarr, size_t linescnt);
struct ptrs* MyRevSort(struct ptrs *ptrsarr, size_t linescnt);
int MyComparator1(const void* par1, const void* par2);
int MyComparator2(const void* par1, const void* par2);

#endif