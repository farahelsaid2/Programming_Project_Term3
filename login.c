#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
void login()
{
    char un[30],ps[30],arr[50],*took;
    int x,y;
    FILE *f=fopen("users.txt","r");
    HANDLE hConsole=GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 9);
    printf ("\t\t\t\t\t Welcome To LOGIN Page \t\t\t\t\t\n");
    SetConsoleTextAttribute(hConsole, 7);
    printf ("Please Enter The UserName:");

    gets(un);
    printf ("Please Enter The Password:");

    gets(ps);
    while (fgets(arr,50,f))
    {
        took=strtok(arr," ");
        x=strcmp(took,un);
        took=strtok('\0'," ");
        y=strcmp(took,ps);


    }
    if (x==0&&y==0)
    {
        SetConsoleTextAttribute(hConsole, 10);
        printf("LOGIN DONE SUCCESSFULLY WELCOME !\n");
        SetConsoleTextAttribute(hConsole, 7);
        menu();
    }
    else
    {
        SetConsoleTextAttribute(hConsole, 12);
        printf("ERROR\nOoops.. something wrong,try later ");
        SetConsoleTextAttribute(hConsole, 7);
        quit();
    }
}
int main()
{

    return 0;
}
