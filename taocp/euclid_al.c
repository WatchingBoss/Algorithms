#include <stdio.h>

void algo(const int*,const int*);

int main()
{
	int m, n;

	printf("Enter m and n integers: ");
	scanf("%d %d", &m, &n);

	algo(&m, &n);

	return 0;
}

void algo(const int *m, const int *n)
{
	int r, m1 = *m, n1 = *n;
	while (r >= 0)
    {
		r = m1 % n1;
		if (r == 0)
		{
			printf("%d is the greatest common divison of %d and %d\n", n1, *m, *n);
			break;
		}
		else
		{
			m1 = n1;
			n1 = r;
		}
    }
}
