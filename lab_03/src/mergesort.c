#include "mergesort.h"

#include <string.h>
#include <stdlib.h>

#define ELEM(array, index, size) ((char*)(array) + (index) * (size))

static int swap(void *elem1, void *elem2, size_t elem_size) {
    void *tmp = malloc(elem_size);
    if (!tmp) return -1;
    
    memcpy(tmp, elem1, elem_size);
    memcpy(elem1, elem2, elem_size);
    memcpy(elem2, tmp, elem_size);
    
    free(tmp);
        
    return 0;
}


static int merge(void *array, int start, int middle, int end, size_t element_size,
                  int (*comparator)(const void*, const void*)) {
    
//    void *middle_elem = ELEM(array, middle, element_size);
//    for (int i = start; i < middle; ++i) {
//        void *elem1 = ELEM(array, i, element_size);
//        if (comparator(elem1, middle_elem) > 0) {
//            // a > b, swap them
//            int err = swap(elem1, middle_elem, element_size);
//            if (err) return err;
//        }
//    }
//
//    // now we have only element in the middle which is unsorted
//    // just find place for it and then bail
//    for (int i = middle; i < end - 1; ++i) {
//        void *elem = ELEM(array, i, element_size);
//        void *next = ELEM(array, i + 1, element_size);
//        if (comparator(elem, next) > 0) {
//            int err = swap(elem, next, element_size);
//            if (err) return err;
//        } else break;
//    }
    
//    int k = start, i = k, j = middle;
//    for (; i < j && j < end; ++k) {
//        void *left_elem = ELEM(array, i, element_size);
//        void *right_elem = ELEM(array, j, element_size);
//        void *write_elem = ELEM(array, k, element_size);
//        if (comparator(left_elem, right_elem) > 0) {
//            // a > b, swap them
//            int err = swap(write_elem, right_elem, element_size);
//            if (err) return err;
//            ++j;
//            if (i == k) i = j - 1; // i flies over to its value
//        } else {
//            if (i++ != k)
//                swap(write_elem, left_elem, element_size);
////            else i++;
//        }
//    }
    
//    while (k < end && (i < end || j < end)) {
//        void *elem = ELEM(array, i < end ? i++ : j++, element_size);
//        void *write_elem = ELEM(array, k, element_size);
//        swap(elem, write_elem, element_size);
//        k++;
//    }
    
    void *buffer = malloc((end - start) * element_size);
    if (!buffer) return -1;
    
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
    
    free(buffer);
    
    return 0;
}


static int sort(void *array, int start, int end, size_t element_size,
                       int (*comparator)(const void*, const void*)) {
    if (end - start < 2) {
        // only one or zero elements in the array, its sorted all right, bail ...
        return 0;
    }
    int middle = (start + end) / 2;
    int err = sort(array, start, middle, element_size, comparator);
    if (err) return err;
    err = sort(array, middle, end, element_size, comparator);
    if (err) return err;
    err = merge(array, start, middle, end, element_size, comparator);
    if (err) return err;
    
    return 0;
}


int mergesort1(void *array, size_t elements, size_t element_size, int (*comparator)(const void*, const void*)) {
    return sort(array, 0, (int)elements, element_size, comparator);
}
