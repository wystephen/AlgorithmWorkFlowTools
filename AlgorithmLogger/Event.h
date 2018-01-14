//
// Created by steve on 18-1-14.
//

#ifndef ALGORITHMWORKFLOWTOOLS_EVENT_H
#define ALGORITHMWORKFLOWTOOLS_EVENT_H


#include <iostream>

#include <chrono>

namespace AWF {
    class Event {
    public:
        Event(std::string name);

    protected:
        std::string event_name_ = "null";
        double event_time_stamp_ = 0.0;


    };

}


#endif //ALGORITHMWORKFLOWTOOLS_EVENT_H
