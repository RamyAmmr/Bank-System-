/* header Guard File*/
#ifndef BANK_FUNCTIONS_H
#define BANK_FUNCTIONS_H

#include "STD_TYPES.h"

void createNewAccount(BankAccount **account);
void deleteAccount(BankAccount *account);
void adminTransaction(Window *Admin);
void clientTransactions(Window *client);
void changeAccountStatus(Window *Admin);
void AdminCash(Window *Admin);
void clientCash(Window *client);
void AdminDeposit(Window*Admin);
void clientDeposit(Window *client);
void clientAccount(Window *client);
void ChangePassword(Window *client);
u32 exitSystem();

#endif 