//
//  Caspomat.cpp
//  Targilratouv2
//
//  Created by Nathan Benamou on 14/12/2019.
//  Copyright © 2019 Nathan Benamou. All rights reserved.
//

#include "Caspomat.hpp"

//extern vector<Account> listOfAccount;

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
    
    while(fgets(cmd, MAX_LINE_SIZE,caspomatFile) != nullptr){
        command = strtok(cmd,delimiters);
    
        if(command==nullptr) break;
        int accountID,accountPassword;
    
        for(int i = 0;i<MAX_ARG;i++){
            args[i]=strtok(nullptr,delimiters);
            if(args[i]!=nullptr){
                num_arg++;
            }
        }
        accountID = atoi(args[0]);
        accountPassword = atoi(args[1]);
        
        if (!strcmp(command,"O")) {
            //COMPLETE
            continue;
        }
        else if(!strcmp(command,"D")){
            //COMPLETE
            continue;
        }
        else if(!strcmp(command,"W")){
            //COMPLETE
            continue;
        }
        else if(!strcmp(command,"B")){
            //COMPLETE
            continue;
        }
        else if(!strcmp(command,"T")){
            //COMPLETE
            continue;
        }
        else{
            perror("Illegal command");
            exit(1);
        }
    }
}
