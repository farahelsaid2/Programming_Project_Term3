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