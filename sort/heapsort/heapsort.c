/*
 * Implementation of heapsort sorting algorithm
 * Benchmark for 1 000 000 int elements (gcc):
 * No optimisation:      0.39 sec
 * O3 optimisation flag: 0.14 sec
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

static void swap(int *prev, int *seq){
	int temp = *prev;
	*prev = *seq;
	*seq = temp;
}

/* heapsort */
static void heapify(int *arr, int size, int index){
	int largest = index, left = index * 2 + 1, right = index * 2 + 2;

	if(left < size && arr[left] > arr[largest]) largest = left;
	if(right < size && arr[right] > arr[largest]) largest = right;

	if(largest == index) return;
	swap(&arr[largest], &arr[index]);
	heapify(arr, size, largest);
}

static void heapsort(int *arr, int size){
	for(int i = size / 2 - 1; i != -1; --i) heapify(arr, size, i);
	for(int i = size - 1; i != -1; --i){
		swap(&arr[0], &arr[i]);
		heapify(arr, i, 0);
	}
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
	heapsort(arr, size);
	clock_t end  = clock();
	float   time = (float)(((float)end - (float)start) / CLOCKS_PER_SEC);

	puts("After sorting: ");
	printing(arr, size);

	printf("\nHeapsort took %.4f seconds to sort %d elements\n", time, size);
}

int main() {
	const int size = 1000000;
	int *     arr  = fillArr(size);
	test(arr, size);

	free(arr);

	return 0;
}
