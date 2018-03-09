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
// Created by steve on 18-2-4.
//

#ifndef ALGORITHMWORKFLOWTOOLS_FUNCTIONABSTRACT_H
#define ALGORITHMWORKFLOWTOOLS_FUNCTIONABSTRACT_H

#include <functional>
#include <tuple>
#include <Eigen/Dense>

namespace AWF{
 class FunctionAbstract {
 public:
     FunctionAbstract();
     std::function<Eigen::MatrixXd(Eigen::MatrixXd&)> func;



};

}


#endif //ALGORITHMWORKFLOWTOOLS_FUNCTIONABSTRACT_H
