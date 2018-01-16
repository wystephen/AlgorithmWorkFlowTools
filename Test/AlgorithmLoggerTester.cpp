//
// Created by steve on 18-1-13.
//


#include <iostream>

#include <thread>
#include <mutex>

#include <chrono>

#include "../AlgorithmLogger/AlgorithmLogger.h"
#include "../AlgorithmLogger/AlgorithmLogger.cpp"

#include "../AlgorithmLogger/Event.h"
#include "../AlgorithmLogger/Event.cpp"

int main() {
    std::cout << "logger" << std::endl;

    AWF::AlgorithmLogger *logger_ptr = AWF::AlgorithmLogger::getInstance();

    for (int i = 0; i < 2; i++) {
        std::thread t([] {
//            std::cout << std::time_put(std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()))


            for (int j = 0; j < 1000; ++j) {
                AWF::AlgorithmLogger *logger_ptr = AWF::AlgorithmLogger::getInstance();
                std::cout << logger_ptr->getName() << std::endl;
                AWF::Event<double> e(std::to_string(j));
                std::cout << e.event_name_
                          << ":"
                          << e.event_time_stamp_
                          << ":"
                          << e.msg_
                          << std::endl;
            }

        });
        t.detach();
    }


}
