#include "/mnt/c/Users/Honor/OneDrive/Рабочий стол/C/ASM-SPU/headers/HeaderForStacks.h"

int ASMInit(assembler_t* ass)
{
    ass -> code = NULL;
    ass -> buff = NULL;
    ass -> lines = 0;
    ass -> arr = NULL;
    ass -> ERR = 0;
    ass -> labels = (int *) calloc(10, sizeof(int)); 
    for (size_t i = 0; i < 10; i++) {ass -> labels[i] = -1;}
    ass -> ip = 0;
    ass -> size = 0;
    return 0;
}

int ReadCode(const char* file, assembler_t *ass)
{
    ass -> buff = ReadFile(file, &ass -> lines);
    ass -> readsize = ass -> lines;
    ass -> lines = CodeLinesCnt(ass -> buff);
    ass -> arr = CreateCodePtrArr(ass -> lines, ass -> readsize, ass -> buff);
    ass -> code = (int *) calloc(ass -> readsize, sizeof (int));
    PRP(ass -> code);
    return OK;
}

size_t CodeLinesCnt(char* buff)
{
    char* save_ptr = buff;
    size_t cnt = 0;
    while (*buff != '\0') {
        char* new_buff = strchr(buff, '\n');
        if (new_buff != NULL) {
            cnt++;
            *new_buff = '\0';
            buff = new_buff + 1;
        }
        else break;
    }
    buff = save_ptr;
    PRU(cnt);
    return cnt - 1;
}

char** CreateCodePtrArr(size_t linescnt, size_t readsize, char* buff)
{
    char* save_ptr = buff;
    char** ptrsarr = (char** )calloc(linescnt, sizeof(char*));
    if (!ptrsarr) return NULL;
    char** save_ptr2 = ptrsarr;
    char* new_buff = NULL;
    size_t i = 0;
    ptrsarr[i] = buff;
    while (((new_buff = strchr(buff, '\0')) != NULL) && ((size_t)(new_buff + 1 - save_ptr) <= readsize)) {
        buff = ptrsarr[i] = new_buff + 1;
        buff++;
        i++;
    }
    buff = save_ptr;
    return save_ptr2;
}

int WhatCommand(char* cmnd)
{
    if (!strcmp(cmnd, "PUSH")) return PUSH;
    else if (!strcmp(cmnd, "POP")) return POP;
    else if (!strcmp(cmnd, "ADD")) return ADD;
    else if (!strcmp(cmnd, "SUB")) return SUB;
    else if (!strcmp(cmnd, "MUL")) return MUL;
    else if (!strcmp(cmnd, "DIV")) return DIV;
    else if (!strcmp(cmnd, "SQRT")) return SQRT;
    else if (!strcmp(cmnd, "OUT")) return OUT;
    else if (!strcmp(cmnd, "HLT")) return HLT;
    else if (!strcmp(cmnd, "JB")) return JB;
    else if (!strcmp(cmnd, "JMP")) return JMP;
    else if (!strcmp(cmnd, "CALL")) return CALL;
    else if (!strcmp(cmnd, "RET")) return RET;
    else if (!strcmp(cmnd, "IN")) return IN;
    else if (strchr(cmnd, ':') != NULL) return LB;
    else return UNKNOWN;
}

int DoPush(assembler_t *ass, const char* ch)
{
    char c = 0;
    int i = 0;
    if (sscanf(ch, "R%cX", &c)) {
        ass -> code[ass -> ip++] = PUSHR;
        ass -> code[ass -> ip++] = c;
    }
    else if (sscanf(ch, "[%d]", &i)) {
        ass -> code[ass -> ip++] = PUSHM;
        ass -> code[ass -> ip++] = i;
    }
    else if (sscanf(ch, "%d", &i)){
        ass -> code[ass -> ip++] = PUSH;
        ass -> code[ass -> ip++] = i;
    }
    else {printf(RED "Must be a tipo after PUSH\n" WHITE);}
    return OK;
}

int DoPop(assembler_t *ass, const char* ch)
{
    char c = 0;
    int i = 0;
    if (sscanf(ch, "R%cX", &c)) {
        ass -> code[ass -> ip++] = POPR;
        ass -> code[ass -> ip++] = c;
    }
    else if (sscanf(ch, "[%d]", &i)) {
        ass -> code[ass -> ip++] = POPM;
        ass -> code[ass -> ip++] = i;
    }
    else if (sscanf(ch, "%d", &i)){
        ass -> code[ass -> ip++] = POP;
        ass -> code[ass -> ip++] = i;
    }
    else {printf(RED "Must be a tipo after POP\n" WHITE);}
    return OK;
}

int LoadCode(const char* file, assembler_t *ass)
{
    ReadCode(file, ass);
    char cmnd[100] = {0};
    int i = 0;
    char ch[4] = "";
    for (size_t g = 0; g < 2; g++) {
        ass -> ip = 0;
        for (size_t j = 0; j < ass -> lines; j++) {
            sscanf(ass -> arr[j], "%s", cmnd);
            int interpreted = WhatCommand(cmnd);
            switch(interpreted) {
                case ADD:
                case SUB:
                case MUL:
                case DIV:
                case SQRT:
                case OUT:
                case HLT:
                case RET:
                    ass -> code[ass -> ip++] = interpreted;
                    break;
                case IN:
                    ass -> code[ass -> ip++] = interpreted;
                    ass -> ip++;
                    break;
                case PUSH:
                    sscanf(ass -> arr[j], "%*s %s", ch);
                    DoPush(ass, ch);
                    break;
                case POP:
                    sscanf(ass -> arr[j], "%*s %s", ch);
                    DoPop(ass, ch);
                    break;
                case JB:
                    ass -> code[ass -> ip++] = JB;
                    sscanf(ass -> arr[j], "%*s :%d", &i);
                    ass -> code[ass -> ip++] = ass -> labels[i];
                    break;
                case JMP:
                    ass -> code[ass -> ip++] = JMP;
                    sscanf(ass -> arr[j], "%*s :%d", &i);
                    ass -> code[ass -> ip++] = ass -> labels[i];
                    SPU_PRINT("in JMP:\t");
                    PRD(i);
                    break;
                case LB:
                    sscanf(ass -> arr[j], ":%d", &i);
                    PRD(i);
                    ass -> labels[i] = (int)ass -> ip;
                    break;
                case CALL:
                    ass -> code[ass -> ip++] = CALL;
                    sscanf(ass -> arr[j], "%*s :%d", &i);
                    PRD(i);
                    PRD(ass -> labels[i]);
                    ass -> code[ass -> ip++] = ass -> labels[i];
                    break;
                case UNKNOWN:
                    ass -> code[ass -> ip++] = POISON;
                    printf("Must be a typo in your file in symbol №%lu\n", ass -> ip);
                    break;
                default: printf("Not interpeted comand №%lu\n", ass -> ip); break;
            }
        }
    }
    return OK;
}

int CodeToFile(assembler_t* ass, const char* file)
{
    FILE *fp = OpenFile(file, "wb");
    int printed = 0;
    for (size_t i = 0; i < ass -> ip; i++) {
        printed += fprintf(fp, "%d ", ass -> code[i]);
    }
    PRD(printed);
    return 0;
}

int ASMDestroy(assembler_t* ass)
{
    free(ass -> code);
    free(ass -> arr);
    free(ass -> buff);
    free(ass -> labels);
    return OK;
}