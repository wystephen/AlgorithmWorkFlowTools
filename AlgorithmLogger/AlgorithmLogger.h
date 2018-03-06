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
                auto t = std::thread([&](AbstractEvent tmp_e) {
//                    std::unique_lock<std::mutex> ulock(queue_mutex_);
                    try {
                        queue_mutex_.lock();
//                        std::cout << thread_counter++
//                                  << ":"
//                                  << logger_name_
//                                  << tmp_e.toString()<<'\n';
//                                  << std::endl;
//                        std::cout.flush();
                        event_queue_.push_back(tmp_e);
                        queue_mutex_.unlock();

                    } catch (std::exception &e) {
                        ERROR_MSG_FLAG(e.what());
                    }


                }, tmp_e);
                t.detach();
//                t.join();
                return true;

            } catch (std::exception &e) {
//                std::cout << __FILE__
//                          << ":"
//                          << __LINE__
//                          << ":"
//                          << e.what()
//                          << std::endl;
                ERROR_MSG_FLAG(e.what());
                return false;
            }
        }

    protected:
        std::deque<AbstractEvent> event_queue_;

        std::string logger_name_ = "logger_" + getFormatTime();

        std::mutex queue_mutex_;

        int thread_counter;// = 0;
    public:
        int getThread_counter() const;

        void setThread_counter(int thread_counter);

        void outputAllEvent(){
            for(auto iter=event_queue_.begin();iter!=event_queue_.end();++iter){
                std::cout << iter->toString() << std::endl;
            }
            std::cout << "queue size: " << event_queue_.size() << std::endl;
        }

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
