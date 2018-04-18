//
// Created by steve on 18-1-13.
//


#include <iostream>

#include <thread>
#include <mutex>

#include <chrono>

#include "AlgorithmLogger/AlgorithmLogger.h"
#include "AlgorithmLogger/AlgorithmLogger.cpp"

//#include "AlgorithmLogger/Event.h"
//#include "AlgorithmLogger/Event.cpp"

int main() {
	std::cout << "logger" << std::endl;

	AWF::AlgorithmLogger *logger_ptr = AWF::AlgorithmLogger::getInstance();
	std::cout.precision(15);

	for (int i = 0; i < 1000; i++) {
		try {
			std::thread t([i] {
				try {
//                    std::cout << double(
//                            std::chrono::duration_cast<std::chrono::milliseconds>(
//                                    std::chrono::system_clock::now().time_since_epoch()
//                            ).count()
//                    ) << std::endl;

					AWF::AlgorithmLogger *logger_ptr = AWF::AlgorithmLogger::getInstance();
					usleep(100);
					for (int j = 0; j < 100; ++j) {

						AWF::AbstractEvent t_event("test_"
						                           + std::to_string(i)
						                           + "_"
						                           + std::to_string(j)
						);
						auto matrix = Eigen::Matrix4d::Identity();

						t_event.setData(matrix);
						logger_ptr->addEvent(t_event);
					}
				} catch (std::exception &e) {
					std::cout << e.what() << std::endl;
				}


			});
			t.detach();
		} catch (std::exception &e) {
			std::cout << e.what() << std::endl;
		}
	}

	sleep(1);
	std::cout << "logger counter : "
	          << logger_ptr->getThread_counter() << std::endl;
	logger_ptr->outputAllEvent();


	int k(0);
	std::cin >> k;


}
