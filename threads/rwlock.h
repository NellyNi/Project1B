#ifndef __RWLOCK_H__
#define __RWLOCK_H__
#include<semaphore.h>
#include "synch.h"
#define HTABLE_SIZE 128

class RWLock{
private:
      //Add  fields for  RWLock. Your solution to Task 3
      //TODO
		Lock  *lck;
		Condition  *Rcondition;
		Condition  *Wcondition;
		int waitReadNumber;
		int readingNumber;
		int waitWriteNumber;
		int writingNumber;
		bool readShouldWait();
		bool writeShouldWait();
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
