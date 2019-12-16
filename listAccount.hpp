//
//  listAccount.hpp
//  Targilratouv2
//
//  Created by Nathan Benamou on 16/12/2019.
//  Copyright © 2019 Nathan Benamou. All rights reserved.
//

#ifndef listAccount_hpp
#define listAccount_hpp

#include <stdio.h>
#include <vector>
using namespace std;
#include "Protection.hpp"
#include "Account.hpp"


class ListAccount
{
public:
   //// ListAccount(); //i think that vector initializes itself, and "protection" has a no parameter builder so the default builder is enough
    ~ListAccount();
    int addAccount(int id,int password,int balance);
    Account* findAccount(int id);
    unsigned long sizeList();
    Account* getAccount(int i);
    void readLockAccount();
    void readUnlockAccount();
    void writeLockAccount();
    void writeUnlockAccount();
private:
    vector<Account*> listOfAccount;
    Protection ReaderWriter;
};
#endif /* listAccount_hpp */
