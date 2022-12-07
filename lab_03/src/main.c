#include <stdio.h>
#include "mergesort.h"

#include <string.h>
#include <stdlib.h>

#define NOMEM "Error: memory allocation failed."
#define CHECKMEM if (!array) { puts(NOMEM); return 1; }

typedef int (*Comparator)(const void*, const void*);
typedef void(*Printer)(const void *elem, int last);

// int greater than comparator
int int_comparator(const void *a, const void *b) {
    return *(int*)a - *(int*)b;
}

int str_comparator(const void *a, const void *b) {
    const char **str1 = (const char**)a;
    const char **str2 = (const char**)b;
    
    return strcmp(*str1, *str2);
}


void int_printer(const void *elem, int last) {
    if (last) printf("%d\n", *(int*)elem);
    else printf("%d ", *(int*)elem);
}

void char_printer(const void *elem, int last) {
    if (last) printf("%c\n", *(int*)elem);
    else printf("%c ", *(int*)elem);
}

void str_printer(const void *elem, int last) {
    const char **str = (const char**)elem;
    if (last) printf("%s\n", *str);
    else printf("%s ", *str);
}


int main(int argc, const char * argv[]) {
    if (argc <= 2) return 0;
    
    Printer printer;
    Comparator comparator;
    size_t count = argc - 2;
    size_t elem_size;
    void *array;
    
    if (strcmp(argv[1], "int") == 0) {
        printer = int_printer;
        comparator = int_comparator;
        elem_size = sizeof(int);
        
        array = calloc(count, elem_size);
        CHECKMEM;
        
        for (int i = 0; i < count; ++i) {
            int num = atoi(argv[2 + i]);
            memcpy((char*)array + i * elem_size, &num, elem_size);
        }
        
    } else if (strcmp(argv[1], "char") == 0) {
        printer = char_printer;
        comparator = int_comparator;
        elem_size = sizeof(char);
        
        array = calloc(count, elem_size);
        CHECKMEM;
        
        for (int i = 0; i < count; ++i)
            memcpy((char*)array + i * elem_size, argv[2 + i], elem_size);
        
    } else if (strcmp(argv[1], "str") == 0) {
        printer = str_printer;
        comparator = str_comparator;
        elem_size = sizeof(char*);
        
        array = calloc(count, elem_size);
        CHECKMEM;
        
        for (int i = 0; i < count; ++i)
            memcpy((char*)array + i * elem_size, argv + 2 + i, elem_size);
        
    } else {
        puts("Undefined behavioud");
        return 1;
    }
    
    if (mergesort(array, count, elem_size, comparator) != 0) {
        puts(NOMEM);
        free(array);
        return 1;
    }
    
    for (int i = 0; i < count; ++i)
        printer((char*)array + i * elem_size, i == count - 1);
    
    free(array);
    
    return 0;
}
