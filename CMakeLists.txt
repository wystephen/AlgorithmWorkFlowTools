cmake_minimum_required(VERSION 3.9)
project(AlgorithmWorkFlowTools)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_BUILD_TOOL Release)
#set(CMAKE_BUILD_TOOL Debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -O3 -g  -lpthread")


#Eigen
find_package(Eigen3 REQUIRED)


LIST(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake_modules)
