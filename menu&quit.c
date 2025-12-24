#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <string.h>

void quit(void)
{
    HANDLE hConsole=GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 12);
    printf("exit the program......");
    SetConsoleTextAttribute(hConsole, 7);
    exit(0);
}
void menu()
{
    int x,y;
    HANDLE hConsole=GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 15);

    printf("ADD\t\t\tDELETE\t\t\tMODIFY\t\t\tSEARCH\t\t\tADVANCEDSEARCH\n\n0\t\t\t1\t\t\t2\t\t\t3\t\t\t4\t\t\t\n\nCHANGE-STATUS\t\tWITHDRAW\t\tDEPOSIT\t\t\tTRANSFERE\t\tREPORT\t\t\t\n\n5\t\t\t6\t\t\t7\t\t\t8\t\t\t9\t\t\t\n\nPRINT\t\t\tQUIT\t\t\t\n\n10\t\t\t11\n");
    SetConsoleTextAttribute(hConsole, 7);
    SetConsoleTextAttribute(hConsole, 8);
    printf("please select one of these options:");
    SetConsoleTextAttribute(hConsole, 7);
    scanf("%d",&x);
    switch(x)
    {
    case 0 ://add();break;
    case 1 ://deletee(); break;
    case 2 ://modify ();break;
    case 3 ://search ();break;
    case 4 ://advancedSEARCH();break;
    case 5 ://changeSTATUS();break;
    case 6 ://withdraw();break;
    case 7 ://deposit();break;
    case 8 ://transfer();break;
    case 9 ://report();break;
    case 10://print();break;
    case 11:
        quit();
    default :
        printf("GO BACK TO MENU (CLICK 1) \nOTHERWISE EXIT ");
        scanf("%d",&y);
        if (y==1)menu();
        else quit();



    }
}

int main()
{

    return 0;
}
