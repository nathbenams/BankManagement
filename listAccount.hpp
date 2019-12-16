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
    ListAccount();
    ~ListAccount();
    int addAccount(int id,int password,int balance);
    Account findAccount(int id);
    unsigned long sizeList();
    Account getAccount(int i);
private:
    vector<Account*> listOfAccount;
    Protection ReaderWriter;
};
#endif /* listAccount_hpp */
