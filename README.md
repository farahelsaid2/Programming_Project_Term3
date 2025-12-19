typedef struct
{
    int month;
    int year;
} dateOpened;


typedef struct
{
    char accNumber[50];
    char name[50];
    char email[50];
    double balance;
    dateOpened date;
    char mobile[12];
    char status[20];
} info;


To call search --> Search(0,"account number");
To call load --> LOAD(the number of needed line);
