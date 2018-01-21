//
// Created by steve on 18-1-19.
//

#ifndef ALGORITHMWORKFLOWTOOLS_ABSTRACTEVENT_H
#define ALGORITHMWORKFLOWTOOLS_ABSTRACTEVENT_H

#include <iostream>
#include <thread>
#include <mutex>
#include <map>
#include <Eigen/Dense>

#include "../UsefulTools/ErrorTools.h"

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
                   + "]:" + event_name_ + ":" +
                   data_string_;
        }

        /**
         * set Data according to matrix.
         * @param m
         * @return
         */
        bool setData(Eigen::MatrixXd m) {
            try {
                Eigen::IOFormat OctaveFmt(Eigen::StreamPrecision,
                                          0, ", ", ";\n", "", "", "[", "]");
                std::stringstream ss;
                ss << "{";
                ss << m.format(OctaveFmt);
                ss << "}";

                data_string_ = ss.str();
                return true;
            } catch (std::exception &e) {
                std::cout << __FILE__
                          << ":"
                          << __LINE__
                          << ":"
                          << e.what()
                          << std::endl;
                return false;
            }
        }


        /**
         *
         * @tparam K type of key
         * @tparam V type of value
         * @param m  map(k->v)
         * @return
         */
        template<typename K, typename V>
        bool setData(std::map<K, V> m) {
            try {
                std::stringstream ss;
                ss << "{";
                for (auto it = m.begin(); it++; it != m.end()) {
                    ss << it.first;
                    ss << ":";
                    ss << it.second;
                    ss << ",";
                }

                ss << "}";
//                ss>>data_string_;
                data_string_ = ss.str();
                return true;

            } catch (std::exception &e) {
                std::cout << __FILE__
                          << ":"
                          << __LINE__
                          << ":"
                          << e.what()
                          << std::endl;

            }

        };


    protected:
        std::string frame_name_ = "empty";
        std::string event_name_ = "null";

        double event_time_stamp_ = 0.0;
        std::string data_string_ = "";

    };
}

#endif //ALGORITHMWORKFLOWTOOLS_ABSTRACTEVENT_H
