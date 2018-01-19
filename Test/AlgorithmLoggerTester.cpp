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

    for (int i = 0; i < 100; i++) {
        try {
            std::thread t([] {
                try {
                    std::cout << double(
                            std::chrono::duration_cast<std::chrono::milliseconds>(
                                    std::chrono::system_clock::now().time_since_epoch()
                            ).count()
                    ) << std::endl;


                    for (int j = 0; j < 1000; ++j) {
                        AWF::AlgorithmLogger *logger_ptr = AWF::AlgorithmLogger::getInstance();
                        std::cout << logger_ptr->getName() << std::endl;
                        AWF::StringEvent e(std::to_string(j));
                    }
                } catch (std::exception &e) {
                    std::cout << e.what() << std::endl;
                }


            });
            t.detach();
//            t.join();
        } catch (std::exception &e) {
            std::cout << e.what() << std::endl;
        }

    }
    int k(0);
    std::cin >> k;


}
