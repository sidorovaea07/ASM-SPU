#ifndef STRUCT_ONE
#define STRUCT_ONE

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <limits.h>
#include <math.h>

#define PURPLE "\033[35m"
#define WHITE "\033[0m"
#define GREY "\033[90m"
#define BLACKFONE "\033[40m"
#define RED "\033[91m"
#define BLUE "\033[36m"
#define YELLOW "\033[33m"

#define PRP(x) printf(PURPLE #x " pointer: %p\n" WHITE, (x))
#define PRD(x) printf(BLUE #x " = %d\n" WHITE, (x))
#define PRU(x) printf(BLUE #x " = %lu\n" WHITE, (x))
#define PRTF(x) printf(PURPLE "print to file returned %d\n" WHITE, (x))

struct ptrs {
    char* val;
    size_t len;
};

const size_t total = 5;

enum Sorts {
    prim = 0,
    sorted = 1,
    revsorted = 2,
    qsorted = 3,
    qrevsorted = 4
};

struct Data {
    const char* input;
    char* buff;
    size_t size;
    size_t linescnt;
    struct ptrs* arrs[total];
};

int Init(struct Data* data);
int FileProcess(struct Data* data, const char* name);
int Switch(ptrs* p1, ptrs* p2);
int Free(struct Data* data);

#endif