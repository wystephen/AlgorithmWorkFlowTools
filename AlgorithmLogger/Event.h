//
// Created by steve on 18-1-14.
//

#ifndef ALGORITHMWORKFLOWTOOLS_EVENT_H
#define ALGORITHMWORKFLOWTOOLS_EVENT_H


#include <iostream>

#include <chrono>
#include "AbstractEvent.h"


namespace AWF {
    template<typename T>
    class Event : public AbstractEvent {
    public:
        Event(std::string name) : AbstractEvent(name),
        data_(){
        }


        /**
         * set data based on type name.
         * @param d
         * @return
         */
        bool setData(T d) {
            data_ = d;
            return true;
        }

        /**
         * get data
         * @return
         */
        T getData_() const {
            return data_;
        }

    protected:
        T data_;


    };

    class StringEvent : public Event<std::string> {
    public:
        StringEvent::StringEvent(const std::string &name) : Event("stringEvent_" + name) {}


        virtual std::string toString() {
            return ((AbstractEvent *) this)->toString() + ":" + data_;
        }


    };


}


#endif //ALGORITHMWORKFLOWTOOLS_EVENT_H
