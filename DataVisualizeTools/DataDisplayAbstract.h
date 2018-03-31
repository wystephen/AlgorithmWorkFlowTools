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
// Created by steve on 18-3-29.
//

#ifndef ALGORITHMWORKFLOWTOOLS_DATAONLINEDISPLAY_H
#define ALGORITHMWORKFLOWTOOLS_DATAONLINEDISPLAY_H


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

namespace AWF {
    class DataDisplayAbstract {
    public:
        /**
         *
         * @param name
         * @param dim : number of line in the chart.
         * @param lable_list
         */
        DataDisplayAbstract(std::string name,
                            int dim,
                            std::vector<std::string> lable_list = {"x", "y", "z"}) {
            win_name_ = name;
            dim_ = dim;
            // use given label list or using number
            if (dim == lable_list.size()) {

                label_name_ = lable_list;
            } else {
                for (int i(0); i < dim; ++i) {
                    label_name_.push_back(std::to_string(i));
                }
            }

        }

        /**
         * Copy constructor function.
         * @param t
         */
        DataDisplayAbstract(DataDisplayAbstract &&t) {

            DataDisplayAbstract(t.win_name_, t.dim_, t.label_name_);
        }

        // display function.
        virtual void displayFunction() {
            std::cout << "display virtual" << std::endl;
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
         * @param stamp
         * @return
         */
        bool addDataVector(Eigen::VectorXd m_data,double stamp=-1.0e20) {
            assert(m_data.size() == dim_);

            {
                std::lock_guard<std::mutex> g(buffer_mutex_);
                Eigen::VectorXd modified_data(m_data.size()*2);
//                std::cout << m_data.transpose() << std::endl;
                for(int i(0);i<m_data.size();++i){
                    if(stamp<-1e19){

                        modified_data(i*2) = data_index_;
                    }else{
                        modified_data(i*2) = stamp;
                    }
                    modified_data(i*2+1) = m_data(i);

                }
//                input_buffer_.push_back(m_data);
                input_buffer_.push_back(modified_data);


            }
            data_index_++;

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

    protected:
        std::string win_name_; // display title and windows name
        int dim_;// dim of input data
        std::vector<std::string> label_name_; // name of serials name




        std::mutex buffer_mutex_;

        std::vector<Eigen::VectorXd> input_buffer_ = std::vector<Eigen::VectorXd>();// data.
        std::vector<double> input_index_ = std::vector<double>(); // index of data

        std::thread draw_thread_;// draw thread.

        std::atomic<bool> run_flag_;//run flag for draw thread.

        double sleep_time_ = 0.5;//sleep time (unit:sec).

        int data_index_ = 0;//data index
    };


}


#endif //ALGORITHMWORKFLOWTOOLS_DATAONLINEDISPLAY_H
