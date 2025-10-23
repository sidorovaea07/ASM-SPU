#include "../../headers/HeaderForStacks.h"

int main()
{  
    assembler_t ass1 = {};
    ASMInit(&ass1);
    LoadCode("txt/new.txt", &ass1);
    for (size_t i = 0; i <= ass1.ip; i++) {SPU_PRINT("%d\n", ass1.code[i]);}
    CodeToFile(&ass1, "txt/bytecode.txt");
    ASMDestroy(&ass1);
    printf(PURPLE"finish\n"WHITE);
    return 0;
}