#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define STRING_MAX_LENGTH (50)

typedef struct _osoba* Position;

typedef struct _osoba
{
	char ime[STRING_MAX_LENGTH];
	char prezime[STRING_MAX_LENGTH];
	int godinaRodenja;
	Position next;
}Student;

typedef struct _studentPodaci
{
	char ime[STRING_MAX_LENGTH];
	char prezime[STRING_MAX_LENGTH];
	int godinaRodenja;
}StudentPodaci;

int InsertAfter(Position position, StudentPodaci studentPodaci);
int InsertEnd(Position head, StudentPodaci studentPodaci);
void IspisListe(Position head);
int DeleteElement(Position position, StudentPodaci studentPodaci);
Position FindPreviousElement(Position head, char *prezime);

int IspisIzbornika();
void PrintElement(Position position);
StudentPodaci GetStudentDataFromConsole();
void FreeAlocatedData(Position head, StudentPodaci studentPodaci);

int main(int agrc, char *argv[])
{
	char izbor = 0;
	char prezime[STRING_MAX_LENGTH];
	Student head;
	StudentPodaci bufferStudent;
	Position bufferPosition;

	head.next = NULL;

	while (izbor != 'K' && izbor != 'k')
	{
		IspisIzbornika();
		scanf_s(" %c", &izbor, 1);
		switch (izbor)
		{
		case '1':
			bufferStudent = GetStudentDataFromConsole();
			InsertAfter(&head, bufferStudent);
			break;
		case '2':
			IspisListe(&head);
			break;
		case '3':
			bufferStudent = GetStudentDataFromConsole();
			InsertEnd(&head, bufferStudent);
			break;
		case '4':
			printf("\nUnesite prezime studenta cije podatke ispisujemo: ");
			scanf(" %s", prezime);
			bufferPosition = FindPreviousElement(&head, prezime);
			if (bufferPosition != NULL)
				PrintElement(bufferPosition->next);
			else
				printf("\nElement ne postoji u listi.");
			break;
		case '5':
			printf("\nUnesite prezime studenta cije podatke brisemo: ");
			scanf(" %s", prezime);
			bufferPosition = FindPreviousElement(&head, prezime);
			if (bufferPosition != NULL)
				DeleteElement(bufferPosition->next, bufferStudent);
			else
				printf("\nElement ne postoji u listi.");
				break;
		case 'k':
		case 'K':
			break;
		default:
			printf("\r\nPogresan izbor <%c>.\r\nPokusajte ponovno.\r\n", izbor);
			break;
	}
		

	}
	FreeAlocatedData(&head, bufferStudent);
	IspisListe(&head);

	system("pause");
	return 0;
}

int IspisIzbornika()
{
	printf("\r\n\r\n");
	printf("\t1. Unos elementa u listu\r\n");
	printf("\t2. Ispis liste\r\n");
	printf("\t3. Unos na kraj\r\n");
	printf("\t4. Pronadji po prezimenu\r\n");
	printf("\t5. Izbrisi po prezimenu\r\n");
	printf("\tK. Izlaz iz programa\r\n");
	printf("\r\n\tIzbor : ");

	return 0;
}

int InsertAfter(Position position, StudentPodaci studentPodaci)
{
	Position newItem = NULL;
	if (position == NULL)
	{
		return -1;
	}

	newItem = (Position)malloc(sizeof(Student));
	if (newItem == NULL)
	{
		return -2;
	}

	newItem->godinaRodenja = studentPodaci.godinaRodenja;
	strcpy(newItem->ime, studentPodaci.ime);
	strcpy(newItem->prezime, studentPodaci.prezime);
	newItem->next = NULL;

	newItem->next = position->next;
	position->next = newItem;

	return 0;
}

int InsertEnd(Position head, StudentPodaci studentPodaci)
{
	

	while (head->next != NULL)
	{
		head = head->next;
	}

	InsertAfter(head, studentPodaci);

	return 0;
}

void IspisListe(Position head)
{
	if (head->next == NULL)
	{
		printf("Lista je prazna!");
	}
	else
	{ 
		while (head->next != NULL)
		{
			printf("%s %s %d\n", head->next->ime, head->next->prezime, head->next->godinaRodenja);
			head = head->next;
		}
	}
}

int DeleteElement(Position position, StudentPodaci studentPodaci)
{
	Position toDelete = NULL;
	toDelete = (Position)malloc(sizeof(StudentPodaci));

	if (position == NULL)
	{
		return -1;
	}

	toDelete = position;
	position = position->next;
	free(toDelete);
	printf("\nUspjesno obrisano!\n");
	return 0;

}

Position FindPreviousElement(Position head, char *prezime)
{
	Position prevItem = head;

	while (head->next != NULL && strcmp(head->next->prezime, prezime) != 0)
	{
		prevItem = head->next;
		head = head->next;
	}
	
	if (strcmp(prevItem->next->prezime, prezime) != 0)
	{
		prevItem = NULL;
	}

	return prevItem;
}

void PrintElement(Position position)
{	
	printf("\n[STUDENT]: %s %s %d\n", position->ime, position->prezime, position->godinaRodenja);
}

StudentPodaci GetStudentDataFromConsole()
{
	StudentPodaci consoleData;

	printf("Ime: ");
	scanf(" %s", consoleData.ime);
	printf("Prezime: ");
	scanf(" %s", consoleData.prezime);
	printf("Godina rodenja: ");
	scanf(" %d", &consoleData.godinaRodenja);

	return consoleData;
}

void FreeAlocatedData(Position head, StudentPodaci studentPodaci)
{
	Position toDelete = NULL;
	toDelete = (Position)malloc(sizeof(StudentPodaci));

	while (head->next != NULL)
	{
		toDelete = head->next;
		head->next = toDelete->next;
		free(toDelete);
	}
}