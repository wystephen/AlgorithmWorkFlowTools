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

        }

        bool initialize(Eigen::Vector3d background_color,
                        Eigen::Vector2d win_size
        ) {

        }

        vtkSmartPointer<vtkChartXY> chart_;
        vtkSmartPointer<vtkTable> table_ = vtkSmartPointer<vtkTable>::New();
        vtkSmartPointer<vtkContextView> view_;
        std::string win_name_ = "default";


        //data vector, flag and mutex


    };

    class DataDisplay2D : public DataDisplayAbstract {
    public:
        DataDisplay2D(const std::string name,
                      int dim,
                      std::vector<std::string> lable_list = {"x", "y", "z"}) :
                DataDisplayAbstract(name, dim, lable_list) {

            draw_call_ = vtkSmartPointer<vtk2DCallback>::New();
            draw_call_->win_name_ = win_name_;

            //initialize table
            draw_call_->table_ = vtkSmartPointer<vtkTable>::New();

            for (int i(0); i < label_name_.size(); ++i) {
                vtkSmartPointer<vtkFloatArray> tx = vtkSmartPointer<vtkDoubleArray>::New();
                vtkSmartPointer<vtkFloatArray> ty = vtkSmartPointer<vtkDoubleArray>::New();
                tx->SetName(label_name_[i].c_str());
                ty->SetName(label_name_[i].c_str());
                draw_call_->table_->AddColumn(tx);
                draw_call_->table_->AddColumn(ty);
            }


            // initial view
            draw_call_->view_ = vtkSmartPointer<vtkContextView>::New();
            draw_call_->view_->SetBackground(1.0, 1.0, 1.0);
            draw_call_->view_->SetSize(500, 700);


            // initial chart
            draw_call_->chart_ = vtkSmartPointer<vtkChartXY>::New();
            draw_call_->chart_->SetShowLegend(true);
            draw_call_->view_->AddItem(draw_call_->chart_);


            //sign up to receive Event
            draw_call_->view_->GetInteractor()->Initialize();
            draw_call_->view_->GetInteractor()->AddObserver(vtkCommand::RenderEvent, draw_call_);

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
                        for (int j(0); j < draw_vec.size(); ++j) {
                            draw_vec[j].push_back((*iter)(j));
                        }
                    }
                    input_buffer_.clear();

                }

                // update graph


                for (int j(0); j < draw_vec.size(); ++j) {
//                    plt::named_plot(std::to_string(j), draw_vec[j], "-+");
                }



            }


        }

        vtkSmartPointer<vtk2DCallback> draw_call_;

    };

}


#endif //ALGORITHMWORKFLOWTOOLS_DATADISPLAY2D_H
