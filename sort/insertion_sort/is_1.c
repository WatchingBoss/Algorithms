/*
 * Implementation of insertion sort algorithm
 * 2 seconds to sort 50,000 elements
 * 8 seconds to sort 100,000 elements
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MIN 1
#define MAX 500
#define NUM 50000

void print_arr(size_t arr[], size_t size)
{
	for(size_t i = 0; i < size; ++i)
	{
		printf("%ld ", arr[i]);
		if(!(i % 25) && i)
			printf("\n");
	}
	printf("\n");
}

void i_sort(size_t arr[], size_t size)
{
	int key = 0, j = 0;
	for(size_t i = 1; i < size; ++i)
	{
		key = arr[i];
		j = i - 1;

		while(j >= 0 && arr[j] > (size_t)key)
		{
			arr[j + 1] = arr[j];
			--j;
		}
		
		arr[j + 1] = key;
	}
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
	i_sort(arr, NUM);
	time_t end = time(NULL);

	print_arr(arr, NUM);
	printf("%ld second to sort %d elements\n", end - begin, NUM);

	return 0;
}
