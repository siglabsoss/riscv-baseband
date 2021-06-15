#include "sort.h"

// sort the array A
void selection_sort_i32(int32_t* const a, const unsigned n) {
    unsigned i, j, min;
    int32_t temp;
    if( n == 0 ) {
       return; // nothing to sort
    }

    for (i = 0; i < n - 1; i++) {
        min = i;
        for (j = i + 1; j < n; j++) {
            if (a[j] < a[min]) {
                min = j;
            }
        }

        if(i == min) {
            continue;
        }

        temp = a[i];
        a[i] = a[min];
        a[min] = temp;
    }
}

// sort the array A
void selection_sort_i64(int64_t* const a, const unsigned n) {
    unsigned i, j, min;
    int64_t temp;
    if( n == 0 ) {
       return; // nothing to sort
    }

    for (i = 0; i < n - 1; i++) {
        min = i;
        for (j = i + 1; j < n; j++) {
            if (a[j] < a[min]) {
                min = j;
            }
        }

        if(i == min) {
            continue;
        }

        temp = a[i];
        a[i] = a[min];
        a[min] = temp;
    }
}

// sort the array A
// sort the array B at the same time, but using the order of A
// general usage: A is a list of unsorted numbers, B is an index
// after the end, A will be sorted, and B will be the order of the sort
void selection_sort_parallel_i32(int32_t* const a, int32_t* const b, const unsigned n) {
    unsigned i, j, min;
    int32_t temp;
    if( n == 0 ) {
       return; // nothing to sort
    }

    for (i = 0; i < n - 1; i++) {
        min = i;
        for (j = i + 1; j < n; j++) {
            if (a[j] < a[min]) {
                min = j;
            }
        }

        if(i == min) {
            continue;
        }

        temp = a[i];
        a[i] = a[min];
        a[min] = temp;
        
        temp = b[i];
        b[i] = b[min];
        b[min] = temp;
    }
}

// sort the array A
// sort the array B at the same time, but using the order of A
// general usage: A is a list of unsorted numbers, B is an index
// after the end, A will be sorted, and B will be the order of the sort
void selection_sort_parallel_u64(uint64_t* const a, uint64_t* const b, const unsigned n) {
    unsigned i, j, min;
    uint64_t temp;
    if( n == 0 ) {
       return; // nothing to sort
    }

    for (i = 0; i < n - 1; i++) {
        min = i;
        for (j = i + 1; j < n; j++) {
            if (a[j] < a[min]) {
                min = j;
            }
        }

        if(i == min) {
            continue;
        }

        temp = a[i];
        a[i] = a[min];
        a[min] = temp;
        
        temp = b[i];
        b[i] = b[min];
        b[min] = temp;
    }
}


// sort the array A
// sort the array B at the same time, but using the order of A
// general usage: A is a list of unsorted numbers, B is an index
// after the end, A will be sorted, and B will be the order of the sort
void selection_sort_parallel_u64_u8(uint64_t* const a, uint8_t* const b, const unsigned n) {
    unsigned i, j, min;
    uint64_t temp;
    uint8_t  temp2;
    if( n == 0 ) {
       return; // nothing to sort
    }

    for (i = 0; i < n - 1; i++) {
        min = i;
        for (j = i + 1; j < n; j++) {
            if (a[j] < a[min]) {
                min = j;
            }
        }

        if(i == min) {
            continue;
        }

        temp = a[i];
        a[i] = a[min];
        a[min] = temp;
        
        temp2 = b[i];
        b[i] = b[min];
        b[min] = temp2;
    }
}


// sort the array A
// sort the array B at the same time, but using the order of A
// general usage: A is a list of unsorted numbers, B is an index
// after the end, A will be sorted, and B will be the order of the sort
void selection_sort_parallel_u64_u32(uint64_t* const a, uint32_t* const b, const unsigned n) {
    unsigned i, j, min;
    uint64_t temp;
    uint32_t  temp2;
    if( n == 0 ) {
       return; // nothing to sort
    }

    for (i = 0; i < n - 1; i++) {
        min = i;
        for (j = i + 1; j < n; j++) {
            if (a[j] < a[min]) {
                min = j;
            }
        }

        if(i == min) {
            continue;
        }

        temp = a[i];
        a[i] = a[min];
        a[min] = temp;
        
        temp2 = b[i];
        b[i] = b[min];
        b[min] = temp2;
    }
}

