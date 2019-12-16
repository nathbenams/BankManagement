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
    
    
private:
    int accountID;
    int accountPassword;
    int accountBalance;
    Protection accountReaderWriter;
};

#endif /* Account_hpp */
