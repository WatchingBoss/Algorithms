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

typedef enum {false, true} bool;

static size_t count = 0;

static void
sys_er(const char *e)
{
	perror(e);
	exit(EXIT_FAILURE);
}

static void *
xmalloc(int size)
{
	void *ptr = malloc(size);
	if(!ptr)
		sys_er("malloc error");
	return ptr;
}

static void *
xrealloc(void *ptr, int size)
{
	void *new_ptr = realloc(ptr, size);
	if(!new_ptr)
		sys_er("realloc error");
	return new_ptr;
}

static void
freeMem(char ***p)
{
	for(size_t i = 0; i < count; ++i)
		free((*p)[i]);
	free(*p);
}

static void
freeAll(char ***f, char ***b,char ***s, char ***i)
{
	freeMem(f);
	freeMem(b);
	freeMem(s);
	freeMem(i);
}

static void
getFiles(char ***files)
{
	DIR *dir;
	struct dirent *dp;
	char **fileNames = NULL;

	if( !(dir = opendir(DIR_PATH)) )
		sys_er("opendir error");

	while( (dp = readdir(dir)) )
	{
		const size_t len = strlen(dp->d_name) + 1;
		fileNames = (char *)xrealloc(fileNames, (count + 1) * sizeof fileNames);
		fileNames[count] = (char *)xmalloc(len * sizeof *fileNames);
		memcpy(fileNames[count++], dp->d_name, len);
	}
	--count;
	closedir(dir);

	*files = fileNames;
}

static int
compStr(const char *str1, const char *str2)
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

static void
swap(char **prev, char **next)
{
	char *temp = *prev;
	*prev = *next;
	*next = temp;
}

static void
Bubble_sort(char **files)
{
	for(size_t i = 0; i < count - 1; ++i)
		for(size_t j = 0; j < count - i; ++j)
			if(compStr(files[j], files[j + 1]) > 0)
				swap(&files[j], &files[j + 1]);
}

static void
Selection_sort(char **files)
{
	for(size_t i = 0; i < count - 1; ++i)
	{
		size_t min = i;
		for(size_t j = i + 1; j <= count; ++j)
		{
			if(compStr(files[min], files[j]) > 0)
				min = j;
		}
		swap(&files[min], &files[i]);
	}
}

static void
Insertion_sort(char **files)
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

static void
copy(char **src, char ***dest)
{
	*dest = (char *)xmalloc(count * sizeof *dest);
	for(size_t i = 0; i <= count; ++i)
	{
		const char *temp = src[i];
		const size_t len = strlen(temp) + 1;
		(*dest)[i] = xmalloc(len * sizeof **dest);
		memcpy((*dest)[i], temp, len);
	}
}

static void
copy_names(char **files, char ***bub, char ***ins, char ***sel)
{
	copy(files, bub);
	copy(files, sel);
	copy(files, ins);
}

static float
sorting(char **files, void (*sort_f)(char **), bool check, const char *type)
{
	struct timeval before, after, dif;

	gettimeofday(&before, NULL);
	(*sort_f)(files);
	gettimeofday(&after, NULL);

	timersub(&after, &before, &dif);
	float sec = (float)dif.tv_usec / 1000000.f;

	printf("%.6f seconds for %s\n", sec, type);

	if(check)
	{
		printf("========== %s ==========\n", type);
		for(size_t i = 0; i <= count; ++i)
			printf("%s\n", files[i]);
	}
		
	return sec;
}

static void
run_sort(char **bub, char **sel, char **ins, bool check)
{
	float
		bub_t = sorting(bub, Bubble_sort, check, "Bubble Sort"),
		sel_t = sorting(sel, Selection_sort, check, "Selection Sort"),
		ins_t = sorting(ins, Insertion_sort, check, "Insertion Sort");

	printf("Selection sort faster than bubble sort in    %.1f times\n"
		   "Insertion sort faster than bubble sort in    %.1f times\n"
		   "Insertion sort faster than selection sort in %.1f times\n",
		   bub_t / sel_t, bub_t / ins_t, sel_t / ins_t);
}

int main()
{
	char
		**files = NULL,
		**bubble = NULL, **selection = NULL, **insertion = NULL;

	getFiles(&files);

	copy_names(files, &bubble, &insertion, &selection);

	run_sort(bubble, insertion, selection, false);

	freeAll(&files, &bubble, &insertion, &selection);

	return 0;
}
