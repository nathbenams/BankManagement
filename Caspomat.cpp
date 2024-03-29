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

Caspomat::Caspomat(int id,const char* _nameFile) : caspomatID(id),caspomatFile(NULL),fileOpened(false),nameFile(_nameFile)
{
 
}

Caspomat::~Caspomat()
{
    if (fileOpened) {
        fclose(caspomatFile);
    }
}

//********************************************
// function name: executeCommandCaspomat
// Description: the main function of the ATMs that read the file and execute the commands
// Parameters:
// Returns:
//********************************************
void* Caspomat::executeCommandCaspomat(void)
{
    char origin_cmd[MAX_LINE_SIZE];
    char* command;
    char* args[MAX_ARG];
    const char* delimiters = " ";
    
    Account* accountTmp;
    Account* accountTmpReceiver;
    usleep(100000);
    
    caspomatFile= fopen(nameFile,"r");
       if(!caspomatFile){
           perror("");
           exit(1);
       }
       fileOpened=true;
    
    
    while(fgets(origin_cmd, MAX_LINE_SIZE,caspomatFile) != NULL){
        char cmd[MAX_LINE_SIZE];
        char* temp;
        strcpy(cmd,origin_cmd);
        cmd[strlen(origin_cmd)-1]='\0';
        command = strtok_r(cmd,delimiters,&temp);
    
        if(command==NULL) break;
        int accountID;
        char* accountPassword;
        
        
        for(int i = 0;i<MAX_ARG;i++){
            args[i]=strtok_r(NULL,delimiters,&temp);
            
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
            origin_cmd[0]='\0';
            cmd[0]='\0';
            continue;
        }
        
        
        else if(!strcmp(command,"D")){
            listOfAccount.readLockAccount();
            accountTmp = listOfAccount.findAccount(accountID);
            listOfAccount.readUnlockAccount();
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
            origin_cmd[0]='\0';
            cmd[0]='\0';
            continue;
        }
        
        
        else if(!strcmp(command,"W")){
            listOfAccount.readLockAccount();
            accountTmp = listOfAccount.findAccount(accountID);
            listOfAccount.readUnlockAccount();
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
            origin_cmd[0]='\0';
            cmd[0]='\0';
            continue;
        }
        
        
        else if(!strcmp(command,"B")){
            listOfAccount.readLockAccount();
            accountTmp = listOfAccount.findAccount(accountID);
            listOfAccount.readUnlockAccount();
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
            origin_cmd[0]='\0';
            cmd[0]='\0';
            continue;
        }
        
        
        else if(!strcmp(command,"T")){
            accountReceiverID = atoi(args[2]);
            amount = atoi(args[3]);
            if(accountID==accountReceiverID) continue;
            listOfAccount.readLockAccount();
            accountTmp = listOfAccount.findAccount(accountID);
            accountTmpReceiver = listOfAccount.findAccount(accountReceiverID);
            listOfAccount.readUnlockAccount();
            
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
                
                
                listOfAccount.writeLockAccount();
                accountTmp->writeLockAccount();

                accountTmpReceiver->writeLockAccount();
                listOfAccount.writeUnlockAccount();
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
            origin_cmd[0]='\0';
            cmd[0]='\0';
            continue;
        }
        
        
        else{
            perror("Illegal command");
            exit(1);
        }
        
        
        
    }
    return NULL;
}
