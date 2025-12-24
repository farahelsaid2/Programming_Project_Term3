
int dailyLimit(info* acc,float t){
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
    acc=LOAD(Search(0,accno));
    accno[strcspn(accno, "\n")] = '\0';
    snprintf(filename, sizeof(filename), "%s.txt", accno);    
    if(Search(0,accno)==-1)
    {
        SetConsoleTextAttribute(hConsole, 12);
        printf("Please enter a valid account number \n");
        SetConsoleTextAttribute(hConsole, 7);
        withdraw();
    }

    else
    {
        if(strcmp(acc.status,"inactive")==0)
        {
            SetConsoleTextAttribute(hConsole, 12);
            printf("The account is not active! \n");
            printf("Please enter a valid account number\n");
            SetConsoleTextAttribute(hConsole, 7);
            getchar();
            withdraw();
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
                printf("Please enter a valid amount \n");
                SetConsoleTextAttribute(hConsole, 7);
                getchar();
                withdraw();
            }
            else if(acc.balance<t)
            {
                SetConsoleTextAttribute(hConsole, 12);
                printf("There is no enough balance to withdraw this ammount \n");
                printf("Please enter a valid amount \n");
                SetConsoleTextAttribute(hConsole, 7);
                getchar();
                withdraw();
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