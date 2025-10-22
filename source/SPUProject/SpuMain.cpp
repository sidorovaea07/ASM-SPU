#include "../../headers/HeaderForStacks.h"

int main()
{  
    processor_t prc1 = {};
    ProcessorInit(&prc1, 1);
    SPU(&prc1, "txt/bytecode.txt");
    PRC_DUMP(&prc1);
    ProcessorDestroy(&prc1);
    printf("finish\n");
    return 0;
}