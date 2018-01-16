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
        static std::once_flag oc;// call once local static variable.
        // call once , to avoid some complexity process of multi-thread DCLP.
        std::call_once(oc,[&]{

            if(instance== nullptr){
                instance = new AlgorithmLogger();
            }
        });
        return instance;
    }
}