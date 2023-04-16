#ifndef __BEER_CALCULATOR_H
#define __BEER_CALCULATOR_H

#include <stdbool.h>

typedef struct {
    char accountNo[20];   
    float belopp;
}Account;

typedef enum {
    Withdraw_Status_Ok,
    Withdraw_Status_No_Such_Account,
    Withdraw_Status_Negative_Amount,
    Withdraw_Status_Not_Enough_Balance,
    Withdraw_Status_Too_Much_Amount
} Withdraw_Status;

typedef enum {
    Deposit_Status_Ok,
    Deposit_Status_No_Such_Account,
    Deposit_Status_Negative_Amount,
} Deposit_Status;

// -1,0,+1
// int strcmp


void atmMenu();
void atmInit();
Account *atmFindAccount(const char *accountNo);
bool atmAddAccount(const char *accountNo, float saldo);
Withdraw_Status atmWithdraw(const char *accountNo, float amount);
Deposit_Status atmDeposit(const char *accountNo, float amount);
#endif