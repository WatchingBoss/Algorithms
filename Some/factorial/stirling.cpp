#include <iostream>
#include <iomanip>
#include <cmath>

#define PI 3.14159265
#define E  2.71828183

void compare(const int *);
int stirling(const int *);
int loop(const int *);

int main()
{
	int number;

	std::cout << "Enter your number: ";
	std::cin >> number;
	std::cout << std::endl;

	if(number <= 12)
		compare(&number);
	else
		std::cout << number << " is too large, we use 32-bit int, "
				  << "hence try max value 12" << std::endl;
	
	return(0);
}

void compare(const int *number)
{
	int rStirling = 0,
		   rLoop     = 0;
	double iDiffer = 0;

	rStirling = stirling(number);
	rLoop     = loop(number);

	iDiffer = (static_cast <double> (rStirling) / static_cast <double> (rLoop));

	std::cout << "Result of stirling formula: " << rStirling << "\n"
			  << "Result of simple loop:      " << rLoop << "\n" << std::endl;
	std::cout << std::setprecision(4) << std::fixed;
	std::cout << "Difference is:              " << iDiffer << "%" << std::endl;
}

int stirling(const int *number)
{
	// n! = sqrt(2pin) * (n / e) ^ n

	double first_part  = 0,
		   second_part = 0;
	int n = *number;
	int result = 1;

	first_part  = sqrt(static_cast <double> (2 * PI * n));
	second_part = pow(static_cast <double> (n / E), static_cast <double> (n));

	result = static_cast <int>(first_part * second_part);

	return(result);
}

int loop(const int *number)
{
	int result = 1;

	for(int i = 1; i <= *number; ++i)
		result *= i;

	return(result);
}
