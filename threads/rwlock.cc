#include<stdio.h>
#include <iostream> //


#include "rwlock.h"

//Implement all methods of RWLock defined in rwlock.h
//Your solution for  Task 3 
//TODO

RWLock::RWLock(){ 
    char *lckname = "L"; 
    lck=new Lock(lckname); 
    
    char *Rconname = "R"; 
    Rcondition=new Condition(Rconname); 
    
    char *Wconname = "W"; 
    Wcondition=new Condition(Rconname); 
    
    waitReadNumber = 0;
    readingNumber = 0;
    waitWriteNumber = 0;
    writingNumber = 0;
}

RWLock::~RWLock(){ 
    delete[] lck;
    delete[] Rcondition;
    delete[] Wcondition;
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
    if(!readShouldWait()){
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
        Wcondition->Wait(lck);
    }
    else if(waitReadNumber > 0){
        Rcondition->Broadcast(lck);
    }
    lck->Release();
}

bool RWLock::readShouldWait(){
  if(writingNumber > 0 || waitWriteNumber > 0){
    return true;
  }
  return false;
}

bool RWLock::writeShouldWait(){
  if(writingNumber > 0 || readingNumber > 0){
    return true;
  }
  return false;
}