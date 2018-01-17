//
// Created by steve on 18-1-14.
//

#ifndef ALGORITHMWORKFLOWTOOLS_EVENT_H
#define ALGORITHMWORKFLOWTOOLS_EVENT_H


#include <iostream>

#include <chrono>

namespace AWF {
    template<typename MsgType>
    class Event {
    public:
        Event(std::string name) : msg_(),
                                  event_name_(name),
                                  event_time_stamp_(double(std::chrono::duration_cast<std::chrono::microseconds>(
                                          std::chrono::system_clock::now().time_since_epoch()
                                  ).count()) / 1000000.0) {

            std::cout.precision(20);
            std::cout <<
                      double(
                              std::chrono::duration_cast<std::chrono::microseconds>(
                                      std::chrono::system_clock::now().time_since_epoch()
                              ).count()
                      ) / 1000000.0
                      << std::endl;

        }

//    protected:
        std::string event_name_ = "null";
        double event_time_stamp_ = 0.0;

        MsgType msg_;


    };

}


#endif //ALGORITHMWORKFLOWTOOLS_EVENT_H
