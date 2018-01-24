//
// Created by steve on 18-1-13.
//

#include "AlgorithmLogger.h"

namespace AWF {


    AlgorithmLogger::AlgorithmLogger(const AlgorithmLogger &) {

    }


    AlgorithmLogger &AlgorithmLogger::operator=(const AlgorithmLogger &) {

    }

    AlgorithmLogger *AlgorithmLogger::instance = nullptr; //new AlgorithmLogger();

//    std::mutex AlgorithmLogger::queue_mutex_ ;

//    int thread_counter = 0;

    /**
     * get or create new instance.
     * @return
     */
    AlgorithmLogger *AlgorithmLogger::getInstance() {
        static std::once_flag oc;// call once local static variable.
        // call once , to avoid some complexity process of multi-thread DCLP.
        if (instance == nullptr) {
            std::call_once(oc, [] {
                if (instance == nullptr) {
                    instance = new AlgorithmLogger();
                }
            });
        }

        return instance;
    }

    int AlgorithmLogger::getThread_counter() const {
        return thread_counter;
    }

    void AlgorithmLogger::setThread_counter(int thread_counter) {
        AlgorithmLogger::thread_counter = thread_counter;
    }


}