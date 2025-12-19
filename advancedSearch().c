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