void Report()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    int j,c;
    int k =0;
    int counter = 0;
    int flag = 0;
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
        SetConsoleTextAttribute(hConsole, 12);
        printf("\nBack to menu\n");
        SetConsoleTextAttribute(hConsole, 7);
        Sleep(5000);
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
                SetConsoleTextAttribute(hConsole, 2);
                printf("\nTotal Balance: ");
                SetConsoleTextAttribute(hConsole, 7);
                printf("%.2lf\n",account.balance);

    fclose(fr);
}