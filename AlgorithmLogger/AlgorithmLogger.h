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


//    /**
//     *
//     * @param m mutex
//     * @param eq event queue
//     */
//    void outputThread(std::mutex &m,
//                      std::deque<AbstractEvent> &eq) {
//        while (true) {
//            std::unique_lock<std::mutex> lk(m);
//
//            auto tmp_event = eq.front();
//            std::cout << tmp_event.toString() << std::endl;
//            lk.unlock();
//        }
//
//    }

    /**
     *  out thread
     * @param m
     * @param event
     */
    void outThread(std::mutex &m,
                   AbstractEvent &event) {
        m.lock();
        std::cout << event.toString() << std::endl;
        m.unlock();

    }


    class AlgorithmLogger {
        //TODO: RTTI
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
        bool addEvent(AbstractEvent &e) {
            try {
                AbstractEvent tmp_e = e;
                auto t = new std::thread([&]() {
//                    std::lock_guard<std::mutex> lk(queue_mutex_);
                    queue_mutex_.lock();
                    std::cout << thread_counter++
                              << ":"
                              << logger_name_
                              << tmp_e.toString()
                              << std::endl;
                    std::cout.flush();
                    queue_mutex_.unlock();
                });
//                t->detach();
//                std::cout << e.toString() << std::endl;

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

        std::string logger_name_ = "logger_" + getFormatTime();

        std::mutex queue_mutex_;

        int thread_counter = 0;

//        static std::condition_variable queue_conditional_var_;

//        static std::thread *out_thread_ptr_;
        // = new std::thread(outputThread,queue_mutex_, event_queue_);


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
