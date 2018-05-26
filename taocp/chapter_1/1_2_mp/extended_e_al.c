/*****************************************************************************/
/*   This algorithm provides to find greatest common divisor of two numbers  */
/*****************************************************************************/

#include <stdio.h>

int algo(int const *, int const *);

int main()
{
	int m = 0, n = 0;

	printf("Enter m and n: ");
	scanf("%d %d", &m, &n);

	if(m > 0 && n > 0)
		printf("%d is the greatest common divisor of %d and %d \n", algo(&m, &n), m, n);

    return 0;
}

int algo(int const *m, int const *n)
{
	int a, b, a1, b1,
		c, d,
		r, q,
		t;

	c  = *m;
	d  = *n;
	a  = b1 = 0;
	a1 = b  = 1;

	while(r >= 0)
	{
		q = c / d;
		r = c % d;

		if(r == 0) // a * m + b * n == d and a1 * m + b1 * n == c
			break;

		c  = d;
		d  = r;
		t  = a1;
		a1 = a;
		a  = t - (q * a);
		t  = b1;
		b1 = b;
		b  = t - (q * b);
	}

	return(d);
}
