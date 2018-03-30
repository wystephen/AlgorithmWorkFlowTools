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
// Created by steve on 18-3-30.
//

#ifndef ALGORITHMWORKFLOWTOOLS_DATADISPLAY2D_H
#define ALGORITHMWORKFLOWTOOLS_DATADISPLAY2D_H

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
#include "DataDisplayAbstract.h"

namespace AWF {


    // 2d callback
    class vtk2DCallback : public vtkCommand {
    public:
        static vtk2DCallback *New() {
            vtk2DCallback *cb = new vtk2DCallback;
//            std::cout << "initialized: " << CName << std::endl;

            return cb;
        }

        /**
         *
         * @param eventId
         * @param callData
         */
        virtual void Execute(vtkObject *vtkNotUsed(caller), unsigned long eventId,
                             void *callData) {
            if(new_data_flag_.load()){
//                auto pop_d =
                {
                    std::lock_guard<std::mutex> g(buffer_mutex_);
//                    while (data_buffer_.size() > 0) {
//
//                        auto pop_d = data_buffer_[0];
//                        table_->InsertNextRow(pop_d);
//                        data_buffer_.pop_back();
//                    }
                    for(auto iter = data_buffer_.begin();iter!=data_buffer_.end();++iter)
                    {
                        std::cout << "..."<< std::endl;
                       table_->InsertNextRow(*iter);
                    }
                    data_buffer_.clear();
                    new_data_flag_.store(false);
                }

                for(int k(0);k<dim_;++k){


                    auto points = chart_->AddPlot(vtkChart::POINTS);
                    vtkPlot *line = chart_->AddPlot(vtkChart::LINE);

                    points->SetInputData(table_, k*2, k*2+1);
                    points->SetColor(k * 20, k * 20, k * 20);
                    points->SetWidth(1.0);
                    points->LegendVisibilityOff();
                    vtkPlotPoints::SafeDownCast(points)->SetMarkerStyle(vtkPlotPoints::CIRCLE);

                    line->SetInputData(table_, k-1, k);
                    line->SetColor(k /dim_/1.001, k /dim_/2.0, k /dim_/2.0);
                    line->SetWidth(1.0);
                }

            }

        }

        bool addData(Eigen::VectorXd v){
            auto dd = vtkSmartPointer<vtkVariantArray>::New();
            dd->Allocate(v.size());
            for(int i(0);i<v.size();++i){
                dd->SetValue(i,v(i));
            }
            {
                std::lock_guard<std::mutex> t(buffer_mutex_);
                data_buffer_.push_back(dd);

            }
            new_data_flag_.store(true);
            return true;
        }



        vtkSmartPointer<vtkChartXY> chart_;
        vtkSmartPointer<vtkTable> table_ = vtkSmartPointer<vtkTable>::New();
        vtkSmartPointer<vtkContextView> view_;
        std::string win_name_ = "default";
        int dim_ = 0;


        //data vector, flag and mutex
        std::vector<vtkSmartPointer<vtkVariantArray>> data_buffer_ =std::vector<vtkSmartPointer<vtkVariantArray>>();
        std::mutex buffer_mutex_;
        std::atomic<bool> new_data_flag_;


    };

    class DataDisplay2D : public DataDisplayAbstract {
    public:
        DataDisplay2D(const std::string name,
                      int dim,
                      std::vector<std::string> lable_list = {"x", "y", "z"}) :
                DataDisplayAbstract(name, dim, lable_list) {

            draw_call_ = vtkSmartPointer<vtk2DCallback>::New();
            draw_call_->win_name_ = win_name_;
            draw_call_->dim_ = dim;

            //initialize table
            draw_call_->table_ = vtkSmartPointer<vtkTable>::New();

            for (int i(0); i < label_name_.size(); ++i) {
                vtkSmartPointer<vtkFloatArray> tx = vtkSmartPointer<vtkFloatArray>::New();
                vtkSmartPointer<vtkFloatArray> ty = vtkSmartPointer<vtkFloatArray>::New();
                tx->SetName("X axis");
                ty->SetName(label_name_[i].c_str());
                draw_call_->table_->AddColumn(tx);
                draw_call_->table_->AddColumn(ty);
            }


            // initial view
            draw_call_->view_ = vtkSmartPointer<vtkContextView>::New();
            draw_call_->view_->GetRenderer()->SetBackground(1.0, 1.0, 1.0);
            draw_call_->view_->GetRenderWindow()->SetSize(500, 700);
            draw_call_->view_->GetRenderWindow()->SetWindowName(name.c_str());


            // initial chart
            draw_call_->chart_ = vtkSmartPointer<vtkChartXY>::New();
            draw_call_->chart_->SetShowLegend(true);
            draw_call_->view_->GetScene()->AddItem(draw_call_->chart_);


            //sign up to receive Event
            draw_call_->view_->GetInteractor()->Initialize();
            draw_call_->view_->GetInteractor()->AddObserver(vtkCommand::RenderEvent, draw_call_,0.1);

            std::thread t([&]() {
                draw_call_->view_->GetInteractor()->Start();
            });
            t.detach();

            draw_thread_ = std::thread(&DataDisplay2D::displayFunction, this);
            draw_thread_.detach();





        }

        void displayFunction() {

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
                        draw_call_->addData(*iter);
                    }
                    input_buffer_.clear();

                }







            }


        }

        vtkSmartPointer<vtk2DCallback> draw_call_;

    };

}


#endif //ALGORITHMWORKFLOWTOOLS_DATADISPLAY2D_H
