#include <iostream>
#include <chrono>
#include <thread>
#include <string>
#include <queue>
#include <vector>

class Message {
public:
    // mock value
    int value;
    Message(int value) {
        this->value = value;
    }
    int getValue() {
        return value;
    }
    ~Message(){}
};

// forward declaration
class Bus;
class Stop {
private:
    bool stopSign = 0;
    std::mutex * lock;
    
    void log(std::string msg) {
        lock->lock();
        std::cout << msg << std::endl;
        lock->unlock();
    }
public:
    // stop
    std::queue<Message*> incomeMessages;
    
    Stop(std::mutex * lock) {
        this->lock = lock;
    }
    
    void receive(Message * m) {
        log("stop received a message");
        incomeMessages.push(m);
    }
    
    void process() {
        log("processing Stop");
        if (!incomeMessages.empty()) {
            log("Mock message : " + std::to_string(incomeMessages.front()->getValue()));
            incomeMessages.pop();
        }
    }
    
    bool shouldTerminate() {
        return stopSign;
    }
    
    void setStopSign(bool s) {
        stopSign = s;
    }
    
    ~Stop(){
    }
};

class Bus {
private:
    bool stopSign = 0;
    std::mutex * lock;
    
    void log(std::string msg) {
        lock->lock();
        std::cout << msg << std::endl;
        lock->unlock();
    }
    
public:
    // bus
    std::queue<Message*> incomeMessages;
    std::vector<Stop*> subscribers;
    
    Bus(std::mutex * lock) {
        this->lock = lock;
    }
    
    void receive(Message * m) {
        log("bus received a message");
        this->incomeMessages.push(m);
    }
    
    void post(Message * m, Stop * s) {
        log("bus sent message to stop");
        s->receive(m);
    }
    
    void process() {
        log("processing bus");
        if (!incomeMessages.empty() && !subscribers.empty()) {
            post(incomeMessages.front(), subscribers[0]);
            incomeMessages.pop();
        }
    }
    
    void addStop(Stop * stop) {
        this->subscribers.push_back(stop);
    }
    
    bool shouldTerminate() {
        return stopSign;
    }
    
    void setStopSign(bool s) {
        stopSign = s;
    }
    
    ~Bus(){
    }
};

void runStop(Stop * a) {
    while (!a->shouldTerminate()) {
        a->process();
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
}

void runBus(Bus * b) {
    while (!b->shouldTerminate()) {
        b->process();
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
}

// Main thread
int main(int, char const**)
{
    std::mutex lock;
    Stop * a = new Stop(&lock);
    Bus * b = new Bus(&lock);
    b->addStop(a);
    std::thread tStop(runStop, a);
    std::thread tBus(runBus, b);

    // TODO: start threads for different components
    // start message bus
    // start console
    // start renderer
    // start ...
    
    // Create the main window (also renderer)
    // TODO: move to renderer class; main thread should just be the console

    /*sf::RenderWindow window(sf::VideoMode(800, 600), "Hello New World");

    while (window.isOpen())
    {
        // Process system events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            
            // TODO: invoke console with esc
        }

        window.clear();
        // TODO: process render event queue
        window.display();
    }*/
    
    // TODO: move to console class
    std::string cmd;
    Message * m1 = new Message(1);
    Message * m2 = new Message(2);
    Message * m3 = new Message(3);
    Message * m4 = new Message(4);
    
    while(1) {
        std::cout << "What do you want?" << std::endl;
        std::getline(std::cin, cmd);
        // TODO: process debug command
        // TODO: cmd - debug
        // TODO: cmd - pause
        // TODO: ...
        if (cmd.compare("quit") == 0) {
            std::cout << "Quiting program";
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            std::cout << ".";
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            std::cout << ".";
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            std::cout << "." << std::endl;
            break;
        }
        
        if (cmd.compare("send1") == 0) {
            b->receive(m1);
        }
    }
    std::cout << "QUIT" << std::endl;
    delete m1;
    delete m2;
    delete m3;
    delete m4;
    a->setStopSign(true);
    b->setStopSign(true);
    tStop.join();
    tBus.join();
    delete a;
    delete b;
    return EXIT_SUCCESS;
}
