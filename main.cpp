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

FILE* log;
ListAccount listOfAccount;
bool active;

int main(int argc, const char * argv[]) {
    
    listOfAccount = ListAccount();
    
    log=fopen("log.txt","w");
    if(log==nullptr){
        perror("");
        exit(1);
    }
    
    pthread_t bankStatus,bankCommission;
    //Create the fonction of bankstatus and bankcommission in bank.cpp
    //and add pthread_create for them
    pthread_create(&bankStatus, NULL,  *(*bankPrint), NULL);
    
    int numberOfCaspomat = atoi(argv[1]);
    vector<Caspomat> listOfCaspomat;
    vector<pthread_t> listOfThreadCaspomat;
    
    for(int i=0; i<numberOfCaspomat;i++){
        // listofcaspomat.pushback(information of him and its file from argv)
        //pthread_create with its function to execute
    }
    
    for(int i=0;i<numberOfCaspomat;i++){
        pthread_join(listOfThreadCaspomat.at(i), NULL);
    }
    
    //pthread_join of the banks
    fclose(log);
    return 0;
}
