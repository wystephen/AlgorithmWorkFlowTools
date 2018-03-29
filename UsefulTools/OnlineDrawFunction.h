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


    class vtkTimerCallback : public vtkCommand {
    public:
        static vtkTimerCallback *New() {
            vtkTimerCallback *cb = new vtkTimerCallback;
            cb->TimerCount = 0;

            // Create a table with some points in it...



            return cb;
        }

        virtual void Execute(vtkObject *vtkNotUsed(caller), unsigned long eventId,
                             void *callData) {
            if (vtkCommand::ConfigureEvent != eventId && this->TimerCount < 500) {
                auto chart = this->chart_;
                vtkPlot *points = chart->AddPlot(vtkChart::POINTS);
                ++this->TimerCount;
                int j = this->TimerCount + numPoints - 1;
                if (j < numPoints * 10) {

                    chart->ClearPlots();
                    double *tmp_d = new double[4];
                    tmp_d[0] = j * inc;
                    tmp_d[1] = cos(j * inc);
                    tmp_d[2] = sin(j * inc);
                    tmp_d[3] = sin(j * inc) - cos(j * inc);
                    auto *dd = vtkVariantArray::New();
                    dd->Allocate(4);
                    dd->Allocate(4);
                    dd->SetValue(0, tmp_d[0]);
//                dd->
                    dd->SetValue(1, tmp_d[1]);
                    dd->SetValue(2, tmp_d[2]);
                    dd->SetValue(3, tmp_d[3]);
                    table->InsertNextRow(dd);


                    for (int k(1); k < 4; ++k) {

                        points = chart->AddPlot(vtkChart::POINTS);
                        vtkPlot *line = chart->AddPlot(vtkChart::LINE);

                        points->SetInputData(table, 0, k);
                        points->SetColor(k * 20, k * 20, k * 20);
                        points->SetWidth(1.0);
                        points->LegendVisibilityOff();
                        vtkPlotPoints::SafeDownCast(points)->SetMarkerStyle(vtkPlotPoints::CIRCLE);

                        line->SetInputData(table, 0, k);
                        line->SetColor(k * 20, k * 20, k * 20);
                        line->SetWidth(1.0);
                    }
                    std::cout << "aaa" << std::endl;


                }

//            cout << this->TimerCount << endl;
            }
//        return;
        }

        vtkSmartPointer<vtkChartXY> chart_;
        int numPoints = 40;
        float inc = 7.5 / (numPoints - 1);
        vtkSmartPointer<vtkTable> table =
                vtkSmartPointer<vtkTable>::New();
        vtkSmartPointer<vtkContextView> view;
    private:
        int TimerCount;

    };


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
