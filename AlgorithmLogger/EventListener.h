//
// Created by steve on 18-1-14.
//

#ifndef ALGORITHMWORKFLOWTOOLS_EVENTLISTENER_H
#define ALGORITHMWORKFLOWTOOLS_EVENTLISTENER_H

namespace AWF {

#include "Event.h"
//    template<E>
    class EventListener {
        /**
         * Must defined in sub-class.
         * @param event
         */
        void virtual receivedEvent(Event event);

    };

}


#endif //ALGORITHMWORKFLOWTOOLS_EVENTLISTENER_H
