//
//  main.cpp
//  Targilratouv2
//
//  Created by Nathan Benamou on 14/12/2019.
//  Copyright © 2019 Nathan Benamou. All rights reserved.
//

#include <iostream>
#include <pthread.h>
#include <vector>
using namespace std;
#include "Bank.hpp"
#include "Caspomat.hpp"
#include "Account.hpp"
#include "listAccount.hpp"
#define BANK 0000

FILE* log;
ListAccount listOfAccount;
bool active;
Account* bankAccount;

int main(int argc, const char * argv[]) {
    
    listOfAccount = ListAccount();
    Account _bankAccount = Account(BANK,BANK,0);
    bankAccount = &_bankAccount;
    active = true;
    log=fopen("log.txt","w");
    if(log==nullptr){
        perror("");
        exit(1);
    }
    
    pthread_t bankStatus,bankTakeCommission;
    
    pthread_create(&bankStatus, NULL,  *(*bankPrint), NULL);
    pthread_create(&bankTakeCommission, NULL, *(*bankCommission),NULL);
    
    int numberOfCaspomat = atoi(argv[1]);
    
    vector<Caspomat> listOfCaspomat;
    pthread_t listThread[numberOfCaspomat];
    
    for(int i=0; i<numberOfCaspomat;i++){
        listOfCaspomat.push_back(Caspomat(i+1,argv[i+2]));
        pthread_create(&listThread[i],NULL,&Caspomat::execute_helper, &listOfCaspomat.at(i));
        
    }
    
    for(int i=0;i<numberOfCaspomat;i++){
        pthread_join(listThread[i], NULL);
    }
    
    active = false;
    
    pthread_join(bankStatus, NULL);
    pthread_join(bankTakeCommission,NULL);
    
    //pthread_join of the banks
    fclose(log);
    return 0;
}
