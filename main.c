#include <stdio.h>
#include "bankomat.h"

int mainmenu(){
    atmInit();
    while(1){
        printf("1. ATM\n2.Exit\nSelect:");
        int sel;
        scanf(" %d", &sel);
        if(sel >= 1 || sel <=3 ) 
            return sel;
   }
}



int main(){
    while(1){
        int sel = mainmenu();
        if(sel == 2)
            break;
        if(sel == 1) atmMenu();
    }
    return 0;
}