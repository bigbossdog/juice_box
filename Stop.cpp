//
//  Stop.cpp
//  HelloNewWorld
//
//  Created by Qi Li on 2/17/17.
//  Copyright (c) 2017 bigbossdog. All rights reserved.
//

#include "Stop.hpp"

Stop::Stop(std::mutex * lock) {
    this->lock = lock;
}

void Stop::setId(int id) {
    this->id = id;
}

int Stop::getId() {
    return id;
}

void Stop::receive(Message * m) {
    log("stop received a message");
    incomeMessages.push(m);
}

void Stop::process() {
    log("processing Stop");
    if (!incomeMessages.empty()) {
        log("Mock message : " + std::to_string(incomeMessages.front()->getValue()));
        incomeMessages.pop();
    }
}

void Stop::setStopSign(bool s) {
    stopSign = s;
}

void Stop::post(Bus * bus, Message * m) {
    bus->receive(m);
}

Stop::~Stop() {}
