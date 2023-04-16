#include <stdio.h>
#include "bankomat.h"

// 1. Genomgång koden - bra = Uppdelat och INTE ui/printf/scanf i "affärslogiken"
// 2. Vi installerar google test
// 3. Vi skriver lite enhets-tester

int mainmenu(){
    while(1){
        printf("1.ATM\n2.Exit\nSelect:");
        int sel;
        scanf(" %d", &sel);
        if(sel >= 1 || sel <=3 ) 
            return sel;
   }
}



int main(){
    atmInit();
    while(1){
        int sel = mainmenu();
        if(sel == 2)
            break;
        if(sel == 1) atmMenu();
    }
    return 0;
}