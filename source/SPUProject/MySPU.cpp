#include "../../headers/HeaderForStacks.h"

int ProcessorInit(processor_t* prc, size_t capacity)
{
    StackInit(&(prc -> stk), capacity + 2);
    prc -> ip = 0;
    prc -> size = 0;
    prc -> code = NULL;
    prc -> ERR = OK;
    prc -> RAM = (int *)calloc(RAMSIZE, sizeof (int));
    StackInit(&prc -> addrs, 10);
    return OK;
}

int ReadCode(processor_t* prc, const char* file)
{
    FILE *fp = OpenFile(file, "rb");
    size_t filesize = FileSize(fp);
    PRU(filesize);
    prc -> code = (int *) calloc(filesize, sizeof (int));
    PRP(prc -> code);
    size_t i = 0;
    while (fscanf(fp, "%d", &(prc -> code[i])) != EOF) {i++;}
    prc -> size = i;
    return OK;
}

// int DoPush(processor_t *prc, int operation);
// int DoPop(processor_t *prc, int operation);
// int DoSqrt(processor_t *prc);
// int DoHlt(processor_t *prc);
// int DoOut(processor_t *prc);
// int DoJb(processor_t *prc, int operation);
// int DoRet(processor_t *prc);
// int DoCall(processor_t *prc);

int SPU(processor_t* prc, const char* file)
{
    ReadCode(prc, file);

    for (prc -> ip = 0; prc -> ip < prc -> size;) {
        switch (prc -> code[prc -> ip]) {
            case ADD: DO_ARIFMETIC(prc, +); break;
            case SUB: DO_ARIFMETIC(prc, -); break;
            case MUL: DO_ARIFMETIC(prc, *); break;
            case DIV: DO_ARIFMETIC(prc, /); break;
            case IN:
            {
                int i = 0;
                SPU_PRINT("doing in...\n");
                scanf("%d", &i);
                StackPush(&prc -> stk, i); 
                prc -> ip += 2;
                break;
            }
            case PUSH:
            {
                SPU_PRINT("doing push %d\n", prc -> code[prc -> ip + 1]);
                StackPush(&prc -> stk, prc -> code[prc -> ip + 1]); 
                prc -> ip += 2; 
                passerted(prc); 
                break;
            }
            case SQRT:
            {
                SPU_PRINT("doing sqrt...\n");
                int x1 = StackPop(&prc -> stk);
                if (x1 < 0) {printf(RED "WE CAN'T SQRT IF < 0\n" WHITE);}
                else {StackPush(&prc -> stk, (int)sqrt(x1));}
                passerted(prc); 
                prc -> ip++;
                break;
            }
            case OUT:
            {
                SPU_PRINT("doing out...\n");
                printf(PURPLE "result = %d\n" WHITE, StackPop(&prc -> stk));
                prc -> ip++;
                passerted(prc); 
                break;
            }
            case HLT:
            {
                SPU_PRINT("doing hlt...\n");
                passerted(prc); 
                return OK;
                break;
            }
            case POPR:
            {
                SPU_PRINT("doing popr...\n");
                int x1 = StackPop(&prc -> stk);
                SPU_PRINT("x1 = %d\n", x1);
                prc -> regs[prc -> code[prc -> ip + 1] - 'A' + 1] = x1;
                SPU_PRINT("prc -> regs[prc -> code[prc -> ip + 1] - 'A' + 1] = %d\n", prc -> regs[prc -> code[prc -> ip + 1] - 'A' + 1]);
                prc -> ip += 2;
                break;
            }
            case PUSHR:
            {
                SPU_PRINT("doing pushr %d\n", prc -> regs[prc -> code[prc -> ip + 1] - 'A' + 1]);
                int x1 = prc -> regs[prc -> code[prc -> ip + 1] - 'A' + 1];
                StackPush(&prc -> stk, x1);
                prc -> ip += 2;
                break;
            }
            case JB: //firstly push x //x1 = x; x2 - stack value //if x2 < x1
            {
                SPU_PRINT("doing jb...\n");
                int x1 = StackPop(&prc -> stk);
                int x2 = StackPop(&prc -> stk);
                if (x2 < x1) {
                    prc -> ip = size_t(prc -> code[prc -> ip + 1]);
                }
                StackPush(&prc-> stk, x2);
                StackPush(&prc-> stk, x1);
                break;
            }
            case CALL:
            {
                SPU_PRINT("doing call...\n");
                StackPush(&prc -> addrs, (int)prc -> ip + 2);
                prc -> ip = (size_t)prc -> code[prc -> ip + 1];
                break;
            }
            case RET:
            {
                SPU_PRINT("doing ret...\n");
                prc -> ip = (size_t)StackPop(&prc -> addrs);
                break;
            }
            default:
                printf("Must be a typo in your file.\n");
                PRC_DUMP(prc);
                exit(0);
                break;
        }
        passerted(prc); 
    }
    passerted(prc); 
    return OK;
}

int ProcessorVerify(processor_t* prc)
{
    prc -> ERR |= StackVerify(&prc -> stk);
    if (!(prc -> code))
        prc -> ERR |= WRONGCODEPTR;
    if (prc -> ip > prc -> size)
        prc -> ERR |= WRONGPRCIP;

    return prc -> ERR;
}

int ProcessorDestroy(processor_t* prc)
{
    StackDestroy(&(prc -> stk));
    free(prc -> code);
    StackDestroy(&prc -> addrs);
    free(prc -> RAM);
    return OK;
}

int ProcessorDump(processor_t *prc, const char *file, const char *func, int line)
{
    printf(BLACKFONE RED "\n");
    printf("ProcessorDump called from %s:%d in function %s()\n", file, line, func);
    switch(prc -> ERR) {
        case OK: 
            PRPRINT(OK);
        case WRONGSTKPTR: 
            PRPRINT(WRONGSTKPTR);
        case WRONGSIZE: 
            PRPRINT(WRONGSIZE);
        case WRONGCANARY1: 
            PRPRINT(WRONGCANARY1);
        case WRONGCANARY2: 
            PRPRINT(WRONGCANARY2);
        case WRONGCODEPTR: 
            PRPRINT(WRONGCODEPTR);
        case WRONGPRCIP: 
            PRPRINT(WRONGPRCIP);
        default: 
            PRPRINT(UNKNOWN);
    }
    printf("prc [%p]\n", prc);
    printf(".size = %lu,\n.code = %p,\n.ip = %lu\n", prc -> size, prc -> code, prc -> ip);
    for (size_t i = 0; i < prc -> size; i++) {
        printf("[%02lu] = %d\n", i, prc -> code[i]);
    }
    printf("REGS:\t");
    for (size_t i = 0; i < 5; i++) {
        printf("%d ", prc -> regs[i]);
    }
    printf("\n"WHITE);
    StackDump(&prc -> stk, file, func, line);
    StackDump(&prc -> addrs, file, func, line);
    
    return OK;
}
