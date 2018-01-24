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


    /**
     *
     * @param m mutex
     * @param eq event queue
     */
    void outputThread(std::mutex &m,
                      std::deque<AbstractEvent> &eq) {
        while (true) {
            std::unique_lock<std::mutex> lk(m);

            auto tmp_event = eq.front();
            std::cout << tmp_event.toString() << std::endl;
            lk.unlock();
        }

    }

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
                auto t = new std::thread([&](AbstractEvent e){

                    std::lock_guard<std::mutex> lk(queue_mutex_);
                    std::cout << e.toString() << std::endl;

                });
                t->detach();

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

        std::string logger_name_;

        mutable std::mutex queue_mutex_;

        static std::condition_variable queue_conditional_var_;

//        static std::thread *out_thread_ptr_;
        // = new std::thread(outputThread,queue_mutex_, event_queue_);


    private:
        /**
         * default constructor function.
         */
        AlgorithmLogger() :
                logger_name_("logger_" + getFormatTime())
        {

        }
//    AlgorithmLogger(){}

        /**
         *
         */
//        ~AlgorithmLogger() {}

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
