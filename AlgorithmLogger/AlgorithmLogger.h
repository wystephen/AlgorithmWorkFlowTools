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

/**
 * Singleton !!!!!
 */
namespace AWF {
    class AlgorithmLogger {
        //TODO: RTTI
    public:
        static AlgorithmLogger *getInstance();


        std::string getName() {
            return "name";
        }


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
        std::deque<AbstractEvent> event_queue_;


    private:
        /**
         * default constructor function.
         */
        AlgorithmLogger();

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
