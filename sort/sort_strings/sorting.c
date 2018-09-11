/* 
 * Using bubble, selection, insertion sorting algorithms
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <sys/types.h>
#include <sys/time.h>
#include <dirent.h>

#define DIR_PATH "/usr/include"

typedef enum{false, true} bool;

static size_t count = 0;

void sys_er(const char *e)
{
	perror(e);
	exit(EXIT_FAILURE);
}

void * xmalloc(int size)
{
	void *ptr = malloc(size);
	if(!ptr)
		sys_er("malloc error");
	return ptr;
}

void * xrealloc(void *ptr, int size)
{
	void *new_ptr = realloc(ptr, size);
	if(!new_ptr)
		sys_er("realloc error");
	return new_ptr;
}

void freeMem(char **a, char **b, char **c, char **d)
{
	for(size_t i = 0; i < count; ++i)
	{
		free(a[i]);
		free(b[i]);
		free(c[i]);
		free(d[i]);

	}
	free(a);
	free(b);
	free(c);
	free(d);
}

void getFiles(char ***files)
{
	DIR *dir;
	struct dirent *dp;
	char **fileNames = NULL;

	if( !(dir = opendir(DIR_PATH)) )
		sys_er("opendir error");

	while( (dp = readdir(dir)) )
	{
		const size_t len = strlen(dp->d_name) + 1;
		fileNames = xrealloc(fileNames, (count + 1) * sizeof fileNames);
		fileNames[count] = xmalloc(len * sizeof *fileNames);
		memcpy(fileNames[count++], dp->d_name, len);
	}
	--count;
	closedir(dir);

	*files = fileNames;
}

int compStr(const char *str1, const char *str2)
{
	size_t len1 = strlen(str1) + 1, len2 = strlen(str2) + 1;
	char news1[len1], news2[len2];
	bzero(news1, len1);
	bzero(news2, len2);
	memcpy(news1, str1, len1);
	memcpy(news2, str2, len2);

	for(size_t i = 0, j = 0; news1[i] != '\0' || news2[j] != '\0'; ++i, ++j)
	{
		news1[i] = tolower(news1[i]);
		news2[j] = tolower(news2[j]);
	}

	if(strcmp(news1, news2) > 0)
		return 1;
	return 0;
}

void b_sort(char **files)
{
	for(size_t i = 0; i < count; ++i)
		for(size_t j = 0; j < count; ++j)
			if(compStr(files[j], files[j + 1]) > 0)
			{
				char *temp = files[j];
				files[j] = files[j + 1];
				files[j + 1] = temp;
			}
}

void s_sort(char **files)
{
	for(size_t i = 0; i < count - 1; ++i)
	{
		size_t min = i;
		for(size_t j = i + 1; j <= count; ++j)
		{
			if(compStr(files[min], files[j]) > 0)
				min = j;
		}

		char *temp = files[min];
		files[min] = files[i];
		files[i] = temp;
	}
}

void i_sort(char **files)
{
	for(size_t i = 1; i <= count; ++i)
	{
		char *key = files[i];
		int j = i - 1;

		while(j >= 0 && (compStr(files[j], key) > 0))
		{
			files[j + 1] = files[j];
			--j;
		}
		files[j + 1] = key;
	}
}

void copy_names(char **files, char ***bub, char ***ins, char ***sel)
{
	*bub = xmalloc(count * sizeof *bub);
	*ins = xmalloc(count * sizeof *ins);
	*sel = xmalloc(count * sizeof *sel);

	for(size_t i = 0; i <= count; ++i)
	{
		char *temp = files[i];
		const size_t len = strlen(temp) + 1;

		(*bub)[i] = xmalloc(len * sizeof **bub);
		memcpy((*bub)[i], temp, len);

		(*ins)[i] = xmalloc(len * sizeof **ins);
		memcpy((*ins)[i], temp, len);

		(*sel)[i] = xmalloc(len * sizeof **sel);
		memcpy((*sel)[i], temp, len);
	}
}

void run_sort(char ** bubble, char **selection, char **insertion, bool check)
{
	float bub = 0.f, sel = 0.f, ins = 0.f;
	{
		struct timeval before, after, dif;
		gettimeofday(&before, NULL);
		b_sort(bubble);
		gettimeofday(&after, NULL);
		timersub(&after, &before, &dif);
		float sec = (float)dif.tv_usec / 1000000.f;
		printf("%.6f seconds for bubble sort\n", sec);
		bub = sec;
	}
	{
		struct timeval before, after, dif;
		gettimeofday(&before, NULL);
		s_sort(selection);
		gettimeofday(&after, NULL);
		timersub(&after, &before, &dif);
		float sec = (float)dif.tv_usec / 1000000.f;
		printf("%.6f seconds for selection sort\n", sec);
		sel = sec;
	}
	{
		struct timeval before, after, dif;
		gettimeofday(&before, NULL);
		i_sort(insertion);
		gettimeofday(&after, NULL);
		timersub(&after, &before, &dif);
		float sec = (float)dif.tv_usec / 1000000.f;
		printf("%.6f seconds for insertion sort\n", sec);
		ins = sec;
	}
	printf("Selection sort faster than bubble sort in    %.1f times\n"
		   "Insertion sort faster than bubble sort in    %.1f times\n"
		   "Insertion sort faster than selection sort in %.1f times\n",
		   bub / sel, bub / ins, sel / ins);

	if(!check) return;

	puts("=============== Bubble sort ===============");
	for(size_t i = 0; i <= count; ++i)
		printf("%s\n", bubble[i]);

	puts("=============== Insertion sort ===============");
	for(size_t i = 0; i <= count; ++i)
		printf("%s\n", insertion[i]);

	puts("=============== Selection sort ===============");
	for(size_t i = 0; i <= count; ++i)
		printf("%s\n", selection[i]);
}

int main()
{
	char
		**files = NULL,
		**bubble = NULL, **insertion = NULL, **selection = NULL;

	getFiles(&files);

	copy_names(files, &bubble, &insertion, &selection);

	run_sort(bubble, insertion, selection, false);

//	freeMem(files, bubble, insertion, selection);


	for(size_t i = 0; i < count; ++i)
	{
		free(files[i]);
		free(bubble[i]);
		free(insertion[i]);
		free(selection[i]);
	}
	free(files);
//	free(bubble);
//	free(insertion);
//	free(selection);

	return 0;
}
