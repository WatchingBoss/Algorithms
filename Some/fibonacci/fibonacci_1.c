/*
 * 6 ways to find fibonacci that DOES NOT WORK
 * LMAO
 * Yeah, okay, may be try recognise what's going on ;)
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

// Matrix utils
void mMultiply(int (*)[]);
int mPow(int (*)[], int);
// Fibonacci
int fib_1(int);
int fib_2(int);
int fib_3(int);
int fib_4(int);
int fib_5(int);
int fib_6(int);
int timeof(int, int (), int);

int main()
{
	int number = 0;

	printf("Enter number: ");
	scanf("%d", &number);

	timeof(1, &fib_1, number);
	timeof(2, &fib_2, number);
	timeof(3, &fib_3, number);
	timeof(4, &fib_4, number);
	timeof(5, &fib_5, number);
	timeof(6, &fib_6, number);

	return(0);
}

int timeof(int type, int fib(), int n)
{
	int t = time(NULL),
		res = fib(n);
	printf("\n $ fib_%d(%d) = %d [%ld sec]\n", type, n, res, time(NULL) - t);
}

int fib_1(int n)
{
	double i, j, result;
	i = pow((1 + sqrt(5)) / 2, n);
	j = pow((1 - sqrt(5)) / 2, n);
	result = (i - j) / sqrt(5);

	return(result);

//	return((pow((1 + sqrt(5)) / 2, n) - pow((1 - sqrt(5)) / 2, n)) / sqrt(5));
}

int fib_2(int n)
{
	if(n <= 2)
		return(1);
	else
		return(fib_2(n - 1) + fib_2(n - 2));

// return(n <= 2 ? 1 : fib_2(n - 1) + fib_2(n - 2));
}

int fib_3(int n)
{
	int array[n + 1],
		i;
	array[1] = array[2] = 1;

	for(i = 3; i <= n; ++i)
		array[i] = array[i - 1] + array[i - 2];
	return(array[i - 1]);
}

int fib_4(int n)
{
	int a = 1,
		b = 1;

	for(int i = 3; i <= n; ++i)
	{
		int c = a + b;
		a = b;
		b = c;
	}

	return(b);
}

int fib_5(int n)
{
	int matrix[2][2] = {1, 0, 0, 1},
		temp;

	for(int i = 1; i < n; ++i)
		mMultiply(matrix);

	return(matrix[0][0]);
}

int fib_6(int n)
{
	int matrix[2][2] = {1, 0, 0, 1};

	mPow(matrix, n - 1);

	return(matrix[0][0]);
}

void mMultiply(int matrix[2][2])
{
	int temp = matrix[0][0] + matrix[0][1];
	matrix[0][0] = matrix[0][0];
	matrix[0][0] = temp;
	temp = matrix[1][0] + matrix[1][1];
	matrix[1][1] = matrix[1][0];
	matrix[1][0] = temp;
}

int mPow(int matrix[2][2], int n)
{
	if(n > 1)
	{
		mPow(matrix, n / 2);
		int m[2][2];
		m[0][0] = matrix[0][0] * matrix[0][0] + matrix[0][1] * matrix[1][0];
		m[0][1] = matrix[0][0] * matrix[0][1] + matrix[0][1] * matrix[1][1];
		m[1][0] = matrix[1][0] * matrix[0][0] + matrix[1][1] * matrix[1][0];
		m[1][1] = matrix[1][0] * matrix[0][1] + matrix[1][1] * matrix[1][1];
		matrix[0][0] = m[0][0];
		matrix[0][1] = m[0][1];
		matrix[1][0] = m[1][0];
		matrix[1][1] = m[1][1];
	}
	if(n % 2)
		mMultiply(matrix);
}

