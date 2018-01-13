//
// Created by steve on 18-1-13.
//

#include "AlgorithmLogger.h"


AlgorithmLogger::AlgorithmLogger(){

}


AlgorithmLogger::AlgorithmLogger(const AlgorithmLogger&){

}


AlgorithmLogger& AlgorithmLogger::operator=(const AlgorithmLogger&){

}


//在此处初始化
AlgorithmLogger* AlgorithmLogger::instance = new AlgorithmLogger();
AlgorithmLogger* AlgorithmLogger::getInstance(){
    return instance;
}