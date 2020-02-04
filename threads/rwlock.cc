#include<stdio.h>
#include <iostream> //


#include "rwlock.h"

//Implement all methods of RWLock defined in rwlock.h
//Your solution for  Task 3 
//TODO

RWLock::RWLock(){ 
    Rcondition=new Condition(NULL); 
    
    Wcondition=new Condition(NULL); 
        
    lck=new Lock(NULL); 
    
    waitReadNumber = 0;
    readingNumber = 0;
    waitWriteNumber = 0;
    writingNumber = 0;
}

RWLock::~RWLock(){ 
    delete Rcondition;
    delete Wcondition;
    delete lck;
}

void RWLock::startRead(){ 
    lck->Acquire();
    waitReadNumber++;
    while(readShouldWait()){
        Rcondition->Wait(lck);
    }
    waitReadNumber--;
    readingNumber++;
    lck->Release();
}
void RWLock::doneRead(){ 
    lck->Acquire();
    readingNumber--;
    if(readingNumber==0 && waitWriteNumber>0){
        Wcondition->Signal(lck);
    }
    lck->Release();
}
void RWLock::startWrite(){ 
    lck->Acquire();
    waitWriteNumber++;
    while(writeShouldWait()){
        Wcondition->Wait(lck);
    }
    waitWriteNumber--;
    writingNumber++;
    lck->Release();
}
void RWLock::doneWrite(){ 
    lck->Acquire();
    writingNumber--;
    if(waitWriteNumber > 0){
        Wcondition->Signal(lck);
    }
    else if(waitReadNumber > 0){
        Rcondition->Broadcast(lck);
    }
    lck->Release();
}

bool RWLock::readShouldWait(){
  if((writingNumber + waitWriteNumber) > 0){
    return true;
  }
  return false;
}

bool RWLock::writeShouldWait(){
  if((writingNumber + readingNumber) > 0){
    return true;
  }
  return false;
}