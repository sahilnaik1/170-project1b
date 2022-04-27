#include<stdio.h>
#include <pthread.h>
#include <iostream> //


#include "rwlock.h"

//Implement all methods of RWLock defined in rwlock.h
//Your solution for  Task 3 
//TODO

RWLock::RWLock() { 
    pthread_cond_init(&okToRead, 0);
    pthread_cond_init(&okToWrite, 0);
    pthread_mutex_init(&lock, 0);
    AR, WR, AW, WW = 0,0,0,0;
}
RWLock::~RWLock() { 

}
void RWLock::startRead() { 
    pthread_mutex_lock(&lock);
    while ((AW + WW) > 0) {
        WR++;
        pthread_cond_wait(&okToRead, &lock);
        WR--;
    }
    AR++;
    pthread_mutex_unlock(&lock);
}
void RWLock::doneRead() { 
    pthread_mutex_lock(&lock);
    AR--;
    if (AR == 0 && WW > 0)
        pthread_cond_signal(&okToWrite);
    pthread_mutex_unlock(&lock);
}
void RWLock::startWrite() { 
    pthread_mutex_lock(&lock);
    while( (AW + AR) > 0){
        WW++;
        pthread_cond_wait(&okToWrite, &lock);
        WW--;
    }
    AW++;
    pthread_mutex_unlock(&lock);
}
void RWLock::doneWrite() { 
    pthread_mutex_lock(&lock);
    AW--;
    if (WW > 0) {
        pthread_cond_signal(&okToWrite);
    } else if (WR > 0) {
        pthread_cond_broadcast(&okToRead);
    }
    pthread_mutex_unlock(&lock);
}
