//
// Created by steve on 18-1-19.
//

#ifndef ALGORITHMWORKFLOWTOOLS_ABSTRACTEVENT_H
#define ALGORITHMWORKFLOWTOOLS_ABSTRACTEVENT_H

#include <iostream>
#include <thread>
#include <mutex>

namespace AWF{
    class AbstractEvent{
    public:
        AbstractEvent(std::string name): event_name_(name),
                                    event_time_stamp_(
                                            double(std::chrono::duration_cast<std::chrono::microseconds>(
                                                    std::chrono::system_clock::now().time_since_epoch()
                                            ).count()) / 1000000.0) {


        }

        /**
         * convert the event to string.
         * @return
         */
        virtual std::string toString() {
            return "["+ std::string(std::to_string(event_time_stamp_))+"]:"+event_name_;
        }

    protected:
        std::string event_name_ = "null";
        double event_time_stamp_ = 0.0;

    };
}

#endif //ALGORITHMWORKFLOWTOOLS_ABSTRACTEVENT_H
