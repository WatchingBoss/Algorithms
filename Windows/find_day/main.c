#include <stdio.h>

void dayWeek(int day, int month, int year)
{
    char *dayWeek[] = { "Monday", "Tuesday", "Wednesday", "Thursday",
                        "Friday", "Saturday", "Sunday" };
    int i = (day + ((153 * (month + 12 * ((14 - month) / 12) - 3) + 2) / 5)
             + (365 * (year + 4800 - ((14 - month) / 12)))
             + ((year + 4800 - ((14 - month) / 12)) / 4)
             - ((year + 4800 - ((14 - month) / 12)) / 100)
             + ((year + 4800 - ((14 - month) / 12)) / 400) - 32045) % 7;
    printf("It is %s\n", dayWeek[i]);
}

int main()
{
    int day, month, year;
    puts("Prompt data in format (DD, MM, YYYY)");
    scanf("%d %d %d", &day, &month, &year);
    if (day > 31)
    {
        printf("Not correct day %d\n", day);
		puts("Press enter to exit");
		fgetc(stdin);
        fgetc(stdin);
        return 0;
    }
    if (month > 12)
    {
        printf("Not correct month %d\n", month);
		puts("Press enter to exit");
		fgetc(stdin);
        fgetc(stdin);
        return 0;
    }
    dayWeek(day, month, year);
	puts("Press enter to exit");
	fgetc(stdin);
    fgetc(stdin);
    return 0;
}