//
// Created by steve on 18-1-17.
//

#ifndef ALGORITHMWORKFLOWTOOLS_ABSTRACTMSG_H
#define ALGORITHMWORKFLOWTOOLS_ABSTRACTMSG_H

#include <iostream>

namespace AWF {
    class AbstractMsg {
    public:
        AbstractMsg(double time) :
                current_time_(time) {

        }

        /**
         *
         * @return
         */
        virtual std::string toString() {
            return std::string(std::to_string(current_time_));

        };

    protected:
        double current_time_;


    };


    class StringMsg:public AbstractMsg{
    public:
        StringMsg(double time):public AbstractMsg(time);

    public:


    };

}


#endif //ALGORITHMWORKFLOWTOOLS_ABSTRACTMSG_H
