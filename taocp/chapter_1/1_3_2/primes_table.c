#include <stdio.h>
#include <stdlib.h>

void prime_table(const int *);

int main()
{
	int countPrime;

	printf("How many primes numbers we need? ");
	scanf("%d", &countPrime);

	prime_table(&countPrime);

	return(0);
}

void prime_table(const int *max)
{
	int *prime;
	int n,
		numbers,
		k;

	prime = (int *)malloc(sizeof(prime) * (*max));

	prime[0] = 2;
	n = 3;
	numbers = 0;

	while(numbers < *max)
	{
		prime[++numbers] = n;
		n += 2;
		k = 1;

		while(numbers < *max)
		{
			if((n % prime[k]) == 0)
				n += 2;
			else
			{
				if((n / prime[k]) <= prime[k])
					break;
				else
					++k;
			}
		}
	}

	printf("\nHere are first %d prime numbers:\n\n", *max);
	for(int i = 0, n = 0; i < 50; ++i)
	{
		for(int j = 0; j < (*max / 50); ++j)
			printf(" %-5d", prime[i + (j * 50)]);
		printf("\n");
	}

	free(prime);
}
