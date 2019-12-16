//
//  Protection.hpp
//  Targilratouv2
//
//  Created by Nathan Benamou on 16/12/2019.
//  Copyright © 2019 Nathan Benamou. All rights reserved.
//

#ifndef Protection_hpp
#define Protection_hpp

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
using namespace std;


class Protection
{
public:
    Protection();
    void enterReader();
    void enterWriter();
    void leaveReader();
    void leaveWriter();
    
private:
    pthread_mutex_t writerLock;
    pthread_mutex_t readerLock;
    int readerCount;
};



#endif /* Protection_hpp */
