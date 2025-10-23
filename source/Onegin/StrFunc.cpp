#include "include/StrFunc.h"

int myputs (char *s)
{
    if (!s)
        return EOF;
    char *save_ptr = s;
    while (*s != '\0' && *s != '\n') {
        putchar(*(s++));
    }
    putchar('\n');
    s = save_ptr;
    return 0;
}

char* mystrchr (char * s, int c)
{
    //const char *save_ptr = s;
    while (*s != '\0') {
        if (*s == c)
        {
            return s;
        }
        s++;
    }
    if (!c) {
        return s;
    }
    return NULL;
}

size_t mystrlen (const char * s)
{
    //const char *save_ptr = s;
    size_t cnt = 0;
    while (*(s++) != '\0') {
        cnt++;
    }
    s -= cnt;
    return cnt;
}

char* mystrcat (char * s1, const char * s2)
{
    char *save_ptr1 = s1; 
    //const char *save_ptr2 = s2; 

    while (*s1 != '\0') {
        s1++;
    }
    while (*s2 != '\0') {
        *(s1++) = *(s2++);
    }
    *s1 = '\0';
    return save_ptr1;
}

char *mystrncat (char * s1, const char * s2, size_t n)
{
    char *save_ptr1 = s1;
    //const char *save_ptr2 = s2;

    size_t i = 0;
    while (*s1 != '\0') {
        s1++;
    }
    
    while (*s2 != '\0' && i++ != n) {
        *s1++ = *s2++;
    }

    *s1 = '\0';

    return save_ptr1;
}

int myatoi(const char * s)
{
    //const char * save_ptr = s;
    int ans = 0;
    while (isspace(*s)) {
        s++;
    }
    while (isdigit(*s)) {
        ans = ans * 10 + (*s++ - '0');
    }
    return ans;
}

char * myfgets(char *s, int n, FILE *fp)
{
    char *save_ptr = s;
    for (int i = 0; i < n; i++) {
        if ((*s = (char) fgetc(fp)) == EOF || *s == '\n') {
            *s = '\0';
            return save_ptr;
        }
        s++;
    }
    return NULL;
}

char *mystrdup(char *s)
{
    //char * save_ptr1 = s;
    char * ptr = (char *) calloc(sizeof (char), mystrlen(s) + 1);
    char * save_ptr2 = ptr;
    while (*s != '\0') {
        *ptr++ = *s++;
    }
    *ptr = '\0';
    return save_ptr2;
}

int mygetline(char **lineptr, size_t *n, FILE *fp)
{
    char *save_ptr = *lineptr;
    if (!(*lineptr))
        *lineptr = (char *) calloc(sizeof (char), *n);
    **lineptr = (char) fgetc(fp);
    size_t cnt = 1;
    while (**lineptr != '\0' && **lineptr != EOF) 
    {    
        putchar((int)**lineptr);
        
        if (**lineptr == '\n')
            return (int) cnt - 1;
        
        (*lineptr)++;

        if (cnt == *n) {
            *n = *n * *n;
            *lineptr = (char *) realloc(save_ptr, *n);
            //assert(*lineptr);
        }

        **lineptr = (char) fgetc(fp);
        cnt++;
    }
    if ((**lineptr == '\0'))
        return (int) cnt - 1;
    
    return EOF;

}

int mystrcmp(const char* s1,const char* s2)
{
    // PUSH
    // push
    const char* save_ptr1 = s1;
    const char* save_ptr2 = s2;
    int ans = 0;
    while (*s1 != '\n' && *s2 != '\n' && *s1 != '\0' && *s2 != '\0')
    {
        while (!isalpha(*s1)) {
            s1++;
        }
        while (!isalpha(*s2)) {
            s2++;
        }
        if (tolower(*s1) < tolower(*s2))
            return -1;
        else if (tolower(*s1) > tolower(*s2))
            return 1;
        else {
            s1++;
            s2++;
        }
    }
    if (*s1 == '\n' && *s2 == '\n') {
        ans = 0;
    }
    else if (*s1 == '\n') {
        ans = -1;
    }
    else {
        ans = 1;
    }
    s1 = save_ptr1;
    s2 = save_ptr2;
    return ans;
}

int myrevstrcmp(const char * s1, const char * s2)
{
    const char * save_ptr1 = s1;
    const char * save_ptr2 = s2;
    int ans = 0;
    while (*s1 != '\n') {s1++;}
    while (*s2 != '\n') {s2++;}
    while (!isalpha(*s1)) {s1--;}
    while (!isalpha(*s2)) {s2--;}
    if (s2 == save_ptr2)
        return 1;
    if (s1 == save_ptr1)
        return -1;
    while (s1 != save_ptr1 && s2 != save_ptr2)
    {
        if (tolower(*s1) < tolower(*s2))
            return -1;
        else if (tolower(*s1) > tolower(*s2))
            return 1;
        else {
            s1--;
            s2--;
        }
    }
    if (s1 == save_ptr1) {
        ans = -1;
    }
    else if (s2 == save_ptr2) {
        ans = 1;
    }
    return ans;
}