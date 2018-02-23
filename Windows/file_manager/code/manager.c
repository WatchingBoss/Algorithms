/* ========================================================
   File manager for command prompt
   Author: santa
   ======================================================== */
#include <stdio.h>
#include <sys/stat.h>

void file(char *nameFile)
{
	FILE *fi = fopen(nameFile, "w");
	fprintf(fi, "%s", "Created file");
	fclose(fi);
	printf("%s has created successfull\n", nameFile);
}

void dir(char *nameDir)
{
	mkdir(nameDir, 0777);
	printf("%s has created successfull\n", nameDir);
}

void del(char *nameDel)
{
	remove(nameDel);
}

int main()
{
	int point;
	char fileName[80], dirName[80], delName[80];
	
	printf("3 - Create file\n"
		   "2 - Create folder\n"
		   "1 - Remove file\n"
		   "0 - Parent catalog\n");
	scanf("%d", &point);
	while(point > 0 && point < 5)
	{
		switch(point)
		{
			case 3:
			{
				printf("Enter name for file: ");
				fgetc(stdin);
				fgets(fileName, sizeof(fileName), stdin);
				file(fileName);
			} break;
			case 2:
			{
				printf("Enter name for folder: ");
				fgetc(stdin);
				fgets(dirName, sizeof(dirName), stdin);
				dir(dirName);
			} break;
			case 1:
			{
				printf("Enter file name to remove: ");
				fgetc(stdin);
				fgets(delName, sizeof(delName), stdin);
				file(delName);
			} break;
			case 0:
			{
			} break;
			default:
			{
			}break;
		}
		
		printf("3 - Create file\n"
		   "2 - Create folder\n"
		   "1 - Remove file\n"
		   "0 - Parent catalog\n");
		scanf("%d", &point);
	}
	
	puts("We are going out. Bye!");
	fflush(stdout);
	getchar();
	
	return 0;
}
