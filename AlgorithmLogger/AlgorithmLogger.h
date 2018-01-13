//
// Created by steve on 18-1-13.
//

#ifndef ALGORITHMWORKFLOWTOOLS_ALGORITHMLOGGER_H
#define ALGORITHMWORKFLOWTOOLS_ALGORITHMLOGGER_H

#include <iostream>

#include <thread>
#include <mutex>

/**
 * Singleton !!!!!
 */

class AlgorithmLogger{
public:
    static AlgorithmLogger* getInstance();

protected:
    static std::mutex instance_mutex_;// mutex for instance....

private:
    AlgorithmLogger();

    /**
     * Set constructor function as private, avoid unnecessary constructor.
     */
    AlgorithmLogger(const AlgorithmLogger&);
    /**
     * Let the operator = as private, preserve it from unacceptable deep copy.
     * @return
     */
    AlgorithmLogger& operator=(const AlgorithmLogger&);

    static AlgorithmLogger* instance;
};


#endif //ALGORITHMWORKFLOWTOOLS_ALGORITHMLOGGER_H
