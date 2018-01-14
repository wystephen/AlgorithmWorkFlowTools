//
// Created by steve on 18-1-14.
//

#include "Event.h"

namespace AWF{
 Event::Event(std::string name) {
     event_name_ = name;
     event_time_stamp_ = std::chrono::duration(std::chrono::system_clock::now().);
 }

}