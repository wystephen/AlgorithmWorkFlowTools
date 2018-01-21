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
    std::cout.precision(15);

//    for (int i = 0; i < 100; i++) {
//        try {
//            std::thread t([] {
//                try {
//                    std::cout << double(
//                            std::chrono::duration_cast<std::chrono::milliseconds>(
//                                    std::chrono::system_clock::now().time_since_epoch()
//                            ).count()
//                    ) << std::endl;
//
//
//                    for (int j = 0; j < 1000; ++j) {
//                        AWF::AlgorithmLogger *logger_ptr = AWF::AlgorithmLogger::getInstance();
//                        std::cout << logger_ptr->getName() << std::endl;
//                        AWF::StringEvent e(std::to_string(j));
//                    }
//                } catch (std::exception &e) {
//                    std::cout << e.what() << std::endl;
//                }
//
//
//            });
//            t.detach();
//        } catch (std::exception &e) {
//            std::cout << e.what() << std::endl;
//        }

//    }
    AWF::StringEvent *sep = new AWF::StringEvent("name");//= new AWF::Event<std::string>("name");
    if (sep== nullptr) {
        std::cout << __LINE__
                  << ":"
                  << "sep is nullptr"
                  << std::endl;
    }
    std::cout << sep->toString() << std::endl;
    std::cout << typeid(sep).name() << std::endl;
    AWF::AbstractEvent *sep1 = (static_cast<AWF::AbstractEvent *>(sep));
    if (sep1 == nullptr) {
        std::cout << __LINE__
                  << ":"
                  << "sep is nullptr"
                  << std::endl;
    }
    std::cout << sep1->toString() << std::endl;
    std::cout << typeid(sep1).name() << std::endl;
    AWF::StringEvent *sep2 = (dynamic_cast<AWF::StringEvent *>(sep));
    if (sep2 == nullptr) {
        std::cout << __LINE__
                  << ":"
                  << "sep is nullptr"
                  << std::endl;
    }
    std::cout << sep2->toString() << std::endl;
    std::cout << typeid(sep2).name() << std::endl;

    int k(0);
    std::cin >> k;


}
