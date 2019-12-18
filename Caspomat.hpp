//
//  Caspomat.hpp
//  Targilratouv2
//
//  Created by Nathan Benamou on 14/12/2019.
//  Copyright © 2019 Nathan Benamou. All rights reserved.
//

#ifndef Caspomat_hpp
#define Caspomat_hpp

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <string.h>
#include <unistd.h>
using namespace std;
#include "Account.hpp"
#include "listAccount.hpp"
#define MAX_LINE_SIZE 50
#define MAX_ARG 5


class Caspomat
{
public:
    Caspomat(int id,const char* nameFile);
    ~Caspomat();
    void* executeCommandCaspomat(void);
    static void *execute_helper(void *context){
        return ((Caspomat *)context)->executeCommandCaspomat();
    }
private:
    int caspomatID;
    FILE* caspomatFile;
    bool fileOpened;
    const char* nameFile;
};
#endif /* Caspomat_hpp */
