#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
struct transc
{
    float amt;
    struct transc *prev;
    struct transc *next;
    struct transc *start;
    char s;
};
struct accnt
{
    char first_name[15];
    char last_name[15];
    char father_name[20];
    char birthdate[3];
    char birthmonth[3];
    char birthyear[5];
    char ph_no[12];
    char accnt_no[15];
    char aadhaar[15];
    float balance;
    char pwd[10];
    struct transc *transctions;
    int c;
};
typedef struct accnt cust;
struct custlinks
{
    struct custlinks *prev;
    cust details;
    struct custlinks *next;
}*head=NULL;
typedef struct custlinks data;
int count=0;
char *m=__DATE__;
void display_accnts()
{
    data *temp=head;
    if(temp==NULL)
        printf("NO ACCOUNTS FOUND\n");
    else
    {
        while(temp!=NULL)
        {
            printf("\t__________________________________________\n");
            printf("\tACCOUNTANT FULLNAME : \033[1;37m%s %s\033[0m\n",temp->details.first_name,temp->details.last_name);
            printf("\tACCOUNT NUMBER      : \033[1;37m%s\n\033[0m",temp->details.accnt_no);
            printf("\tACCOUNT BALANCE     : \033[1;32m₹%.2f\n\033[0m",temp->details.balance);
            temp=temp->next;
        }
    }
    printf("\n\n________________________________________________\n");
}
void display(data *temp)
{
    printf("\t\tYOUR BANK DETAILS\n");
    printf("\tACCOUNTANT FULLNAME : \033[1;37m%s %s\n\033[0m",temp->details.first_name,temp->details.last_name);
    printf("\tACCOUNT BALANCE     : \033[1;32m₹%.2f\n\033[0m",temp->details.balance);
    printf("\tFATHER NAME         : \033[1;37m%s\n\033[0m",temp->details.father_name);
    printf("\tDATE OF BIRTH       : \033[1;37m%s-%s-%s\n\033[0m",temp->details.birthdate,temp->details.birthmonth,temp->details.birthyear);
    printf("\tPHONE NUMBER        : \033[1;37m%s\n\033[0m",temp->details.ph_no);
    printf("\tAADHAAR NUMBER      : \033[1;37m%s\n\033[0m",temp->details.aadhaar);
    printf("\t**ACCOUNT NUMBER    : \033[1;31m%s\033[0m\n",temp->details.accnt_no);
    printf("\n\n\t___________________________________________\n");
}
data* find_acc()
{
    data* temp=head;
    char acc[15],pin[10];
    printf("\n\tENTER YOUR ACCOUNT NUMBER : ");
    scanf(" %s",acc);
    while(temp!=NULL && strcmp(temp->details.accnt_no,acc)!=0)
        temp=temp->next;
    if(temp==NULL)
    {
        printf("\n\tNO ACCOUNT FOUND WITH ACCOUNT NUMBER : : %s\n",acc);
        return NULL;
    }
    else
    {
        printf("\n\tENTER YOUR ACCOUNT PIN :: \n");
        scanf(" %s",pin);
        if(strcmp(temp->details.pwd,pin)==0)
            return temp;
        else
        {
            printf("\t\033[1;31mWRONG PIN ENTERED\033[0m\n");
            return NULL;
        }
        
    }
            
}
void deposit()
{
    system("clear");
    printf("\033[1;33m BANK SERVICES ONLINE PORTAL\t\t\tDATE : %s\033[0m\n",m);
    data* ptr=find_acc();
    if(ptr!=NULL)
    {
        struct transc *temp=ptr->details.transctions->start;
        while(temp->next!=NULL)
            temp=temp->next;
        printf("\n\tENTER AMOUNT TO DEPOSIT : \n");
        struct transc* new=(struct transc*)malloc(sizeof(struct transc));
        scanf("%f",&new->amt);
        if(new->amt <= 0)
        {
            printf("\033[1;31m\tINVALID AMOUNT\033[0m\n");
            free(new);
            return;
        }
        new->prev=temp;
        new->next=NULL;
        temp->next=new;
        ptr->details.balance+=new->amt;
        new->s='+';
        ptr->details.c++;
        printf("\033[1;32m\t%.2frs IS CREDITED INTO YOUR ACCOUNT\033[0m\n", new->amt);
        printf("\tAVAILABLE BALANCE : %.2frs\n",ptr->details.balance);
    }
    printf("\n\n\t___________________________________________\n");
}
void withdrawl()
{
    system("clear");
    printf("\033[1;33m BANK SERVICES ONLINE PORTAL\t\t\tDATE : %s\033[0m\n",m);
    data* ptr=find_acc();
    if(ptr!=NULL)
    {
        struct transc *temp=ptr->details.transctions->start;
        while(temp->next!=NULL)
            temp=temp->next;
        struct transc* new=(struct transc*)malloc(sizeof(struct transc));
        printf("\n\tENTER AMOUNT TO WITHDRAW : \n");
        scanf("%f",&new->amt);
        if(new->amt<ptr->details.balance)
        {
            new->prev=temp;
            new->next=NULL;
            temp->next=new;
            ptr->details.balance-=new->amt;
            ptr->details.c++;
            new->s='-';
            printf("\033[1;31m\t%.2frs IS DEBITED SUCCESSFULLY FROM YOUR ACCOUNT\033[0m\n",new->amt);
            printf("\tAVAILABLE BALANCE : %.2frs\n",ptr->details.balance);
        }
        else
            printf("\tNO SUFFICIENT BALANCE\n");
    }
    printf("\n\n\t___________________________________________\n");
}
void tranc_hist()
{
    system("clear");
    printf("\033[1;33m BANK SERVICES ONLINE PORTAL\t\t\tDATE : %s\033[0m\n",m);
    data* ptr=find_acc();
    if(ptr!=NULL)
    {
        struct transc *temp=ptr->details.transctions->start;
        printf("\tTRANSACTION DETAILS OF ACCOUNT NUMBER : %s \n",ptr->details.accnt_no);
        while(temp!=NULL)
        {
            if (temp->s == '+')
            {
                printf("\033[1;32m\t\t%c ₹%.2f\033[0m\n",temp->s,temp->amt);
            }
            else
            {
                printf("\033[1;31m\t\t%c ₹%.2f\033[0m\n",temp->s, temp->amt);
            }
            temp=temp->next;
        }
    }
    printf("\n\n\t___________________________________________\n");
}
void check_balance()
{
    system("clear");
    printf("\033[1;33m BANK SERVICES ONLINE PORTAL\t\t\tDATE : %s\033[0m\n",m);
    data* ptr=find_acc();
    if(ptr!=NULL)
    {
        printf("\t\tBALANCE AVAILABLE :: \n\tACCOUNT NUMBER    : %s \n\tACCOUNT HOLDER    : %s %s \n\tAVAILABLE BALANCE : ₹%.2f\n",ptr->details.accnt_no,ptr->details.first_name,ptr->details.last_name,ptr->details.balance);
    }
    printf("\n\n\t___________________________________________\n");
}
void delete_acc()
{
    system("clear");
    printf("\033[1;33m BANK SERVICES ONLINE PORTAL\t\t\tDATE : %s\033[0m\n",m);
    float amunt;
    data *ptr,*del_acc;
    struct transc *temp;
    ptr=find_acc();
    if(ptr!=NULL)
    {
        del_acc=ptr;
        printf("\tAVAILABLE BALANCE IS %.2frs\n",del_acc->details.balance);
        if((int)ptr->details.balance!=0)
        {
            printf("\t%.2frs IS RECEIVED BY ACCOUNT HOLDER %s %s\n",ptr->details.balance,ptr->details.first_name,ptr->details.last_name);
        }
        else
            printf("\tBALANCE IS 0.00rs,NO AMOUNT TO WITHDRAW\n");
        if(ptr==head)
        {
            if(ptr->next==NULL)
                head=NULL;
            else
            {
                head=ptr->next;
                head->prev=NULL;
            }
        }
        else
        {
            ptr->prev->next=ptr->next;
            if(ptr->next!=NULL)
                ptr->next->prev=ptr->prev;
        }
    }
    free(del_acc);
    printf("\t\033[1;31m*ACCOUNT SUCCESSFULLY DELETED*\033[0m\n");
    printf("\n\n\t___________________________________________\n");
}
void load_accounts_from_file()
{
    FILE *fp;
    fp = fopen("accounts.txt", "r");
    if(fp==NULL)
    {
        return;
    }
    int e;
    e = fgetc(fp);
    if (e == EOF)
    {
        return;
    }
    rewind(fp);
    while (!feof(fp))
    {
        int n;
        data *new_customer;
        new_customer = (data *)malloc(sizeof(data));
        struct transc *ptr;
        fscanf(fp, "%s %s %s %s %s %s %s %s %s %f %s %d %d ",
               new_customer->details.first_name, new_customer->details.last_name,
               new_customer->details.father_name, new_customer->details.birthdate,
               new_customer->details.birthmonth, new_customer->details.birthyear,
               new_customer->details.ph_no, new_customer->details.accnt_no,
               new_customer->details.aadhaar, &new_customer->details.balance,
               new_customer->details.pwd, &count, &n);
        new_customer->prev = new_customer->next = NULL;
        new_customer->details.transctions = (struct transc *)malloc(sizeof(struct transc));
        new_customer->details.transctions->start = NULL;
        new_customer->details.c=n;
        for (int i = 1; i <= n; i++)
        {
            struct transc *new = (struct transc *)malloc(sizeof(struct transc));
            fscanf(fp, "%c %f ", &new->s, &new->amt);
            new->next = new->prev = NULL;
            if (i == 1)
            {
                new_customer->details.transctions->start = new;
            }
            else
            {
                struct transc *temp = new_customer->details.transctions->start;
                while (temp->next != NULL)
                {
                    temp = temp->next;
                }
                temp->next = new;
                new->prev = temp;
            }
        }

        if (head == NULL)
        {
            head = new_customer;
        }
        else
        {
            data *temp = head;
            while (temp->next != NULL)
            {
                temp = temp->next;
            }
            temp->next = new_customer;
            new_customer->prev = temp;
        }
    }
    fclose(fp);
}

void save_accounts_to_file() 
{
    FILE *fp;
    fp = fopen("accounts.txt", "w"); 
    data *temp = head;
    while (temp != NULL)
    {
        fprintf(fp, "%s %s %s %s %s %s %s %s %s %.2f %s %d %d ",
            temp->details.first_name, temp->details.last_name,
            temp->details.father_name, temp->details.birthdate,
            temp->details.birthmonth, temp->details.birthyear,
            temp->details.ph_no, temp->details.accnt_no,
            temp->details.aadhaar, temp->details.balance,
            temp->details.pwd,count,temp->details.c);
        struct transc *ptr=temp->details.transctions->start;
        while(ptr!=NULL)
        {
            if(ptr->next!=NULL)
                fprintf(fp,"%c %.2f ",ptr->s,ptr->amt);
            else
                fprintf(fp,"%c %.2f\n",ptr->s,ptr->amt);
            ptr=ptr->next;
        }
        temp = temp->next;
    }
    fclose(fp); 
}
void addcustomer()
{
    int amunt,i;
    char b[5];
    for(i=7;m[i]!='\0';i++)
        b[i-7]=m[i];
    system("clear");
    printf("\033[1;33m BANK SERVICES ONLINE PORTAL\t\t\tDATE : %s\033[0m\n",m);
    cust user;
    count++;
    printf("\nEnter Your FIRST NAME:: ");
    scanf(" %[^\n]",user.first_name);
    for(i=0;user.first_name[i]!='\0';i++)
    {
        user.first_name[i]=toupper(user.first_name[i]);
    }
    printf("\nEnter Your LAST NAME:: ");
    scanf(" %[^\n]",user.last_name);
    for(i=0;user.last_name[i]!='\0';i++)
    {
        user.last_name[i]=toupper(user.last_name[i]);
    }
    printf("\nEnter Your FATHER NAME:: ");
    scanf(" %s",user.father_name);
    for(i=0;user.father_name[i]!='\0';i++)
    {
        user.father_name[i]=toupper(user.father_name[i]);
    }
    printf("\n  ENTER YOUR DOB\nDATE MONTH YEAR(**with spaces)\n   ");
    dob : scanf(" %s %s %s",user.birthdate,user.birthmonth,user.birthyear);
    int reqage=atoi(b)-atoi(user.birthyear);
    if(1>atoi(user.birthdate)>31 || 1>atoi(user.birthmonth)>13 || reqage<16 || reqage>105)
    {
        if(reqage<16 && reqage>0)
        {
            printf("\033[1;31m\tACCOUNT CANNOT BE CREATED AT YOUR AGE\n\tMINIMUM AGE SHOULD BE 16\033[0m\n");
            count--;
            return;
        }
        printf("\n\tACCOUNT CANNOT BE CREATED\n");
        printf("\n\tENTER VALID DATE OF BIRTH :: ");
        goto dob;
    }
    printf("\nEnter Your 10-DIGIT PHONE NUMBER:: ");
    enter : scanf(" %s",user.ph_no);
    if(strlen(user.ph_no)!=10)
    {
        printf("\n\tENTER CORRECT 10-DIGIT PHONE NUMBER ::  ");
        goto enter;
    }
    printf("\nEnter Your 12-DIGIT AADHAAR NUMBER:: ");
    adhar : scanf(" %s",user.aadhaar);
    if(strlen(user.aadhaar)!=12)
    {
        printf("\n\tENTER CORRECT 12-DIGIT AADHAAR NUMBER :: ");
        goto adhar;
    }
    printf("\nCREATE YOUR SECURE 6-DIGIT PIN FOR FURTHER USES :: ");
    pswd : scanf(" %s",user.pwd);
    if(strlen(user.pwd)!=6)
    {
        printf("\n\tCREATE 6-DIGIT PIN ONLY :: \n");
        goto pswd;
    }
    char d[4];
    sprintf(d,"%d",count);
    strcpy(user.accnt_no,"");
    strcat(user.accnt_no,"567843219");
    strcat(user.accnt_no,d);
    printf("\n\tPlease DEPOSIT INITIAL amount :: \n");
    struct transc* ptr;
    ptr=(struct transc*)malloc(sizeof(struct transc));
    scanf("%f",&ptr->amt);
    user.balance=ptr->amt;
    user.transctions=(struct transc*)malloc(sizeof(struct transc));
    user.c=1;
    ptr->s='+';
    user.transctions->start=ptr;
    ptr->next=ptr->prev=NULL;
    data *new_customer;
    new_customer=(data*)malloc(sizeof(data));
    new_customer->prev=new_customer->next=NULL;
    new_customer->details=user;
    system("clear");
    printf("\033[1;33m BANK SERVICES ONLINE PORTAL\t\t\tDATE : %s\033[0m\n",m);
    display(new_customer);
    if(head==NULL)
        head=new_customer;
    else
    {
        data *temp=head;
        while(temp->next!= NULL)
            temp=temp->next;
        temp->next=new_customer;
    }
    printf("\n\033[1;32m\t\t*ACCOUNT SUCCESSFULLY CREATED*\033[0m\n");
    printf("\n\n\t___________________________________________\n");
}
void edit_details()
{
    system("clear");
    printf("\033[1;33m BANK SERVICES ONLINE PORTAL\t\t\tDATE : %s\033[0m\n",m);
    int ch;
    data* ptr=find_acc();
    if(ptr!=NULL)
    {
        display(ptr);
        printf("\tWHAT DO YOU WANT TO UPDATE\n");
        printf("\t1.FIRST NAME\n\t2.LAST NAME\n\t3.PHONE NUMBER\n\t4.Date of birth\n");
        printf("\nENTER YOUR CHOICE TO EDIT YOUR DETAILS\n");
        scanf("%d",&ch);
        switch(ch)
        {
            case 1: printf("\nEnter first name want to change : ");
                    scanf(" %[^\n]",ptr->details.first_name);
                    break;
            case 2: printf("\nEnter last name want to edit : ");
                    scanf(" %s",ptr->details.last_name);
                    break;
            case 3: printf("\nEnter new PHONE NUMBER : ");
                    scanf(" %s",ptr->details.ph_no);
                    break;
            case 4: printf("\nEnter new date of birth want to change : ");
                    scanf(" %s %s %s",ptr->details.birthdate,ptr->details.birthmonth,ptr->details.birthyear);
                    break;
        }
        system("clear");
        printf("\nUPDATED DETAILS");
        display(ptr);
    }
    printf("\n\n\t___________________________________________\n");
}
void search_by_name()
{
    system("clear");
    printf("\033[1;33m BANK SERVICES ONLINE PORTAL\t\t\tDATE : %s\033[0m\n",m);
    char fname[20],lname[20];
    printf("\nENTER YOUR First NAME TO SEARCH :: ");
    scanf(" %[^\n]",fname);
    printf("\nENTER YOUR LAST NAME :: ");
    scanf(" %[^\n]",lname);
    data *ptr=head;
    while(ptr!=NULL && (strcmp(ptr->details.first_name,fname)!=0 && strcmp(ptr->details.last_name,lname)!=0))
        ptr=ptr->next;
    if(ptr==NULL)
        printf("\nNO ACCOUNT WITH NAME %s %s\n",fname,lname);
    else
    {
        display(ptr);
    }
    printf("\n\n\t___________________________________________\n");
}
int main()
{  
    load_accounts_from_file();
    //load_transactions();
    int ch;
    char acc[15];
    printf("\033[1;31m\t\t ____    _    _   _ _  __\033[0m\n");
    printf("\033[1;32m\t\t| __ )  / \\  | \\ | | |/ /\033[0m\n");
    printf("\033[1;33m\t\t|  _ \\ / _ \\ |  \\| | ' /\033[0m\n");
    printf("\033[1;32m\t\t| |_) / ___ \\| |\\  | . \\\033[0m\n");
    printf("\033[1;31m\t\t|____/_/   \\_\\_| \\_|_|\\_\\\n\033[0m\n");
    printf("\t\t\033[1;36m========================\033[0m\t\t\n\n");
    printf("\t\t\033[1;35m*WELCOME TO OUR BANK SERVICES*\033[0m\n");
    while(1)
    {
        printf("\n\t1.New account\n\t2.DEPOSIT\n\t3.WITHDRAWAL\n\t4.CHECK TRANSACTION HISTORY\n");
        printf("\t5.BALANCE ENQUIRY\n\t6.DELETE ACCOUNT\n\t7.DISPLAY ALL ACCOUNTS\n\t8.EDIT DETAILS\n");
        printf("\t9.SEARCH ACCOUNT BY ACCOUNT NUMBER\n\t10.SEARCH ACCOUNT BY NAME\n\t11.EXIT\n");
        printf("\n\t\033[1;33m=>  Enter your choice\n\033[0m");
        scanf("%d",&ch);
        switch(ch)
        {
            case 1: addcustomer();
                    break;
            case 2: deposit();
                    break;
            case 3: withdrawl();
                    break;
            case 4: tranc_hist();
                    break;
            case 5: check_balance();
                    break;
            case 6: delete_acc();
                    break;
            case 7: system("clear");
                    printf("\033[1;33m BANK SERVICES ONLINE PORTAL\t\t\tDATE : %s\033[0m\n",m);
                    display_accnts();
                    break;
            case 8: edit_details();
                    break;
            case 9: system("clear");
                    printf("\033[1;33m BANK SERVICES ONLINE PORTAL\t\t\tDATE : %s\033[0m\n",m);
                    data *ptr;
                    ptr=find_acc();
                    if(ptr!=NULL)
                        display(ptr);
                    break;
            case 10:search_by_name();
                    break; 
            case 11:save_accounts_to_file();
                    exit(0);
            default:printf("\tINVALID CHOICE\n");
        }
        printf("\033[1;32m\n\n\t\t   🙂  THANKYOU FOR VISITING  🙂   \n\t\t    HAVE A NICE DAY\n\033[0m");
        printf("\n\n\t___________________________________________\n");
    }
    return 0;
}  