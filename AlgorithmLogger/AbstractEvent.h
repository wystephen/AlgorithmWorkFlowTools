//
// Created by steve on 18-1-19.
//

#ifndef ALGORITHMWORKFLOWTOOLS_ABSTRACTEVENT_H
#define ALGORITHMWORKFLOWTOOLS_ABSTRACTEVENT_H

#include <iostream>
#include <thread>
#include <mutex>
#include <Eigen/Dense>

namespace AWF {
    class AbstractEvent {
    public:
        AbstractEvent(std::string event_name) :
                event_name_(event_name),
                event_time_stamp_(
                        double(std::chrono::duration_cast<std::chrono::microseconds>(
                                std::chrono::system_clock::now().time_since_epoch()
                        ).count()) / 1000000.0) {


        }

        /**
         * convert the event to string.
         * @return
         */
        std::string toString() {
            return "[" + std::string(std::to_string(event_time_stamp_))
                   + "]:" + event_name_;
        }

        bool setData(Eigen::MatrixXd m) {
            try {
                Eigen::IOFormat OctaveFmt(Eigen::StreamPrecision,
                                          0, ", ", ";\n", "", "", "[", "]");
                std::stringstream ss;
                ss << m.format(OctaveFmt);
//                ios>>data_string_;
                ss >> data_string_;
            } catch (std::exception &e) {
                std::cout << __FILE__
                          << ":"
                          << __LINE__
                          << ":"
                          << e.what()
                          << std::endl;
            }
        }


    protected:
        std::string frame_name_ = "empty";
        std::string event_name_ = "null";

        double event_time_stamp_ = 0.0;
        std::string data_string_ = "";

    };
}

#endif //ALGORITHMWORKFLOWTOOLS_ABSTRACTEVENT_H
