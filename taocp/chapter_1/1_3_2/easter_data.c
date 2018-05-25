/*
 * Find date of Easter for current year
 */

#include <stdio.h>

void easter(const int *);

int main()
{
	int year;

	printf("Enter year for which date of Easter is desired: ");
	scanf("%d", &year);

	easter(&year);

	return(0);
}

void easter(const int *year)
{
	int golden_number,
		century,
		dropped_leap_year,
		correction,
		day,
		epact,
		date;

	golden_number = *year % 19 + 1;

	century = *year / 100 + 1;

	dropped_leap_year = (3 * century) / 4 - 12;
	correction = (8 * century + 5) / 25 - 5;

	day = (5 * *year) / 4 - dropped_leap_year - 10;

	epact = (11 * golden_number + 20 + correction - dropped_leap_year) % 30;

	if(epact == 25 && golden_number > 1)
		++epact;

	date = 44 - epact;
	
	if(date < 21)
		date += 30;

	date = (date + 7) - ((day + date) % 7);

	if(date > 31)
		printf("%d of April\n", date - 31);
	else
		printf("%d of March\n", date);
}
