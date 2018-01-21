//
// Created by steve on 18-1-21.
//

#ifndef ALGORITHMWORKFLOWTOOLS_USEFULTOOLS_H
#define ALGORITHMWORKFLOWTOOLS_USEFULTOOLS_H


#include <iostream>
#include <chrono>


#include <time.h>
#include <time_stamp.h>

namespace AWF {
    std::string getFormatTime() {
        std::chrono::system_clock::time_point tt =
                std::chrono::system_clock::now();
        auto tm = std::localtime(reinterpret_cast<const time_t *>(std::chrono::system_clock::to_time_t(tt)));
        return "[" + std::to_string(tm->tm_year) + "-"
               + std::to_string(tm->tm_mon) + "-"
               + std::to_string(tm->tm_mday) + "-"
               + std::to_string(tm->tm_hour) + ":"
               + std::to_string(tm->tm_min) + ":"
               + std::to_string(tm->tm_sec) + "]";


    }

    double getDoubleSecondTime() {
        auto tt = std::chrono::system_clock::now();
        auto t_nanosec = std::chrono::duration_cast<std::chrono::nanoseconds>(tt.time_since_epoch());

        return (double(t_nanosec.count()) * 1e-9);
    }

}

#endif //ALGORITHMWORKFLOWTOOLS_USEFULTOOLS_H
