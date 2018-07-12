/*
 * Add elements in dynamic allocating array and sort them with bubble sort
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void print_arr(size_t *arr, size_t size)
{
	for(int i = 0; i < size; ++i)
		printf("%ld ", arr[i]);
	printf("\n\n");
}

void swap(size_t *seq, size_t *prev)
{
	size_t temp = *prev;
	*prev = *seq;
	*seq = temp;
}

void insertion(size_t arr[], size_t size)
{
	for(int i = 1; i < size; ++i)
		for(int j = i; j > 0 && arr[j - 1] > arr[j]; --j)
			swap(&(arr[j]), &(arr[j - 1]));
}

size_t * add_number(size_t *numbers, size_t *size, size_t next_number)
{
	size_t *arr = NULL;
	arr = realloc(arr, sizeof arr * (*size + 1));

	if(*size)
		for(int i = 0; i < (*size); ++i)
			arr[i] = numbers[i];

	arr[*size] = next_number;
	*size += 1;

	if(*size > 1)
		insertion(arr, *size);

	return arr;
}

int main()
{

	size_t *numbers = NULL;
	size_t adding_number = 0,
		   size = 0;

#define SIZE 5000
#define MIN 1
#define MAX 500

	size_t array_numbers[SIZE];
	srand(time(NULL));
	for(int i = 0; i < SIZE; ++i)
		array_numbers[i] = rand() % (MAX + 1 - MIN) + MIN;
//	printf("Before sorting\n");
//	print_arr(array_numbers, SIZE);

	time_t begin = time(NULL);

	for(int i = 0; i < SIZE; ++i)
		numbers = add_number(numbers, &size, array_numbers[i]);

	time_t end = time(NULL);

	printf("After sorting\n");
	print_arr(numbers, size);

	printf("To sorting %d numbers was taken %ld second\n", SIZE, end - begin);

	return 0;
}

/*
 * Sort 50,000 numbers for 13 second. Is it fast?
 */
