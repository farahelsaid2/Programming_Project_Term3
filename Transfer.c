int transfer() {
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
    sacc = LOAD(Search(0, saccno));
    saccno[strcspn(saccno, "\n")] = '\0';
    snprintf(sfilename, sizeof(sfilename), "%s.txt", saccno);    
    if (Search(0, saccno) == -1) {
        SetConsoleTextAttribute(hConsole, 12);
        printf("Please enter a valid account number \n");
        SetConsoleTextAttribute(hConsole, 7);
        transfer();
    } else {
        if (strcmp(sacc.status, "inactive") == 0) {
            SetConsoleTextAttribute(hConsole, 12);
            printf("The sender account is not active! \n");
            printf("Please enter a valid account number\n");
            SetConsoleTextAttribute(hConsole, 7);
            transfer();
        } else {
            SetConsoleTextAttribute(hConsole, 3);
            printf("Enter the ammount of money you want to transfer: ");
            SetConsoleTextAttribute(hConsole, 7);
            scanf("%f", &t);
            getchar();
            if (sacc.balance < t) {
                SetConsoleTextAttribute(hConsole, 12);
                printf("There is no enough balance to transfer this ammount \n");
                printf("Please enter a valid amount \n");
                SetConsoleTextAttribute(hConsole, 7);
                transfer();
            } else { 
                SetConsoleTextAttribute(hConsole, 3);
                printf("Enter the reciver account number: ");
                fgets(raccno, sizeof(raccno), stdin);
                racc = LOAD(Search(0, raccno));
                raccno[strcspn(raccno, "\n")] = '\0';
                snprintf(rfilename, sizeof(rfilename), "%s.txt", raccno);    
                if (Search(0, raccno) == -1) {
                    SetConsoleTextAttribute(hConsole, 12);
                    printf("Please enter a valid account number \n");
                    SetConsoleTextAttribute(hConsole, 7);
                    transfer();
                } else {
                    if (strcmp(racc.status, "inactive") == 0) {
                        SetConsoleTextAttribute(hConsole, 12);
                        printf("The reciver account is not active! \n");
                        printf("Please enter a valid account number");
                        SetConsoleTextAttribute(hConsole, 7);
                        transfer();
                    }
                    if (Save(&racc,t,&sacc,t) == 1) {   
                        sacc.balance -= t;
                        racc.balance += t;
                        LOAD(Search(0, saccno));
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
