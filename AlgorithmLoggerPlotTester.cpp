/** 
                   _ooOoo_ 
                  o8888888o 
                  88" . "88 
                  (| -_- |) 
                  O\  =  /O 
               ____/`---'\____ 
             .'  \\|     |//  `. 
            /  \\|||  :  |||//  \ 
           /  _||||| -:- |||||-  \ 
           |   | \\\  -  /// |   | 
           | \_|  ''\---/''  |   | 
           \  .-\__  `-`  ___/-. / 
         ___`. .'  /--.--\  `. . __ 
      ."" '<  `.___\_<|>_/___.'  >'"". 
     | | :  `- \`.;`\ _ /`;.`/ - ` : | | 
     \  \ `-.   \_ __\ /__ _/   .-` /  / 
======`-.____`-.___\_____/___.-`____.-'====== 
                   `=---=' 
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ 
         佛祖保佑       永无BUG 
*/
//
// Created by steve on 18-3-31.
//


#include <iostream>

#include <thread>
#include <mutex>

#include <chrono>

#include <cmath>

#include <random>

#include "AlgorithmLogger/AlgorithmLogger.h"
#include "AlgorithmLogger/AlgorithmLogger.cpp"

#include "AlgorithmLogger/Event.h"
#include "AlgorithmLogger/Event.cpp"

int main() {
    std::cout << "logger" << std::endl;

    AWF::AlgorithmLogger *logger_ptr = AWF::AlgorithmLogger::getInstance();
    std::cout.precision(15);


    std::random_device rd;
    auto random_engine = std::mt19937_64(rd);
    std::uniform_int_distribution<> uni_dis(1,10);
    auto trace_3d_f = [&](std::string group_name, std::string trace_name) {
        int off_set = uni_dis(random_engine);
        for (int i(0); i < 10000; ++i) {
            Eigen::Vector3d trace_v(std::sin(double(i/100.0+off_set)),
                                    std::cos(double(i/100.0+off_set)),
                                    i/100);
            logger_ptr->addTrace3dEvent(group_name,trace_name,trace_v);

        }
    };

    auto trace_2d_f = [&](std::string group_name, std::string trace_name){
        int off_set = uni_dis(random_engine);
        for(int i(0);i<10000;++i){
            Eigen::Vector2d trace_v(std::sin(double(i/100.0+off_set)),i);
            logger_ptr->addTraceEvent(group_name,trace_name,trace_v);
        }
    };

    auto plot_f = [&](std::string group_name, std::string trace_name){
        int off_set = uni_dis(random_engine);
        for(int i(0);i<10000;++i){
            Eigen::Matrix4d tm;
            tm(0,0) = std::sin(i/1000.0+off_set);
            tm(0,1) = std::cos(i/1000.0+off_set)+std::sin(i/1000.0+off_set);
            tm(1,0) = std::cos(i/1000.0+off_set);
            tm(1,1) = std::cos(i/1000.0+off_set)-std::sin(i/1000.0+off_set);
            logger_ptr->addPlotEvent(group_name,trace_name,tm);
        }
    };


    sleep(1);
    std::cout << "logger counter : "
              << logger_ptr->getThread_counter() << std::endl;
    logger_ptr->outputAllEvent();


    int k(0);
    std::cin >> k;


}