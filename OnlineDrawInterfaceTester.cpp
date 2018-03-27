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

#include <iostream>
#include <Eigen/Dense>

#include <thread>

#include "AWF.h"

int main(){

    auto odi = AWF::OnlineDrawInterface("test_1",3);

    auto f1 = [](double x)->double{
        return sin(x/100.0);

    };

    auto f2 = [](double x)->double{
        return cos(x/100.0);

    };

    auto f3 = [](double x)->double{
        return sin(x/100.0)+cos(x/100.0);

    };

    for(int i(0);i<1000000;++i){
        Eigen::Vector3d tv(f1(i),f2(i),f3(i));
        std::cout << tv.transpose() << std::endl;
        odi.addDataVector(tv);
        usleep(100);
    }

}

