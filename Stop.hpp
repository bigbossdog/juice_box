//
//  Stop.h
//  HelloNewWorld
//
//  Created by Qi Li on 2/17/17.
//  Copyright (c) 2017 bigbossdog. All rights reserved.
//

#ifndef __HelloNewWorld__Stop__
#define __HelloNewWorld__Stop__

#include <string>
#include <mutex>
#include <iostream>
#include <queue>

#include "Message.hpp"
#include "Bus.hpp"
// forward declaration
class Bus;
class Stop {
private:
    int id;
    bool stopSign = 0;
    std::mutex * lock;
    std::queue<Message*> incomeMessages;

    void log(std::string msg) {
        lock->lock();
        std::cout << msg << std::endl;
        lock->unlock();
    }
    
public:
    
    Stop(std::mutex * lock);
    
    void setId(int id);
    
    int getId();
    
    void receive(Message * m);
    void process();
    
    bool shouldTerminate() {
        return stopSign;
    }
    
    void setStopSign(bool s);
    void post(Bus * bus, Message * m);
    ~Stop();
};



#endif /* defined(__HelloNewWorld__Stop__) */
