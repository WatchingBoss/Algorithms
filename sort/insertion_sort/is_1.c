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

/* Slower */
void i_sort_2(size_t arr[], size_t size)
{
	for(size_t i = 2; i < size; ++i)
	{
		size_t j = 1;
		while(arr[i] > arr[j])
			++j;
		size_t m = arr[i];
		for(size_t k = 0; (int)k < (int)i - (int)j - 1; ++k)
			arr[i - k] = arr[i - k - 1];
		arr[j] = m;
	}
}

/* Faster */
void i_sort(size_t arr[], size_t size)
{
	size_t key = 0, j = 0;
	for(size_t i = 1; i < size; ++i)
	{
		key = arr[i];
		j = i - 1;

		while((int)j >= 0 && arr[j] > key)
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

	clock_t begin = clock();
	i_sort(arr, NUM);
	clock_t end = clock();

//	print_arr(arr, NUM);
	printf("%.5f second to sort %d elements\n",
		   ((float)end - (float)begin) / 1000000.f, NUM);

	return 0;
}
