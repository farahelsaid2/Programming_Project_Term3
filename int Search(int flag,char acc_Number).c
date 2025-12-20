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
        printf("Account not found");
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