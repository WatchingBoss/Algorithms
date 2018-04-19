#include <iostream>

void algo(const int &,const int &);

int main()
{
    int m, n;

	std::cout << "Enter m and n integers: ";
	std::cin >> m >> n;

	algo(m, n);

    return 0;
}

void algo(const int &m, const int &n)
{
	int r, m1 = m, n1 = n;

	while(r >= 0)
	{
		r = m1 % n1;

		if(r == 0)
		{
			std::cout << n1 << " is the greatest common division of " << m
					  << " and " << n << std::endl;
			break;
		}
		else
		{
			m1 = n1;
			n1 = r;
		}
	}
}
