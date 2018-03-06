//
// Created by steve on 18-1-21.
//

#ifndef ALGORITHMWORKFLOWTOOLS_ERRORTOOLS_H
#define ALGORITHMWORKFLOWTOOLS_ERRORTOOLS_H
#include <iostream>
#include <string>

#define ERROR_MSG_FLAG(s) std::string(__FILE__)+":"+std::to_string(__LINE__)+":"+std::string(__FUNCTION__)+":"+s

#endif //ALGORITHMWORKFLOWTOOLS_ERRORTOOLS_H
