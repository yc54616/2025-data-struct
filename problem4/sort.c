#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_SIZE 100000
#define MAX_ELEMENT 100000

typedef struct {
    long comparisons;
} Metrics;

typedef struct {
    int key;
} element;

typedef struct {
    element heap[MAX_ELEMENT];
    int heap_size;
} HeapType;

void swap(int *a, int *b) {
    int t = *a; *a = *b; *b = t;
}

void bubble_sort(int arr[], int n, Metrics* m) {
    m->comparisons = 0;
    for (int i = 0; i < n-1; i++)
        for (int j = 0; j < n-i-1; j++) {
            m->comparisons++;
            if (arr[j] > arr[j+1])
                swap(&arr[j], &arr[j+1]);
        }
}

void selection_sort(int arr[], int n, Metrics* m) {
    m->comparisons = 0;
    for (int i = 0; i < n-1; i++) {
        int min = i;
        for (int j = i+1; j < n; j++) {
            m->comparisons++;
            if (arr[j] < arr[min]) min = j;
        }
        swap(&arr[i], &arr[min]);
    }
}

void insertion_sort(int arr[], int n, Metrics* m) {
    m->comparisons = 0;
    for (int i = 1; i < n; i++) {
        int key = arr[i], j = i - 1;
        while (j >= 0 && (++m->comparisons, arr[j] > key)) {
            arr[j+1] = arr[j];
            j--;
        }
        arr[j+1] = key;
    }
}

void shell_sort(int arr[], int n, Metrics* m) {
    m->comparisons = 0;
    for (int gap = n/2; gap > 0; gap /= 2)
        for (int i = gap; i < n; i++) {
            int temp = arr[i], j = i;
            while (j >= gap && (++m->comparisons, arr[j - gap] > temp)) {
                arr[j] = arr[j - gap];
                j -= gap;
            }
            arr[j] = temp;
        }
}

void merge(int arr[], int l, int m, int r, Metrics* mtr) {
    int n1 = m - l + 1, n2 = r - m;
    int *L = malloc(n1 * sizeof(int)), *R = malloc(n2 * sizeof(int));
    for (int i = 0; i < n1; i++) L[i] = arr[l+i];
    for (int j = 0; j < n2; j++) R[j] = arr[m+1+j];

    int i=0, j=0, k=l;
    while (i<n1 && j<n2) {
        mtr->comparisons++;
        arr[k++] = (L[i] <= R[j]) ? L[i++] : R[j++];
    }
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
    free(L); free(R);
}

void merge_sort(int arr[], int l, int r, Metrics* m) {
    if (l < r) {
        int m_ = l + (r - l) / 2;
        merge_sort(arr, l, m_, m);
        merge_sort(arr, m_+1, r, m);
        merge(arr, l, m_, r, m);
    }
}

int partition(int arr[], int low, int high, Metrics* m) {
    int pivot = arr[high];
    int i = low-1;
    for (int j = low; j < high; j++) {
        m->comparisons++;
        if (arr[j] <= pivot)
            swap(&arr[++i], &arr[j]);
    }
    swap(&arr[i+1], &arr[high]);
    return i+1;
}

void quick_sort(int arr[], int low, int high, Metrics* m) {
    if (low < high) {
        int pi = partition(arr, low, high, m);
        quick_sort(arr, low, pi - 1, m);
        quick_sort(arr, pi + 1, high, m);
    }
}

void insert_max_heap(HeapType *h, int key, Metrics* m) {
    int i = ++(h->heap_size);
    element item = { key };

    while ((i != 1) && (++m->comparisons && item.key > h->heap[i / 2].key)) {
        h->heap[i] = h->heap[i / 2];
        i /= 2;
    }
    h->heap[i] = item;
}

int delete_max_heap(HeapType *h, Metrics* m) {
    int parent = 1, child = 2;
    element item = h->heap[1];
    element temp = h->heap[h->heap_size--];

    while (child <= h->heap_size) {
        if (child < h->heap_size && (++m->comparisons && h->heap[child].key < h->heap[child + 1].key))
            child++;

        if (++m->comparisons && temp.key >= h->heap[child].key)
            break;

        h->heap[parent] = h->heap[child];
        parent = child;
        child *= 2;
    }
    h->heap[parent] = temp;
    return item.key;
}

void heap_sort(int arr[], int n, Metrics* m) {
    HeapType h;
    h.heap_size = 0;
    m->comparisons = 0;

    for (int i = 0; i < n; i++)
        insert_max_heap(&h, arr[i], m);

    for (int i = n - 1; i >= 0; i--)
        arr[i] = delete_max_heap(&h, m);
}

void load_data(const char* filename, int arr[], int* size) {
    FILE* fp = fopen(filename, "r");
    if (!fp) {
        perror("파일 읽기 실패");
        exit(1);
    }
    int val, idx = 0;
    while (fscanf(fp, "%d", &val) != EOF) arr[idx++] = val;
    *size = idx;
    fclose(fp);
}

void run_and_measure(void (*sort_fn)(int*, int, Metrics*), const char* name, int data[], int n) {
    int* arr = malloc(n * sizeof(int));
    memcpy(arr, data, n * sizeof(int));
    Metrics m;

    clock_t start = clock();
    sort_fn(arr, n, &m);
    clock_t end = clock();

    printf("%-12s | 비교 횟수: %8ld | 시간: %.4f초\n", name, m.comparisons, (double)(end - start)/CLOCKS_PER_SEC);
    free(arr);
}

int main() {
    const char* file_map[4][7] = {
        { "data/data_100.txt", "data/data_100_copy1.txt", "data/data_100_copy2.txt", "data/data_100_copy3.txt", "data/data_100_copy4.txt", "data/data_100_copy5.txt", "data/data_100_copy6.txt" },
        { "data/data_1000.txt", "data/data_1000_copy1.txt", "data/data_1000_copy2.txt", "data/data_1000_copy3.txt", "data/data_1000_copy4.txt", "data/data_1000_copy5.txt", "data/data_1000_copy6.txt" },
        { "data/data_10000.txt", "data/data_10000_copy1.txt", "data/data_10000_copy2.txt", "data/data_10000_copy3.txt", "data/data_10000_copy4.txt", "data/data_10000_copy5.txt", "data/data_10000_copy6.txt" },
        { "data/data_100000.txt", "data/data_100000_copy1.txt", "data/data_100000_copy2.txt", "data/data_100000_copy3.txt", "data/data_100000_copy4.txt", "data/data_100000_copy5.txt", "data/data_100000_copy6.txt" },
    };

    typedef void (*SortFunc)(int*, int, Metrics*);

    typedef struct {
        const char* name;
        SortFunc func;
    } SortAlgo;

    SortAlgo algorithms[7] = {
        { "Bubble", bubble_sort },
        { "Selection", selection_sort },
        { "Insertion", insertion_sort },
        { "Shell", shell_sort },
        { "Heap", heap_sort },
        { "Merge", NULL },
        { "Quick", NULL }
    };

    for (int i = 0; i < 4; i++) {
        printf("\n=== 데이터 크기: %s ===\n", file_map[i][0]);

        for (int j = 0; j < 7; j++) {
            int data[MAX_SIZE], n;
            load_data(file_map[i][j], data, &n);

            if (j < 5) {
                run_and_measure(algorithms[j].func, algorithms[j].name, data, n);
            } else if (j == 5) {
                Metrics m = {0};
                clock_t t1 = clock();
                merge_sort(data, 0, n - 1, &m);
                clock_t t2 = clock();
                printf("%-12s | 비교 횟수: %8ld | 시간: %.4f초\n", "Merge", m.comparisons, (double)(t2 - t1)/CLOCKS_PER_SEC);
            } else if (j == 6) {
                Metrics m = {0};
                clock_t t1 = clock();
                quick_sort(data, 0, n - 1, &m);
                clock_t t2 = clock();
                printf("%-12s | 비교 횟수: %8ld | 시간: %.4f초\n", "Quick", m.comparisons, (double)(t2 - t1)/CLOCKS_PER_SEC);
            }
        }
    }

    return 0;
}
