#ifndef __RWLOCK_H__
#define __RWLOCK_H__
#include<semaphore.h>
#include "synch.h"

class RWLock{
private:
    	//Add  fields for  RWLock. Your solution to Task 3
    	//TODO

		pthread_cond_t okToRead, okToWrite;
		pthread_mutex_t lock;
		int AR, WR, AW, WW;
public:
    	RWLock();
    	~RWLock();
    //Reader
    	void startRead();
    	void doneRead();
    // Writer
    	void startWrite();
    	void  doneWrite();
};

#endif
