//
// Created by steve on 18-1-17.
//

#ifndef ALGORITHMWORKFLOWTOOLS_ABSTRACTMSG_H
#define ALGORITHMWORKFLOWTOOLS_ABSTRACTMSG_H


class AbstractMsg {
public:
    AbstractMsg(double time):
            current_time_(time){

    }

private:
    double current_time_;


};


#endif //ALGORITHMWORKFLOWTOOLS_ABSTRACTMSG_H
