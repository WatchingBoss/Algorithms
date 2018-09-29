#include <stdio.h>
#include <stdlib.h>

#define PRINT_FREQ 0
#define CHECK 0

void * xmalloc(size_t size);

typedef struct Freq
{
	size_t amount;
	size_t freq[];
} Freq; 

typedef struct Sym_Freq
{
	Freq *freq;
	char symbols[];
} Sym_Freq;

Sym_Freq * create_whole_array(char[], size_t[], char[], size_t[], char[], size_t[], char[], size_t[]);

Sym_Freq * count_freq(char *file)
{
	Sym_Freq *sfa = NULL;
	FILE *fp = fopen(file, "r");
	if(!fp)
	{
		perror("File openning error");
		exit(EXIT_FAILURE);
	}
	char ch = 0;

	size_t freq_lower[26] = {0}, freq_upper[26] = {0}, freq_digit[10] = {0}, freq_other[8] = {0};
	char lower[26] = {0}, upper[26] = {0}, digit[10] = {0}, other[8] = {0};

	for(int i = 0; i < 26; ++i)
		lower[i] = (char)(97 + i);
	for(int i = 0; i < 26; ++i)
		upper[i] = (char)(65 + i);
	for(int i = 0; i < 10; ++i)
		digit[i] = (char)(48 + i);
	other[0] = ' '; other[1] = '!'; other[2] = ','; other[3] = '.';
	other[4] = ':'; other[5] = ';'; other[6] = '?'; other[7] = '\n';

	while((ch = fgetc(fp)) != EOF)
	{
		if(ch >= 97 && ch <= 122)
			freq_lower[ch - 97] += 1;
		else if(ch >= 65 && ch <= 90)
			freq_upper[ch - 65] += 1;
		else if(ch >= 48 && ch <= 57)
			freq_digit[ch - 48] += 1;
		else if(ch == ' ' || ch == '!' || ch == ',' || ch == '.' ||
				ch == ':' || ch == ';' || ch == '?' || ch == '\n')
		{
			switch(ch)
			{
				case ' ':
					freq_other[0] += 1;
					break;
				case '!':
					freq_other[1] += 1;
					break;
				case ',':
					freq_other[2] += 1;
					break;
				case '.':
					freq_other[3] += 1;
					break;
				case ':':
					freq_other[4] += 1;
					break;
				case ';':
					freq_other[5] += 1;
					break;
				case '?':
					freq_other[6] += 1;
					break;
				case '\n':
					freq_other[7] += 1;
					break;
			}
		}
	}

	sfa = create_whole_array(lower, freq_lower, upper, freq_upper,
							 digit, freq_digit, other, freq_other);

#if PRINT_FREQ
	printf("\nLowercase:\n");
	for(int i = 0; i < 26; ++i)
		if(freq_lower[i])
			printf("%2c - %ld\n", lower[i], freq_lower[i]);
	printf("\nUppercase:\n");
	for(int i = 0; i < 26; ++i)
		if(freq_upper[i])
			printf("%2c - %ld\n", upper[i], freq_upper[i]);
	printf("\nDigits:\n");
	for(int i = 0; i < 10; ++i)
		if(freq_digit[i])
			printf("%2c - %ld\n", digit[i], freq_digit[i]);
	printf("\nOther symbols:\n");
	for(int i = 0; i < 7; ++i)
		if(freq_other[i])
			if(freq_other[i])
				printf("%2c - %ld\n", other[i], freq_other[i]);
	if(freq_other[7])
		printf("\\n - %ld\n", freq_other[7]);
#endif

	return sfa;
}

Sym_Freq * create_whole_array(char lower[], size_t freq_lower[],
							  char upper[], size_t freq_upper[],
							  char digit[], size_t freq_digit[],
							  char other[], size_t freq_other[])
{
	size_t quantity = 0, seq = 0;

	for(int i = 0; i < 26; ++i)
		if(freq_lower[i])
			++quantity;
	for(int i = 0; i < 26; ++i)
		if(freq_upper[i])
			++quantity;
	for(int i = 0; i < 10; ++i)
		if(freq_digit[i])
			++quantity;
	for(int i = 0; i < 8; ++i)
		if(freq_other[i])
			++quantity;

	char symbols[quantity];
	size_t freq[quantity];

	for(int i = 0; i < 26; ++i)
		if(freq_lower[i])
		{
			symbols[seq] = lower[i];
			freq[seq++] = freq_lower[i];
		}
	for(int i = 0; i < 26; ++i)
		if(freq_upper[i])
		{
			symbols[seq] = upper[i];
			freq[seq++] = freq_upper[i];
		}
	for(int i = 0; i < 10; ++i)
		if(freq_digit[i])
		{
			symbols[seq] = digit[i];
			freq[seq++] = freq_digit[i];
		}
	for(int i = 0; i < 7; ++i)
		if(freq_other[i])
		{
			symbols[seq] = other[i];
			freq[seq++] = freq_other[i];
		}

	Sym_Freq *sfa = xmalloc(sizeof(Sym_Freq) + sizeof seq * seq);
	Freq *fr = xmalloc(sizeof(Freq) + sizeof seq * seq);

	fr->amount = seq;
	for(int i = 0; i < seq; ++i)
	{
		sfa->symbols[i] = symbols[i];
		fr->freq[i] = freq[i];
	}
	sfa->freq = fr;

#if CHECK 
	for(int i = 0; i < seq; ++i)
		printf("%2c - %ld\n", symbols[i], freq[i]);
#endif

	return sfa;
}
