#include <stdio.h>
#include <stdlib.h>

int multi(int, int *, int);
void fact(const int *);

int main()
{
	int number;

	printf("Enter your number and this pretty cool program will compute factorial\n"
		   "LMAO :))  : ");
	scanf("%d", &number);

	fact(&number);

	return(0);
}

void fact(const int *n)
{
	int *res;
	res = (int *)calloc(*n, sizeof(int));

	res[0] = 1;
	int resSize = 1;

	for(int i = 2; i <= *n; ++i)
		resSize = multi(i, res, resSize);

	printf("Factorial of %d is ", *n);
	for(int i = resSize - 1; i >= 0; --i)
		printf("%d", res[i]);
	printf("\n");
}

int multi(int x, int *res, int resSize)
{
	int carry = 0;

	for(int i = 0; i < resSize; ++i)
	{
		int prod = res[i] * x + carry;

		res[i] = prod % 10;

		carry = prod / 10;
	}

	while(carry)
	{
		res[resSize] = carry % 10;
		carry = carry / 10;
		++resSize;
	}

	return(resSize);
}
