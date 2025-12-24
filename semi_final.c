#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string.h>
#include <windows.h>

#define MAX_Tran 250

//Structures in code
typedef struct
{
    int month;
    int year;
} dateOpened;


typedef struct
{
    char accNumber[50];
    char name[50];
    char email[50];
    double balance;
    dateOpened date;
    char mobile[12];
    char status[20];
    int limitwd;
} info;


//Main functions
void menu();
void quit(void);
int Save(info* racc,float d,info* sacc,float w);
void login();
void advancedSearch();
int Search(int flag,char acc_Number[50]);
info LOAD(int targetIndex);
int dailyLimit(info* acc,float t);
int withdraw();
int deposit();
int transfer();
void Report();
void PRINT();


//Auxiliary Functions
void printDate(info acc);
void strtolower(char *s);
void trim(char *s);
info* sortByName(int count);
info* sortByBalance(int count);
info* sortByDateOpened(int count);
info* sortByStatus(int count);
int compareByName(const void *a, const void *b)

int main()
{
    login();
    while(1)
    {
        printf("\n");
        menu();
    }
        return 0;
}

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
            printf("\nEnter 1 if you want to try again otherwise exit :");
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
        printf("\nEnter 1 if you want to try again otherwise exit :");
        scanf(" %d",&redo);
        getchar();
        if (redo==1)login();
        else quit();
    }
    fclose(f);
}

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
    printf("Please select one of these options: ");
    SetConsoleTextAttribute(hConsole, 7);
    scanf("%d",&x);
    getchar();
    switch(x)
    {
    case 0 ://add();break;
    case 1 ://deletee(); break;
    case 2 ://modify ();break;
    case 3 :Search (1,"1"); break;
    case 4 :advancedSearch(); break;
    case 5 ://changeSTATUS();break;
    case 6 :withdraw(); break;
    case 7 :deposit(); break;
    case 8 :transfer(); break;
    case 9 :Report(); break;
    case 10:PRINT(); break;
    case 11:quit();
    default :
        printf("GO BACK TO MENU (CLICK 1) \nOTHERWISE EXIT ");
        scanf("%d",&y);
        if (y==1)menu();
        else quit();
    }
}

int Save(info* racc,float d,info* sacc,float w)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    char answer[10];
    FILE* fptr;
    SetConsoleTextAttribute(hConsole, 2);
    printf("Do you want to save (Y/N): ");
    SetConsoleTextAttribute(hConsole, 7);
    fgets(answer,sizeof(answer),stdin);
    answer[strcspn(answer, "\n")] = '\0';
    answer[0] = tolower(answer[0]);

    if (strcmp(answer,"y") == 0){
        FILE *f = fopen("accounts.txt", "r");
        FILE *temp = fopen("temp.txt", "w");
        char line[256];
        if(!f||!temp){
            SetConsoleTextAttribute(hConsole, 12);
            printf("Error in opening the file");
            SetConsoleTextAttribute(hConsole, 7);
            return -1;
        }

        while(fgets(line, sizeof(line), f)) {
        char accnum[50];
        sscanf(line, "%49[^,]", accnum);
        trim(accnum);

        if(racc&&strcmp(accnum, racc->accNumber) == 0) {

        fprintf(temp, "%s,%s,%s,%.2lf,%s,%02d-%d,%s\n",
            racc->accNumber,
            racc->name,
            racc->email,
            racc->balance+d,
            racc->mobile,
            racc->date.month,
            racc->date.year,
            racc->status
        );

    }
    else if(sacc&&strcmp(accnum, sacc->accNumber) == 0){
        fprintf(temp, "%s,%s,%s,%.2lf,%s,%02d-%d,%s\n",
            sacc->accNumber,
            sacc->name,
            sacc->email,
            sacc->balance-w,
            sacc->mobile,
            sacc->date.month,
            sacc->date.year,
            sacc->status
        );
    }

    else {

        fputs(line, temp);
    }
}

fclose(f);
fclose(temp);
remove("accounts.txt");
rename("temp.txt", "accounts.txt");



        return 1;
    }
    if (strcmp(answer,"n") == 0){
        return 0;
    }


    SetConsoleTextAttribute(hConsole, 12);
    printf("\nInvalid Input\nEdits will be discarded\n");
    SetConsoleTextAttribute(hConsole, 7);

    SetConsoleTextAttribute(hConsole, 3);
    printf("Press A to try again\nPress E to exit\n");
    SetConsoleTextAttribute(hConsole, 7);

    fgets(answer,sizeof(answer),stdin);
    answer[0] = tolower(answer[0]);

    if (strcmp(answer,"a") == 0)
        return Save(racc,d,sacc,w);
    if (strcmp(answer,"e") == 0)
        return 0;

return 0;
}


void advancedSearch()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    char s[100], str[300], lowerName[100];
    char *token;
    int index = 0;

    printf("Enter the name: ");
    fgets(s, sizeof(s), stdin);
    trim(s);
    strtolower(s);

    FILE *fr = fopen("accounts.txt", "r");
    if(!fr)
    {
        printf("Error accessing file\n");
        exit(1);
    }

    while(fgets(str, sizeof(str), fr))
    {
        token = strtok(str, ",");   // skip acc number
        token = strtok(NULL, ",");   // get name

        if(token)
        {
            strcpy(lowerName, token);
            trim(lowerName);
            strtolower(lowerName);

            // check full match
            if(strstr(lowerName, s) != NULL)
            {
                info acc = LOAD(index);

                SetConsoleTextAttribute(hConsole, 3);
                printf("Account Information\n");
                SetConsoleTextAttribute(hConsole, 7);
                printf("Account Number: %s\n", acc.accNumber);
                printf("Name: %s\n", acc.name);
                printf("E-mail: %s\n", acc.email);
                printf("Balance: %.2f\n", acc.balance);
                printf("Mobile: %s\n", acc.mobile);
                printDate(acc);

                trim(acc.status);
                if(strcmp(acc.status, "active")==0)
                    SetConsoleTextAttribute(hConsole, 2);  // green
                else
                    SetConsoleTextAttribute(hConsole, 12); // red

                printf("Status: %s\n\n", acc.status);
                SetConsoleTextAttribute(hConsole, 7);
            }
        }

        index++;
    }

    fclose(fr);
}

int Search(int flag,char acc_Number[50]) //if any function need to search only call by (0,acc_number)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    char s[250];
    char searchNum[50];
    char buffer[50];
    char *token;
    int index =0;
    int foundIndex = -1;
    strcpy(buffer,acc_Number);
    trim(buffer);
    if(strcmp(buffer,"1") == 0)

    {
        printf("Enter the account number:");
        fgets(buffer,50, stdin);
        trim(buffer);
    }


    FILE *fr=fopen("accounts.txt","r");

    if(fr == NULL)
    {
        printf("Error in accessing info\nPlease restart Program");
        exit(1);
    }


    while(fgets(s,250,fr))
    {
        token = strtok(s,",");
        strcpy(searchNum,token);
        trim(searchNum);

        if (strcmp(buffer,searchNum) == 0)
        {
            foundIndex = index;
            break;
        }

        index++;
    }

    fclose(fr);

    if(foundIndex == -1)
    {
        SetConsoleTextAttribute(hConsole, 12);  // red
        printf("Account not found\n");
        SetConsoleTextAttribute(hConsole, 7);   // default

        return -1;
    }

    if(flag)
    {
        info acc = LOAD(foundIndex);
        SetConsoleTextAttribute(hConsole, 3);
        printf("Account Information\n");
        SetConsoleTextAttribute(hConsole, 7);
        printf("Account Number : %s \n",acc.accNumber);
        printf("Name : %s\n",acc.name);
        printf("E-mail : %s\n",acc.email);
        printf("Balance : %.2f\n",acc.balance);
        printf("Mobile: %s\n",acc.mobile);
        printDate(acc);
        if(strcmp(acc.status,"active")==0)
        {
            SetConsoleTextAttribute(hConsole, 2);
            printf("Status: %s\n",acc.status);
            SetConsoleTextAttribute(hConsole, 7);

        }
        else
        {
            SetConsoleTextAttribute(hConsole, 12);
            printf("Status: %s\n",acc.status);
            SetConsoleTextAttribute(hConsole, 7);

        }

    }

    return foundIndex;

}

info LOAD(int targetIndex)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    FILE *fr = fopen("accounts.txt", "a+");
    if (!fr)
    {
        SetConsoleTextAttribute(hConsole, 12);
        printf("File error\n");
        SetConsoleTextAttribute(hConsole, 7);
        exit(1);
    }

    char str[200];
    char *token;
    int index = 0;
    info acc;

    while (fgets(str, 200, fr))
    {
        if (index == targetIndex)
        {
            token = strtok(str, ",");
            strcpy(acc.accNumber, token);

            token = strtok(NULL, ",");
            strcpy(acc.name, token);

            token = strtok(NULL, ",");
            strcpy(acc.email, token);

            token = strtok(NULL, ",");
            acc.balance = atof(token);

            token = strtok(NULL, ",");
            strcpy(acc.mobile, token);

            token = strtok(NULL, "-");
            acc.date.month = atoi(token);

            token = strtok(NULL, ",");
            acc.date.year = atoi(token);

            token = strtok(NULL, ",");
            strcpy(acc.status, token);
            trim(acc.status);

            break;
        }
        index++;
    }

    fclose(fr);
    return acc;
}

int dailyLimit(info* acc,float t)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
if((acc->limitwd+t)>=50000){
    SetConsoleTextAttribute(hConsole, 12);
    printf("You excced the daily limit of withdrawas in one day!\n");
    SetConsoleTextAttribute(hConsole, 7);
    return -1;
}
else{
   acc->limitwd+=t;
   return 1;
}
}

int withdraw()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    float t;
    int c;
    char accno[50];
    char filename[200];
    info acc;
    FILE *fptr;
    SetConsoleTextAttribute(hConsole, 3);
    printf("Enter account number:");
    fgets(accno,sizeof(accno),stdin);
    int search = Search(0,accno);
    acc=LOAD(search);
    accno[strcspn(accno, "\n")] = '\0';
    snprintf(filename, sizeof(filename), "%s.txt", accno);
    if(search==-1)
    {
        /* SetConsoleTextAttribute(hConsole, 12);
        printf("Please enter a valid account number \n");
        SetConsoleTextAttribute(hConsole, 7);
        withdraw(); */
    }

    else
    {
        if(strcmp(acc.status,"inactive")==0)
        {
            SetConsoleTextAttribute(hConsole, 12);
            printf("The account is not active! \n");
            /* printf("Please enter a valid account number\n");
            SetConsoleTextAttribute(hConsole, 7);
            getchar();
            withdraw(); */
        }

        else
        {
            SetConsoleTextAttribute(hConsole, 3);
            printf("Enter the ammount of money you want to withdraw: ");
            SetConsoleTextAttribute(hConsole, 7);
            scanf("%f",&t);

            while((c=getchar()) != '\n' && c != EOF);
            if(t>10000)
            {
                SetConsoleTextAttribute(hConsole, 12);
                printf("The maximum ammount to withdraw is 10,000$ per transaction \n");
                return 0;
               /* printf("Please enter a valid amount \n");
                SetConsoleTextAttribute(hConsole, 7);
                getchar();
                withdraw(); */
            }
            else if(acc.balance<t)
            {
                SetConsoleTextAttribute(hConsole, 12);
                printf("There is no enough balance to withdraw this ammount \n");
                return 0;
                /* printf("Please enter a valid amount \n");
                SetConsoleTextAttribute(hConsole, 7);
                getchar();
                withdraw(); */
            }
            else
            {

                if(dailyLimit(&acc,t)==-1)
                {
                    return -1;
                }

                if(dailyLimit(&acc,t)==1)
                {
                    if(Save(NULL,0,&acc,t)==1)
                    {
                        acc.balance-=t;
                        LOAD(Search(0,accno));
                        fptr=fopen(filename,"a");
                        if(!fptr){
                            SetConsoleTextAttribute(hConsole, 12);
                            printf("Error in opening the file\n");
                            SetConsoleTextAttribute(hConsole, 7);
                            return -1;
                        }
                        fprintf(fptr,"D:%d \n",0);
                        fprintf(fptr,"TT:%d \n",0);
                        fprintf(fptr,"W:%.2f \n",t);
                        fprintf(fptr,"RF:%d \n",0);
                        SetConsoleTextAttribute(hConsole, 2);
                        printf("The transaction is saved successfully \n");
                        SetConsoleTextAttribute(hConsole, 7);
                        fclose(fptr);
                    }

                     else
                    {
                     SetConsoleTextAttribute(hConsole, 12);
                     printf("The transaction is not saved \n");
                      SetConsoleTextAttribute(hConsole, 7);

                    }
                }
            }
        }
    }

}

int deposit()
{
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
float t;
int c;
char accno[50];
char filename[50];
info acc;
SetConsoleTextAttribute(hConsole, 3);
printf("Enter the account number:");
fgets(accno,sizeof(accno),stdin);
SetConsoleTextAttribute(hConsole, 7);
int search = Search(0,accno);
acc=LOAD(search);
accno[strcspn(accno, "\n")] = '\0';
snprintf(filename, sizeof(filename), "%s.txt", accno);
 if(search == -1)
    {
       /* SetConsoleTextAttribute(hConsole, 12);
        printf("Please enter a valid account number\n");
        SetConsoleTextAttribute(hConsole, 7);
        deposit(); */
    }

    else
    {
        if(strcmp(acc.status,"inactive")==0)
        {
            SetConsoleTextAttribute(hConsole, 12);
            printf("The account is not active!\n");
           /* printf("Please enter a valid account number\n");
            SetConsoleTextAttribute(hConsole, 7);
            deposit(); */
        }
         else
        {
        SetConsoleTextAttribute(hConsole, 3);
        printf("Enter the ammount of money you want to deposit: ");
        scanf("%f",&t);
        while((c=getchar()) != '\n' && c != EOF);
        SetConsoleTextAttribute(hConsole, 7);
        if(t>=10000){
            SetConsoleTextAttribute(hConsole, 12);
            printf("The maximum amount to deposit is 10,000$ per transaction \n");
            printf("Please enter a valid amount \n");
            SetConsoleTextAttribute(hConsole, 7);
            getchar();
            deposit();
        }
        else
        {
            if(Save(&acc,t,NULL,0)==1)
                    {   FILE* fptr;
                        acc.balance+=t;
                        LOAD(Search(0,accno));
                        fptr=fopen(filename,"a");
                        if(!fptr){
                            SetConsoleTextAttribute(hConsole, 12);
                            printf("Error in opening the file\n");
                            SetConsoleTextAttribute(hConsole, 7);
                            return -1;
                        }
                        fprintf(fptr,"D:%.2f \n",t);
                        SetConsoleTextAttribute(hConsole, 3);
                        printf("The transaction is saved successfully\n");
                        SetConsoleTextAttribute(hConsole, 7);
                        fclose(fptr);
                    }

                     else
                {
                    SetConsoleTextAttribute(hConsole, 12);
                    printf("The transaction is not saved\n");
                    SetConsoleTextAttribute(hConsole, 7);
                    return -1;
                }
            }
        }
    }
}

int transfer()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    float t;
    char saccno[50];
    char raccno[50];
    char sfilename[200];
    char rfilename[200];
    info sacc, racc;
    FILE *sptr, *rptr;
    SetConsoleTextAttribute(hConsole, 3);
    printf("Enter the sender account number: ");
    fgets(saccno, sizeof(saccno), stdin);
    int search = Search(0, saccno);
    sacc = LOAD(search);
    saccno[strcspn(saccno, "\n")] = '\0';
    snprintf(sfilename, sizeof(sfilename), "%s.txt", saccno);
    if (search == -1) {
       /* SetConsoleTextAttribute(hConsole, 12);
        printf("Please enter a valid account number \n");
        SetConsoleTextAttribute(hConsole, 7);
        transfer(); */
    } else {
        if (strcmp(sacc.status, "inactive") == 0) {
            SetConsoleTextAttribute(hConsole, 12);
            printf("The sender account is not active! \n");
            return 0;
            /* printf("Please enter a valid account number\n");
            SetConsoleTextAttribute(hConsole, 7);
            transfer(); */
        } else {
            SetConsoleTextAttribute(hConsole, 3);
            printf("Enter the ammount of money you want to transfer: ");
            SetConsoleTextAttribute(hConsole, 7);
            scanf("%f", &t);
            getchar();
            if (sacc.balance < t) {
                SetConsoleTextAttribute(hConsole, 12);
                printf("There is no enough balance to transfer this ammount \n");
                return 0;
                /* printf("Please enter a valid amount \n");
                SetConsoleTextAttribute(hConsole, 7);
                transfer(); */
            } else {
                SetConsoleTextAttribute(hConsole, 3);
                printf("Enter the reciver account number: ");
                fgets(raccno, sizeof(raccno), stdin);
                int searchR = Search(0, raccno);
                racc = LOAD(searchR);
                raccno[strcspn(raccno, "\n")] = '\0';
                snprintf(rfilename, sizeof(rfilename), "%s.txt", raccno);
                if (searchR == -1) {
                    /* SetConsoleTextAttribute(hConsole, 12);
                    printf("Please enter a valid account number \n");
                    SetConsoleTextAttribute(hConsole, 7);
                    transfer(); */
                } else {
                    if (strcmp(racc.status, "inactive") == 0) {
                        SetConsoleTextAttribute(hConsole, 12);
                        printf("The reciver account is not active! \n");
                        return 0;
                       /* printf("Please enter a valid account number");
                        SetConsoleTextAttribute(hConsole, 7);
                        transfer(); */
                    }
                    if (Save(&racc,t,&sacc,t) == 1) {
                        sacc.balance -= t;
                        racc.balance += t;
                        LOAD(search);
                        sptr = fopen(sfilename, "a");
                        rptr = fopen(rfilename, "a");
                        if (!sptr || !rptr) {
                            SetConsoleTextAttribute(hConsole, 12);
                            printf("Error in opening the file\n");
                            SetConsoleTextAttribute(hConsole, 7);
                            return -1;
                        }
                        fprintf(rptr, "RF:%.2f \n", t);
                        fprintf(sptr, "TT:%.2f \n", t);
                        SetConsoleTextAttribute(hConsole, 2);
                        printf("The transaction is saved successfully \n");
                        SetConsoleTextAttribute(hConsole, 7);
                        fclose(sptr);
                        fclose(rptr);
                    } else {
                        SetConsoleTextAttribute(hConsole, 12);
                        printf("The transaction is not saved \n");
                        SetConsoleTextAttribute(hConsole, 7);
                    }
                }
            }
        }
    }
}

void Report()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    int j,c;
    int k =0;
    int counter = 0;
    int flag = 1;
    double dollars;
    char *token;
    char filename[50];
    char money[50];
    char operation[5];
    char accNumber[50];
    char transactions[MAX_Tran][50];
    char buffer[MAX_Tran][50];

    SetConsoleTextAttribute(hConsole, 3);
    printf("Enter the account number: ");
    SetConsoleTextAttribute(hConsole, 7);
    fgets(accNumber, 50, stdin);
    trim(accNumber);
    accNumber[strcspn(accNumber, "\n")] = '\0';
    accNumber[strcspn(accNumber, "\r")] = '\0';
    int index = Search(0,accNumber);
    if(index == -1)

    {

        return;
    }

    info account = LOAD(index);
    sprintf(filename, "%s.txt", accNumber);
    FILE *fr = fopen(filename, "r");

    if (!fr)
    {
        SetConsoleTextAttribute(hConsole, 12);
        printf("File error\n");
        SetConsoleTextAttribute(hConsole, 7);
        exit(1);
    }

    while(fgets(buffer[counter],MAX_Tran,fr) != NULL)
        counter ++;

    for (j = counter - 1; j >= 0 && k < 5; j--)

    {
        strcpy(transactions[k], buffer[j]);
        k++;
    }

    for(c=k-1;c>=0;c--)
    {
            token = strtok(transactions[c], ":");
            strcpy(operation, token);

            token = strtok(NULL, "\n");
            strcpy(money, token);
            dollars = atof(money);
            SetConsoleTextAttribute(hConsole, 7);
            if(strcmp(operation,"D") == 0)
            {
                SetConsoleTextAttribute(hConsole, 3);
                printf("Deposit: ");
                SetConsoleTextAttribute(hConsole, 7);
                printf("%.2lf\n",dollars);
                flag = 0;
            }

           else if(strcmp(operation,"W") == 0)
            {
                SetConsoleTextAttribute(hConsole, 3);
                printf("Withdrawal: ");
                SetConsoleTextAttribute(hConsole, 7);
                printf("%.2lf\n",dollars);
                flag = 0;

            }

           else if(strcmp(operation,"TT") == 0)
            {
                SetConsoleTextAttribute(hConsole, 3);
                printf("Amount of money ");
                SetConsoleTextAttribute(hConsole, 14);
                printf("transfered: ");
                SetConsoleTextAttribute(hConsole, 7);
                printf("%.2lf\n",dollars);
                flag = 0;

            }

           else if(strcmp(operation,"RF") == 0)
            {
                SetConsoleTextAttribute(hConsole, 3);
                printf("Amount of money ");
                SetConsoleTextAttribute(hConsole, 14);
                printf("recieved: ");
                SetConsoleTextAttribute(hConsole, 7);
                printf("%.2lf\n",dollars);
                flag = 0;

            }





    }
                if(flag)
                {
                    SetConsoleTextAttribute(hConsole, 12);
                    printf("No transactions made yet");
                    SetConsoleTextAttribute(hConsole, 7);
                }
                if(strcmp(account.status,"inactive")==0)
                {
                    SetConsoleTextAttribute(hConsole, 12);
                    printf("\nAccount is inactive");
                }
                SetConsoleTextAttribute(hConsole, 2);
                printf("\nTotal Balance: ");
                SetConsoleTextAttribute(hConsole, 7);
                printf("%.2lf\n",account.balance);

    fclose(fr);
}

void PRINT()
{
    int n, flag = 0;
    int count=0;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    info *acc;
    SetConsoleTextAttribute(hConsole, 3);
    printf("Type 1 for name\nType 2 for balance\nType 3 for date opened\nType 4 for status\n");
    printf("Enter desired order\n");
    SetConsoleTextAttribute(hConsole, 7);
    scanf("%d",&n);
    getchar();
    FILE *fr = fopen("accounts.txt", "r");
    if (!fr)
    {
        SetConsoleTextAttribute(hConsole, 12);
        printf("File error\n");
        SetConsoleTextAttribute(hConsole, 7);
        exit(1);
    }

    char str[200];
    while (fgets(str, sizeof(str), fr))
        count++;
    fclose(fr);


    switch(n)
    {
    case 1:
        acc = sortByName(count);
        SetConsoleTextAttribute(hConsole, 3);
        printf("\nAccounts sorted by first letter of name:\n");
        SetConsoleTextAttribute(hConsole, 7);
        flag = 1;
        break;
    case 2:
        acc = sortByBalance (count);
        SetConsoleTextAttribute(hConsole, 3);
        printf("\nAccounts sorted by balance:\n");
        SetConsoleTextAttribute(hConsole, 7);
        flag = 1;
        break;
    case 3:
        acc = sortByDateOpened(count);
        SetConsoleTextAttribute(hConsole, 3);
        printf("\nAccounts sorted by date opened:\n");
        SetConsoleTextAttribute(hConsole, 7);
        flag = 1;
        break;
    case 4:
        acc = sortByStatus(count);
        SetConsoleTextAttribute(hConsole, 3);
        printf("\nAccounts sorted by Status:\n");
        SetConsoleTextAttribute(hConsole, 7);
        flag = 1;
        break;
    default:
    {
        SetConsoleTextAttribute(hConsole, 12);
        printf("Invalid input\n");
        return;
    }

    }
    if(flag)
    {
        for (int i = 0; i < count ; i++)
        {
            info account = acc[i];
            printf("Account Number : %s \n", account.accNumber);
            printf("Name : %s\n", account.name);
            printf("E-mail : %s\n", account.email);
            printf("Balance : %.2f\n", account.balance);
            printf("Mobile: %s\n", account.mobile);
            printDate(account);

            if (strcmp(account.status, "active") == 0)
            {
                SetConsoleTextAttribute(hConsole, 2);
                printf("Status: %s\n", account.status);
                SetConsoleTextAttribute(hConsole, 7);
            }
            else
            {
                SetConsoleTextAttribute(hConsole, 12);
                printf("Status: %s\n", account.status);
                SetConsoleTextAttribute(hConsole, 7);
            }

            printf("\n");
        }
    }
    free(acc);
}

void printDate(info acc)
{
    switch(acc.date.month)
    {
    case 1:
        printf("Date Opened : January %d\n", acc.date.year);
        break;
    case 2:
        printf("Date Opened : February %d\n", acc.date.year);
        break;
    case 3:
        printf("Date Opened : March %d\n", acc.date.year);
        break;
    case 4:
        printf("Date Opened : April %d\n", acc.date.year);
        break;
    case 5:
        printf("Date Opened : May %d\n", acc.date.year);
        break;
    case 6:
        printf("Date Opened : June %d\n", acc.date.year);
        break;
    case 7:
        printf("Date Opened : July %d\n", acc.date.year);
        break;
    case 8:
        printf("Date Opened : August %d\n", acc.date.year);
        break;
    case 9:
        printf("Date Opened : September %d\n", acc.date.year);
        break;
    case 10:
        printf("Date Opened : October %d\n", acc.date.year);
        break;
    case 11:
        printf("Date Opened : November %d\n", acc.date.year);
        break;
    case 12:
        printf("Date Opened : December %d\n", acc.date.year);
        break;
    default:
        printf("Month Not found");

    }
}

void strtolower(char *s)
{
    for(int i = 0; s[i]; i++)
        s[i] = tolower((unsigned char)s[i]);
}

void trim(char *s)
{
    // remove trailing newline/space
    int len = strlen(s);
    while(len > 0 && (s[len-1]==' ' || s[len-1]=='\n' || s[len-1]=='\r'))
        s[--len] = '\0';

    // remove leading spaces
    int start = 0;
    while(s[start] == ' ') start++;
    if(start > 0)
        memmove(s, s + start, len - start + 1); // +1 for '\0'
}

int compareByName(const void *a, const void *b)
{
    const info *acc1 = (const info *)a;
    const info *acc2 = (const info *)b;

    return strcasecmp(acc1->name, acc2->name);
}

info* sortByName(int count)
{
    info *accounts = malloc(sizeof(info) * count);
    if (!accounts)
    {
        printf("Memory allocation failed\n");
        exit(1);
    }

    // Load accounts
    for (int i = 0; i < count; i++)
    {
        accounts[i] = LOAD(i);
    }

    // Sort by name
    qsort(accounts, count, sizeof(info), compareByName);

    return accounts;
}


info* sortByBalance(int count)
{
    info *accounts = malloc(sizeof(info) * (count));
    if (!accounts)
    {
        printf("Memory allocation failed\n");
        exit(1);
    }

    // Load each account
    for (int i = 0; i < count; i++)
    {
        accounts[i] = LOAD(i);
    }

    // Sort by balance
    for (int i = 0; i < count - 1; i++)
    {
        for (int j = 0; j < count - i - 1; j++)
        {
            double b1 = accounts[j].balance;
            double b2 = accounts[j + 1].balance;

            if (b1 > b2)
            {
                info tempAcc = accounts[j];
                accounts[j] = accounts[j + 1];
                accounts[j + 1] = tempAcc;
            }
        }
    }
    return accounts;
}

info* sortByDateOpened(int count)
{
    info *accounts = malloc(sizeof(info) * (count));
    if (!accounts)
    {
        printf("Memory allocation failed\n");
        exit(1);
    }

    // Load each account
    for (int i = 0; i < count; i++)
    {
        accounts[i] = LOAD(i);
    }

    // Sort by dateOpened
    for (int i = 0; i < count - 1; i++)
    {
        for (int j = 0; j < count - i - 1; j++)
        {
            int d1 = accounts[j].date.year;
            int d2 = accounts[j + 1].date.year;

            if (d1 > d2)
            {
                info tempAcc = accounts[j];
                accounts[j] = accounts[j + 1];
                accounts[j + 1] = tempAcc;
            }
            else if(d1 == d2)
            {
                int m1 = accounts[j].date.month;
                int m2 = accounts[j + 1].date.month;
                if (m1 > m2)
                {
                    info tempAcc = accounts[j];
                    accounts[j] = accounts[j + 1];
                    accounts[j + 1] = tempAcc;
                }
            }
        }
    }
    return accounts;

}

info* sortByStatus(int count)
{
    info* accounts = malloc(sizeof(info) * count);
    if (!accounts)
    {
        printf("Memory allocation failed\n");
        exit(1);
    }

    // Load each account
    for (int i = 0; i < count; i++)
    {
        accounts[i] = LOAD(i);
        trim(accounts[i].status);  // <-- use accounts[i]
    }

    // Bubble sort: move "inactive" accounts to the end
    for (int i = 0; i < count - 1; i++)
    {
        for (int j = 0; j < count - i - 1; j++)
        {
            // Swap if the current is active and next is inactive
            if (strcmp(accounts[j].status, "inactive") == 0 &&
                strcmp(accounts[j + 1].status, "inactive") != 0)
            {
                info tempAcc = accounts[j];
                accounts[j] = accounts[j + 1];
                accounts[j + 1] = tempAcc;
            }
        }
    }

    return accounts;
}





