#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    int nIter = 0;
	double x, y;
	int count = 0;
	double z, pi;

	printf("Enter the number of iterations used to estimate pi: ");
	scanf("%d", &nIter);

	srand(time(0));
	for(int i = 0; i < nIter; ++i)
	{
		x = (double)rand() / RAND_MAX;
		y = (double)rand() / RAND_MAX;
		z = x * x + y * y;
		if(z <= 1) ++count;
	}
	pi = (double)count / nIter * 4;
	printf("# of trials = %d, estimate of pi is %g\n", nIter, pi);

    return 0;
}
