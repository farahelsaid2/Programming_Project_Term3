#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <string.h>
void login()
{
    char un[30],ps[30],arr[50],*took;
    int x,y,redo;
    FILE *f=fopen("users.txt","r");
    HANDLE hConsole=GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 9);
    printf ("\t\t\t\t\t Welcome To LOGIN Page \t\t\t\t\t\n");
    SetConsoleTextAttribute(hConsole, 7);
    printf ("Please Enter The UserName:");
    gets(un);

    while (fgets(arr,50,f))
    {
        took=strtok(arr," ");
        x=strcmp(took,un);
        took=strtok(NULL,"\n");

        if(x==0) break;
    }
    if (x==0)
    {
        printf ("Please Enter The Password:");
        gets(ps);
        y=strcmp(took,ps);
        if (y==0)
        {
            SetConsoleTextAttribute(hConsole, 10);
            printf("LOGIN DONE SUCCESSFULLY WELCOME !\n");
            SetConsoleTextAttribute(hConsole, 7);
            return;
        }
        else
        {
            SetConsoleTextAttribute(hConsole, 12);
            printf("Ooops.. WRONG PASSWORD ");
            SetConsoleTextAttribute(hConsole, 7);
            printf("\nenter 1 if you want to try again otherwise exit :");
            scanf("%d",&redo);
            getchar();
            if (redo)login();
            else quit();
        }
    }
    else
    {
        SetConsoleTextAttribute(hConsole, 12);
        printf("Ooops.. WRONG USERNAME ");
        SetConsoleTextAttribute(hConsole, 7);
        printf("\nenter 1 if you want to try again otherwise exit :");
        scanf(" %d",&redo);
        getchar();
        if (redo==1)login();
        else quit();
    }
    fclose(f);
}

int main()
{
    login();
    return 0;
}
