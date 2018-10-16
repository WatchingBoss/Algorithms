#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

static void sys_er(const char *er) {
	perror(er);
	exit(EXIT_FAILURE);
}

static void *xmalloc(int bytes) {
	void *ptr = malloc(bytes);
	if (!ptr) sys_er("xmalloc: malloc error");
	return ptr;
}

static void *xrealloc(void *ptr, int bytes) {

	/* DEBUG */
	printf("\nXREALLOC:\n"
		   "Address: %p   Next size: %d\n", ptr, bytes);

	void *new_ptr = realloc(ptr, bytes);
	if (!new_ptr) sys_er("xrealloc: realloc error");
	return new_ptr;
}

static inline int random_int(int min, int max) {
	return rand() % (max + 1 - min) + min;
}

static int *fill_array(int size) {
	int *new_arr = (int *)xmalloc(size * sizeof(int));

	srand(time(NULL));
	for (int i = 0; i != size; ++i) new_arr[i] = random_int(1, size - 1);
	return new_arr;
}

static void printing(int *arr, int size) {
	printf("First: ");
	for (int i = 0; i != 10; ++i) printf("%d ", arr[i]);
	printf("\nLast: ");
	for (int i = size - 10; i != size; ++i) printf("%d ", arr[i]);
	putchar('\n');
}

typedef struct _one_dim_arr {
	int  size, count;
	int *arr;
} one_dim_arr;

typedef struct _two_dim_arr {
	int          size, count;
	one_dim_arr *arr;
} two_dim_arr;

static void run_free(one_dim_arr *run) {
	free(run->arr);
	run->size  = 0;
	run->count = 0;
}

static void run_append(one_dim_arr *run, int value) {
	/* DEBUG */
	printf("appending: run size BEFORE = %d\n", run->size);

	run->size += sizeof value;

	if (!run->count)
		run->arr = (int *)xmalloc(run->size);
	else
		run->arr = (int *)xrealloc(run->arr, run->size);

	/* DEBUG */
	printf("appending: run size AFTER = %d\n", run->size);

	run->arr[run->count] = value;
	run->count += 1;
}

static void runs_append(two_dim_arr *runs, one_dim_arr run) {
	/* DEBUG */
	if (!run.count) {
		printf("runs.count = %d\n", runs->count);
		sys_er("");
	}

	int run_size = sizeof(int) * 2 + run.size;
	/* DEBUG */
	printf("\nSize of appending run: %d\n", run_size);

	/* DEBUG */
	printf("BEFORE runs size = %d\n", runs->size);

	runs->size += run_size;
	if(!runs->count)
		runs->arr = (one_dim_arr *)malloc(runs->size);
	else
		runs->arr = (one_dim_arr *)xrealloc(runs->arr, runs->size);

	/* DEBUG */
	printf("AFTER runs size = %d\n", runs->size);

	runs->arr[runs->count] = run;
	runs->count += 1;
}

static one_dim_arr temp_run(int value) {
	one_dim_arr temp = { 0, 0, NULL };
	run_append(&temp, value);
	return temp;
}

static int binary_search(int *arr, int item, int start, int end) {
	if (start == end) {
		if (arr[start] > item)
			return start;
		else
			return start + 1;
	}
	if (start > end) return start;

	int mid = (start + end) / 2;

	if (arr[mid] < item)
		return binary_search(arr, item, mid + 1, end);
	else if (arr[mid] > item)
		return binary_search(arr, item, start, mid - 1);

	return mid;
}

static void sort_run(one_dim_arr *run, int pos, int value, int index) {
	int temp_arr[run->count];
	for (int i = 0; i != run->count; ++i) temp_arr[i] = run->arr[i];

	int arr_i = 0;

	for (int p = 0; p < pos; ++p) {
		if (arr_i + 1 == run->count) sys_er("sort_run: 0 - pos");
		run->arr[arr_i++] = temp_arr[p];
	}

	run->arr[arr_i++] = value;
	for (int p = pos; p < index; ++p) {
		if (arr_i + 1 == run->count) sys_er("sort_run: pos - index");
		run->arr[arr_i++] = temp_arr[p];
	}
	for (int p = index + 1; p != run->count; ++p) {
		if (arr_i + 1 == run->count) sys_er("sort_run: index + 1 - end");
		run->arr[arr_i++] = temp_arr[p];
	}
}

static void insertion_sort(one_dim_arr *run) {
	for (int index = 0; index != run->count; ++index) {
		int value = run->arr[index];
		int pos   = binary_search(run->arr, value, 0, index - 1);
		sort_run(run, pos, value, index);
	}
}

static void merge_sort(int *arr, int arr_i, int arr_size, int *run, int run_i,
                       int run_size) {
	if (arr_i == arr_size - 1 || run_i == run_size - 1) return;
	if (arr[arr_i] < run[run_i]) {
		merge_sort(arr, ++arr_i, arr_size, run, run_i, run_size);
	} else {
		arr[arr_i] = run[run_i];
		merge_sort(arr, arr_i, arr_size, run, ++run_i, run_size);
	}
}

static void timsort(int *arr, int size) {
	one_dim_arr new_run = { 0, 0, NULL };
	two_dim_arr runs = { 0, 0, NULL }, sorted_runs = { 0, 0, NULL };

	run_append(&new_run, arr[0]);

	for (int i = 1; i != size; ++i) {
		/* DEBUG */
		printf("\nIteration #%d\n", i);
		if (i == size - 1) {
			run_append(&new_run, arr[i]);
			runs_append(&runs, new_run);
			run_free(&new_run);
			break;
		}
		if (arr[i] < arr[i - 1]) {
			if (!new_run.size) {
				/* DEBUG */
				printf("Use temp\n");
				one_dim_arr temp = temp_run(arr[i]);
				/* DEBUG */
				printf("Append run to runs. runs count = %d, run size = %d\n",
				       runs.count, new_run.size);
				runs_append(&runs, temp);
				run_append(&new_run, arr[i]);
				run_free(&temp);
			} else {
				/* DEBUG */
				printf("Append run to runs. runs count = %d, run size = %d\n",
				       runs.count, new_run.size);
				runs_append(&runs, new_run);
				run_free(&new_run);
			}
		} else {
			/* DEBUG */
			printf("Append new_run. run count = %d, run size = %d\n",
			       new_run.count, new_run.size);
			run_append(&new_run, arr[i]);
		}
	}

	/* DEBUG */
	printf("runs.count = %d\n", runs.count);

	for (int run = 0; run != runs.count; ++run) {
		one_dim_arr sorted_run = { 0, 0, NULL };

		/* DEBUG */
		printf("run #%d\n", run);
		printf("run.count = %d\n", runs.arr[run].count);

		for (int item = 0; item != runs.arr[run].count; ++item)
			run_append(&sorted_run, runs.arr[run].arr[item]);

		insertion_sort(&sorted_run);

		runs_append(&sorted_runs, sorted_run);

		run_free(&sorted_run);
	}

	for (int run = 0; run != sorted_runs.count; ++run) {
		merge_sort(arr, 0, size, sorted_runs.arr[run].arr, 0,
		           sorted_runs.arr[run].count);
	}
}

static void test_sorting(int *arr, int size) {
	puts("Before sorting: ");
	printing(arr, size);

	clock_t start = clock();
	timsort(arr, size);
	clock_t end  = clock();
	float   time = (float)(((float)end - (float)start) / CLOCKS_PER_SEC);

	puts("After sorting: ");
	printing(arr, size);

	printf("\nTimsort took %.3f seconds to sort %d elements\n", time, size);
}

int main() {
	int  size     = 500;
	int *my_array = fill_array(size);

	test_sorting(my_array, size);

	free(my_array);

	return 0;
}
