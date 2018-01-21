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
#include "AbstractEvent.h"

#include "../UsefulTools/TimeTools.h"

/**
 * Singleton !!!!!
 */
namespace AWF {
    class AlgorithmLogger {
        //TODO: RTTI
    public:
        static AlgorithmLogger *getInstance();


        std::string getName() {
//            return "name";
            return logger_name_;
        }


        /**
         * Add event to event queue,
         * multi-thread safety.
         * @param e
         * @return
         */
        bool addEvent(AbstractEvent &e) {
            try {

                event_queue_.push_back(e);
            } catch (std::exception &e) {
                std::cout << __FILE__
                          << ":"
                          << __LINE__
                          << ":"
                          << e.what()
                          << std::endl;
            }
        }

    protected:
        std::deque<AbstractEvent> event_queue_=std::deque<AbstractEvent>();

        std::string logger_name_;


    private:
        /**
         * default constructor function.
         */
        AlgorithmLogger():
                logger_name_("logger_" + getFormatTime()){

        }
//    AlgorithmLogger(){}

        /**
         * Set constructor function as private, avoid unnecessary constructor.
         */
        AlgorithmLogger(const AlgorithmLogger &);

        /**
         * Let the operator = as private, preserve it from unacceptable deep copy.
         * @return
         */
        AlgorithmLogger &operator=(const AlgorithmLogger &);

        static AlgorithmLogger *instance;
    };

}


#endif //ALGORITHMWORKFLOWTOOLS_ALGORITHMLOGGER_H
