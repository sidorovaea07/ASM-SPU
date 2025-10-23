#include "include/StructOnE.h"
#include "include/MySorts.h"
#include "include/StrFunc.h"
#include "include/FileWork.h"
#include "PtrsWork.h"

#include <stdio.h>
int main()
{
    struct Data OnE = {};
    Init(&OnE);
    FileProcess(&OnE, "onegfromkr.txt");
    MySort(OnE.arrs[sorted], OnE.linescnt);
    MyRevSort(OnE.arrs[revsorted], OnE.linescnt);
    qsort(OnE.arrs[qsorted], OnE.linescnt, sizeof(OnE.arrs[prim][0]), &MyComparator1);
    qsort(OnE.arrs[qrevsorted], OnE.linescnt, sizeof(OnE.arrs[prim][0]), &MyComparator2);
    
    for (size_t i = 0; i < total; i++) {
        PRTF(PrintToFile(OnE.arrs[i], OnE.linescnt));
    }

    Free(&OnE);
    printf(RED "finish\n" WHITE);
    return 0;
}