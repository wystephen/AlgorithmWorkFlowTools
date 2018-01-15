//
// Created by steve on 18-1-13.
//

#include "AlgorithmLogger.h"

namespace AWF {

    AlgorithmLogger::AlgorithmLogger() {

    }


    AlgorithmLogger::AlgorithmLogger(const AlgorithmLogger &) {

    }


    AlgorithmLogger &AlgorithmLogger::operator=(const AlgorithmLogger &) {

    }


    AlgorithmLogger *AlgorithmLogger::instance = nullptr; //new AlgorithmLogger();


    AlgorithmLogger *AlgorithmLogger::getInstance() {
        if (instance == nullptr) {
//            instance_mutex_.lock();
            if (instance == nullptr) {
                instance = new AlgorithmLogger();
            }
//            instance_mutex_.unlock();

        }
        return instance;
    }
}