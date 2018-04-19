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

//#include "AlgorithmLogger/Event.h"
//#include "AlgorithmLogger/Event.cpp"

int main() {
    std::cout << "logger" << std::endl;

    double start_time = TimeStamp::now();
    AWF::AlgorithmLogger *logger_ptr = AWF::AlgorithmLogger::getInstance();
    std::cout.precision(15);


    std::random_device rd;
    std::mt19937 random_engine(rd());
    std::uniform_int_distribution<> uni_dis(1, 10);
    auto trace_3d_f = [&](std::string group_name, std::string trace_name) {
        int off_set = uni_dis(random_engine);
        for (int i(0); i < 100000; ++i) {
            Eigen::Vector3d trace_v(std::sin(double(i / 100.0 + off_set)),
                                    std::cos(double(i / 100.0 + off_set)),
                                    i / 100);
            logger_ptr->addTrace3dEvent(group_name, trace_name, trace_v);


        }
    };

    auto trace_2d_f = [&](std::string group_name, std::string trace_name) {
        int off_set = uni_dis(random_engine);
        for (int i(0); i < 100000; ++i) {
            Eigen::Vector2d trace_v(std::sin(double(i / 100.0 + off_set)), i);
            logger_ptr->addTraceEvent(group_name, trace_name, trace_v);
        }
    };

    auto plot_f = [&](std::string group_name, std::string trace_name) {
        int off_set = uni_dis(random_engine);
        for (int i(0); i < 100000; ++i) {
            Eigen::Matrix2d tm;
            tm(0, 0) = std::sin(i / 1000.0 + off_set);
            tm(0, 1) = std::cos(i / 1000.0 + off_set) + std::sin(i / 1000.0 + off_set);
            tm(1, 0) = std::cos(i / 1000.0 + off_set);
            tm(1, 1) = std::cos(i / 1000.0 + off_set) - std::sin(i / 1000.0 + off_set);
            logger_ptr->addPlotEvent(group_name, trace_name, tm);

            logger_ptr->addPlotEvent(group_name,trace_name+"1",tm(0,1));
            logger_ptr->addPlotEvent(group_name,trace_name+"2",tm(1,0));
        }
    };

    std::thread t_trace3_1(trace_3d_f, "ga", "ta");
    std::thread t_trace3_2(trace_3d_f, "ga", "tb");
    std::thread t_trace3_3(trace_3d_f, "gb", "ta");
    std::thread t_trace3_4(trace_3d_f, "gb", "tb");
    t_trace3_1.detach();
    t_trace3_2.detach();
    t_trace3_3.detach();
    t_trace3_4.detach();


    std::thread t_trace2_1(trace_2d_f, "ga", "ta");
    std::thread t_trace2_2(trace_2d_f, "ga", "tb");
    std::thread t_trace2_3(trace_2d_f, "gb", "ta");
    std::thread t_trace2_4(trace_2d_f, "gb", "tb");
    t_trace2_1.detach();
    t_trace2_2.detach();
    t_trace2_3.detach();
    t_trace2_4.detach();

    std::thread t_plot2_1(plot_f, "ga", "ta");
    std::thread t_plot2_2(plot_f, "ga", "tb");
    std::thread t_plot2_3(plot_f, "gb", "ta");
    std::thread t_plot2_4(plot_f, "gb", "tb");
    t_plot2_1.join();
    t_plot2_2.join();
    t_plot2_3.join();
    t_plot2_4.join();

    sleep(1);
    std::cout << "logger counter : "
              << logger_ptr->getThread_counter() << std::endl;
    double end_time = TimeStamp::now();
    std::cout << "set event time:" << end_time-start_time << std::endl;


    double start_save_time = TimeStamp::now();

    logger_ptr->outputAllEvent(true);
    double end_save_time = TimeStamp::now();
    std::cout << "total time:" << end_save_time - start_save_time << std::endl;


//    int k(0);
//    std::cin >> k;


}