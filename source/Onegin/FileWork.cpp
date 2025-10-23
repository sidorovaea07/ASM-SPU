#include "include/FileWork.h"

size_t FileSize(FILE *fp)
{
    fseek(fp, 0L, SEEK_END);
    size_t size = (size_t)ftell(fp);
    fseek(fp, 0L, SEEK_SET);
    return size;
}

FILE* OpenFile(const char *myfile, const char *mode)
{
    FILE *fp = fopen(myfile, mode);
    if (!fp) {
        printf(RED "ERROR WHILE OPENING THE FILE: %s.\n" WHITE, myfile);
        return NULL;
    }
    return fp;

}

char* ReadFile(const char* myfile, size_t* readsize)
{
    FILE *fp = OpenFile(myfile, "rb");
    //PRP(fp);
    size_t filesize = FileSize(fp);
    // printf("FILESIZE = ");
    // PRP(filesize);
    char *buff = (char *) calloc(filesize + 3, sizeof (char));
    *readsize = fread(buff, sizeof (char), filesize, fp);
    // printf("readSIZE = ");
    // PRD(*readsize);
    buff[*readsize] = '\n';
    //buff[*readsize + 1] = '\n';
    buff[*readsize + 1] = '\0';
    fclose(fp);
    return buff;
}

int PrintToFile(ptrs* ptrsarr, size_t linescnt)
{
    ptrs* save_ptr = ptrsarr;
    FILE *fp = OpenFile("newoutputfile.txt", "a+");
    for (size_t i = 0; i < linescnt; i++) {
        fwrite(ptrsarr[i].val, sizeof(char), ptrsarr[i].len, fp);
    }
    fputs("----------\n", fp);
    fclose(fp);
    ptrsarr = save_ptr;
    return 0;
}


