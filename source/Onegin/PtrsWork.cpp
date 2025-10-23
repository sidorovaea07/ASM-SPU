#include "include/PtrsWork.h"
#include "include/StrFunc.h"

size_t LinesCnt(char* buff)
{
    char* save_ptr = buff;
    size_t cnt = 0;
    //putchar(*buff);
    while (!isalpha(*buff)) {buff++;}
    while (*buff != '\0') {
        char* new_buff = mystrchr(buff, '\n');
        //PRP(*new_buff);
        if (new_buff != NULL) {
            if (AlphasCheck(new_buff + 1)) {
                cnt++;
                //PRD(cnt);
            }
            buff = new_buff + 1;
        }
        else break;
    }
    buff = save_ptr;
    //PRD(cnt + 1);
    return cnt + 1;
}

size_t MyLen(char* s1, char* s2)
{
    size_t len = 0;
    char* save_ptr1 = s1;
    char* save_ptr2 = s2;
    while (s1 != s2)
    {
        s1++;
        len++;
    }
    s1 = save_ptr1;
    s2 = save_ptr2;
    return len + 1;
}

int AlphasCheck(char * s)
{
    char* save_ptr = s;
    int alphas = 0;
    while (*s != '\n' && *s != '\0') {
        if (isalpha(*s))
            alphas++;
        s++;
    }
    s = save_ptr;
    if (!alphas)
        return 0;
    else
        return 1;
}

ptrs *CreatePtrArr(size_t linescnt, char* buff)
{
    char* save_ptr = buff;
    ptrs* ptrsarr = (ptrs* )calloc(linescnt, sizeof(ptrs));
    //PRP(ptrsarr);
    if (!ptrsarr)
        return NULL;
    ptrs* save_ptr2 = ptrsarr;
    // printf("buff in create ");
    // PRP(buff);
    size_t i = 0;
    char* new_buff = NULL;
    while (!isalpha(*buff)) {buff++;}
    ptrsarr[i].val = buff;
    new_buff = mystrchr(buff, '\n');
    
    if (new_buff != NULL) {
        ptrsarr[i].len = (size_t)(new_buff + 1 - ptrsarr[i].val);
    }
    else {
        printf("bad buff\n");
    }
    while (i < linescnt) {
        new_buff = mystrchr(buff, '\n');
        if (new_buff != NULL) {
            ptrsarr[i].len = size_t(new_buff + 1 -ptrsarr[i].val);
            if (AlphasCheck(new_buff + 1)) {
                i++;
                buff = ptrsarr[i].val = new_buff + 1;
                ptrsarr[i].len = size_t(mystrchr(buff, '\n') + 1 - ptrsarr[i].val);
                //PRD(ptrsarr[i].len);
            }
            else
                buff = new_buff + 1;
        }
        else {
            break;
        }
    }
    buff = save_ptr;
    return save_ptr2;
}

int PtrsPrint(ptrs* ptrsarr, size_t linescnt)
{
    ptrs* save_ptr = ptrsarr;
    for (size_t i = 0; i < linescnt; i++) {
        for (size_t j = 0; j < ptrsarr[i].len; j++) {
            putchar(ptrsarr[i].val[j]);
        }
        PRP(&ptrsarr[i]);
    }
    ptrsarr = save_ptr;
    return 0;
}