//
//  Message.hpp
//  HelloNewWorld
//
//  Created by Qi Li on 2/17/17.
//  Copyright (c) 2017 bigbossdog. All rights reserved.
//

#ifndef HelloNewWorld_Message_hpp
#define HelloNewWorld_Message_hpp

class Stop;
class Message {
private:
    // mock value, can be anything
    // for now, set it to the destination id
    int value;
    Stop * fromStop;
    
public:
    Message(int value, Stop * fromStop);
    
    int getValue();
    
    Stop * getFromStop();
    
    ~Message();
};

#endif
