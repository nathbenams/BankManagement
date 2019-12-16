//
//  Caspomat.cpp
//  Targilratouv2
//
//  Created by Nathan Benamou on 14/12/2019.
//  Copyright © 2019 Nathan Benamou. All rights reserved.
//

#include "Caspomat.hpp"

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
