#ifndef mergesort_h
#define mergesort_h

#include <stddef.h>

int mergesort(void *array, size_t elements, size_t element_size, int (*comparator)(const void*, const void*));

#endif /* mergesort_h */
