#include "mergesort.h"

#include <string.h>
#include <stdlib.h>

#define ELEM(array, index, size) ((char*)(array) + (index) * (size))

/// One buffer for all operations in merge sort
static void *buffer;


static void merge(void *array, int start, int middle, int end, size_t element_size,
                  int (*comparator)(const void*, const void*)) {
    int i = start, k = 0, j = middle;
    while (i < middle && j < end) {
        if (comparator(ELEM(array, i, element_size), ELEM(array, j, element_size)) > 0) {
            memcpy(ELEM(buffer, k++, element_size), ELEM(array, j++, element_size), element_size);
        } else {
            memcpy(ELEM(buffer, k++, element_size), ELEM(array, i++, element_size), element_size);
        }
    }
    
    while (i < middle) {
        memcpy(ELEM(buffer, k++, element_size), ELEM(array, i++, element_size), element_size);
    }
    while (j < end) {
        memcpy(ELEM(buffer, k++, element_size), ELEM(array, j++, element_size), element_size);
    }
    
    memcpy(ELEM(array, start, element_size), buffer, element_size * (end - start));
}


static void sort(void *array, int start, int end, size_t element_size,
                       int (*comparator)(const void*, const void*)) {
    if (end - start < 2) {
        // only one or zero elements in the array, its sorted all right, bail ...
        return;
    }
    int middle = (start + end) / 2;
    sort(array, start, middle, element_size, comparator);
    sort(array, middle, end, element_size, comparator);
    merge(array, start, middle, end, element_size, comparator);
}


int mergesort(void *array, size_t elements, size_t element_size, int (*comparator)(const void*, const void*)) {
    buffer = calloc(elements, element_size);
    if (!buffer) return -1;
    sort(array, 0, (int)elements, element_size, comparator);
    free(buffer);
    return 0;
}
