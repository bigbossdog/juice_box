//
//  Bus.cpp
//  HelloNewWorld
//
//  Created by Qi Li on 2/17/17.
//  Copyright (c) 2017 bigbossdog. All rights reserved.
//

#include "Bus.hpp"

Bus::Bus(std::mutex * lock) {
    this->lock = lock;
}

void Bus::receive(Message * m) {
    log("bus received a message");
    this->incomeMessages.push(m);
}

void Bus::post(Message * m, Stop * s) {
    log("bus sent message to stop");
    s->receive(m);
}

void Bus::process() {
    log("processing bus ... ");
    if (!incomeMessages.empty() && !subscribers.empty()) {
        Message * m = incomeMessages.front();
        int value = m->getValue();
        if (value < subscribers.size() && subscribers[value] != NULL) {
            post(m, subscribers[value]);
        } else {
            log("ERROR: message destination not found: " + std::to_string(m->getValue()));
        }
        incomeMessages.pop();
    }
    
}

// TODO: support unsubscribe
int Bus::addStop(Stop * stop) {
    subscribers.push_back(stop);
    return subscribers.size() - 1;
}

bool Bus::shouldTerminate() {
    return stopSign;
}

void Bus::setStopSign(bool s) {
    stopSign = s;
}

Bus::~Bus(){
}