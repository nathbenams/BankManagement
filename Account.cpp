//
//  Account.cpp
//  Targilratouv2
//
//  Created by Nathan Benamou on 14/12/2019.
//  Copyright © 2019 Nathan Benamou. All rights reserved.
//

#include "Account.hpp"

Account:: Account(int id, const char* password, int balance){////// i assume that all the validation of the input was done before calling this function
	accountID = id;
    
    accountPassword = new char[strlen(password)]; 
    strcpy(accountPassword, password);
    accountBalance = balance;
    accountReaderWriter = Protection();
}

Account:: ~Account(){
    if(accountPassword!= NULL) delete accountPassword;
}

int Account:: getID(){
	return(accountID);
}


char* Account:: getPassword(){
	return(accountPassword);
}

int Account:: getBalance(){
	return(accountBalance);
}
//********************************************
// function name: takeMoney
// Description: remove the amount off the account's balance
// Parameters: amount to remove
// Returns: true if success, false if the account's balance smaller than the amount
//********************************************
bool Account:: takeMoney(int amount){
	if (accountBalance < amount)
		return false;
	accountBalance-=amount;
	return true;
}
//********************************************
// function name: addMoney
// Description: add the amount to the account's balance
// Parameters: amount to add
// Returns:
//********************************************
void Account:: addMoney(int amount){////// assumes that amount is not negitive
		accountBalance+=amount;
}
//********************************************
// function name: readLockAccount
// Description: lock the reader's locker of the account
// Parameters:
// Returns:
//********************************************
void Account::readLockAccount(){
	accountReaderWriter.enterReader();
}
//********************************************
// function name: readUnlockAccount
// Description: Unlock the account reader's locker
// Parameters:
// Returns:
//********************************************
void Account::readUnlockAccount(){
	accountReaderWriter.leaveReader();
}
//********************************************
// function name: writeLockAccount
// Description: Lock the account writer's locker
// Parameters:
// Returns:
//********************************************
void Account::writeLockAccount(){
	accountReaderWriter.enterWriter();
}
//********************************************
// function name: writeUnlockAccount
// Description: unlock the writer's locker of the account
// Parameters:
// Returns:
//********************************************
void Account::writeUnlockAccount(){
	accountReaderWriter.leaveWriter();
}
