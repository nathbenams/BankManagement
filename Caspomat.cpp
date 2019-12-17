//
//  Caspomat.cpp
//  Targilratouv2
//
//  Created by Nathan Benamou on 14/12/2019.
//  Copyright © 2019 Nathan Benamou. All rights reserved.
//

#include "Caspomat.hpp"

extern FILE* log;
extern ListAccount listOfAccount;

Caspomat::Caspomat(int id,char* nameFile) : caspomatID(id),caspomatFile(nullptr),fileOpened(false)
{
    caspomatFile= fopen(nameFile,"r");
    if(!caspomatFile){
        perror("");
        exit(1);
    }
    fileOpened=true;
}

Caspomat::~Caspomat()
{
    if (fileOpened) {
        fclose(caspomatFile);
    }
}

void Caspomat::executeCommandCaspomat()
{
    char cmd[MAX_LINE_SIZE];
    char* command;
    char* args[MAX_ARG];
    const char* delimiters = " ";
    int num_arg = 0;
    Account* accountTmp;
    Account* accountTmpReceiver;
    usleep(100000);
    while(fgets(cmd, MAX_LINE_SIZE,caspomatFile) != nullptr){
        command = strtok(cmd,delimiters);
    
        if(command==nullptr) break;
        int accountID;
        char* accountPassword;
        for(int i = 0;i<MAX_ARG;i++){
            args[i]=strtok(nullptr,delimiters);
            if(args[i]!=nullptr){
                num_arg++;
            }
        }
        accountID = atoi(args[0]);
        accountPassword = args[1];
        int amount,accountReceiverID;
        
        if (!strcmp(command,"O")) {
            amount=atoi(args[2]);
            listOfAccount.writeLockAccount();
            if(!listOfAccount.addAccount(accountID,accountPassword, amount)){
                fprintf(log, "%d: New account id is %d with password %s and initial balance %d\n", caspomatID, accountID, accountPassword, amount);
            }
            else{
                fprintf(log, "Error %d: Your transaction failed - account with the same id exist\n", caspomatID);
            }
            sleep(1);
            listOfAccount.writeUnlockAccount();
            continue;
        }
        
        
        else if(!strcmp(command,"D")){
            
            accountTmp = listOfAccount.findAccount(accountID);
            if (accountTmp == NULL) {
            fprintf(log,"Error %d: Your transaction failed - account id %d does not exist\n",caspomatID, accountID );
            }
            else if(strcmp(accountTmp->getPassword(),accountPassword)){
               fprintf(log, "Error %d: Your transaction failed - password for account id %d is incorrect\n", caspomatID, accountID);
            }
            else{
                amount = atoi(args[2]);
                accountTmp->writeLockAccount();
                accountTmp->addMoney(amount);
                fprintf(log, "%d: Account %d new balance is %d after %d $ was deposited\n", caspomatID, accountID, accountTmp->getBalance(),amount);
                sleep(1);
                accountTmp->writeUnlockAccount();
            }
            continue;
        }
        
        
        else if(!strcmp(command,"W")){
            accountTmp = listOfAccount.findAccount(accountID);
            if (accountTmp == NULL) {
            fprintf(log,"Error %d: Your transaction failed - account id %d does not exist\n",caspomatID, accountID );
            }
            else if(strcmp(accountTmp->getPassword(),accountPassword)){
               fprintf(log, "Error %d: Your transaction failed - password for account id %d is incorrect\n", caspomatID, accountID);
            }
            else{
                amount = atoi(args[2]);
                accountTmp->writeLockAccount();
                if(accountTmp->takeMoney(amount)){
                    fprintf(log, "%d: Account %d new balance is %d after %d $ was withdrew\n", caspomatID, accountID, accountTmp->getBalance(), amount);
                }
                else{
                    fprintf(log, "Error %d: Your transaction failed - account id %d balance is lower than %d\n", caspomatID, accountID, amount);
                }
                sleep(1);
                accountTmp->writeUnlockAccount();
            }
            continue;
        }
        
        
        else if(!strcmp(command,"B")){
            accountTmp = listOfAccount.findAccount(accountID);
            if (accountTmp == NULL) {
            fprintf(log,"Error %d: Your transaction failed - account id %d does not exist\n",caspomatID, accountID );
            }
            else if(strcmp(accountTmp->getPassword(),accountPassword)){
               fprintf(log, "Error %d: Your transaction failed - password for account id %d is incorrect\n", caspomatID, accountID);
            }
            else{
                accountTmp->readLockAccount();
                fprintf(log, "%d: Account %d balance is %d\n", caspomatID, accountID, accountTmp->getBalance());
                sleep(1);
                accountTmp->readUnlockAccount();
            }
            continue;
        }
        
        
        else if(!strcmp(command,"T")){
            accountReceiverID = atoi(args[2]);
            amount = atoi(args[3]);
            accountTmp = listOfAccount.findAccount(accountID);
            accountTmpReceiver = listOfAccount.findAccount(accountReceiverID);
            if (accountTmp == NULL) {
            fprintf(log,"Error %d: Your transaction failed - account id %d does not exist\n",caspomatID, accountID );
            }
            else if(accountTmpReceiver==NULL){
                fprintf(log,"Error %d: Your transaction failed - account id %d does not exist\n",caspomatID, accountReceiverID );
            }
            else if(strcmp(accountTmp->getPassword(),accountPassword)){
               fprintf(log, "Error %d: Your transaction failed - password for account id %d is incorrect\n", caspomatID, accountID);
            }
            else{
                accountTmp->writeLockAccount();
                accountTmpReceiver->writeLockAccount();
                if(accountTmp->takeMoney(amount)){
                    accountTmpReceiver->addMoney(amount);
                    fprintf(log, "%d: Transfer %d from account %d to account %d new account balance is %d new target account balance is %d\n", caspomatID, amount, accountID, accountReceiverID, accountTmp->getBalance(), accountTmpReceiver->getBalance());
                }
                else{
                    fprintf(log, "Error %d: Your transaction failed - account id %d balance is lower than %d\n", caspomatID, accountID, amount);
                }
                sleep(1);
                accountTmp->writeUnlockAccount();
                accountTmpReceiver->writeUnlockAccount();
                
            }
            continue;
        }
        
        
        else{
            perror("Illegal command");
            exit(1);
        }
    }
}
