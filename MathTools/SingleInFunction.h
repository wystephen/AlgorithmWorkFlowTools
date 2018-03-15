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
// Created by steve on 18-3-14.
//

#ifndef ALGORITHMWORKFLOWTOOLS_SINGLEINFUNCTION_H
#define ALGORITHMWORKFLOWTOOLS_SINGLEINFUNCTION_H

#include <Eigen/Dense>

#include "FunctionAbstract.h"

namespace AWF {
    class SingleInFunction : public FunctionAbstract {
    public:
        SingleInFunction(int out_dim) :
                FunctionAbstract(out_dim, 1) {

        }

        virtual Eigen::MatrixXd operator()(Eigen::MatrixXd in);

        Eigen::MatrixXd operator()(std::vector<Eigen::MatrixXd> in_vec) {
            return operator()(in_vec[0]);
        }


        /**
         * derivate the function.
         * @param in
         * @return
         */
        std::vector<Eigen::MatrixXd> derivate(Eigen::MatrixXd in) {

            return d(compress(in));
        }


        std::vector<Eigen::MatrixXd> minimize_error(Eigen::MatrixXd in,
                                              int max_iter_num = 1000,
                                              double learning_rate = 1e-5,
                                              int method_type = 0) {
            return minimize(compress(in), max_iter_num, learning_rate, method_type);
        }

        /**
         *
         * @param in
         * @return
         */
        std::vector<Eigen::MatrixXd> compress(Eigen::MatrixXd in) {
            std::vector<Eigen::MatrixXd> t = {};
            t.push_back(in);
            return t;
        }


    };
}


#endif //ALGORITHMWORKFLOWTOOLS_SINGLEINFUNCTION_H
