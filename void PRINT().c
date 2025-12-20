info* sortByName(int count)
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

    // Sort by names
    for (int i = 0; i < count - 1; i++)
    {
        for (int j = 0; j < count - i - 1; j++)
        {
            char c1 = toupper(accounts[j].name[0]);
            char c2 = toupper(accounts[j + 1].name[0]);

            if (c1 > c2)
            {
                info tempAcc = accounts[j];
                accounts[j] = accounts[j + 1];
                accounts[j + 1] = tempAcc;
            }
        }
    }

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

    // Sort by Status
    for (int i = 0; i < count - 1; i++)
    {
        for (int j = 0; j < count - i - 1; j++)
        {
            if (strcmp(accounts->status,"inactive") == 0)
            {
                info tempAcc = accounts[j];
                accounts[j] = accounts[j + 1];
                accounts[j + 1] = tempAcc;
            }
        }
    }

    return accounts;

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
        printf("Invalid input\nFor any other invalid input program will quit\n");
        SetConsoleTextAttribute(hConsole, 3);
        printf("Type 5 to quit\nType 6 to choose again\n");
        SetConsoleTextAttribute(hConsole, 7);
        scanf("%d", &n);
        getchar();
        if(n == 5) Quit();
        else if(n == 6) PRINT();
        else Quit();
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
}