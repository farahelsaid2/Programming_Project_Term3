int deposit(){
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
acc=LOAD(Search(0,accno));
accno[strcspn(accno, "\n")] = '\0';
snprintf(filename, sizeof(filename), "%s.txt", accno);
 if(Search(0,accno)==-1)
    {
        SetConsoleTextAttribute(hConsole, 12);
        printf("Please enter a valid account number");
        SetConsoleTextAttribute(hConsole, 7);
        deposit();
    }

    else
    {
        if(strcmp(acc.status,"inactive")==0)
        {
            SetConsoleTextAttribute(hConsole, 12);
            printf("The account is not active!\n");
            printf("Please enter a valid account number\n");
            SetConsoleTextAttribute(hConsole, 7);
            deposit();
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