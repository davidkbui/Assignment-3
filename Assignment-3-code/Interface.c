/*******************************************************************************
 * Interface - David Bui
*******************************************************************************/

/*******************************************************************************
 * This prints the school logo.
*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void print_logo(void){
  printf("_______________________________________"
"\n|            _ _.-^-._ _               |"
"\n|            ;.'________'.;            |"
"\n|_________n.[____________].n_________  |"
"\n||::_::_::_::||==||==||==||::_::_::_::]|"
"\n||:::::::::::||..||..||..||:::::::::::||"
"\n||=|= =|= =|=||==||==||==||=|= =|= =|=||"
"\n||.. .. .. ..||..||..||..||.. .. .. ..||"
"\n||** - **||::|LI=| __ |=LI|** - **||::||"
"\n|______________________________________|"
"\n           **UTS UNIFORM SHOP**"
"\n     -------------------------------\n");
}

/*******************************************************************************
 * This prints the inital welcome prompt.
*******************************************************************************/
void print_bold_magenta(){
  printf("\033[1;35m");
}

/*******************************************************************************
 * This prints the inital welcome prompt.
*******************************************************************************/
void print_magenta(){
  printf("\033[0;35m");
}

/*******************************************************************************
 * This prints the inital welcome prompt.
*******************************************************************************/
void print_reset_color(){
  printf("\033[0m");
}

/*******************************************************************************
 * This prints the inital welcome prompt.
*******************************************************************************/
void intro_prompt(void){
    print_bold_magenta();
    print_logo();
    printf("\n"
    "Welcome to UTS uniform order page\n"
    "1. Student\n"
    "2. Admin\n"
    "3. Exit\n"
    "Enter choice 1 - 3>\n");
    print_reset_color();
}

/*******************************************************************************
 * Function Description
*******************************************************************************/
int getChoice(){
  int choice = 0;

  if (scanf("%d", &choice) == 1)                         /*if input is scanned*/
  {
    if(choice < 1 || choice > 3) {
      printf("Invalid choice\n");
      return -1;
    }

    else {
      return choice;                                      /*1-6 returns choice*/
    }
  }
  else return -1;                                   /*Logic for resetting main*/
}

int matchID(char ID[10]) {
  int i, x=0, validFlag, p;
  p = strlen(ID);
  for (i=0; i<p; i++)
    {
      if (ID[i] >= '0' && ID[i] <= '9')
        {
          validFlag = 1;
        }
      else {
            printf("Invalid ID, try again\n");
            scanf("%s", ID);
            validFlag = 0;
      }
    }
  return validFlag;
  }

void adminMenu (void) {
  char ID[10];
  printf(
    "Admin Menu\n"
    "Type in your ID\n");
    scanf("%s", &ID[10]);
    int isValidFlag = matchID(ID);
    while (isValidFlag == 0)
      {
        printf("Invalid ID\n");
          printf("%d", isValidFlag);
        scanf("%s", &ID[10]);
      }
}

void studentMenu (void) {
  printf("User Menu");
}

void inputCases (int input)
{
    switch(input) {                                   /*choose function to run*/
      case 1: studentMenu(); break;
      case 2: adminMenu(); break;
      case 3: exit(0); break;
    }
}
