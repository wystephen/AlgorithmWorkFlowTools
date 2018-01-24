//
// Created by steve on 18-1-13.
//

#include "AlgorithmLogger.h"

namespace AWF {


    AlgorithmLogger::AlgorithmLogger(const AlgorithmLogger &) {

    }


    AlgorithmLogger &AlgorithmLogger::operator=(const AlgorithmLogger &) {

    }


//    static AlgorithmLogger *AlgorithmLogger::instance = nullptr; //new AlgorithmLogger();

    static AlgorithmLogger *AlgorithmLogger::getInstance() {
        static std::once_flag oc;// call once local static variable.
        // call once , to avoid some complexity process of multi-thread DCLP.
        std::call_once(oc, [&] {

            if (instance == nullptr) {
                instance = new AlgorithmLogger();
                out_thread_ptr_ = new std::thread(outputThread,
                                                  queue_mutex_, event_queue_);
                out_thread_ptr_->detach();
            }
        });
        return instance;
    }


}