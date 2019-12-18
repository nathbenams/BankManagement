//
//  Account.hpp
//  Targilratouv2
//
//  Created by Nathan Benamou on 14/12/2019.
//  Copyright © 2019 Nathan Benamou. All rights reserved.
//

#ifndef Account_hpp
#define Account_hpp

#include <stdio.h>
#include "Protection.hpp"

class Account
{
public:
    Account(int id, char* password, int balance);
    ~Account();
    int getID();
    char* getPassword();
    int getBalance();
    bool takeMoney(int amount);
    void addMoney(int amount);
    void readLockAccount();
    void readUnlockAccount();
	void writeLockAccount();
    void writeUnlockAccount();
    
private:
    int accountID;
    char* accountPassword;
    int accountBalance;
    Protection accountReaderWriter;
};

#endif /* Account_hpp */
