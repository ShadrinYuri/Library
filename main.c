#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <time.h>

#define size 100
#define max 1000

struct library {
	unsigned long long isbn;
  char id[size];
  char data[size];
};

struct user {
  char login[size];
  char pass[size];
  int book;
	int student;
};

struct book {
	unsigned long long isbn;
	char author[size];
	char title[size];
	int abook;
	int ubook;
};

struct student {
    char id[size];
    char surname[size];
    char name[size];
    char middlename[size];
    char department[size];
    char major[size];
};

//student_book.csv
int lineSB()
{
	int line = 0;
  FILE *f = fopen("student_book.csv", "r+");
	if (f == NULL)
	{
		printf("No file!\n");
	}
	else
	{
		while (!feof(f))
		{
			if (fgetc(f)=='\n')
				line++;
		}
		return ++line;
		fclose(f);
	}
}

struct library *readfileSB()
{
	struct library *readlibrary =  calloc(0, sizeof(struct library));
	FILE *f = fopen("student_book.csv", "r");
	if (f == NULL)
	{
		printf("Not file\n");
		return 0;
	}
	else
	{
		int line = lineSB();
		char buf[max];
		for (int i = 0; i < line; i++)
		{
			fgets(buf, max, f);

			readlibrary = realloc(readlibrary, (i+1) * sizeof(struct library));

			readlibrary[i].isbn = atoll(strtok(buf,";")); //разбиение строки на части по указанному разделителю ;
			strcpy(readlibrary[i].id,strtok(NULL,";"));
			strcpy(readlibrary[i].data,strtok(NULL,"\n"));
		}
		return readlibrary;
	}
}

void listSB(struct library *libraries, int line)
{
	char ISBN[8] = "   ISBN";
	char ID[6] = "  ID";
	char data[10] = " Data";
	printf("%-10s %-10s %-10s\n",ISBN, ID, data);

	for(int i = 0; i < line; i++)
	{
		if (libraries[i].isbn != 0) printf("%10lli; %-6s; %-10s\n", libraries[i].isbn ,libraries[i].id, libraries[i].data);
	}
}

struct library *writefileSB(struct library *libraries, int line)
{
	FILE *f = fopen("student_book.csv", "w+");
	rewind(f);

	for (int i = 0; i < 1; i++)
	{
		fprintf(f,"%lli",libraries[i].isbn);
		fprintf(f,";%s",libraries[i].id);
		fprintf(f,";%s",libraries[i].data);
	}
	for (int i = 1; i < line; i++)
	{
		fprintf(f,"\n%lli",libraries[i].isbn);
		fprintf(f,";%s",libraries[i].id);
		fprintf(f,";%s",libraries[i].data);
	}
	fclose(f);
}

//checing
int checkBk(struct book *books, long long ISBN, int line)
{
	int fl = -1;

	for (int i = 0; i < line; i++)
	{
		if (ISBN == books[i].isbn)
			fl = i;
	}

	return fl;
}

int checkBkAuthor(struct book *books, char author[size], int line)
{
	int fl = -1;

	for (int i = 0; i < line; i++)
	{
		if (strcmp(author, books[i].author) == 0) // сравнение строк, если полностью совпадает, то выдает 0
			fl = i;
	}

	return fl;
}

int checkBL(struct book *books, struct library *libraries, long long ISBN, int line)
{
	int fl = -1;

	for (int i = 0; i < line; i++)
	{
		if (ISBN == books[i].isbn)
			fl = i;
	}

	if (fl != -1)
	{
		for (int i = 0; i < line; i++)
		{
			if (ISBN == libraries[i].isbn)
				fl = -2;
		}
	}
	return fl;
}

int checkSt(struct student *students, char id[size], int line)
{
	int fl = -1;

	for (int i = 0; i < line; i++)
	{
		if (strcmp(id, students[i].id) == 0)
			fl = i;
	}

	return fl;
}

int checkStSurname(struct student *students, char surname[size], int line)
{
	int fl = -1;

	for (int i = 0; i < line; i++)
	{
		if (strcmp(surname, students[i].surname) == 0)
			fl = i;
	}

	return fl;
}

int checkSL(struct student *students, struct library *libraries, char id[size], int line)
{
	int fl = -1;

	for (int i = 0; i < line; i++)
	{
		if (strcmp(id, students[i].id) == 0)
			fl = i;
	}

	if (fl != -1)
	{
		for (int i = 0; i < line; i++)
		{
			if (strcmp(id, libraries[i].id) == 0)
				fl = -2;
		}
	}

	return fl;
}

//book.csv
int lineBk()
{
	int line = 0;
  FILE *f = fopen("book.csv", "r+");
	if (f == NULL)
	{
		printf("No file!\n");
	}
	else
	{
		while (!feof(f))
		{
			if (fgetc(f)=='\n')
				line++;
		}
		return ++line;
		fclose(f);
	}
}

int lineBkcopy(char namefile[size])
{
	int line = 0;
  FILE *f = fopen(namefile, "r+");
	if (f == NULL)
	{
		return -1;
	}
	else
	{
		while (!feof(f))
		{
			if (fgetc(f)=='\n')
				line++;
		}
		return ++line;
		fclose(f);
	}
}

struct book *readfileBk()
{
	struct book *readbook =  calloc(0, sizeof(struct book));
	FILE *f = fopen("book.csv", "r");
	if (f == NULL)
	{
		printf("Not file\n");
		return 0;
	}
	else
	{
		int line = lineBk();
		char buf[max];
		for (int i = 0; i < line; i++)
		{
			fgets(buf, max, f); //построчное считывание

			readbook = realloc(readbook, (i+1) * sizeof(struct book));

			readbook[i].isbn = atoll(strtok(buf,";"));//atoll преобразовывает тип lli
			strcpy(readbook[i].author,strtok(NULL,";"));
			strcpy(readbook[i].title,strtok(NULL,";"));
			readbook[i].abook = atoi(strtok(NULL,";"));
			readbook[i].ubook = atoi(strtok(NULL,"\n"));
		}
		return readbook;
	}
}

struct book *writefileBk(struct book *books, int line)
{
	FILE *f = fopen("book.csv", "w+");
	rewind(f);

	for (int i = 0; i < 1; i++)
	{
		fprintf(f,"%lli",books[i].isbn);
		fprintf(f,";%s",books[i].author);
		fprintf(f,";%s",books[i].title);
		fprintf(f,";%d",books[i].abook);
		fprintf(f,";%d",books[i].ubook);
	}
	for (int i = 1; i < line; i++)
	{
		fprintf(f,"\n%lli",books[i].isbn);
		fprintf(f,";%s",books[i].author);
		fprintf(f,";%s",books[i].title);
		fprintf(f,";%d",books[i].abook);
		fprintf(f,";%d",books[i].ubook);
	}
	fclose(f);
}

struct book *sortbook(struct book *books, int line)
{
	struct book buf;

	for (int i = 0; i < line - 1; i++)
		for( int j = 0; j < line - i; j++)
			if (books[j].isbn > books[j + 1].isbn)
			{
				buf = books[j];
				books[j] = books[j + 1];
				books[j + 1] = buf;
			}

	return books;
}

//22
void listBk(struct book *books, int line)
{
	char ISBN[8] = "   ISBN";
	char author[12] = "     Author";
	char title[13] = "       Title";
	char all[7] = "   All";
	char used[7] = "  Used";
	printf("%-10s %-15s %-15s %-4s %-4s\n", ISBN, author, title, all, used);
	for(int i = 0; i < line; i++)
	{
		if (books[i].isbn != 0) printf("%10lli; %-15s; %-15s; %4d; %4d\n", books[i].isbn,books[i].author, books[i].title, books[i].abook, books[i].ubook);
	}
}

//1
struct book *addbook(struct book *books, int line)
{
	struct book newbook;

	int k;
	printf("Enter ISBN : ");
	do {
		fflush(stdin); // очиста потока ввода
		scanf("%lli",&newbook.isbn);
		k = checkBk(books, newbook.isbn, line);
		if(k != -1)
		{
			printf("Error:This book is already in the file!\n");
			printf("Enter ISBN : ");
		}
	} while(k != -1);

	printf("Enter author : ");
	fflush(stdin);
	gets(newbook.author);

	printf("Enter title : ");
	fflush(stdin);
	gets(newbook.title);

	printf("Enter all book : ");
	fflush(stdin);
	scanf("%d",&newbook.abook);

	printf("Enter used book : ");
	fflush(stdin);
	scanf("%d",&newbook.ubook);

	books = realloc(books, (line+1) * sizeof(struct book));

	books[line].isbn = newbook.isbn;
	strcpy(books[line].author,newbook.author); //копирование строк
	strcpy(books[line].title,newbook.title);
	books[line].abook = newbook.abook;
	books[line].ubook = newbook.ubook;

	printf("Success!\n");

	return books;
}

//2
struct book *deletebook(struct book *books, struct library *libraries, int line)
{
	struct book *bufbooks = calloc(line-1, sizeof(struct book));

	int k;
	printf("Enter ISBN book to delete : ");
	do {
		long long deleteisbn;
		fflush(stdin);
		scanf("%lli",&deleteisbn);
		k = checkBL(books, libraries, deleteisbn, line);
		if(k == -1)
		{
			printf("No book found in file!\n");
			printf("Enter ISBN book to delete : ");
		}
		else if (k == -2)
		{
			printf("The student has this book, so you can't delete it!\n");
			printf("Enter ISBN book to delete : ");
		}
	} while ((k == -1) || (k == -2));

	for (int i = 0; i < line; i++)
	{
		if (i < k)
		{
			bufbooks[i].isbn = books[i].isbn;
			strcpy(bufbooks[i].author, books[i].author);
			strcpy(bufbooks[i].title, books[i].title);
			bufbooks[i].abook = books[i].abook;
			bufbooks[i].ubook = books[i].ubook;
		}
		else if (i > k)
		{
			bufbooks[i-1].isbn = books[i].isbn;
			strcpy(bufbooks[i-1].author, books[i].author);
			strcpy(bufbooks[i-1].title, books[i].title);
			bufbooks[i-1].abook = books[i].abook;
			bufbooks[i-1].ubook = books[i].ubook;
		}
	}
	printf("Success!\n");

	return bufbooks;
}

//3
void infobook(struct book *books, int line)
{
	int k;
	printf("Enter ISBN book to get information : ");
	do {
		long long infoisbn;
		fflush(stdin);
		scanf("%lli", &infoisbn);
		k = checkBk(books, infoisbn, line);
		if(k == -1)
		{
			printf("No book found in file!\n");
			printf("Enter ISBN book to get information : ");
		}
	} while(k == -1);

	for (int i = 0; i < line; i++)
	{
		if (i == k)
		printf("\tISBN: %lli;\n\tAuthor: %s;\n\tTitle: %s;\n\tAll book: %d;\n\tUsed book: %d\n", books[i].isbn,books[i].author, books[i].title, books[i].abook, books[i].ubook);
	}
}

//4
void infoallbooks(struct book *books, int line)
{
	books = sortbook(books, line);

	char ISBN[8] = "   ISBN";
	char author[12] = "     Author";
	char title[13] = "      Title";
	char all[7] = "   All";
	char used[7] = "  Used";
	printf("%-10s|%-15s|%-15s|%-4s|%-4s\n", ISBN, author, title, all, used);

	for(int i = 0; i < line; i++)
	{
		if (books[i].isbn != 0)
		{
				printf("----------+---------------+---------------+------+------\n");
				printf("%10lli|%-15s|%-15s|%6d|%6d\n", books[i].isbn,books[i].author, books[i].title, books[i].abook, books[i].ubook);
		}
	}
	printf("--------------------------------------------------------\n");
}

//5
struct book *editbook(struct book *books, int line)
{
	struct book bufbooks;

	int k;
	printf("Enter ISBN book to edit : ");
	do {
		long long deleteisbn;
		fflush(stdin);
		scanf("%lli",&deleteisbn);
		k = checkBk(books, deleteisbn, line);
		if(k == -1)
		{
			printf("No book found in file!\n");
			printf("Enter ISBN book to edit : ");
		}
	} while(k == -1);

	printf("Enter new author : ");
	fflush(stdin);
	gets(bufbooks.author);

	printf("Enter new title : ");
	fflush(stdin);
	gets(bufbooks.title);

	for(int i = 0; i < line; i++)
	{
		if (i == k)
		{
			strcpy(books[i].author, bufbooks.author);
			strcpy(books[i].title, bufbooks.title);
		}
	}
	printf("Success!\n");

	return books;
}

//6
struct book *changebook(struct book *books, int line)
{
	struct book bufbooks;

	int k;
	printf("Enter ISBN book to change : ");
	do {
		long long deleteisbn;
		fflush(stdin);
		scanf("%lli",&deleteisbn);
		k = checkBk(books, deleteisbn, line);
		if(k == -1)
		{
			printf("No book found in file!\n");
			printf("Enter ISBN book to change : ");
		}
	} while(k == -1);

	printf("Enter new all book : ");
	fflush(stdin);
	scanf("%d",&bufbooks.abook);

	printf("Enter new used book : ");
	fflush(stdin);
	scanf("%d",&bufbooks.ubook);

	for (int i = 0; i < line; i++)
	{
		if (i == k)
		{
			books[i].abook = bufbooks.abook;
			books[i].ubook = bufbooks.ubook;

			printf("\tAuthor of book : %s",books[i].author);
			printf("\n\tTitle of book : %s",books[i].title);
			printf("\n\tTotal books in the library is : %d",books[i].abook);
			printf("\n\tFree books in the library is : %d\n",books[i].abook - books[i].ubook);
		}
	}
	printf("Success!\n");

	return books;
}

//7
struct book *givebook(struct book *books, struct student *students, struct library *libraries, int lineb, int lines, int linesb)
{
	int k;
	printf("Enter ISBN book to give a student : ");
	long long giveisbn;
	do {
		fflush(stdin);
		scanf("%lli",&giveisbn);
		k = checkBk(books, giveisbn, lineb);
		if(k == -1)
		{
			printf("No book found in file!\n");
			printf("Enter ISBN book to give a student : ");
		}
	} while(k == -1);

	if (books[k].abook == books[k].ubook)
	{
		printf("Sorry, there are no books available\n");
		int pos;
		for(int i = 0; i < linesb; i++)
		{
			if (libraries[i].isbn == books[k].isbn)
				pos = i;
		}

		printf("Nearest book, with ISBN: %lli, releases in %s!\n", books[k].isbn, libraries[pos].data);
	}
	else
	{
		int s;
		printf("Enter ID student, who give book : ");
		do {
			char giveid[size];
			fflush(stdin);
			gets(giveid);
			s = checkSt(students, giveid, lines);
			if(s == -1)
			{
				printf("No student found in file!\n");
				printf("Enter ISBN book to give a student : ");
			}
		} while(s == -1);

		int pos = -1;
		for (int i = 0; i < linesb; i++)
		{
			if ((libraries[i].isbn == books[k].isbn) && (strcmp(libraries[i].id, students[s].id) == 0))
				pos = i;
		}

		if(pos != -1)
		{
			printf("The book with ISBN: %lli already taken by a student with ID: %s\n", books[k].isbn, students[s].id);
		}
		else
		{
			printf("Enter data, when student should return book : ");
			char data[size];
			fflush(stdin);
			gets(data);

			libraries = realloc(libraries, (linesb+1) * sizeof(struct library));

			libraries[linesb].isbn = books[k].isbn;
			strcpy(libraries[linesb].id, students[s].id);
			strcpy(libraries[linesb].data, data);
			++linesb;

			writefileSB(libraries, linesb);
			free(libraries);

			books[k].ubook = books[k].ubook + 1;
			printf("Success!\n");
			printf("Free books in the library is : %d\n",books[k].abook - books[k].ubook);
		}
	}
	return books;
}

//8
struct book *takebook(struct book *books, struct student *students, struct library *libraries, int lineb, int lines, int linesb)
{
	int k;
	printf("Enter ISBN book to take a student : ");
	do {
		long long takeisbn;
		fflush(stdin);
		scanf("%lli",&takeisbn);
		k = checkBk(books, takeisbn, lineb);
		if(k == -1)
		{
			printf("No book found in file!\n");
			printf("Enter ISBN book to take a student : ");
		}
	} while(k == -1);

	if (books[k].abook == books[k].ubook)
	{
		printf("Sorry, аll books in the library\n");
	}
	else
	{
		int s;
		printf("Enter ID student, who take book : ");
		char takeid[size];
		do {
			fflush(stdin);
			gets(takeid);
			s = checkSt(students, takeid, lines);
			if(s == -1)
			{
				printf("No student found in file!\n");
				printf("Enter ISBN book to take a student : ");
			}
		} while(s == -1);

		printf("Enter data, when student should return book : ");
		char data[size];
		fflush(stdin);
		gets(data);

		int pos = -1;
		for(int j = 0; j < linesb; j++)
		{
			if ((libraries[j].isbn = books[k].isbn) && (strcmp(libraries[j].id, takeid) == 0) && (strcmp(libraries[j].data, data) == 0))
				pos = j;
		}

		if (pos == -1)
		{
			printf("Error:The student with ID:%s must not return the book with ISBN: %lli to the library \n", students[s].id, books[k].isbn);
		}
		else
		{
			struct library *buflibraries = calloc(linesb-1, sizeof(struct library));

			for (int i = 0; i < linesb; i++)
			{
				if (i < pos)
				{
					buflibraries[i].isbn = libraries[i].isbn;
					strcpy(buflibraries[i].id, libraries[i].id);
					strcpy(buflibraries[i].data, libraries[i].data);
				}
				else if (i > pos)
				{
					buflibraries[i-1].isbn = libraries[i].isbn;
					strcpy(buflibraries[i-1].id, libraries[i].id);
					strcpy(buflibraries[i-1].data, libraries[i].data);
				}
			}
			--linesb;

			writefileSB(buflibraries, linesb);
			free(buflibraries);

			books[k].ubook = books[k].ubook - 1;
			printf("Success!\n");
		}
	}

	return books;
}

//9
int makecopyfileBk(struct book *books, int line)
{
		time_t     now;
    struct tm  ts;
    char  buf[size];
    char copy[size]="books_";
    time(&now);
    ts = *localtime(&now);
    strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", &ts);
    int lencopy=strlen(copy);
    int lenbuf=strlen(buf);
    for(int i = 0; i < lenbuf; i++)
    {
        if(buf[i]==' ')
            buf[i]='.';
        if(buf[i]==':')
            buf[i]='-';
    }
		strcat(copy, buf);
		char csv[size] = ".csv";
		strcat(copy, csv);

		FILE *fcopy = fopen(copy, "w+");
		rewind(fcopy);

		for (int i = 0; i < 1; i++)
		{
			fprintf(fcopy,"%lli",books[i].isbn);
			fprintf(fcopy,";%s",books[i].author);
			fprintf(fcopy,";%s",books[i].title);
			fprintf(fcopy,";%d",books[i].abook);
			fprintf(fcopy,";%d",books[i].ubook);
		}
		for (int i = 1; i < line; i++)
		{
			fprintf(fcopy,"\n%lli",books[i].isbn);
			fprintf(fcopy,";%s",books[i].author);
			fprintf(fcopy,";%s",books[i].title);
			fprintf(fcopy,";%d",books[i].abook);
			fprintf(fcopy,";%d",books[i].ubook);
		}
		fclose(fcopy);

		printf("Success!\n");
}

//10
struct book *restorefileBk(char namefile[size], int line)
{
	struct book *readbook =  calloc(0, sizeof(struct book));
	FILE *f = fopen(namefile, "r");

	char buf[max];
	for (int i = 0; i < line; i++)
	{
		fgets(buf, max, f);

		readbook = realloc(readbook, (i+1) * sizeof(struct book));

		readbook[i].isbn = atoll(strtok(buf,";"));
		strcpy(readbook[i].author,strtok(NULL,";"));
		strcpy(readbook[i].title,strtok(NULL,";"));
		readbook[i].abook = atoi(strtok(NULL,";"));
		readbook[i].ubook = atoi(strtok(NULL,"\n"));
	}
	fclose(f);
	writefileBk(readbook, line);

	printf("Success!\n");
	return readbook;
}

//11
void infobookbyauthor(struct book *books, int line)
{
	int k;
	printf("Enter surname author book to get information : ");
	char infoauthor[size];
	do {
		fflush(stdin);
		gets(infoauthor);
		k = checkBkAuthor(books, infoauthor, line);
		if(k == -1)
		{
			printf("No book found in file!\n");
			printf("Enter surname author book to get information : ");
		}
	} while(k == -1);

	for (int i = 0; i < line; i++)
	{
		if (strcmp(books[i].author, infoauthor) == 0)
			printf("\tISBN: %lli;\n\tAuthor: %s;\n\tTitle: %s;\n\tAll book: %d;\n\tUsed book: %d\n\n", books[i].isbn,books[i].author, books[i].title, books[i].abook, books[i].ubook);
	}
}

//12
void infostudentbybook(struct book *books, struct student *students, struct library *libraries,int lineb, int lines, int linesb)
{
	int k;
	printf("Enter ISBN book to get information : ");
	long long infoisbn;
	do {
		fflush(stdin);
		scanf("%lli", &infoisbn);
		k = checkBk(books, infoisbn, lineb);
		if(k == -1)
		{
			printf("No book found in file!\n");
			printf("Enter ISBN book to get information : ");
		}
	} while(k == -1);

	int num = 0;
	for(int i = 0; i < linesb; i++)
	{
		if (libraries[i].isbn == infoisbn)
		{
			for(int j = 0; j < lines; j++)
			{
				if (strcmp(students[j].id, libraries[i].id) == 0)
				{
					printf("\tID: %s;\n\tSurname: %s;\n\tName: %s;\n\tMiddlename: %s;\n\tDepartment: %s;\n\tMajor: %s\n", students[j].id,students[j].surname, students[j].name, students[j].middlename, students[j].department, students[j].major);
				}
			}
			printf("\tData return book: %s\n\n", libraries[i].data);
			num++;
		}
	}

	if (num == 0)
	{
		printf("The book with ISBN: %lli nobody don't give\n", books[k].isbn);
	}
}

//student.csv
int lineSt()
{
	int line = 0;
	FILE *f = fopen("student.csv", "r+");
	if (f == NULL)
	{
		printf("No file!\n");
	}
	else
	{
		while (!feof(f))
		{
			if (fgetc(f)=='\n')
			line++;
		}
		return ++line;
		fclose(f);
	}
}

int lineStcopy(char namefile[size])
{
	int line = 0;
  FILE *f = fopen(namefile, "r+");
	if (f == NULL)
	{
		return -1;
	}
	else
	{
		while (!feof(f))
		{
			if (fgetc(f)=='\n')
				line++;
		}
		return ++line;
		fclose(f);
	}
}

struct student *readfileSt()
{
	struct student *readstudent =  calloc(0, sizeof(struct student));
	FILE *f = fopen("student.csv", "r");
	if (f == NULL)
	{
		printf("Not file\n");
		return 0;
	}
	else
	{
		int line = lineSt();
		char buf[max];
		for (int i = 0; i < line; i++)
		{
			fgets(buf, max, f);

			readstudent = realloc(readstudent, (i+1) * sizeof(struct student));

			strcpy(readstudent[i].id,strtok(buf,";"));
			strcpy(readstudent[i].surname,strtok(NULL,";"));
			strcpy(readstudent[i].name,strtok(NULL,";"));
			strcpy(readstudent[i].middlename,strtok(NULL,";"));
			strcpy(readstudent[i].department,strtok(NULL,";"));
			strcpy(readstudent[i].major,strtok(NULL,"\n"));
		}
		return readstudent;
	}
}

struct student *writefileSt(struct student *students, int line)
{
	FILE *f = fopen("student.csv", "w+");
	rewind(f);

	for (int i = 0; i < 1; i++)
	{
		fprintf(f,"%s",students[i].id);
		fprintf(f,";%s",students[i].surname);
		fprintf(f,";%s",students[i].name);
		fprintf(f,";%s",students[i].middlename);
		fprintf(f,";%s",students[i].department);
		fprintf(f,";%s",students[i].major);
	}
	for (int i = 1; i < line; i++)
	{
		fprintf(f,"\n%s",students[i].id);
		fprintf(f,";%s",students[i].surname);
		fprintf(f,";%s",students[i].name);
		fprintf(f,";%s",students[i].middlename);
		fprintf(f,";%s",students[i].department);
		fprintf(f,";%s",students[i].major);
	}
	fclose(f);
}

void listSt(struct student *students, int line)
{
	char ID[6] = "  ID";
	char surname[12] = " Surname";
	char name[12] = "    Name";
	char middlename[16] = "    Middlename";
	char department[20] = "        Department";
	char major[20] = "      Major";
	printf("%-10s %-15s %-15s %-15s %-15s %-15s\n", ID, surname, name, middlename, department, major);
	for(int i = 0; i < line; i++)
	{
		if (students[i].id != 0) printf("%-6s; %-15s; %-15s; %-20s; %-15s; %-15s\n", students[i].id,students[i].surname, students[i].name, students[i].middlename, students[i].department, students[i].major);
	}
}

//1
struct student *addstudent(struct student *students, int line)
{
	struct student newstudent;

	int k;
	printf("Enter ID : ");
	do {
		fflush(stdin);
		gets(newstudent.id);
		k = checkSt(students, newstudent.id, line);
		if( k != -1)
		{
			printf("Error:This student is already in the file!\n");
			printf("Enter ID : ");
		}
	} while( k != -1);

	printf("Enter surname : ");
	fflush(stdin);
	gets(newstudent.surname);

	printf("Enter name : ");
	fflush(stdin);
	gets(newstudent.name);

	printf("Enter middlename : ");
	fflush(stdin);
	gets(newstudent.middlename);

	printf("Enter department : ");
	fflush(stdin);
	gets(newstudent.department);

	printf("Enter major : ");
	fflush(stdin);
	gets(newstudent.major);

	students = realloc(students, (line+1) * sizeof(struct student));

	strcpy(students[line].id,newstudent.id);
	strcpy(students[line].surname,newstudent.surname);
	strcpy(students[line].name,newstudent.name);
	strcpy(students[line].middlename,newstudent.middlename);
	strcpy(students[line].department,newstudent.department);
	strcpy(students[line].major,newstudent.major);

	printf("Success!\n");

	return students;
}

//2
struct student *deletestudent(struct student *students, struct library *libraries, int line)
{
	struct student *bufstudents = calloc(line-1, sizeof(struct student));

	int k;
	printf("Enter ID student to delete : ");
	do {
		char deleteid[size];
		fflush(stdin);
		gets(deleteid);
		k = checkSL(students, libraries, deleteid, line);
		if (k == -1)
		{
			printf("No student found in file!\n");
			printf("Enter ID student to delete : ");
		}
		else if (k == -2)
		{
			printf("Since the student has a book, it cannot be deleted!\n");
			printf("Enter ID student to delete : ");
		}
	} while ((k == -1) || (k == -2));

	for (int i = 0; i < line; i++)
	{
		if (i < k)
		{
			strcpy(bufstudents[i].id,students[i].id);
			strcpy(bufstudents[i].surname,students[i].surname);
			strcpy(bufstudents[i].name,students[i].name);
			strcpy(bufstudents[i].middlename,students[i].middlename);
			strcpy(bufstudents[i].department,students[i].department);
			strcpy(bufstudents[i].major,students[i].major);
		}
		else if (i > k)
		{
			strcpy(bufstudents[i-1].id,students[i].id);
			strcpy(bufstudents[i-1].surname,students[i].surname);
			strcpy(bufstudents[i-1].name,students[i].name);
			strcpy(bufstudents[i-1].middlename,students[i].middlename);
			strcpy(bufstudents[i-1].department,students[i].department);
			strcpy(bufstudents[i-1].major,students[i].major);
		}
	}
	printf("Success!\n");

	return bufstudents;
}

//3
struct student *editstudent(struct student *students, int line)
{
	struct student bufstudents;

	int k;
	printf("Enter ID student to edit : ");
	do {
		fflush(stdin);
		gets(bufstudents.id);
		k = checkSt(students, bufstudents.id, line);
		if(k == -1)
		{
			printf("No student found in file!\n");
			printf("Enter ID student to edit : ");
		}
	} while(k == -1);

	printf("Enter new surname : ");
	fflush(stdin);
	gets(bufstudents.surname);

	printf("Enter new name :");
	fflush(stdin);
	gets(bufstudents.name);

	printf("Enter new middlename :");
	fflush(stdin);
	gets(bufstudents.middlename);

	printf("Enter new department :");
	fflush(stdin);
	gets(bufstudents.department);

	printf("Enter new major :");
	fflush(stdin);
	gets(bufstudents.major);

	for (int i = 0; i < line; i++)
	{
		if (i == k)
		{
			strcpy(students[i].id, bufstudents.id);
			strcpy(students[i].surname,bufstudents.surname);
			strcpy(students[i].name,bufstudents.name);
			strcpy(students[i].middlename,bufstudents.middlename);
			strcpy(students[i].department,bufstudents.department);
			strcpy(students[i].major,bufstudents.major);
		}
	}
	printf("Success!\n");

	return students;
}

//4
void infostudent(struct student *students, int line)
{
	int k;
	printf("Enter ID student to get information : ");
	do {
		char infoid[size];
		fflush(stdin);
		gets(infoid);
		k = checkSt(students, infoid, line);
		if(k == -1)
		{
			printf("No student found in file!\n");
			printf("Enter ID student to get information : ");
		}
	} while(k == -1);

	for (int i = 0; i < line; i++)
	{
		if (i == k)
		printf("\tID: %s;\n\tSurname: %s;\n\tName: %s;\n\tMiddlename: %s;\n\tDepartment: %s;\n\tMajor: %s\n", students[i].id,students[i].surname, students[i].name, students[i].middlename, students[i].department, students[i].major);
	}
}

//5
int makecopyfileSt(struct student *students, int line)
{
		time_t     now;
    struct tm  ts;
    char  buf[size];
    char copy[size]="students_";
    time(&now);
    ts = *localtime(&now);
    strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", &ts);
    int lencopy=strlen(copy);
    int lenbuf=strlen(buf);
    for(int i = 0; i < lenbuf; i++)
    {
        if(buf[i]==' ')
            buf[i]='.';
        if(buf[i]==':')
            buf[i]='-';
    }
		strcat(copy, buf);
		char csv[size] = ".csv";
		strcat(copy, csv);

		FILE *fcopy = fopen(copy, "w+");
		rewind(fcopy);

		for (int i = 0; i < 1; i++)
		{
			fprintf(fcopy,"%s",students[i].id);
			fprintf(fcopy,";%s",students[i].surname);
			fprintf(fcopy,";%s",students[i].name);
			fprintf(fcopy,";%s",students[i].middlename);
			fprintf(fcopy,";%s",students[i].department);
			fprintf(fcopy,";%s",students[i].major);
		}
		for (int i = 1; i < line; i++)
		{
			fprintf(fcopy,"\n%s",students[i].id);
			fprintf(fcopy,";%s",students[i].surname);
			fprintf(fcopy,";%s",students[i].name);
			fprintf(fcopy,";%s",students[i].middlename);
			fprintf(fcopy,";%s",students[i].department);
			fprintf(fcopy,";%s",students[i].major);
		}
		fclose(fcopy);

		printf("Success!\n");
}

//6
struct student *restorefileSt(char namefile[size], int line)
{
	struct student *readstudent =  calloc(0, sizeof(struct student));
	FILE *f = fopen(namefile, "r");

	char buf[max];
	for (int i = 0; i < line; i++)
	{
		fgets(buf, max, f);

		readstudent = realloc(readstudent, (i+1) * sizeof(struct student));

		strcpy(readstudent[i].id,strtok(buf,";"));
		strcpy(readstudent[i].surname,strtok(NULL,";"));
		strcpy(readstudent[i].name,strtok(NULL,";"));
		strcpy(readstudent[i].middlename,strtok(NULL,";"));
		strcpy(readstudent[i].department,strtok(NULL,";"));
		strcpy(readstudent[i].major,strtok(NULL,"\n"));
	}
	fclose(f);
	writefileSt(readstudent, line);

	printf("Success!\n");
	return readstudent;
}

//7
void infostudentbysurname(struct student *students, int line)
{
	int k;
	printf("Enter surname student to get information : ");
	char infosurname[size];
	do {
		fflush(stdin);
		gets(infosurname);
		k = checkStSurname(students, infosurname, line);
		if(k == -1)
		{
			printf("No student found in file!\n");
			printf("Enter surname student to get information : ");
		}
	} while(k == -1);

	for (int i = 0; i < line; i++)
	{
		if (strcmp(students[i].surname, infosurname) == 0)
			printf("\tID: %s;\n\tSurname: %s;\n\tName: %s;\n\tMiddlename: %s;\n\tDepartment: %s;\n\tMajor: %d\n\n", students[i].id,students[i].surname, students[i].name, students[i].middlename, students[i].department, students[i].major);
	}
}

//8
void infobookbystudent(struct student *students, struct book *books, struct library *libraries, int lines, int lineb, int linesb)
{
	int k;
	printf("Enter ID student to get information : ");
	char infoid[size];
	do {
		fflush(stdin);
		gets(infoid);
		k = checkSt(students, infoid, lines);
		if(k == -1)
		{
			printf("No student found in file!\n");
			printf("Enter ID student to get information : ");
		}
	} while(k == -1);

	int num = 0;
	for(int i = 0; i < linesb; i++)
	{
		if (strcmp(libraries[i].id, infoid) == 0)
		{
			for(int j = 0; j < lineb; j++)
			{
				if (books[j].isbn == libraries[i].isbn)
				{
					printf("\tISBN: %lli;\n\tAuthor: %s;\n\tTitle: %s;\n\tAll book: %d;\n\tUsed book: %d\n\n", books[j].isbn,books[j].author, books[j].title, books[j].abook, books[j].ubook);
				}
			}
			printf("\tData return book: %s\n\n", libraries[i].data);
			num++;
		}

		if (num == 0)
		{
			printf("The student with ID: %s don't take books\n", students[k].id);
		}
	}
}

//user.csv
int lineUser()
{
	int line = 0;
  FILE *f = fopen("user.csv", "r");
	if (f == NULL)
	{
		printf("No file!\n");
	}
	else
	{
		while (!feof(f))
		{
			if (fgetc(f)=='\n')
				line++;
		}
		return ++line;
		fclose(f);
	}
}

struct user *readfileUser()
{
	struct user *readuser =  calloc(0, sizeof(struct user));
	FILE *f = fopen("user.csv", "r");
	if (f == NULL)
	{
		printf("Not file\n");
		return 0;
	}
	else
	{
		int line = lineUser();
		char buf[max];
		for (int i = 0; i < line; i++)
		{
			fgets(buf, max, f);

			readuser = realloc(readuser, (i+1) * sizeof(struct user));

			strcpy(readuser[i].login,strtok(buf,";"));
			strcpy(readuser[i].pass,strtok(NULL,";"));
			readuser[i].book = atoi(strtok(NULL,";"));
			readuser[i].student = atoi(strtok(NULL,"\n"));
		}
		return readuser;
	}
}

int checkUser(struct user *users, char log[size], char pass[size], int line)
{
	int fl = -1;

		for(int i = 0; i < line; i++)
		{
			if ((strcmp(log, users[i].login) == 0) && (strcmp(pass, users[i].pass) == 0))
				fl = i ;
		}

		return fl;
}

//main_book
void mainbook(char login[size])
{
	struct book *books = readfileBk();
	struct student *students;
	struct library *libraries;
	int lineb = lineBk();
	int linesb = lineSB();
	int lines = lineSt();
	for(;;)
	{
		printf("\nMenu:\n");
		printf("1.Add new books\n");
		printf("2.Delete book\n");
		printf("3.Information about book\n");
		printf("4.Information about all book\n");
		printf("5.Edit book\n");
		printf("6.Change book\n");
		printf("7.Give book to a student\n");
		printf("8.Take book to a student\n");
		printf("9.Make a copy of the file\n");
		printf("10.Restore a file\n");
		printf("11.Information for a book by author\n");
		printf("12.Information about student for a book\n");
		printf("22.List all books\n");
		printf("33.List all student, who have books\n");
		printf("0.Exit\n");
		int a;
		scanf("%d",&a);
		switch(a)
		{
			case 1:
				books = addbook(books, lineb);
				++lineb;
				break;
			case 2:
				libraries = readfileSB();
				books = deletebook(books, libraries, lineb);
				--lineb;
				break;
			case 3:
				infobook(books, lineb);
				break;
			case 4:
				infoallbooks(books, lineb);
				break;
			case 5:
				books = editbook(books, lineb);
				break;
			case 6:
				books = changebook(books, lineb);
				break;
			case 7:
				students = readfileSt();
				libraries = readfileSB();
				books = givebook(books, students, libraries, lineb, lines, linesb);
				++linesb;
				break;
			case 8:
				students = readfileSt();
				libraries = readfileSB();
				books = takebook(books, students, libraries, lineb, lines, linesb);
				--linesb;
				break;
			case 9:
				makecopyfileBk(books, lineb);
				break;
			case 10:
				printf("Enter the file you backed up : ");
				char namefile[size];
				fflush(stdin);
				gets(namefile);
				lineb = lineBkcopy(namefile);
				if (lineb == -1)
				{
					printf("No file!\n");
					break;
				}
				else
				{
					books = restorefileBk(namefile, lineb);
					break;
				}
			case 11:
				infobookbyauthor(books, lineb);
				break;
			case 12:
				students = readfileSt();
				libraries = readfileSB();
				infostudentbybook(books, students, libraries, lineb, lines, linesb);
				break;
			case 22:
				listBk(books, lineb);
				break;
			case 33:
				libraries = readfileSB();
				listSB(libraries, linesb);
				break;
		}
		if(a == 0)
			break;
		FILE *flog;
    time_t now;
    struct tm  ts;
    char buf[size];
    time(&now);
    ts = *localtime(&now);
    strftime(buf, sizeof(buf), "%a %Y-%m-%d %H:%M:%S", &ts);
		fflush(stdin);

		flog = fopen("library3.log","a");
		fprintf(flog,"\n\"%s\"",buf);
		fprintf(flog,",\"BOOK.CSV\"");
		fprintf(flog,",\"%s\"",login);
		if(a==1)
				fprintf(flog,",\"Add new books\"");
		else if(a==2)
				fprintf(flog,",\"Delete book\"");
		else if(a==3)
				fprintf(flog,",\"Information about book\"");
		else if(a==4)
				fprintf(flog,",\"Information about all book\"");
		else if(a==5)
				fprintf(flog,",\"Edit book\"");
		else if(a==6)
				fprintf(flog,",\"Change book\"");
		else if(a==7)
				fprintf(flog,",\"Give book to a student\"");
		else if(a==8)
				fprintf(flog,",\"Take book to a student\"");
		else if(a==9)
				fprintf(flog,",\"Make a copy of the file\"");
		else if(a==10)
				fprintf(flog,",\"Restore a file\"");
		else if(a==11)
				fprintf(flog,",\"Information for a book by author\"");
		else if(a==12)
				fprintf(flog,",\"Information about student for a book\"");
		else if(a==22)
				fprintf(flog,",\"List all book\"");
		else if(a==33)
				fprintf(flog,",\"List all student, who have books\"");
		else if(a==0)
				fprintf(flog,",\"Exit\"");
		else break;
		fclose(flog);
	}

	writefileBk(books, lineb);
	free(books);
	free(students);
	free(libraries);
}

//main_student
void mainstudent(char login[size])
{
	struct student *students = readfileSt();
	struct book *books;
	struct library *libraries;
	int lines = lineSt();
	int lineb = lineBk();
	int linesb = lineSB();
	for(;;)
	{
		printf("\nMenu:\n");
		printf("1.Add new students\n");
		printf("2.Delete student\n");
		printf("3.Edit student\n");
		printf("4.Information about student\n");
		printf("5.Make a copy of the file\n");
		printf("6.Restore a file\n");
		printf("7.Information for a student by surname\n");
		printf("8.Information about books for a student\n");
		printf("22.list all students\n");
		printf("33.List all student, who have books\n");
		printf("0.Exit\n");
		int a;
		scanf("%d",&a);
		switch(a)
		{
			case 1:
				students = addstudent(students, lines);
				++lines;
				break;
			case 2:
				libraries = readfileSB();
				students = deletestudent(students, libraries, lines);
				--lines;
				break;
			case 3:
				students = editstudent(students, lines);
				break;
			case 4:
				infostudent(students, lines);
				break;
			case 5:
				makecopyfileSt(students, lines);
				break;
			case 6:
				printf("Enter the file you backed up : ");
				char namefile[size];
				fflush(stdin);
				gets(namefile);
				lines = lineStcopy(namefile);
				if (lines == -1)
				{
					printf("No file!\n");
					break;
				}
				else
				{
					students = restorefileSt(namefile, lines);
					break;
				}
			case 7:
				infostudentbysurname(students, lines);
				break;
			case 8:
				books = readfileBk();
				libraries = readfileSB();
				infobookbystudent(students, books, libraries, lines, lineb, linesb);
				break;
			case 22:
				listSt(students, lines);
				break;
			case 33:
				libraries = readfileSB();
				listSB(libraries, linesb);
				break;
		}
		if(a == 0)
			break;
		FILE *flog;
    time_t now;
    struct tm  ts;
    char buf[size];
    time(&now);
    ts = *localtime(&now);
    strftime(buf, sizeof(buf), "%a %Y-%m-%d %H:%M:%S", &ts);
		fflush(stdin);

		flog = fopen("library3.log","a");
		fprintf(flog,"\n\"%s\"",buf);
		fprintf(flog,",\"STUDENT.CSV\"");
		fprintf(flog,",\"%s\"",login);
		if(a==1)
			fprintf(flog,",\"Add new students\"");
		else if(a==2)
			fprintf(flog,",\"Delete student\"");
		else if(a==3)
			fprintf(flog,",\"Edit student\"");
		else if(a==4)
			fprintf(flog,",\"Information about student\"");
		else if(a==5)
			fprintf(flog,",\"Make a copy of the file\"");
		else if(a==6)
			fprintf(flog,",\"Restore a file\"");
		else if(a==7)
			fprintf(flog,",\"Information for a student by surname\"");
		else if(a==8)
			fprintf(flog,",\"Information about books for a student\"");
		else if(a==22)
			fprintf(flog,",\"List all students\"");
		else if(a==33)
			fprintf(flog,",\"List all student, who have books\"");
		else if(a==0)
			fprintf(flog,",\"Exit\"");
		else break;
		fclose(flog);
	}

	writefileSt(students, lines);
	free(students);
	free(libraries);
	free(books);
}

//main_user
void mainuser()
{
	struct user *users = readfileUser();
	int line = lineUser();

	char login[size];
	char pass[size];

	int k;
	do {
		fflush(stdin);
		printf("Enter login : ");
		gets(login);
		printf("Enter password : ");
		gets(pass);
		k = checkUser(users, login, pass, line);
		if( k == -1)
		{
			printf("Error:Your login or password is not correct!\n");
			printf("Try again?\n");
			printf("1.Yes\n");
			printf("2.No\n");
			int ans;
			scanf("%d", &ans);
			if (ans == 2)
			{
				break;
			}
		}
	} while (k == -1);

	if (k != -1)
	{
		printf("Success!\n");
		if(users[k].book==1 && users[k].student==0 )
		{
			printf("Welcome to file BOOK.CSV!\n");
			mainbook(login);
		}
		else if (users[k].book==0 && users[k].student==1 )
		{
			printf("Welcome to file STUDENT.CSV!\n");
			mainstudent(login);
		}
		else if(users[k].book==1 && users[k].student==1 )
		{
			int c;
			for(;;)
			{
				printf("1. Menu book. \n");
				printf("2. Menu student. \n");
				printf("3. Exit. \n");
				scanf("%d",&c);
				if(c == 1)
				{
					printf("Welcome to file BOOK.CSV!\n");
					mainbook(login);
				}
				else if(c == 2)
				{
					printf("Welcome to file STUDENT.CSV!\n");
					mainstudent(login);
				}
				else
				{
					break;
				}
			}
		}
	}

	free(users);
}

int main()
{
	mainuser();
	return 0;
}
