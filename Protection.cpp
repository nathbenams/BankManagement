//
//  Protection.cpp
//  Targilratouv2
//
//  Created by Nathan Benamou on 16/12/2019.
//  Copyright © 2019 Nathan Benamou. All rights reserved.
//

#include "Protection.hpp"

Protection::Protection() : writerLock(),readerLock(),readerCount(0)
{
    writerLock = PTHREAD_MUTEX_INITIALIZER;
    readerLock = PTHREAD_MUTEX_INITIALIZER;
}

void Protection::enterReader()
{
    pthread_mutex_lock(&readerLock);
    readerCount++;
    if(readerCount==1){
        pthread_mutex_lock(&writerLock);
    }
    pthread_mutex_unlock(&readerLock);
}

void Protection::enterWriter()
{
    pthread_mutex_lock(&writerLock);
}

void Protection::leaveReader()
{
    pthread_mutex_lock(&readerLock);
    readerCount--;
    if(!readerCount){
        pthread_mutex_unlock(&writerLock);
    }
    pthread_mutex_unlock(&readerLock);
}

void Protection::leaveWriter()
{
    pthread_mutex_unlock(&writerLock);
}
