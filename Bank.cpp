//
//  Bank.cpp
//  Targilratouv2
//
//  Created by Nathan Benamou on 14/12/2019.
//  Copyright © 2019 Nathan Benamou. All rights reserved.
//

#include "Bank.hpp"


extern bool active;
extern ListAccount listOfAccount;
extern Account* bankAccount;
extern FILE* log;

void* bankPrint(void *arg){
    
    while(active){
        usleep(HALFSECOND);
        printf("\033[2J");
        printf("\033[1;1H");
        printf("Current Bank Status\n");
        listOfAccount.readLockAccount();
        for(unsigned long i=0;i<listOfAccount.sizeList();i++){
            listOfAccount.getAccount(i)->readLockAccount();
        }
        
        for(unsigned long i=0;i<listOfAccount.sizeList();i++){
            printf("Account %d: Balance – %d $ , Account Password – %d\n",listOfAccount.getAccount(i)->getID(),listOfAccount.getAccount(i)->getBalance(),listOfAccount.getAccount(i)->getPassword());
        }
//        printf("The Bank has %d $",............) TO FILL
        
        for(unsigned long i=0;i<listOfAccount.sizeList();i++){
            listOfAccount.getAccount(i)->readUnlockAccount();
        }
        listOfAccount.readUnlockAccount();
        

    }
    
    
    return NULL;
}

void* bankCommission(void* arg){
    
    while (active) {
        
        sleep(3);
        int commission = rand()%INTERVAL + INTERVAL;
        listOfAccount.readLockAccount();
        for(unsigned long i=0;i<listOfAccount.sizeList();i++){
            listOfAccount.getAccount(i)->writeLockAccount();
        }
        int commissionAccount;
        Account* accountTmp;
        for(unsigned long i=0;i<listOfAccount.sizeList();i++){
            
            accountTmp = listOfAccount.getAccount(i);
            
            commissionAccount = (int)(accountTmp->getBalance() *(commission/100));
            
            bankAccount->writeLockAccount();
            
            bankAccount->addMoney(commissionAccount);
            accountTmp->takeMoney(commissionAccount);
            
            fprintf(log, "Bank: commissions of %d%% were charged, the bank gained %d $ from account %d\n"
            , commission, commissionAccount, accountTmp->getID());
            
            bankAccount->writeUnlockAccount();
            accountTmp->writeUnlockAccount();
            
        }
        
        listOfAccount.readUnlockAccount();
        
        
    }
    
    
    return NULL;
}
