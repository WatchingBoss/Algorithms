/*
 * Implementation of bubble sort algorithm
 * 12 second to sort 50,000 elements
 * 48 second to sort 100,000 elements
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MIN 1
#define MAX 500
#define NUM 5000

void print_arr(size_t arr[], size_t size)
{
	for(size_t i = 0; i < size; ++i)
	{
		printf("%ld ", arr[i]);
		if(!(i % 30) && i)
			printf("\n");
	}
	printf("\n");
}

void swap(size_t *src, size_t *dest)
{
	size_t temp = *dest;
	*dest = *src;
	*src = temp;
}

void b_sort(size_t arr[], size_t size)
{
	for(size_t i = 0; i < size; ++i)
		for(size_t j = 0; j < size; ++j)
			if(arr[j] > arr[j + 1])
				swap(&arr[j + 1], &arr[j]);
}

int main()
{
	srand(time(NULL));

#ifndef NUM
	int NUM = 0;
	printf("Enter number of elements: ");
	scanf("%d", &NUM);
#endif

	size_t arr[NUM];
	for(int i = 0; i < NUM; ++i)
		arr[i] = rand() % (MAX + 1 - MIN) + MIN;

	time_t begin = time(NULL);
	b_sort(arr, NUM);
	time_t end = time(NULL);

	print_arr(arr, NUM);
	printf("%ld second for sort %d elemetns\n", end - begin, NUM);

	return 0;
}
