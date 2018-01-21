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
// Created by steve on 18-1-13.
//


//#define CATCH_CONFIG_MAIN
//#include "catch.hpp"
#include <Eigen/Dense>

#include "ExtentedIO/FileReader.h"
#include "ExtentedIO/FileReader.cpp"

int main(){
//    auto f = new AWF::FileReader("/home/steve/Data/II/30/vertex_time.csv");
    auto f = new AWF::FileReader("/home/steve/Data/FusingLocationData/0017/sim_imu.csv");
    Eigen::MatrixXd m = f->extractDoulbeMatrix(",");
    std::cout << m.rows()<<","<<m.cols() << std::endl;
//    std::cout << m.norm() << std::end;
    for(int i(0);i<m.cols();++i)
    {
        std::cout << "cols " << i << " :"
                                  << m.block(0,i,m.rows()-1,1).transpose().norm()
                                  << std::endl;
    }
    return 0;

}


