//
// Created by steve on 18-1-13.
//

#ifndef ALGORITHMWORKFLOWTOOLS_ALGORITHMLOGGER_H
#define ALGORITHMWORKFLOWTOOLS_ALGORITHMLOGGER_H


#include <iostream>
#include <queue>
#include <deque>

#include <thread>
#include <mutex>
#include <condition_variable>
#include <fstream>

#include <unistd.h>


#include "AbstractEvent.h"

#include "../UsefulTools/TimeTools.h"

/**
 * Singleton !!!!!
 */
namespace AWF {


	class AlgorithmLogger {
	public:
		static AlgorithmLogger *getInstance();


		std::string getName() {
			return logger_name_;
		}


		/**
		 * Add event to event queue,
		 * multi-thread safety.
		 * @param e
		 * @return
		 */
		bool addEvent(AbstractEvent &e);


		bool addTraceEvent(std::string group_name, std::string value_name, const Eigen::MatrixXd &matrix);

		bool addPlotEvent(std::string group_name, std::string value_name, double value) {
			Eigen::Matrix<double, 1, 1> m;
			m(0, 0) = value;
			addPlotEvent(group_name, value_name, m);
		}

		bool addPlotEvent(std::string group_name, std::string value_name, const Eigen::MatrixXd &matrix);

		bool addTrace3dEvent(std::string group_name, std::string value_name, const Eigen::MatrixXd &matrix);

		int getThread_counter() const;

		void setThread_counter(int thread_counter);


		void outputAllEvent(bool display = false) {
			std::ofstream log_file(logger_name_ + ".log");

			for (auto iter = event_queue_.begin(); iter != event_queue_.end(); ++iter) {

//                std::cout << iter->toString() << std::endl;
				log_file << iter->toString() << "\n";

			}
			log_file.flush();
			std::cout << "queue size: " << event_queue_.size() << std::endl;

			log_file.close();

			if (display) {
//				std::thread t([&]() {
					system(("python3 /home/steve/Code/AlgorithmWorkFlowTools/UsefulScript/LoggerFiltPloter.py "
					        + logger_name_ + ".log").c_str());
//				});
//				t.detach();

			}

			return;

		}

	protected:
		std::deque<AbstractEvent> event_queue_;

//        std::string logger_name_ = "/tmp/ramdisk/logger_" + getFormatTime();
		std::string logger_name_ = "/home/steve/SourceData/AlgorithmLog/logger_" + getFormatTime();

		std::mutex queue_mutex_;

		int thread_counter;// = 0;


		std::mutex map_mutex_;


	private:
		/**
		 * default constructor function.
		 */
		AlgorithmLogger() {}

		/**
		 *
		 */
		~AlgorithmLogger() {}

		/**
		 * Set constructor function as private, avoid unnecessary constructor.
		 */
		AlgorithmLogger(const AlgorithmLogger &);

		/**
		 * Let the operator = as private, preserve it from unacceptable deep copy.
		 * @return
		 */
		AlgorithmLogger &operator=(const AlgorithmLogger &);

		static AlgorithmLogger *instance;//= nullptr;

	};

}


#endif //ALGORITHMWORKFLOWTOOLS_ALGORITHMLOGGER_H
