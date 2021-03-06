#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


#define MAX_NO_ITEMS 9
#define MAX_NO_FIRSTNAME 20
#define MAX_NO_LASTNAME 20
#define MAX_NO_FULLNAME 40
#define MAX_NO_CARDNUMBER 20
#define MAX_NO_STUDENT_ID 8
#define MAX_NO_USERS 5
#define MAX_NO_PASSWORD 10
#define MAX_NO_ITEM_NAME 10
#define STUDENT_DB_NAME "students"
#define TRANSACTION_DB_NAME "transactions"

/*Insert structs here*/
struct payment{
    char student_id[MAX_NO_STUDENT_ID];
    int card_number;
    char cardholder[MAX_NO_FULLNAME];
    int expiry;
    int CVC;
};
typedef struct payment payment_t;
//changing
struct date{
    int day;
    int month;
    int year;
};
typedef struct date date_t;

struct user{
    char first_name[MAX_NO_FIRSTNAME];
    char last_name[MAX_NO_LASTNAME];
    char user_id[MAX_NO_STUDENT_ID + 1];
    date_t birthdate;
    char password[MAX_NO_PASSWORD];
    int payment_valid;
    int is_admin;
};

typedef struct user user_t;

typedef struct admin admin_t;

struct transaction{
    int student_id;
    int transaction_id;
    date_t transaction_date;
};
typedef struct trasaction trasaction_t;

struct item{
    int item_id;
    char item_name[MAX_NO_ITEM_NAME];
    double item_price; 
    char item_size;
};
typedef struct item item_t;


/*functions*/
void load_items(item_t *items);
void login(user_t *users);
void menu();
void search();
void edit();
void print();
void add();
void intro_prompt();
void register_user();
int load_user(user_t *users_p);
void open_user_console(user_t user);
int main (void)
{
    item_t items[MAX_NO_ITEMS];
    load_items(items);
    user_t users[MAX_NO_USERS];
    load_user(users);
    
    /*int variable that would store user input for menu*/
    int choice;

    /*menu would loop unless user enters 3 */
    while(choice != 3){ 
        intro_prompt();    /* print login prompt */
        if(scanf("%d", &choice) != 1){     /* if user input is NOT digit */    
            while ((getchar()) != '\n');      /* flush input buffer */
            printf("Invalid choice \n");      /* prints error message */
        } else {     /* if user input is digit */
            switch(choice){
                case 1: 
                    login(users);
                    break;
                case 2: 
                    register_user();
                    break;
                case 3:
                    break;
                default:      /* when user input is digit but not 1-5 */
                    printf("Invalid choice \n"); 
                    break;
            }    
        }
    }
    
    return 0;
}

void load_items(item_t *items){
    /*draft items
     *TBU later
    */
    item_t item;
    item.item_id = 0; 
    strcpy(item.item_name, "Shirt");
    item.item_price = 20.0;
    item.item_size = 'L';
    items[0] = item;
    item.item_id = 0; 
    strcpy(item.item_name, "Shirt");
    item.item_price = 20.0;
    item.item_size = 'M';
    items[1] = item;
    item.item_id = 0; 
    strcpy(item.item_name, "Shirt");
    item.item_price = 20.0;
    item.item_size = 'S';
    items[2] = item;
}


void intro_prompt(){
    printf("\n"
    "Welcome to UTS uniform order page\n"
    "1. Existing user\n"
    "2. New user\n"
    "3. Exit\n"
    "Enter choice 1 - 3>\n");
}

/*Insert function protoypes here*/
void login(user_t *users) {
    char login_id[MAX_NO_STUDENT_ID]; 
    char password[MAX_NO_PASSWORD];
    int existing_user = 1;
    int i ;
    user_t user;

    while(existing_user){
        printf("Enter your id \n");
        scanf("%s", login_id); 
        for(i = 0; i < MAX_NO_USERS; i++){
            if(!strcmp(login_id, users[i].user_id)){
                user = users[i];
                existing_user = 0; 
            } 
        }
        if(user.user_id == '\0') {
            printf("Invalid user! \n");
        }
    }
    int right_password = 1;
    while(right_password){
        printf("Enter your password \n");
        scanf("%s", password); 
        if(!strcmp(password, user.password)){
            printf("Welcome, %s \n", user.first_name);
            open_user_console(user);
            right_password = 0;
        } else {
            printf("Invalid password. Please check again! \n");
        }
    }

}


void open_user_prompt(){
    printf("\n"
    "Welcome to UTS uniform order page\n"
    "1. Order uniform\n"
    "2. View your transaction\n"
    "3. Update my payment details\n"
    "4. Exit\n"
    "Enter choice 1 - 4>\n");
}

void open_admin_prompt(){
    printf("\n"
    "Hello, You are in administration mode\n"
    "1. View all transactions\n"
    "2. Search for trasactions\n"
    "3. Search for student\n"
    "4. Exit\n"
    "Enter choice 1 - 4>\n");
}


void open_user_console(user_t user){
    if(!user.is_admin) {

        open_user_prompt();
    } else {
        open_admin_prompt();
    }
}


void register_user(){

}

int save_db(const user_t *users_p){
     /* Pointer to the file */
    FILE *fp;

     /* Opening a file in w mode*/
    fp = fopen(STUDENT_DB_NAME, "w");

    /* If there is issue opening file, print error message and finish */
    if(fp == NULL){
        printf("Write error\n");
        return 1;
    } 

    /* int variable for for loop */
    int i;

    /* loop the number of flights and write to file in certain format, 
        changing line with each flight  */
    for(i = 0; i < MAX_NO_USERS; i++){
        fprintf(fp, "%s %s %s %d %d %d %s %d %d",
               users_p[i].first_name, users_p[i].last_name, users_p[i].user_id,
               users_p[i].birthdate.day, 
               users_p[i].birthdate.month, users_p[i].birthdate.year, 
               users_p[i].password, 
               users_p[i].payment_valid, users_p[i].is_admin);
    }

    /* close file */
    fclose(fp);
    return 0;
}

int load_user(user_t *users_p){
     /* Pointer to the file */
    FILE *fp;

     /* Opening a file in r mode */
    fp = fopen(STUDENT_DB_NAME, "r");

    /* If fp is NULL, print error message and finish */ 
    if(fp == NULL){
        printf("Students not loaded. Is database in right folder? \n");
        return 1;
    } 

    /* variable for while loop */
    int i = 0;

    /* while incrementing i is not equal to no_of_lines which 
        stores the number of new lines (=flights) in text file,
        read from file and store that into flights array */
    while(i != MAX_NO_USERS){
        fscanf(fp, "%s %s %s %d %d %d %s %d %d",
               users_p[i].first_name, users_p[i].last_name, users_p[i].user_id,
               &users_p[i].birthdate.day, 
               &users_p[i].birthdate.month, &users_p[i].birthdate.year, 
               users_p[i].password, 
               &users_p[i].payment_valid, &users_p[i].is_admin);
        i++;
    }
    /* close file */
    fclose(fp);
    return 0;
}

int is_admin (int ID) {
    return 0;
}

void menu() {
    printf("1. ");
}

void search();

void edit();

void print();

void add ();
