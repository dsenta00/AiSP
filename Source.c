#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define PRAZNI_RED printf("\n")


int CountStudents(char *fileName);
int ReadStudentsFromFile(struct student *s, int count, char *fileName);
int PrintStudents(struct student *s, int count, int max, int *rel_Bod);
int Max_Points(char *fileName);

struct student
{
	char ime[15];
	char prezime[15];
	int bodovi;
};

int main()
{

	char fileName[20] = "stud.txt";
	int *rel_Bodovi = (int *)malloc(sizeof(int)*CountStudents(fileName));

	struct student *Students = (struct student *)malloc(sizeof(struct student)*CountStudents(fileName));


	printf("Studenata je %d.\n", CountStudents(fileName));
	printf("Najveci broj bodova je %d.\n", Max_Points(fileName));
	PRAZNI_RED;
	ReadStudentsFromFile(Students, CountStudents(fileName), fileName);
	PrintStudents(Students, CountStudents(fileName), Max_Points(fileName), rel_Bodovi);

	free(Students);
	free(rel_Bodovi);

	system("pause");
	return 0;
}

int CountStudents(char *fileName) {

	char str[50];
	int brojac_Studenata = 0;
	FILE *fp;
	fp = fopen(fileName, "r");
	if (fp == NULL)
	{
		printf("greskaa");
		return -1;
	}

	while (!feof(fp))
	{
		fgets(str, 50, fp);
		brojac_Studenata++;
	}

	fclose(fp);
	return brojac_Studenata;
}


int Max_Points(char *fileName)
{
	int tmp = 0;
	int max = 0;


	FILE *fp;
	fp = fopen(fileName, "r");
	if (fp == NULL)
	{

		printf("Greska");
		return -1;
	}
	while (!feof(fp))
	{
		fscanf(fp, "%*s %*s %d", &tmp);
		if (tmp > max)
		{
			max = tmp;
		}
	}
	fclose(fp);
	return max;
}


int ReadStudentsFromFile(struct student *s, int count, char *fileName)
{

	FILE *fp;
	fp = fopen(fileName, "r");
	if (fp == NULL)
	{

		printf("Greska");
		return -1;
	}

	for (int i = 0; i < count; i++)
	{
		fscanf(fp, " %s %s %d", s->ime, s->prezime, &s->bodovi);
		//printf("%s %s %d ", s->ime, s->prezime, s->bodovi);
		s++;
	}
	fclose(fp);
}


int PrintStudents(struct student *s, int count, int max, int *rel_Bod)
{

	for (int i = 0; i < count; i++)
	{
		*rel_Bod = (s->bodovi * 100) / max;
		if ((float)*rel_Bod / 100 >= 0.5)
			*rel_Bod = *rel_Bod + 1;
		printf("[Ime]:%s\t [Prezime]:%s\t [Aps.bodovi]:%d\t [Rel.bodovi]:%d\n", s->ime, s->prezime, s->bodovi, *rel_Bod);
		s++;
		rel_Bod++;
	}

	PRAZNI_RED;
	return 0;
}