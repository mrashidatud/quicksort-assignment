// src/quicksort.c
#include <stddef.h>

/*
 * Quicksort using first element as pivot (Lomuto variant).
 * Sorts 'a[0..n-1]' in ascending order, in-place.
 */

static inline void swap_int(int *a, int *b) {
    int t = *a; *a = *b; *b = t;
}

/* Partition that always uses the first element as pivot.
 * We swap a[lo] with a[hi], then do classic Lomuto using a[hi] as pivot.
 */
static int partition_first_pivot(int *a, int lo, int hi) {
    swap_int(&a[lo], &a[hi]);
    int pivot = a[hi];
    int i = lo;
    for (int j = lo; j < hi; ++j) {
        if (a[j] <= pivot) {
            swap_int(&a[i], &a[j]);
            i++;
        }
    }
    swap_int(&a[i], &a[hi]);
    return i;
}

static void quicksort_first_pivot_impl(int *a, int lo, int hi) {
    if (lo >= hi) return;
    int p = partition_first_pivot(a, lo, hi);
    quicksort_first_pivot_impl(a, lo, p - 1);
    quicksort_first_pivot_impl(a, p + 1, hi);
}

void quicksort_first_pivot(int *a, int n) {
    if (!a || n <= 1) return;
    quicksort_first_pivot_impl(a, 0, n - 1);
}
