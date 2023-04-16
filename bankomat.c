#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "bankomat.h"


typedef struct {
    Account *accounts;
    int count;
}AccountsDB;

AccountsDB accountsDb;

int randomBetween(int min, int max){
    return (rand() %
        (max - min + 1)) + min;    
}

void atmInit(){
    time_t t;
    srand((unsigned) time(&t));
    accountsDb.count = 10;
    accountsDb.accounts = malloc(accountsDb.count * sizeof(Account));
    for(int i = 0; i < accountsDb.count; i++){
        accountsDb.accounts[i].belopp = rand() % 10000;
        sprintf(accountsDb.accounts[i].accountNo,"%d-%d-%d", 
                                randomBetween(100,999),
                                randomBetween(1000,9999), 
                                randomBetween(1000,9999));
    }
}


void atmPrintAllAccounts(){
    printf("All accounts\n**************************\n");
    for(int i = 0; i < accountsDb.count;i++){
        printf("%s   %.2f\n", accountsDb.accounts[i].accountNo, accountsDb.accounts[i].belopp);
    }

}

Account *atmFindAccount(const char *accountNo){
    for(int i = 0; i < accountsDb.count;i++)
        if(strcmp(accountNo,accountsDb.accounts[i].accountNo ) == 0)
            return &accountsDb.accounts[i];
    return NULL;
}




Withdraw_Status atmWithdraw(const char *accountNo, float amount){
    Account *acc = atmFindAccount(accountNo);

    if(acc == NULL) return Withdraw_Status_No_Such_Account;

    if(amount > 3000) return Withdraw_Status_Too_Much_Amount;

    if(amount < 0) return Withdraw_Status_Negative_Amount;

    if(amount > acc->belopp) return Withdraw_Status_Not_Enough_Balance;
    acc->belopp -= amount;
    return Withdraw_Status_Ok;
}

Deposit_Status atmDeposit(const char *accountNo, float amount){
    Account *acc = atmFindAccount(accountNo);
    if(acc == NULL) return Deposit_Status_No_Such_Account;

    if(amount < 0) return Deposit_Status_Negative_Amount;

    acc->belopp += amount;
    return Deposit_Status_Ok;
}

bool atmAddAccount(const char *accountNo, float saldo){
    if(atmFindAccount(accountNo) != NULL) return false;

    accountsDb.count++;
    accountsDb.accounts = realloc(accountsDb.accounts, accountsDb.count*sizeof(Account));
    strcpy(accountsDb.accounts[accountsDb.count-1].accountNo,accountNo);
    accountsDb.accounts[accountsDb.count-1].belopp = saldo;
    return true;

}

void atmMenu(){
    while(1){
        printf("The ATM machine\n********************\n");
        printf("1. Create account\n");
        printf("2. List accounts\n");
        printf("3. Withdraw\n");
        printf("4. Deposit\n");
        printf("Enter action:");
        int action;
        scanf(" %d", &action);
        if(action == 1){
            char accountNo[100];
            printf("Enter your account no:");
            scanf(" %s", accountNo);
            if(atmAddAccount(accountNo,0)){
                printf("Account created\n");
                continue;
            }
            printf("Account already existing?\n");
        }
        if(action == 2){
            atmPrintAllAccounts();                
        }
        if(action == 3 || action == 4){
            char accountNo[100];
            printf("Enter your account no:");
            scanf(" %s", accountNo);
            if(atmFindAccount(accountNo) == NULL){
                printf("No such account?");
                continue;
            }
            printf("Enter amount:");
            float amount;
            scanf(" %f", &amount);

            if(action == 4){
                Deposit_Status status= atmDeposit(accountNo,amount);
                if(status != Deposit_Status_Ok){
                    printf("Ngt gick fel");
                }
            }
            else if(action == 3){
                Withdraw_Status status= atmWithdraw(accountNo,amount);
                if(status != Withdraw_Status_Ok){
                    printf("Ngt gick fel");
                }
            }


        }


    }
}