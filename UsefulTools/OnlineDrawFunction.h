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
// Created by steve on 18-3-27.
//

#ifndef ALGORITHMWORKFLOWTOOLS_ONLINEDRAWFUNCTION_H
#define ALGORITHMWORKFLOWTOOLS_ONLINEDRAWFUNCTION_H

#include "matplotlibcpp.h"
#include <iostream>
#include <thread>
#include <Eigen/Dense>
#include <mutex>
#include <atomic>
#include <chrono>

namespace AWF {

    /**
     * Online draw Interface
     */
    class OnlineDrawInterface {
    public:
        /**
         * Constructor function.
         * @param win_name
         */
        OnlineDrawInterface(std::string win_name, int dim) :
                win_name_(win_name), dim_(dim) {


        }


        bool addDataMatrix(Eigen::MatrixXd m_data) {
//            Eigen::Map<Eigen::VectorXd> vt(m_data.data(), m_data.size());

            return true;

        }

        bool addDataVector(Eigen::VectorXd m_data) {

            {
                std::lock_guard<std::mutex> g(buffer_mutex_);
                input_buffer_.push_back(m_data);
            }

            return true;

        }

        /**
         * stop
         * @return
         */
        bool stopDataVector() {
//            run_flag_ = false;

        }

        /**
         * plot function for display main function,
         */
        void plot_function() {
            std::vector<std::vector<double>> draw_vec;
            for (int i(0); i < dim_; ++i) {
                draw_vec.push_back(std::vector<double>());
            }


        }


    private:
        std::string win_name_;
        int dim_;


        std::mutex buffer_mutex_;

        std::vector<Eigen::VectorXd> input_buffer_ = std::vector<Eigen::VectorXd>();
        std::thread draw_thread_;

//        std::atomic<bool> run_flag_ = true;

        double sleep_time_ = 0.5;
    };


}

#endif //ALGORITHMWORKFLOWTOOLS_ONLINEDRAWFUNCTION_H
