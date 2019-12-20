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
    pthread_mutex_init(&writerLock, NULL);
    pthread_mutex_init(&readerLock, NULL);
    
}

Protection::~Protection(){
    pthread_mutex_destroy(&writerLock);
    pthread_mutex_destroy(&readerLock);
    
}
//********************************************
// function name: enterReader
// Description: enter a reader in the critical section if its free
//              of writer, wait otherwise
// Parameters:
// Returns:
//********************************************
void Protection::enterReader()
{
    pthread_mutex_lock(&readerLock);
    readerCount++;
    if(readerCount==1){
        pthread_mutex_lock(&writerLock);
    }
    pthread_mutex_unlock(&readerLock);
}
//********************************************
// function name: enterWriter
// Description: enter a writer in the critical section if its free
//              of writer or reader in the critical section , or wait
// Parameters:
// Returns:
//********************************************
void Protection::enterWriter()
{
    pthread_mutex_lock(&writerLock);
}
//********************************************
// function name: leaveReader
// Description: leave the critical section if he was the last unlock the
//              mutex
// Parameters:
// Returns:
//********************************************
void Protection::leaveReader()
{
    pthread_mutex_lock(&readerLock);
    readerCount--;
    if(!readerCount){
        pthread_mutex_unlock(&writerLock);
    }
    pthread_mutex_unlock(&readerLock);
}
//********************************************
// function name: leave writer
// Description: unlock the writer's mutex
// Parameters:
// Returns:
//********************************************
void Protection::leaveWriter()
{
    pthread_mutex_unlock(&writerLock);
}
