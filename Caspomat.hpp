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
#include <iostream>
#include <vector>
using namespace std;
#include "Account.hpp"
#define MAX_LINE_SIZE 50
#define MAX_ARG 5


class Caspomat
{
public:
    Caspomat(int id,char* nameFile);
    ~Caspomat();
    void executeCommandCaspomat();
private:
    int caspomatID;
    FILE* caspomatFile;
    bool fileOpened;
};
#endif /* Caspomat_hpp */
