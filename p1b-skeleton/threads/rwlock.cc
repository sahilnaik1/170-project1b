#include<stdio.h>
#include <pthread.h>
#include <iostream> //


#include "rwlock.h"

//Implement all methods of RWLock defined in rwlock.h
//Your solution for  Task 3 
//TODO

RWLock::RWLock() { 
    char read_debug[] = "read_debug";
    okToRead = new Condition(read_debug);
    char write_debug[] = "write_debug";
    okToWrite = new Condition(write_debug);
    char lock_debug[] = "lock_debug";
    lock = new Lock(lock_debug);
    AR, WR, AW, WW = 0,0,0,0;
}
RWLock::~RWLock() { 
    delete okToRead;
    delete okToWrite;
    delete lock;
}
void RWLock::startRead() { 
    lock->Acquire();
    while ((AW + WW) > 0) {
        WR++;
        okToRead->Wait(lock);
        WR--;
    }
    AR++;
    lock->Release();
}
void RWLock::doneRead() { 
    lock->Acquire();
    AR--;
    if (AR == 0 && WW > 0)
        okToWrite->Signal(lock);
    lock->Release();
}
void RWLock::startWrite() { 
    lock->Acquire();
    while( (AW + AR) > 0){
        WW++;
        okToWrite->Wait(lock);
        WW--;
    }
    AW++;
    lock->Release();
}
void RWLock::doneWrite() { 
    lock->Acquire();
    AW--;
    if (WW > 0) {
        okToWrite->Signal(lock);
    } else if (WR > 0) {
        okToRead->Broadcast(lock);
    }
    lock->Release();
}
