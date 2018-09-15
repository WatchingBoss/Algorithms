#include <stdio.h>
#include <stdlib.h>

void change_making(size_t coins[], size_t size, size_t value)
{
	printf("To get %ld we need:\n", value);

	for(size_t i = 0; i < size; ++i)
	{
		size_t count = 0;
		while(value >= coins[i])
		{
			++count;
			value -= coins[i];
		}

		if(count > 0)
			printf("%2ld coins of %ld denomination\n", count, coins[i]);
	}
}

int main()
{
	size_t coins[] = {25, 10, 5, 1};
	size_t size = sizeof coins / sizeof *coins;
	size_t value = 0;

	printf("What value you want to get: ");
	scanf("%ld", &value);

	change_making(coins, size, value);

	return 0;
}
