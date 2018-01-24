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
        bool addEvent(const AbstractEvent &e) {
            try {
                std::unique_lock<std::mutex> lk(queue_mutex_);
                event_queue_.push_back(e);
                queue_conditional_var_.notify_all();
                lk.unlock();

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
        std::deque<AbstractEvent> event_queue_ = std::deque<AbstractEvent>();

        std::string logger_name_;

        mutable std::mutex queue_mutex_;

        std::condition_variable queue_conditional_var_;

        std::thread out_thread_;

        /**
         * out through thread
         * @return
         */
        bool outputThread() {
            while (true) {
                std::unique_lock<std::mutex> lk(queue_mutex_);
                queue_conditional_var_.wait(
                        lk,
                        [&]() {

                            auto tmp_event = event_queue_.front();
                            std::cout << tmp_event.toString() << std::endl;
                            return true;
                        }
                );
                lk.unlock();
            }

        }


    private:
        /**
         * default constructor function.
         */
        AlgorithmLogger() :
                logger_name_("logger_" + getFormatTime()) {
            out_thread_=std::thread(outputThread);
            out_thread_.detach();

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
