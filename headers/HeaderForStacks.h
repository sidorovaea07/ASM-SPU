#ifndef STACKSHEADER
#define STACKSHEADER

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <math.h>
#include "../../../2Dmas/evgene/include/FileWork.h"
#include "../../../2Dmas/evgene/include/PtrsWork.h"
   
#define PRPRINT(x) printf("ProcessorVerify returned " #x"\n"); break;
#define STPRINT(x) printf("StackVerify returned " #x"\n");

#undef PRP
#undef PRD
#undef PRU
#undef PRTF

//#define DEBUG

#ifdef DEBUG
    #define SPU_PRINT(fmt, ...) printf(YELLOW fmt WHITE, ##__VA_ARGS__ )
    #define SPU_CMNDPRINT(x) printf(YELLOW "doing " #x "...\n" WHITE)
    #define asserted(x)                                             \
        do {                                                        \
            int err_code = StackVerify(x);                          \
            if (err_code != OK)                                     \
                StackDump((x), __FILE__, __FUNCTION__, __LINE__);   \
        } while (0)

    #define passerted(x)                                            \
        do {                                                        \
            int err_code = ProcessorVerify(x);                      \
            if (err_code != OK)                                     \
                ProcessorDump((x), __FILE__, __FUNCTION__, __LINE__);\
        } while (0)
    #define PRC_DUMP(x)         \
        ProcessorDump((x), __FILE__, __FUNCTION__, __LINE__);
    #define PRP(x) printf(PURPLE #x " pointer: %p\n" WHITE, (x))
    #define PRD(x) printf(BLUE #x " = %d\n" WHITE, (x))
    #define PRU(x) printf(BLUE #x " = %lu\n" WHITE, (x))
    #define PRTF(x) printf(PURPLE "print to file returned %d\n" WHITE, (x))
#else
    #define SPU_PRINT(fmt, ...)
    #define asserted(x)                                             
    #define passerted(x)
    #define PRC_DUMP(x)
    #define SPU_CMNDPRINT(x)
    #define PRP(x)
    #define PRD(x)
    #define PRU(x)
    #define PRTF(x)                                      
#endif

#define DO_ARIFMETIC(prc, y)                                        \
    do {                                                            \
        SPU_CMNDPRINT(y);                                           \
        int x1 = StackPop(&prc -> stk);                             \
        int x2 = StackPop(&prc -> stk);                             \
        if (x1 == 0 && #y[0] == '/') {printf("WE CAN'T DIV ON NULL\n");}\
        StackPush(&prc -> stk, x2 y x1);                            \
        passerted(prc);                                             \
        prc -> ip++;                                                \
    } while (0)                         

#define RAMSIZE 100
typedef const int canary;
const int POISON = 0xdeadbee;
canary CANARY1 = 0xc0cca;
canary CANARY2 = 0x5055a;

typedef struct stack_t
{
    int *data;
    size_t size;
    size_t capacity;
    int ERR;
} stack_t;

typedef struct assembler_t
{
    int* code;
    char* buff;
    size_t lines;
    char** arr;
    int ERR;
    int* labels;
    size_t ip;
    size_t size;
    size_t readsize;
} assembler_t;

typedef struct processor_t
{
    stack_t stk;
    int* code;
    size_t size;
    size_t ip;
    int ERR;
    int regs[5];
    int* labels;
    stack_t addrs;
    int* RAM;
} processor_t;

enum errors_t
{
    OK = 0,
    WRONGSTKPTR = 1,
    WRONGSIZE = 2,
    WRONGREALLOCATION = 4,
    WRONGCANARY1 = 8,
    WRONGCANARY2 = 16,
    WRONGDATAOPERATIONS = 32,
    WRONGCODEPTR = 64,
    WRONGPRCIP = 128,
};

enum comands_t
{
    PUSH = 1,
    ADD,
    SUB,
    MUL,
    DIV,
    SQRT,
    OUT,
    POP,
    HLT,
    IN,
    UNKNOWN,
    PUSHR = 32,
    POPR,
    PUSHM,
    POPM,
    JB = 50,
    JMP,
    LB,
    CALL,
    RET,
};

int StackInit(stack_t *stk, size_t capacity);
int StackPush(stack_t *stk, int val);
int StackPop(stack_t *stk);
int StackVerify(stack_t *stk);
int StackDump(stack_t *stk, const char *file, const char* func, int line);
int StackDestroy(stack_t *stk);
int StackReallocation(stack_t *stk);

int ASMInit(assembler_t* ass);
int InputProcess(stack_t *stk);
int ReadCode(const char* file, assembler_t *ass);
size_t CodeLinesCnt(char* buff);
char** CreateCodePtrArr(size_t linescnt, size_t readsize, char* buff);
int LoadCode(const char* file, assembler_t *ass);
int CodeToFile(assembler_t *ass, const char *file);
int ASMDestroy(assembler_t* ass);

int ProcessorInit(processor_t *prc, size_t capacity);
int ProcessorVerify(processor_t *prc);
int ProcessorDump(processor_t *prc, const char *file, const char* func, int line);
int ProcessorDestroy(processor_t *prc);
int ReadCode(processor_t *prc, const char *file);
int SPU(processor_t *prc, const char* file);

int WhatCommand(char* cmnd);
// int DoArifmetic(processor_t *prc, int operation);
// int DoPush(processor_t *prc, int operation);
// int DoPop(processor_t *prc, int operation);
// int DoSqrt(processor_t *prc);
// int DoHlt(processor_t *prc);
// int DoOut(processor_t *prc);
// int DoJb(processor_t *prc, int operation);
// int DoRet(processor_t *prc);
// int DoCall(processor_t *prc);

int DoPush(assembler_t *ass, const char* ch);
int DoPop(assembler_t *ass, const char* ch);

#endif
