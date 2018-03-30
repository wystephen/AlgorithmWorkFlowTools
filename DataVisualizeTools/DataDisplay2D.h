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
    template<std::string Name>
    class vtk2DCallback : public vtkCommand {
    public:
        static vtk2DCallback *New() {
            vtk2DCallback *cb = new vtk2DCallback;

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
        ){

        }

        vtkSmartPointer<vtkChartXY> chart_;
        vtkSmartPointer<vtkTable> table_ = vtkSmartPointer<vtkTable>::New();
        vtkSmartPointer<vtkContextView> view_;


    };

    class DataDisplay2D : public DataDisplayAbstract {
    public:
        DataDisplay2D(std::string name,
                      int dim,
                      std::vector<std::string> lable_list = {"x", "y", "z"}):
                DataDisplayAbstract(name,dim,lable_list) {


        }

    };

}


#endif //ALGORITHMWORKFLOWTOOLS_DATADISPLAY2D_H
