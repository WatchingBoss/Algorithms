/*
 * Impelentation of selection sort algorithm
 * 3 seconds to sort 50,000 numbers
 * 12 seconds to sort 100,000 numbers
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 500
#define MIN 1
#define NUM 50000

void print_arr(size_t arr[], size_t size)
{
	for(int i = 0; i < size; ++i)
		printf("%ld ", arr[i]);
	printf("\n");
}

void swap(size_t *src, size_t *dest)
{
	size_t temp = *dest;
	*dest = *src;
	*src = temp;
}

void s_sort(size_t arr[], size_t size)
{
	int min = 0;

	for(int i = 0; i < size - 1; ++i)
	{
		min = i;

		for(int j = i + 1; j < size; ++j)
		{
			if(arr[j] < arr[min])
				min = j;
		}
		swap(&arr[min], &arr[i]);
	}
}

int main()
{
	srand(time(NULL));
	size_t arr[NUM];
	for(int i = 0; i < NUM; ++i)
		arr[i] = rand() % (MAX + 1 - MIN) + MIN;

	time_t begin = time(NULL);
	s_sort(arr, NUM);
	time_t end = time(NULL);

	print_arr(arr, NUM);
	printf("%ld seconds - time to sort %d elements\n", end - begin, NUM);

	return 0;
}

