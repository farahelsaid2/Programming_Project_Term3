#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct
{

    int month;
    int year;

} dateOpened;
typedef struct
{
    long long accNumber;
    char name[50];
    char email[100];
    double balance;
    dateOpened date;
    char mobile[12];
    char status[20];

} info;
info *LOAD()
{
    char *token;
    int i=0;
    info *acc = malloc(100*sizeof(info));
    FILE *fr=fopen("accounts.txt","r");
    char str[200];


    while(fgets(str,200,fr))
    {
        token=strtok(str,",");
        acc[i].accNumber= atoll(token);
        token=strtok(NULL,",");
        strcpy(acc[i].name,token);
        token=strtok(NULL,",");
        strcpy(acc[i].email,token);
        token=strtok(NULL,",");
        acc[i].balance=atof(token);
        token=strtok(NULL,",");
        strcpy(acc[i].mobile,token);
        token=strtok(NULL,"-");
        acc[i].date.month=atoi(token);
        token=strtok(NULL,",");
        acc[i].date.year=atoi(token);
        token=strtok(NULL,",");
        strcpy(acc[i].status,token);

        i++;

    }



    fclose(fr);
    return acc;
}
int main()
{
    LOAD();
    return 0;
}
