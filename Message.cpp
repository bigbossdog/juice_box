//
//  Message.cpp
//  HelloNewWorld
//
//  Created by Qi Li on 2/17/17.
//  Copyright (c) 2017 bigbossdog. All rights reserved.
//

#include "Message.hpp"

Message::Message(int value, Stop * fromStop) {
    this->value = value;
    this->fromStop = fromStop;
}

int Message::getValue(){
    return value;
}

Stop * Message::getFromStop() {
    return fromStop;
}

Message::~Message() {}