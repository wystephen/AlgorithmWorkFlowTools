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

#include <vtkVersion.h>
#include <vtkSmartPointer.h>

#include <vtkChartXY.h>
#include <vtkContextScene.h>
#include <vtkContextView.h>
#include <vtkFloatArray.h>
#include <vtkPlotPoints.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkTable.h>
#include <vtkAutoInit.h>
#include <vtkVariantArray.h>

namespace plt=matplotlibcpp;
namespace AWF {


    /**
     * Online draw Interface
     */
    class OnlineDrawInterface {
    private:


    public:
        /**
         * Constructor function.
         * @param win_name
         */
        OnlineDrawInterface(std::string win_name, int dim) :
                win_name_(win_name), dim_(dim) {
            run_flag_.store(true);

            draw_thread_ = std::thread([&]() {
                // initial vector
                std::vector<std::vector<double>> draw_vec;
                for (int i(0); i < dim_; ++i) {
                    draw_vec.push_back(std::vector<double>());
                }
                plt::figure();

                //
                while (run_flag_.load()) {
                    // load data from buffer
                    {
                        std::lock_guard<std::mutex> g(buffer_mutex_);

                        for (auto iter = input_buffer_.begin();
                             iter != input_buffer_.end();
                             ++iter) {
                            for (int j(0); j < draw_vec.size(); ++j) {
                                draw_vec[j].push_back((*iter)(j));
                            }
                        }
                        input_buffer_.clear();

                    }

                    // update graph

                    plt::clf();

                    for (int j(0); j < draw_vec.size(); ++j) {
                        plt::named_plot(std::to_string(j), draw_vec[j], "-+");
                    }

                    plt::title(win_name_);
                    plt::legend();
                    plt::grid(true);
                    plt::pause(0.1);


                }


            });
            draw_thread_.detach();

        }

        /**
         * Copy constructor function.
         * @param t
         */
        OnlineDrawInterface(OnlineDrawInterface &&t) {

            OnlineDrawInterface(t.win_name_, t.dim_);
        }


        /**
         *
         * @param m_data
         * @return
         */
        bool addDataMatrix(Eigen::MatrixXd m_data) {
            Eigen::Map<Eigen::VectorXd> vt(m_data.data(), m_data.size());

            return addDataVector(vt);

        }

        /**
         * add vector
         * @param m_data
         * @return
         */
        bool addDataVector(Eigen::VectorXd m_data) {
            assert(m_data.size() == dim_);

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
            run_flag_.store(false);
            return false;

        }


    private:
        std::string win_name_;
        int dim_;


        std::mutex buffer_mutex_;

        std::vector<Eigen::VectorXd> input_buffer_ = std::vector<Eigen::VectorXd>();
        std::thread draw_thread_;

        std::atomic<bool> run_flag_;

        double sleep_time_ = 0.5;
    };


}

#endif //ALGORITHMWORKFLOWTOOLS_ONLINEDRAWFUNCTION_H
