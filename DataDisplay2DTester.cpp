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


#include <iostream>
#include <Eigen/Dense>

#include <thread>

#include "AWF.h"

#include "DataVisualizeTools/DataDisplay2D.h"
#include "DataVisualizeTools/DataDisplayAbstract.h"

int main() {

//    vtkSmartPointer<AWF::vtk2DCallback> c1 = vtkSmartPointer<AWF::vtk2DCallback>::New();
//    vtkSmartPointer<AWF::vtk2DCallback> c2= vtkSmartPointer<AWF::vtk2DCallback>::New();
//    c1->win_name_ = "c1";
//    c2->win_name_ = "c2";



    AWF::OnlineDrawInterface odi("test_1", 3);
    AWF::DataDisplay2D odim("matrix", 6);

    double scale = 10000.0;
    auto f1 = [&](double x) -> double {
        return sin(x / scale);

    };

    auto f2 = [&](double x) -> double {
        return cos(x / scale);

    };

    auto f3 = [&](double x) -> double {
        return sin(x / scale) + cos(x / scale);

    };

    for (int i(0); i < 1000000; ++i) {
        Eigen::Vector3d tv(f1(i), f2(i), f3(i));
//        std::cout << tv.transpose() << std::endl;
        Eigen::MatrixXd m(3, 2);
        m(0, 0) = f1(i);
        m(0, 1) = f2(i);
        m(1, 0) = f1(i) + f2(i);
        m(1, 1) = f1(i) - f2(i);
        m(2, 0) = -1.0 * m(1, 1);
        m(2, 1) = f1(i) + f2(i) * f1(i);
        odi.addDataVector(tv);
        odim.addDataMatrix(m);
        usleep(10);
    }
    std::cin >> scale;
    return 0;

}
