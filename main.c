// main.c
// Reads numbers from datasets/<input_file>, sorts with quicksort (first-element pivot, Lomuto-style),
// and writes sorted numbers to outputs/<input_file>.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <errno.h>

#ifndef OUTPUT_DIR
#define OUTPUT_DIR "outputs"
#endif

#ifndef INPUT_DIR
#define INPUT_DIR "datasets"
#endif

// Swap helper
static inline void swap(int *a, int *b) {
    int t = *a; *a = *b; *b = t;
}

// Quicksort using FIRST element as pivot (Lomuto-style partitioning adapted to first pivot)
static int partition_first_pivot(int *arr, int low, int high) {
    int pivot = arr[low];       // first element as pivot
    int i = low;                // place for next smaller-than-pivot
    for (int j = low + 1; j <= high; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    // place pivot to its final position
    swap(&arr[low], &arr[i]);
    return i;
}

static void quicksort(int *arr, int low, int high) {
    if (low < high) {
        int p = partition_first_pivot(arr, low, high);
        quicksort(arr, low, p - 1);
        quicksort(arr, p + 1, high);
    }
}

// Ensure directory exists (mkdir -p like, but only single level)
static int ensure_dir(const char *dir) {
    struct stat st;
    if (stat(dir, &st) == 0) {
        if ((st.st_mode & S_IFMT) == S_IFDIR) return 0;
        fprintf(stderr, "Path exists but is not a directory: %s\n", dir);
        return -1;
    }
    if (mkdir(dir, 0755) == 0) return 0;
    if (errno == EEXIST) return 0;
    perror("mkdir");
    return -1;
}

// Read all ints from a text file with arbitrary whitespace, dynamic growth
static int *read_ints_from_file(const char *path, size_t *out_n) {
    FILE *f = fopen(path, "r");
    if (!f) {
        perror("fopen");
        return NULL;
    }

    size_t cap = 1024;
    size_t n = 0;
    int *a = (int *)malloc(cap * sizeof(int));
    if (!a) {
        fclose(f);
        fprintf(stderr, "malloc failed\n");
        return NULL;
    }

    while (1) {
        int x;
        int rc = fscanf(f, "%d", &x);
        if (rc == 1) {
            if (n == cap) {
                cap *= 2;
                int *tmp = (int *)realloc(a, cap * sizeof(int));
                if (!tmp) {
                    fclose(f);
                    free(a);
                    fprintf(stderr, "realloc failed\n");
                    return NULL;
                }
                a = tmp;
            }
            a[n++] = x;
        } else if (rc == EOF) {
            break;
        } else {
            // Non-integer token encountered
            fprintf(stderr, "Warning: non-integer token in input; stopping read.\n");
            break;
        }
    }

    fclose(f);
    *out_n = n;
    return a;
}

static int write_ints_to_file(const char *path, const int *a, size_t n) {
    FILE *f = fopen(path, "w");
    if (!f) {
        perror("fopen");
        return -1;
    }
    for (size_t i = 0; i < n; i++) {
        if (fprintf(f, "%d\n", a[i]) < 0) {
            perror("fprintf");
            fclose(f);
            return -1;
        }
    }
    fclose(f);
    return 0;
}

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <input_filename_in_datasets>\n", argv[0]);
        fprintf(stderr, "Example: %s random_100k.txt\n", argv[0]);
        return 1;
    }

    // Build input path: datasets/<filename>
    const char *in_name = argv[1];
    char in_path[4096];
    snprintf(in_path, sizeof(in_path), "%s/%s", INPUT_DIR, in_name);

    // Build output dir and path: outputs/<filename>
    if (ensure_dir(OUTPUT_DIR) != 0) {
        return 1;
    }
    char out_path[4096];
    snprintf(out_path, sizeof(out_path), "%s/%s", OUTPUT_DIR, in_name);

    // Read
    size_t n = 0;
    int *arr = read_ints_from_file(in_path, &n);
    if (!arr) {
        fprintf(stderr, "Failed to read input file: %s\n", in_path);
        return 1;
    }
    if (n == 0) {
        fprintf(stderr, "No integers read from: %s\n", in_path);
        free(arr);
        return 1;
    }

    // Sort
    quicksort(arr, 0, (int)n - 1);

    // Write
    if (write_ints_to_file(out_path, arr, n) != 0) {
        fprintf(stderr, "Failed to write output file: %s\n", out_path);
        free(arr);
        return 1;
    }

    printf("Sorted %zu integers.\n", n);
    printf("Input : %s\n", in_path);
    printf("Output: %s\n", out_path);

    free(arr);
    return 0;
}
