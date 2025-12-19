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