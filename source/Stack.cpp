#include "../headers/HeaderForStacks.h"

int StackInit(stack_t *stk, size_t capacity)
{
    stk -> data = (int *)calloc(capacity + 2, sizeof(int));
    stk -> size = 1;
    stk -> capacity = capacity;
    stk -> data[0] = CANARY1;
    stk -> data[stk -> capacity + 1] = CANARY2;
    stk -> ERR = 0;
    for (size_t i = (stk -> size); i <= (stk -> capacity); i++) {
        stk -> data[i] = POISON;
    }
    asserted(stk);
    return OK;
}

int StackVerify(stack_t *stk)
{
    if (!stk)
        stk -> ERR |= WRONGSTKPTR;
    if (stk -> size - 1 > stk -> capacity)
        stk -> ERR |= WRONGSIZE; 
    if (stk -> data[0] != CANARY1)
        stk -> ERR |= WRONGCANARY1;
    if (stk -> data[stk -> capacity + 1] != CANARY2)
        stk -> ERR |= WRONGCANARY2;
    for (size_t i = stk -> size; i < stk -> capacity; i++) {
        if (stk -> data[i] != POISON) {
            stk -> ERR |= WRONGDATAOPERATIONS;
        }
    }
    return stk -> ERR;
}

int StackDump(stack_t *stk, const char *file, const char* func, int line)
{
    printf(BLACKFONE RED "\n");
    printf("StackDump called from %s:%d in function %s()\n", file, line, func);
    if (stk -> ERR == OK)
        STPRINT(OK);
    if (((1 << 0) & stk -> ERR))
        STPRINT(WRONGSTKPTR);
    if (((1 << 1) & stk -> ERR))
        STPRINT(WRONGSIZE);
    if (((1 << 2) & stk -> ERR))
        STPRINT(WRONGREALLOCATION);
    if (((1 << 3) & stk -> ERR))
        STPRINT(WRONGCANARY1);
    if (((1 << 4) & stk -> ERR))
        STPRINT(WRONGCANARY2);
    if (((1 << 5) & stk -> ERR))
        STPRINT(WRONGDATAOPERATIONS);
    
    printf("Stack [%p]\n", stk);
    printf(".size = %lu,\n.capacity = %lu,\n.data = %p\n", stk -> size - 1, stk -> capacity, stk -> data);
    printf("canary1 = %x, canary2 = %x\n", (unsigned int) stk -> data[0], (unsigned int) stk -> data[stk -> capacity + 1]);
    for (size_t i = 1; i < stk -> capacity + 1; i++) {
        if (i < stk -> size) {
            printf("*[%02lu] = %d\n", i, stk -> data[i]);
        }
        else
            printf("[%02lu] = %x\n", i, (unsigned int)stk -> data[i]);
    }
    printf(WHITE);
    return OK;
}

int InputProcess(stack_t *stk)
{
    char desire[10] = "";
    int t = 0;
    int N = 0;
    printf(YELLOW "How many operations do you want to do?\n" WHITE);
    scanf("%d", &N);
    for (int i = 0; i < N; i++) 
    {
        asserted(stk);
        printf(YELLOW "Enter PUSH ADD SUB MUL DIV SQRT OUT PRINT HLT.\n" WHITE);
        scanf("%s", desire);

        if (!strcmp(desire, "PUSH")) {
            scanf("%d", &t);
            StackPush(stk, t);
            asserted(stk);
        }
        else if (!strcmp(desire, "ADD"))
        {
            int x1 = StackPop(stk);
            int x2 = StackPop(stk);
            StackPush(stk, x2 + x1);
            asserted(stk);
        }
        else if (!strcmp(desire, "SUB"))
        {
            int x1 = StackPop(stk);
            int x2 = StackPop(stk);
            StackPush(stk, x2 - x1);
            asserted(stk);
        }
        else if (!strcmp(desire, "MUL"))
        {
            int x1 = StackPop(stk);
            int x2 = StackPop(stk);
            StackPush(stk, x2 * x1);
            asserted(stk);
        }
        else if (!strcmp(desire, "DIV"))
        {
            int x1 = StackPop(stk);
            if (x1 == 0) {printf("we can't div on null\n"); break;}
            int x2 = StackPop(stk);
            StackPush(stk, x2 / x1);
            asserted(stk);
        }
        else if (!strcmp(desire, "SQRT"))
        {
            int x1 = StackPop(stk);
            StackPush(stk, (int)sqrt((int)x1));
            asserted(stk);
        }
        else if (!strcmp(desire, "OUT"))
        {
            printf("%d\n", StackPop(stk));
            asserted(stk);
        }
        else if (!strcmp(desire, "PRINT"))
        {
            StackDump(stk, __FILE__, __FUNCTION__, __LINE__);
            asserted(stk);
        }
        else if (!strcmp(desire, "HLT"))
        {
            i = N;
            asserted(stk);
        }
        else
        {
            printf(YELLOW "Wrong comand\n" WHITE);
        }
    }
    asserted(stk);
    return OK;
}

int StackPush(stack_t *stk, int val)
{
    StackReallocation(stk);
    stk -> data[stk -> size++] = val;
    asserted(stk);
    return OK;
}

int StackPop(stack_t *stk)
{
    int ans = stk -> data[stk -> size - 1]; 
    stk -> data[stk -> size - 1] = POISON;
    stk -> size--;
    asserted(stk);
    return ans;
}

int StackDestroy(stack_t *stk)
{
    free(stk -> data);
    return OK;
}

int StackReallocation(stack_t *stk) 
{
    while (stk -> capacity <= stk -> size) {
        stk -> data[stk -> capacity + 1] = POISON;
        stk -> capacity *= 2;
        stk -> data = (int *)realloc(stk -> data, (stk -> capacity + 2)*(sizeof (int)));
        //PRP(stk -> data);
        //PRU(stk -> capacity);
        if (!stk -> data) stk -> ERR |= WRONGREALLOCATION;
        for (size_t i = stk -> size; i <= stk -> capacity; i++) {
            stk -> data[i] = POISON;
        }
        stk -> data[stk -> capacity + 1] = CANARY2;
        asserted(stk);
    }
    return OK;
}
