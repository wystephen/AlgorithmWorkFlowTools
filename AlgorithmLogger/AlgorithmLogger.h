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


#include
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


        bool addTraceEvent(std::string group_name, std::string value_name, Eigen::MatrixXd matrix);

        bool addPlotEvent(std::string group_name, std::string value_name, Eigen::MatrixXd matrix);

        bool addTrace3dEvent(std::string group_name, std::string value_name, Eigen::MatrixXd matrix);

        int getThread_counter() const;

        void setThread_counter(int thread_counter);


        void outputAllEvent() {
            std::ofstream log_file(logger_name_ + ".log");

            for (auto iter = event_queue_.begin(); iter != event_queue_.end(); ++iter) {

//                std::cout << iter->toString() << std::endl;
                log_file << iter->toString() << "\n";

            }
            std::cout << "queue size: " << event_queue_.size() << std::endl;

            log_file.close();
        }

    protected:
        std::deque<AbstractEvent> event_queue_;

        std::string logger_name_ = "logger_" + getFormatTime();

        std::mutex queue_mutex_;

        int thread_counter;// = 0;



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
