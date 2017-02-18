
//
// Disclaimer:
// ----------
//
// This code will work only if you selected window, graphics and audio.
//
// Note that the "Run Script" build phase will copy the required frameworks
// or dylibs to your application bundle so you can execute it on any OS X
// computer.
//
// Your resource files (images, sounds, fonts, ...) are also copied to your
// application bundle. To get the path to these resources, use the helper
// function `resourcePath()` from ResourcePath.hpp
//

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

// Here is a small helper for you! Have a look.
#include "ResourcePath.hpp"

#include <iostream>
#include <chrono>
#include <thread>
#include <string>
#include <queue>
#include <vector>

#include "Message.hpp"
#include "Stop.hpp"



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
    Stop * stop1 = new Stop(&lock);
    Stop * stop2 = new Stop(&lock);
    Bus * b = new Bus(&lock);
    stop1->setId(b->addStop(stop1));
    stop2->setId(b->addStop(stop2));
    
    std::thread tStop1(runStop, stop1);
    std::thread tStop2(runStop, stop2);
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
    
    // test message, send 1 to bus
    Message * m1 = new Message(1, stop1);
    
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
            stop1->post(b, m1);
        }
    }
    std::cout << "QUIT" << std::endl;
    stop1->setStopSign(true);
    stop2->setStopSign(true);
    b->setStopSign(true);
    tStop1.join();
    tStop2.join();
    tBus.join();
    delete stop1;
    delete stop2;
    delete b;
    return EXIT_SUCCESS;
}
