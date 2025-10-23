#include "include/MySorts.h"

ptrs* MySort(ptrs *ptrsarr, size_t linescnt)
{
    ptrs* save_ptr = ptrsarr;
    for (size_t i = 0; i < linescnt - 1; i++) {
        for (size_t j = 0; j < linescnt - i - 1; j++) {
            if (mystrcmp(ptrsarr[j].val, ptrsarr[j + 1].val) > 0) {
                Switch(&ptrsarr[j], &ptrsarr[j + 1]);
            }
        }
    }
    ptrsarr = save_ptr;
    return ptrsarr;
}

ptrs* MyRevSort(ptrs* ptrsarr, size_t linescnt)
{
    ptrs* save_ptr = ptrsarr;
    for (size_t i = 0; i < linescnt - 1; i++) {
        for (size_t j = 0; j < linescnt - i - 1; j++) {
            if (myrevstrcmp(ptrsarr[j].val, ptrsarr[j + 1].val) > 0) {
                Switch(&ptrsarr[j], &ptrsarr[j + 1]);
            }
        }
    }
    ptrsarr = save_ptr;
    return ptrsarr;
}

int MyComparator1(const void* par1, const void* par2)
{
    //const void* -> const (type) * 
    // PRP(par1);
    // PRP(par2);
    const char* par11 = *(const char**)par1;
    const char* par22 = *(const char**)par2; // const 
    // PRP(par11);
    // PRP(par22);
    // puts(par11);
    // puts(par22);
    return mystrcmp(par11, par22);
}

int MyComparator2(const void* par1, const void* par2)
{
    // PRP(par1);
    // PRP(par2);
    const char* par11 = *(const char**)par1;
    const char* par22 = *(const char**)par2; // const 
    // PRP(par11);
    // PRP(par22);
    // puts(par11);
    // puts(par22);
    return myrevstrcmp(par11, par22);
}

