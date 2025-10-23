#ifndef mystruct
#define mystruct
#include "include/StructOnE.h"
#include "include/FileWork.h"
#include "include/PtrsWork.h"
int Init(struct Data* data)
{
    data -> input = "";
    data -> linescnt = 0;
    data -> buff = NULL;
    data -> size = 0;
    return 0;
}

int FileProcess(struct Data* data, const char* name)
{
    data -> input = name;
    data -> buff = ReadFile(data -> input, &data -> size);
    data -> linescnt = LinesCnt(data -> buff);
    for (size_t i = 0; i < total; i++) {
        data -> arrs[i] = CreatePtrArr(data -> linescnt, data -> buff);
    }
    // printf(YCOLOR"IN FILE PROCESS: \n"WCOLOR);
    // PRP(data -> buff);
    // PRD(data -> size);
    // PRD(data -> linescnt);
    // PtrsPrint(data -> arrs[prim], data -> linescnt);
    // puts(data -> buff);
    return 0;
}
int Switch(ptrs *p1, ptrs *p2)
{
    char* temp = p1 -> val;
    p1 -> val = p2 -> val;
    p2 -> val = temp;

    size_t t = p1 -> len;
    p1 -> len = p2 -> len;
    p2 -> len = t;
    return 0;
}

int Free(struct Data *data)
{
    free(data -> buff);
    for (size_t i = 0; i < total; i++) {
        free(data -> arrs[i]);
    }
    return 0;
}
#endif