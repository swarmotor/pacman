#include "head.h"
void mainmenu()
{
    char option,sign;
    printf("                                      Pacman\n");
    printf("--------------------------------------------------------------------------------");
    printf("1. New games .\n");
    printf("2. Create new map .\n");
    printf("3. High score .\n");
    printf("4. Exit game .\n");
    do
    {
        printf("Please enter the serial number: ");
        fflush(stdin);
        scanf("%1c",&option);
        fflush(stdin);
        if(option<'1'||option>'4'){
            printf("Error! Do you want finish the program ?\n");
            printf("Please enter the Y or N : ");
            scanf("%c",&sign);
            if(toupper(sign)!='N')
                exit(0);
        }
    }while(option<'1'||option>'4');
    fflush(stdin);
    switch(option)
    {
        case '1' : New_game();       break;
        case '2' : Producenew_map(); break;
        case '3' : High_score();     break;
        case '4' : exit(0);          break;
    }
    mainmenu();
}