//
// Created by steve on 18-1-14.
//

#ifndef ALGORITHMWORKFLOWTOOLS_EVENT_H
#define ALGORITHMWORKFLOWTOOLS_EVENT_H


#include <iostream>

#include <chrono>


#include "AbstractMsg.h"

namespace AWF {
    class Event {
    public:
        Event(std::string name) :
                event_name_(name),
                event_time_stamp_(
                        double(std::chrono::duration_cast<std::chrono::microseconds>(
                                std::chrono::system_clock::now().time_since_epoch()
                        ).count()) / 1000000.0) ,
        {


        }

        virtual std::string toString(){
            return std::string(std::to_string(event_time_stamp_));
        }

    protected:
        std::string event_name_ = "null";
        double event_time_stamp_ = 0.0;



    };



}


#endif //ALGORITHMWORKFLOWTOOLS_EVENT_H
