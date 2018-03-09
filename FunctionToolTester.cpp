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
// Created by steve on 18-2-6.
//

#include <iostream>
#include "MathTools/FunctionAbstract.h"
#include "MathTools/SimpleTestFunction.h"

#include <Eigen/Dense>


int main() {
    std::cout << " math tool function abstract" << std::endl;

//    auto f = AWF::FunctionAbstract<4,2>();
//    f(10,10,10);
    std::cout.precision(20);
    auto f = AWF::SimpleTestFunction();
    Eigen::MatrixXd xy(2, 1);
    xy = Eigen::Vector2d(10.0, 1.0);
    Eigen::MatrixXd zt(2, 1);
    zt = Eigen::Vector2d(0.1, 0.01);
    std::cout << f.compute(xy, zt) << std::endl;

    std::vector<Eigen::MatrixXd> jac_vec;
    std::vector<Eigen::MatrixXd>  p_vec;
//    p_vec.push_back(xy);
//    p_vec.push_back(zt);
    jac_vec = f.derivative(xy,zt);
    for(auto iter = jac_vec.begin();iter!=jac_vec.end();++iter){
        std::cout << *iter << std::endl;
    }


    return 0;
}

