//
// Created by steve on 18-1-14.
//

#ifndef ALGORITHMWORKFLOWTOOLS_EVENT_H
#define ALGORITHMWORKFLOWTOOLS_EVENT_H


#include <iostream>

#include <chrono>


namespace AWF {
    template <typename T>
    class Event {
    public:
        Event(std::string name) :
                event_name_(name),
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

        /**
         * set data based on type name.
         * @param d
         * @return
         */
        bool setData(T d){
            data_ = d;
            return true;
        }

    protected:
        std::string event_name_ = "null";
        double event_time_stamp_ = 0.0;
        T data_;


    };

    class StringEvent : public Event<std::string> {
    public:
        StringEvent::StringEvent(const std::string &name) : Event("stringEvent_" + name) {}


        virtual std::string toString() {
            return ((Event*)this)->toString()+":"+data_;
        }


    };


}


#endif //ALGORITHMWORKFLOWTOOLS_EVENT_H
