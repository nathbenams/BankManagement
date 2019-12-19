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
    ///// do i need to initiaize the lock to be open??YES
}

////// we assume that lock and unlock are done from outside the module!!! ////
//////////////////////////////////////////////////////////////////////////////////
Account:: ~Account(){
    if(accountPassword!= NULL) delete accountPassword;
	//while(pthread_mutex_destroy(&accountReaderWriter));///// if this function success, it returns 0 then i put it in a while
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

bool Account:: takeMoney(int amount){
	if (accountBalance < amount)
		return false;
	accountBalance-=amount;
	return true;
}

void Account:: addMoney(int amount){////// assumes that amount is not negitive
		accountBalance+=amount;
}

void Account::readLockAccount(){
	accountReaderWriter.enterReader();
}
void Account::readUnlockAccount(){
	accountReaderWriter.leaveReader();
}
void Account::writeLockAccount(){
	accountReaderWriter.enterWriter();
}

void Account::writeUnlockAccount(){
	accountReaderWriter.leaveWriter();
}
