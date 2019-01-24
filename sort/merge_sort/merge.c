/*
 * Implementation of merge sorting algorithm
 * Benchmark for 1 000 000 int elements (gcc):
 * No optimisation:      0.24 sec
 * O3 optimisation flag: 0.13 sec
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static void sys_er(const char *er) {
	perror(er);
	exit(EXIT_FAILURE);
}

static void *xmalloc(int bytes) {
	void *ptr = malloc(bytes);
	if (!ptr) sys_er("xmalloc: malloc");
	return ptr;
}

static inline int randomInt(int min, int max) {
	return rand() % (max + 1 - min) + min;
}

static int *fillArr(int size) {
	srand(time(NULL));
	int *arr = (int *)xmalloc(size * sizeof(int));
	for (int i = 0; i < size; ++i) arr[i] = randomInt(1, size - 1);
	return arr;
}

/* Merge sorting */

static void merging(int *arr, int size, int low, int mid, int high) {
	int *temp = (int *)xmalloc(size * sizeof *arr);
	int  l1 = low, l2 = mid + 1, i = low;

	for (; l1 <= mid && l2 <= high; ++i) {
		if (arr[l1] <= arr[l2])
			temp[i] = arr[l1++];
		else
			temp[i] = arr[l2++];
	}

	while (l1 <= mid) temp[i++] = arr[l1++];
	while (l2 <= high) temp[i++] = arr[l2++];

	for (int i = low; i <= high; ++i) arr[i] = temp[i];

	free(temp);
}

static void merge_sort(int *arr, int size, int low, int high) {
	if (low >= high) return;
	int mid = (low + high) / 2;
	merge_sort(arr, size, low, mid);
	merge_sort(arr, size, mid + 1, high);
	merging(arr, size, low, mid, high);
}

static void printing(int *arr, int size) {
	printf("First 10:   ");
	for (int i = 0; i < 10; ++i) printf("%d  ", arr[i]);
	printf("\nLast 10:   ");
	for (int i = size - 10; i < size; ++i) printf("%d  ", arr[i]);
	puts("\n");
}

static void test(int *arr, int size) {
	puts("Befor sorting: ");
	printing(arr, size);

	clock_t start = clock();
	merge_sort(arr, size, 0, size - 1);
	clock_t end  = clock();
	float   time = (float)(((float)end - (float)start) / CLOCKS_PER_SEC);

	puts("After sorting: ");
	printing(arr, size);

	printf("\nMerge took %.4f seconds to sort %d elements\n", time, size);
}

int main() {
	const int size = 500000;
	int *     arr  = fillArr(size);
	test(arr, size);

	free(arr);

	return 0;
}
