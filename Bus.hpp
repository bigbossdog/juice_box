//
//  Bus.h
//  HelloNewWorld
//
//  Created by Qi Li on 2/17/17.
//  Copyright (c) 2017 bigbossdog. All rights reserved.
//

#ifndef __HelloNewWorld__Bus__
#define __HelloNewWorld__Bus__

#include <vector>
#include <queue>
#include <mutex>
#include <iostream>

#include "Message.hpp"
#include "Stop.hpp"

class Bus {
private:
    // used to terminate the thread
    bool stopSign = 0;
    std::mutex * lock;
    
    void log(std::string msg) {
        lock->lock();
        std::cout << msg << std::endl;
        lock->unlock();
    }
    
    std::queue<Message*> incomeMessages;
    std::vector<Stop*> subscribers;
    
public:
    Bus(std::mutex * lock);
    
    void receive(Message * m);
    
    void post(Message * m, Stop * s);
    
    void process();
    
    // TODO: support unsubscribe
    int addStop(Stop * stop);
    
    bool shouldTerminate();
    
    void setStopSign(bool s);
    
    ~Bus();
};


#endif /* defined(__HelloNewWorld__Bus__) */
