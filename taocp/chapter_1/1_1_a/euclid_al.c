#include <stdio.h>

void algo(const int*,const int*);

int main()
{
	int m, n;

	printf("Enter m and n integers: ");
	scanf("%d %d", &m, &n);

	if(m >= 0 && n >= 0)
		algo(&m, &n);

	return 0;
}

void algo(const int *m, const int *n)
{
	int r = 0, m1, n1;

	// Exchange m and n if m < n
	if(*m >= *n)
	{
		m1 = *m;
		n1 = *n;
	}
	else
	{
		m1 = *n;
		n1 = *m;
	}

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

