int Save()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    char answer[10];

    SetConsoleTextAttribute(hConsole, 2);
    printf("Do you want to save (Y/N): ");
    SetConsoleTextAttribute(hConsole, 7);

    fgets(answer,sizeof(answer),stdin);
    answer[strcspn(answer, "\n")] = '\0';
    answer[0] = tolower(answer[0]);

    if (strcmp(answer,"y") == 0)
        return 1;

    if (strcmp(answer,"n") == 0)
        return 0;

    SetConsoleTextAttribute(hConsole, 12);
    printf("\nInvalid Input\nEdits will be discarded\n");
    SetConsoleTextAttribute(hConsole, 7);

    SetConsoleTextAttribute(hConsole, 3);
    printf("Press A to try again\nPress E to exit\n");
    SetConsoleTextAttribute(hConsole, 7);

    fgets(answer,sizeof(answer),stdin);
    answer[0] = tolower(answer[0]);

    if (strcmp(answer,"a") == 0)
        return Save();
    if (strcmp(answer,"e") == 0)
        return 0;

return 0;
}
