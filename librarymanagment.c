#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<windows.h>
#include<string.h>
#include<time.h>
#include<stdbool.h>
void resetColor(){ /// reset the old color of console
  printf("\033[0m");
}
// System Operation Functions 
void password(void);
void menu(void);
void user_menu();
void userPanel(void);
void bookPanel(void);
void password_menu();
void Ragister();
void Login();
void forget_password();
// user operation function
void modifyUser();
void listUser();
int searchUser();
void deleteUser();
void list_books();
void searchByName();
void searchByID();
void searchbooks();
void view_issueinfo();
void gotoxy(int , int);
// Staff Operation Function
void addUser();
void bookPanal();
void view_books();
void search_book();
void issue_book();
void return_book();
void remove_book();
void book_menu();
void user_search();
void add_book();
// Supporting Function 
void replaceInFile();
void view_list();
void due_date();
bool checkid();
bool checkuser();
void getuserdata();

char uid2[12];
struct library{
    char Book_Name[50];
    char Author_Name[20];
    char Book_Number[10];
    char edition[5];
    char rack[8];
    char price[8];
    char category[20];
    char year_publication[6];
    char issued[3];
    char issue_to[20];
    char issue_date[20];
    char duedate[20];

};
struct library book;
struct user{
    char username[20];
    char gender[2];
    char phone[11];
    char userId[11];
    char Password[12];
};
struct user user;
int main(){
    resetColor();
    system("cls");
    printf("\n====================================================");
    printf("\n >>>>> LIBRARY RECORD MANAGEMENT SYSTEM <<<<<< \n");
    printf(" ====================================================\n\n\n");
    
    printf("Press any key to continue ");
    getch();
    system("cls");
    menu();
}
void password(){

    char user[8];
    char userid[8]={"Admin"};
    char pwd[255];
    char code[255]={"Admin"};

    printf("--------------------\n");
    printf(">>> Login First <<<\n");
    printf("--------------------\n\n");
    printf("Enter your username: ");
    scanf("%s", user);
	printf("Enter your password: ");
    scanf("%s", pwd);

    // verifies the password 
    if(!strcmp(user, userid))
    {
        if(!strcmp(pwd, code)){
            book_menu();
        }else{
            printf("\nInvaild Password!\n");
            password();
        }
    }
    else
    {
        printf("\nInvaild Username!\n");
        password();
    }
}
void password_menu(){
    int choice;
    system("cls");
    printf("\n====================================================");
    printf("\n >>>>> USER ACCOUNT RAGISTRATION  <<<<<< \n");
    printf(" ====================================================\n\n");
    printf(">> 1. RAGISTER  \n");
    printf(">> 2. LOGIN  \n");
    printf(">> 3. FORGATE PASSWORD \n\n");
    fflush(stdin);
    printf("enter choice : ");
    scanf("%d",&choice);
    switch(choice){
        case 1:
        Ragister();
        break;
        case 2:
        Login();
        break;
        case 3:
        forget_password();
        break;
        default:
        printf("Invalid entry ..\n");
    }
}
void Ragister(){
    struct user user;
    printf("--------------------\n");
    printf(">>> Ragister Yourself <<<\n");
    printf("--------------------\n\n");
    FILE *pF = fopen("user_Records.txt", "ab");
    if(pF != NULL)
    {
        fflush(stdin);
        printf("Enter the  Name: ");
        gets(user.username);
        printf("Enter Gender [M/F]: ");
        gets(user.gender);
        printf("Enter Phone Number: ");
        gets(user.phone);
        printf("Enter User ID: ");
        gets(user.userId);
        printf("Enter password : ");
        gets(user.Password);
        fwrite(&user,sizeof(user),1,pF);

        printf("\n>>> you Ragister Successfully <<< \n");
    }
    else{
        printf("\n >>>> you have somthing error <<<< \n");
    }
    fclose(pF);
    fflush(stdin);
    printf("press any key to continue.... ");
    getch();
    password_menu();

}
void Login(){
    system("cls");
    struct user user;
    char uid[12];
    char pass[12];
    int found=0;
    printf("--------------------\n");
    printf(">>> Login Yourself <<<\n");
    printf("--------------------\n\n");
    fflush(stdin);
    printf("USERNAME : ");
    gets(uid);

    printf("PASSWORD : ");
    gets(pass);
    FILE *pF = fopen("user_Records.txt", "rb");
    if(pF == NULL){
        printf("\n You are enable to login ");
    }
    while(fread(&user,sizeof(user),1,pF)==1){
        if(strcmp(user.userId,uid)==0 && strcmp(user.Password,pass)==0){
            printf(" \n\n >> you login succesfully << \n");
            found=1;
            strcpy(uid2,uid);
        }

    }
    if(found==0){
        printf("\n\n >>> You have enterd wrong password or username <<<< \n");
        fclose(pF);
        password_menu();
    }
    else{

        fclose(pF);
        fflush(stdin);
        printf("press any key to continue : ");
        getch();
        user_menu();    
    }
    
}
void forget_password(){
    printf("--------------------\n");
    printf(">>> Forget password <<<\n");
    printf("--------------------\n\n");
    struct user user;
    char  pass[12] ,pass1[12];
    int flag=0;
    char find[9];
    srand(time(NULL));
    int n = 1000 + rand()%100;
    printf("CAPTCHA CODE \n  %d \n",n);
    int captcha;
    printf("Enetr captcha value : ");
    scanf("%d",&captcha);
    fflush(stdin);
    if(captcha == n){
        printf("Enter the user ID for forget password : ");
        gets(find);

        FILE *pF = fopen("user_Records.txt", "rb");
        FILE *pT = fopen("temporary.txt", "ab");

        while(fread(&user,sizeof(struct user),1,pF)==1){
            if(strcmp(find,user.userId)==0){
                fflush(stdin);
                printf(">> Enetr password : ");
                gets(pass);
                printf(">> Confirm password : ");
                gets(pass1);
                if(strcmp(pass , pass1)==0){
                    strcpy(user.Password,pass);
                    fwrite(&user,sizeof(user),1,pT);
                    printf("\n\nProcessing your changes....");
                }
                else{
                    printf("\n password not matched \n"); 
                }
                flag = 1;
            }
            else{
                fwrite(&user,sizeof(user),1,pT);
            }
        }
        fflush(stdin);
        fclose(pF);
        fclose(pT);

        if(flag == 0){
            printf("\n\n-------------------------------\n");
            printf(">>> Record Not Found <<<\n");
            printf("-------------------------------\n\n");
            printf("Redirecting to User Panel...");
            pT = fopen("temporary.txt", "wb");
            fclose(pT);
            printf("\n press key to continue \n");
            getch();
            password_menu();
        }

        pF = fopen("user_Records.txt", "wb");
        fclose(pF);

        pF = fopen("user_Records.txt", "ab");
        pT = fopen("temporary.txt", "rb");

        while(fread(&user,sizeof(user),1,pT)==1){
            fwrite(&user,sizeof(user),1,pF);
        }
        fclose(pF);
        fclose(pT);
        pT = fopen("temporary.txt", "wb");
        fclose(pT);
    }
    else{
        printf("\n Invalid captcha code \n");
    }
    printf("\n press any key to continue ");
    getch();
    password_menu();
}

// Main Selection menu between User & Book Panel
void menu(){
    system("cls");

    int number;
    printf("----------------------------------\n");
    printf(">>> Library Management System <<< \n");
    printf("----------------------------------\n\n");
    printf("> 1. User Management Panel \n");
    printf("> 2. Book Management Panel \n");
    printf("> 3. Exit programe \n\n");
    printf("> Enter the number: ");
    scanf("%d",&number);

    switch(number)
    {
        case 1:
            userPanel();
            break;
        case 2:
            bookPanel();
            break;
        case 3:
            exit(0);
            break;
        default:
            printf("\n>>> Invaild Input! <<<");
            menu();
        
    }
}
void bookPanel(){
    printf("-----------------------------------------------\n");
    printf(">>> Library Management System - Book Panel <<< \n");
    printf("-----------------------------------------------\n\n");
    password();  
}
void userPanel(){
    printf("-----------------------------------------------\n");
    printf(">>> Library Management System - Book Panel <<< \n");
    printf("-----------------------------------------------\n\n");
    password_menu();      
}
void user_menu(){
    system("cls");
    char uid1[12];
    strcpy(uid1,uid2);
    int number;

    printf("-----------------------------------------------\n");
    printf(">>> Library Management System - User Menu <<< \n");
    printf("-----------------------------------------------\n\n");
    printf("> 1. Search book \n");
    printf("> 2. List of issued book  \n");
    printf("> 3. List of Books      \n");
    printf("> 4. Modify User \n");
    printf("> 5. Search User \n");
    printf("> 6. Delete User \n");
    printf("> 7. Open Main Menu \n");
    printf("> 8. Close the Program... \n\n");

    printf("> Enter the number & hit ENTER: ");
    scanf("%d",&number);

    switch(number)
    {
        case 1:
            search_book();
            break;
        case 4:
            modifyUser(uid1);
            break;
        case 2:
            view_issueinfo(uid1);
            break;
        case 3:
            list_books();
            break;
        case 5:
            searchUser();
            break;
        case 6:
            deleteUser(uid1);
            break;
        case 7:
            menu();
            break;
        case 8:
            exit(0);
            break;
        default:
            printf("Invaild Input!");
            userPanel();
    }
}
void addUser(){
    
label1:
    
    system("cls");

    FILE *pF = fopen("user_Records.txt", "ab");

    if(pF != NULL)
    {
        fflush(stdin);
        printf("Enter the First Name: ");
        gets(user.username);
        printf("Enter Gender [M/F]: ");
        gets(user.gender);
        printf("Enter Phone Number: ");
        gets(user.phone);
        printf("Enter User ID: ");
        gets(user.userId);
        printf("Enter the Last Name: ");
        gets(user.Password);
        fwrite(&user,sizeof(user),1,pF);

        printf("\n>>> User Record Added Successfully <<< \n");

    }
    else
    {
        printf("Unable to open/locate the file.");
    }

    fclose(pF); 
    char input;

retry:
    //retry screen

    printf("\nDo you wanna enter more records [Y/N]: ");
    scanf(" %c",&input);

    if(input == 'y' || input=='Y')
    {
        goto label1;
    }
    else if(input=='n' || input=='N')
    {
        printf("\nRedirecting to User Panel.");
        book_menu();
    }
    else
    {
        printf("\nInvaild input. Redirecting to User Panel.");
        goto retry;
    }
}

void modifyUser(char uid[]){
    system("cls");
    char name1[255], gender1[5];
    char  uid1[9];
    char  phone1[11];

    int flag=0;

    char find[9];
    strcpy(uid1,uid);
    FILE *pF = fopen("user_Records.txt", "rb");
    FILE *pT = fopen("temporary.txt", "ab");

    while(fread(&user,sizeof(struct user),1,pF)==1)
    {
        if(strcmp(find,user.userId)==0)
        {
            printf("\n---------------------------------------------\n");
            printf(">>> Record Found, Allowing Modifications <<<\n");
            printf("-----------------------------------------------\n\n");
            fflush(stdin);
            printf("> Enter First Name: ");
            gets(name1);
            strcpy(user.username,name1);

            printf("> Enter Gender [M/F]: ");
            gets(gender1);
            strcpy(user.gender,gender1);
            fflush(stdin);
            printf("> Enter Student ID: ");
            gets(uid1);
            strcpy(user.userId,uid1);
            fflush(stdin);
            printf("> Enter Phone Number: ");
            gets(phone1);
            strcpy(user.phone,phone1);

            fwrite(&user,sizeof(user),1,pT);
            printf("\n\nProcessing your changes....");

            flag = 1;
        }
        else
        {
            fwrite(&user,sizeof(user),1,pT);
        }
    }
    fflush(stdin);
    fclose(pF);
    fclose(pT);

    if(flag == 0)
    {
        printf("\n\n-------------------------------\n");
        printf(">>> Record Not Found <<<\n");
        printf("-------------------------------\n\n");
        printf("Redirecting to User Panel...");
        pT = fopen("temporary.txt", "wb");
        fclose(pT);
        userPanel();
    }

    pF = fopen("user_Records.txt", "wb");
    fclose(pF);

    pF = fopen("user_Records.txt", "ab");
    pT = fopen("temporary.txt", "rb");

    while(fread(&user,sizeof(user),1,pT)==1)
    {
        fwrite(&user,sizeof(user),1,pF);
    }

    fclose(pF);
    fclose(pT);

    pT = fopen("temporary.txt", "wb");
    fclose(pT);

    userPanel();
}
void listUser(){
    
    system("cls");
    
    FILE *pF = fopen("user_Records.txt", "rb");
    int empty=1;

    printf("-------------------------------\n");
    printf(">>> List of Users Record <<< \n");
    printf("-------------------------------\n\n");
    
    while(fread(&user,sizeof(user),1,pF)==1){
        printf("-------------------------------\n");
        printf("> Full Name: %s \n", user.username);
        //printf("> Last Name: %s \n", lname); 
        printf("> Gender: %s \n", user.gender);
        printf("> Student-ID: %s \n", user.userId);
        printf("> Phone No.: %s \n", user.phone);
        printf("-------------------------------\n\n\n");
        empty=0; 
    }

    fclose(pF);

    if(empty)
    {
        printf("-------------------------------------\n");
        printf("There is no user records added yet...\n");
        printf("--------------------------------------\n\n");
    }

    printf("Press any key to get back to User Panel.\n");
    getch();
    book_menu();
}
int searchUser(){

label2:

    system("cls");

    int flag=0;
    //int compare;   
    char find[9];

    printf("Search by User ID of the student: ");
    scanf("%s", find);

    FILE *pF = fopen("user_Records.txt", "rb");

     while(fread(&user,sizeof(user),1,pF)==1)
    {
        //strcmp(variable, variable1) -- if both the strings are equal then it will return 0 otherwise a random number.
        //compare = strcmp(find, uid);

        if(!strcmp(find, user.userId))
        {

            printf("\n---------------------\n");
            printf(">>> Record Found <<< \n");
            printf("---------------------\n\n");

            printf("-------------------------------\n");
            printf("> Full Name: %s \n", user.username);
            printf("> Gender: %s \n", user.gender);
            printf("> Student-ID: %s \n", user.userId);
            printf("> Phone Number: %s \n", user.phone);
            printf("-------------------------------\n\n");
            flag=1;
        }
    }
    
    fclose(pF);

    if(flag == 0)
    {
        printf("\n>>> Record Not Found <<< \n\n");
    }
    
    printf("Press any key to redirect back to Panel.");
    getch();
    user_menu();
}
void deleteUser(char uid[]){

    system("cls");

    int flag=0;
    fflush(stdin);
    char find[9];
    strcpy(find,uid);
    FILE *pF = fopen("user_Records.txt", "rb");
    FILE *pT = fopen("temporary.txt", "ab");
    if(pF==NULL && pT ==NULL){
        printf("file cant open ");
    }

    while(fread(&user,sizeof(user),1,pF)==1)
    {

        if(strcmp(find, user.userId)==0)
        {
            printf("\n---------------------------------------------\n");
            printf(">>> Record Deleted <<<\n");
            printf("-----------------------------------------------\n\n");
            printf("Redirecting to User Panel...");


            flag = 1;
        }
        else
        {
            fwrite(&user,sizeof(user),1,pT);
        }
    }

    fclose(pF);
    fclose(pT);

    pF = fopen("user_Records.txt", "wb");
    fclose(pF);

    if(flag == 0)
    {
        printf("\n\n-------------------------------\n");
        printf(">>> Record Not Found <<<\n");
        printf("-------------------------------\n\n");
        printf("Redirecting to User Panel...");
    }

    pF = fopen("user_Records.txt", "ab");
    pT = fopen("temporary.txt", "rb");

    while(fread(&user,sizeof(user),1,pT)==1)
    {
        fwrite(&user,sizeof(user),1,pF);
    }

    fclose(pF);
    fclose(pT);

    pT = fopen("temporary.txt", "wb");
    fclose(pT);

    userPanel();
}
void book_menu(){
    int choice;
    system("cls");
    gotoxy(5,3);
    printf("\n---------------------------------------------\n");
    printf(">>> BOOK MENU <<<\n");
    printf("-----------------------------------------------\n");
    printf("\n-----------------------------\n");
    printf(" 1 : Add Books              \n");
    printf(" 2 : View Books             \n");
    printf(" 3 : List of User           \n");
    printf(" 4 : Issue Books            \n");
    printf(" 5 : Return Books           \n");
    printf(" 6 : Delete Books           \n");
    printf(" 7 : user information       \n");
    printf(" 8 : Add User               \n");
    printf(" 9 : menu                   \n");
    printf("-------------------------------\n");
    fflush(stdin);
    printf(">>Enter choice : ");
    scanf("%d",&choice);
    
    switch(choice){
        case 1: 
        add_book();
        break;
        case 2:
        view_books();
        break;
        case 3:
        listUser();
        break;
        case 4:
        issue_book();
        break;
        case 5:
        return_book();
        break;
        case 6:
        remove_book();
        break;
        case 7:
        user_search();
        break;
        case 8:
        addUser();
        break;
        case 9:
        menu();
        default:
        gotoxy(15,14);
        printf("Invalid Entry... \n");
    }
    
}
void add_book(){ 
    FILE *ptr; 
    char b[2]={0};
    char a ='y'; 

    struct library book; 
    ptr = fopen("book.txt","ab"); 

    if(ptr == NULL){ 
        printf("Error opening file"); 
        exit(1); 
    } 
    fflush(stdin);
    while( a == 'y'){
        printf("\n---------------------------------------------\n");
        printf(">>> ADD BOOK DATA <<<\n");
        printf("-----------------------------------------------\n\n");
        printf(">>>Book Name "); 
        gets(book.Book_Name); 
        printf(">>>Author Name "); 
        gets(book.Author_Name); 
        printf(">>>Publication year "); 
        gets(book.year_publication); 
        printf(">>>Book Number "); 
        gets(book.Book_Number); 
        printf(">>>Edition of Book "); 
        gets(book.edition); 
        printf(">>>category of Book "); 
        gets(book.category);
        printf(">>>price of Book "); 
        gets(book.price);
        printf(">>>rack no of Book "); 
        gets(book.rack);
        fwrite(&book,sizeof(struct library),1,ptr); 
        printf("Enter Y to continue or N to leave..... "); 
        scanf("%c",&a); 
             
    } 
    fclose(ptr);
    printf("Press any key to continue...."); 
    getch(); 
    book_menu(); 
}
void list_books(){
    FILE *fptr;
    //struct library lib;
    fptr=fopen("book.txt","rb");
    printf("\n---------------------------------------------\n");
    printf(">>> VIEW BOOK DATA <<<\n");
    printf("-----------------------------------------------\n\n");
    while(fread(&book,sizeof(struct library),1,fptr)==1){
        printf("\n-------------------------------------------\n\n");
        printf(">>book name %s \n",book.Book_Name);
        printf(">>auther name %s \n",book.Author_Name);
        printf(">>book published %s \n",book.year_publication);
        printf(">>book number %s \n",book.Book_Number); 
        printf(">>book edition %s \n",book.edition);
        printf(">>book price %s \n",book.price);
        printf(">>rack no %s \n",book.rack);
        printf("\n-------------------------------------------\n\n");
    }
    fclose(fptr);
    printf("press any key to continue....");
    getch();
    user_menu();
}
void search_book()
{
    system("cls");
    printf("\n---------------------------------------------\n");
    printf(">>> SEARCH BOOK DATA <<<\n");
    printf("-----------------------------------------------\n\n");
    printf("\n\n");
    printf("1. Search By ID");
    printf("\n\n");
    printf(" 2. Search By Name");
    printf("\n\n");
    printf("Enter Your Choice.....");
    fflush(stdin);
    switch(getch())
    {
        case '1':
            searchByID();
            break;
        break;
        case '2':
            searchByName();
            break;
        default :
            getch();
            search_book();
    }
}
void issue_book(){
    printf("\n---------------------------------------------\n");
    printf(">>> ISSUE BOOK <<<\n");
    printf("-----------------------------------------------\n\n");
    char bookid[10];
    char id_no[15];
    char name[50];
    int day=0,month=0,year=0;
    char date[6];
    struct library book;
    printf("Enter book number to be issued : ");
    fflush(stdin);
    gets(bookid);
    time_t current_time = time(NULL);
    time_t now;
    time(&now);
    struct tm *currentDate = localtime(&now);
    char date_string[20];
    strftime(date_string, 20, "%Y-%m-%d", localtime(&current_time));
    FILE *fptr;
    FILE *ptr;
    FILE *file;
    fptr=fopen("book.txt","rb+");
    file =fopen("issue.txt","ab");
    if(fptr==NULL && ptr == NULL){
        printf("Error in file opening ");
    }
    due_date(20,currentDate);
    day=currentDate->tm_mday;
    month=currentDate->tm_mon;
    year=currentDate->tm_year + 1900;
    strftime(date,20,"%Y-%m-%d",currentDate);
    free(currentDate);
    if(checkid(bookid)){
        printf("Enter user id : ");
        gets(id_no);
        while(fread(&book,sizeof(book),1,fptr)==1){
            if(strcmp(book.Book_Number,bookid)==0){
                strcpy(book.issue_to,id_no);
                strcpy(book.issue_date,date_string);
                strcpy(book.duedate,date);
                fwrite(&book,sizeof(struct library),1,file);
                printf("\n=============================================\n");
                printf(">>>>>>> book issued successfully <<<<<<<<<<\n"); 
                printf("\n=============================================\n");
                fclose(file);  
            }
            fflush(stdin);
        }
    }
    else{
        printf("book not available in library \n");
    }
    fclose(fptr);
    printf("press any key for continue.....");
    getch();
    fflush(stdin);
    book_menu();

}
void return_book(){
    printf("\n---------------------------------------------\n");
    printf(">>> RETURN BOOK <<<\n");
    printf("-----------------------------------------------\n\n");
    int found =0;
    char bookid[10];
    char uid1[12];
    fflush(stdin);
    printf("book number to be return : ");
    gets(bookid);
    printf("user id :");
    gets(uid1);
    printf("\n");
    FILE *fptr;
    fptr=fopen("issue.txt","rb");
    if(fptr==NULL){
        printf("Error in filr opening ");
    }

    while(fread(&book ,sizeof(book),1,fptr)==1){
        found=1;
        if(strcmp(book.Book_Number,bookid)==0){
            view_list(bookid,uid1);
            printf("\n===============================================\n");
            printf(">>>>>>>>>> book returned successfully <<<<<<<<<\n"); 
            printf("\n===============================================\n");  
        }
    }
    if(found==0){
        printf("Somthing went Wrong ...... \n ");
    }
    fclose(fptr);
    printf("Press any key to continue."); 
    getch(); 
    book_menu();   
 
}
void remove_book(){
    printf("\n---------------------------------------------\n");
    printf(">>> BOOK Record Delete <<<\n");
    printf("-----------------------------------------------\n\n");
    char bookid[100];
    fflush(stdin);
    printf("Enter name of book you want to delete ");
    gets(bookid);
    FILE *fptr;
    FILE *ptr;
    int found=0;

    struct library book;
    fptr=fopen("book.txt","rb");
    ptr=fopen("tem.txt","wb");
    if(fptr ==NULL && ptr==NULL){
        printf("Error in file opening  ");
    } 
	while (fread(&book,sizeof(struct library),1,fptr)==1){
		if (strcmp(book.Book_Name,bookid)==0){
            printf("\n====================================================\n");
			printf(" \n A Record with requested Name found and deleted.\n\n");
            printf("\n====================================================\n");
			found=1;
		} 
        else {
			fwrite(&book, sizeof(struct library), 1, ptr);
		}
	}
	if (found==0) {
		printf(" \n No record(s) found with the requested name of book : %s\n\n",bookid);
	}

	fclose(fptr);
	fclose(ptr);
    fptr = fopen("book.txt", "wb");
    fclose(fptr);
    fptr = fopen("book.txt", "ab");
    ptr = fopen("tem.txt", "rb");
    while(fread(&user,sizeof(user),1,ptr)==1){
        fwrite(&user,sizeof(user),1,fptr);
    }

    fclose(fptr);
    fclose(ptr);
    ptr= fopen("tem.txt", "wb");
    fclose(ptr);
    fflush(stdin);
    printf("press any key to continue.....");
    getch();
    book_menu();
}
void view_books(){
    FILE *fptr;
    //struct library lib;
    fptr=fopen("book.txt","rb");
    printf("\n---------------------------------------------\n");
    printf(">>> VIEW BOOK DATA <<<\n");
    printf("-----------------------------------------------\n\n");
    while(fread(&book,sizeof(struct library),1,fptr)==1){
        printf("\n-------------------------------------------\n\n");
        printf(">>book name %s \n",book.Book_Name);
        printf(">>auther name %s \n",book.Author_Name);
        printf(">>book published %s \n",book.year_publication);
        printf(">>book number %s \n",book.Book_Number); 
        printf(">>book edition %s \n",book.edition);
        printf(">>book price %s \n",book.price);
        printf(">>rack no %s \n",book.rack);
        printf("\n-------------------------------------------\n\n");
    }
    fclose(fptr);
    printf("press any key to continue....");
    getch();
    book_menu();
}
void user_search(){
    FILE *fptr;
    fptr=fopen("user_Records.txt","rb");
    if(fptr==NULL){
        printf(" Find Error in Open txt file");
    }
    else{
        fflush(stdin);
        char another='Y';
        char id_no[15];
        printf("Enter user id :");
        gets(id_no);
        struct user user;
        if(checkuser(id_no)){
        
            printf("\n>>-----user data available in library database------<<\n");
            while((fread(&user,sizeof(user),1,fptr))==1){
                printf("User Name :");
                printf(user.username);
                printf("\nUser ID : ");
                printf(user.userId);
                printf("\nUser Mobile No : ");
                printf(user.phone);
                printf("\n");                  
            
            }
        }
        else{
            getuserdata(id_no);
        }
        fclose(fptr);
        fflush(stdin);
        printf("press any key to continue ...");
        getch();
        book_menu();

    }
}
void getuserdata(char choice[]){
    char another ='Y';
    FILE *fptr;
    fptr=fopen("user_Records.txt","ab");
    strcpy(user.userId,choice);
    printf("Enter User Name : ");
    gets(user.username);
    printf("Enter User Mobile No : ");
    gets(user.phone);
    printf(" gender [M/F] : ");
    gets(user.gender);
    printf("Enter password : ");
    gets(user.Password);
    fwrite(&user,sizeof(user),1,fptr);
    fclose(fptr);
    fflush(stdin);
}
bool checkid(char t[]){
 //check whether the book is exist in library or not
    FILE *temp;
	temp = fopen("book.txt","rb+");
	while(fread(&book,sizeof(book),1,temp)==1)
        if(strcmp(book.Book_Number ,(t))==0){
            fclose(temp);
            return true;
        }
        fclose(temp);
        return false;

}

void searchByID(){
    printf("\n---------------------------------------------\n");
    printf(">>> SEARCH RECORD BY ID <<<\n");
    printf("-----------------------------------------------\n\n");
    system("cls");
    char id[10];
    FILE *fp;
    gotoxy(25,4);
    printf("*Search Books By Id*");
    gotoxy(20,5);
    printf("Enter the book id:");
    gets(id);
    int findBook = 0;
    fp = fopen("book.txt","rb+");
    while(fread(&book,sizeof(book),1,fp)==1){
        if(strcmp(book.Book_Number,(id))==0){
            Sleep(2); 
            gotoxy(20,7);
            printf("The Book is available");
            gotoxy(20,8);
            gotoxy(20,9);
    
            printf("\n--------------------------------------------------\n");
            printf(" ID: %s \n",book.Book_Number);
            printf(" Name: %s \n",book.Book_Name);
            printf(" Author: %s \n ", book.Author_Name);
            printf(" year of publication : %s \n ",book.year_publication);
            printf(" Price:Rs. %s \n",book.price);
            printf(" Rack No: %s \n",book.rack);
            printf("\n--------------------------------------------------\n");
            findBook = 1;
        }
    }
    if(findBook == 0){  //checks whether conditiion enters inside loop or not
        gotoxy(20,8);
        gotoxy(20,10);
        gotoxy(22,9);
        printf("\aNo Record Found");
    }
    fclose(fp);
    gotoxy(20,17);
    printf("Try another search?(Y/N)");
    if(getch()=='y')
        searchByID();
    else
        user_menu();
}

void searchByName(){
    printf("\n---------------------------------------------\n");
    printf(">>> SEARCH RECORD BY NAME <<<\n");
    printf("-----------------------------------------------\n\n");
    system("cls");
    char s[15];
    int d=0;
    FILE *fp;
    gotoxy(25,4);
    printf("*Search Books By Name*");
    gotoxy(20,5);
    fflush(stdin);
    printf("Enter Book Name:");
    gets(s);
    fp = fopen("book.txt","rb");
    while(fread(&book,sizeof(book),1,fp)==1){
        if(strcmp(book.Book_Name,(s))==0){ //checks whether book.name is equal to s or not
            printf("\n\n\n");
            printf("The Book is available");
            printf("\n-------------------------------------------------\n");
            printf(" ID: %s \n",book.Book_Number);
            printf(" Name: %s \n",book.Book_Name);
            printf(" Author: %s \n",book.Author_Name);
            printf(" year of publication : %s \n",book.year_publication );
            printf(" Price:Rs. %s \n",book.price);
            printf(" Rack No: %s \n",book.rack);
            printf("\n--------------------------------------------------\n");
            d++;
        }
    }
    if(d==0){
        gotoxy(20,8);
        gotoxy(20,9); gotoxy(38,9);
        gotoxy(20,10);
        gotoxy(22,9);printf("\aNo Record Found");
    }
    fclose(fp);
    gotoxy(20,17);
    printf("Try another search?(Y/N)");
    if(getch()=='y')
        searchByName();
    else
        user_menu();
}
void view_issueinfo(char uid[]){
    printf("\n---------------------------------------------\n");
    printf(">>> SHOW ISSUE INFORMATION <<<\n");
    printf("-----------------------------------------------\n\n");
    FILE *fptr;
    fptr =fopen("issue.txt","rb+");
    while(fread(&book,sizeof(struct library),1,fptr)==1){
        if(strcmp(book.issue_to,uid2)==0){
            printf("\n-----------------------------------------\n\n");
            printf("book name %s \n",book.Book_Name);
            printf("book number %s \n",book.Book_Number);
            printf("author name %s \n",book.Author_Name);
            printf("user Id  %s \n",book.issue_to);
            printf("issue date %s \n",book.issue_date);
            printf("due date %s \n",book.duedate);
            printf("issued %s \n",book.issued); 
            printf("\n------------------------------------------\n\n");
        }
    }
    fclose(fptr);
    fflush(stdin);
    printf("press any key to continue......");
    getch();
    user_menu();
}
bool checkuser(char t[]){
    FILE *temp;
	temp = fopen("user_Records.txt","rb");
	while(fread(&user,sizeof(user),1,temp)==1)
        if(strcmp(user.userId ,(t))==0){
            fclose(temp);
            return true;
        }
        fclose(temp);
        return false;

}
void due_date(int days, struct tm *date){
    time_t time = mktime(date); // Convert struct tm to time_t
    time += days * 24 * 60 * 60; // Add 'days' seconds to current time
    *date = *localtime(&time); // Convert time_t back to struct tm
}
void view_list(char bookid[],char uid1[]){
    FILE *fptr;
    FILE *ptr;
    int found=0;
    struct library book;
    fptr=fopen("issue.txt","rb");
    ptr=fopen("temp.txt","wb");
    if(fptr==NULL && ptr == NULL){
        printf("error in file opening");
    }
	while (fread(&book,sizeof(struct library),1,fptr)==1){
		if ((strcmp(book.Book_Number,bookid)==0) && (strcmp(book.issue_to,uid1)==0)){
			found=1;
		} 
        else {
			fwrite(&book, sizeof(struct library), 1, ptr);
		}
	}
	fclose(fptr);
	fclose(ptr);
    fptr = fopen("issue.txt", "wb");
    fclose(fptr);
    fptr = fopen("issue.txt", "ab");
    ptr = fopen("temp.txt", "rb");
    while(fread(&user,sizeof(user),1,ptr)==1){
        fwrite(&user,sizeof(user),1,fptr);
    }

    fclose(fptr);
    fclose(ptr);
    ptr= fopen("temp.txt", "wb");
    fclose(ptr);
    fflush(stdin);
}
void gotoxy(int x, int y) {
    COORD c;
    c.X = x;
    c.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}