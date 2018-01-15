//
// Created by steve on 18-1-13.
//


#include <iostream>

#include <thread>
#include <mutex>

#include <chrono>

#include "../AlgorithmLogger/AlgorithmLogger.h"
#include "../AlgorithmLogger/AlgorithmLogger.cpp"

int main() {
    std::cout << "logger" << std::endl;

    AWF::AlgorithmLogger *logger_ptr = AWF::AlgorithmLogger::getInstance();

    for (int i = 0; i < 100; i++) {
        std::thread t([] {
//            std::cout << std::time_put(std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()))


            AWF::AlgorithmLogger *logger_ptr = AWF::AlgorithmLogger::getInstance();
            std::cout << logger_ptr->getName() << std::endl;
        });
        t.detach();
    }


}
