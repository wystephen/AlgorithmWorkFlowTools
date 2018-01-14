//
// Created by steve on 18-1-13.
//


#include <iostream>

#include <thread>
#include <mutex>

#include "../AlgorithmLogger/AlgorithmLogger.h"
#include "../AlgorithmLogger/AlgorithmLogger.cpp"

int main(){
   std::cout << "logger" << std::endl;

   AWF::AlgorithmLogger* logger_ptr = AWF::AlgorithmLogger::getInstance();

    for(int i=0;i<100;i++){
        std::thread t ([]{

            AWF::AlgorithmLogger* logger_ptr = AWF::AlgorithmLogger::getInstance();
            std::cout << logger_ptr->getName() << std::endl;
        });
        t.detach();
    }



}
