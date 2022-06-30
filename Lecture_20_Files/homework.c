#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING_SIZE (20)

void Cleanup(char *buf);

struct abonent
{
    char firstname[MAX_STRING_SIZE];
    char surname[MAX_STRING_SIZE];
    char phone[MAX_STRING_SIZE];
};

typedef struct abonent abonent;

abonent abonents[100];
char abonentcount = 0;

void ShowAll(void)
{
    int i;
    for(i = 0; i < abonentcount; ++i)
    {
        printf("%s %s: %s\n", abonents[i].firstname,
            abonents[i].surname, abonents[i].phone);
    }
}

void ShowByNumber(char *buf)
{
    int i;
    Cleanup(buf);
    for(i = 0; i < abonentcount; ++i)
    {
        if(!strcmp(abonents[i].phone, buf))
            printf("%s %s: %s\n", abonents[i].firstname,
                abonents[i].surname, abonents[i].phone);
    }
}

void DeleteByNumber(char *buf)
{
    int i;
    Cleanup(buf);
    for(i = 0; i < abonentcount; ++i)
    {
        if(!strcmp(abonents[i].phone, buf))
        {
            strcpy(abonents[i].firstname, abonents[abonentcount-1].firstname);
            strcpy(abonents[i].surname, abonents[abonentcount-1].surname);
            strcpy(abonents[i].phone, abonents[abonentcount-1].phone);
            abonentcount--;
        }
    }
}

void Cleanup(char *buf)
{
    int i;
    for(i=0; i<MAX_STRING_SIZE; i++)
    {
        if(buf[i] == 13 || buf[i] == 10)
        {
            buf[i] = 0;
            break;
        }
    }
}

void NewLine(char *buf)
{
    fgets(buf, MAX_STRING_SIZE, stdin);
    Cleanup(buf);
}

void AddNew(void)
{
    NewLine(abonents[abonentcount].firstname);
    NewLine(abonents[abonentcount].surname);
    NewLine(abonents[abonentcount].phone);
    abonentcount++;
}

void ReadFromFile(void)
{
    FILE *pf;
    pf = fopen("database.db", "r");
    fread(&abonentcount, sizeof(char), 1, pf);
    fread(abonents, sizeof(abonent), 100, pf);
    fclose(pf);
}

void WriteToFile(void)
{
    FILE *pf;
    pf = fopen("database.db", "w");
    fwrite(&abonentcount, sizeof(char), 1, pf);
    fwrite(abonents, sizeof(abonent), 100, pf);
    fclose(pf);
}

int main(void)
{
    char buffer[MAX_STRING_SIZE];
    while(1)
    {
        printf("1: Add, 2: ShowAll, 3: ShowByNumber, 4: Delete, 5: Read, 6: Write, 0: Quit\n");
        fgets(buffer, MAX_STRING_SIZE, stdin);
        switch(buffer[0])
        {
            case '0': exit(0);
            case '1': AddNew(); break;
            case '2': ShowAll(); break;
            case '3': fgets(buffer, MAX_STRING_SIZE, stdin);
                      ShowByNumber(buffer);
                      break;
            case '4': fgets(buffer, MAX_STRING_SIZE, stdin);
                      DeleteByNumber(buffer);
                      break;
            case '5': ReadFromFile();
                      break;
            case '6': WriteToFile();
                      break;
        }
    }
    return 0;
}
