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
#include "FunctionAbstract.cpp"

namespace AWF {
    class SingleFunctionAbstract : public FunctionAbstract {
    public:
        SingleFunctionAbstract(int out_dim) :
                FunctionAbstract(out_dim, 1) {

        }


        /**
         * Compute the function..... defined the target function.
         * @param in
         * @return
         */
        virtual Eigen::MatrixXd compute(Eigen::MatrixXd in) {
            auto t = Eigen::MatrixXd(OutDim, 1);
            t.setZero();
            return t;
        }

        /**
         * @param in_vec
         * @return
         */
        Eigen::MatrixXd operator()(std::vector<Eigen::MatrixXd> in_vec) {
            return compute(in_vec[0]);
        }


        /**
         * derivate the function.
         * @param in
         * @return
         */
        std::vector<Eigen::MatrixXd> derivate(Eigen::MatrixXd in) {

            return d(compress(in));
        }


        /**
         * Minimize the function.
         * @param in
         * @param max_iter_num
         * @param learning_rate
         * @param method_type
         * @return
         */
        std::vector<Eigen::MatrixXd> minimize_error(Eigen::MatrixXd in,
                                                    int max_iter_num = 1000,
                                                    double learning_rate = 1e-5,
                                                    int method_type = 0) {
            return minimize(compress(in), max_iter_num, learning_rate, method_type);
        }

        /**
         * Transform input to std::vector<Eigen::MatrixXd>
         * @param in
         * @return
         */
        std::vector<Eigen::MatrixXd> compress(Eigen::MatrixXd in) {
            std::vector<Eigen::MatrixXd> t = {};
            t.push_back(in);
            return t;
        }


    };


    class DualFunctionAbstract : public FunctionAbstract {
    public:
        DualFunctionAbstract(int out_dim) :
                FunctionAbstract(out_dim, 2) {

        }


        /**
         * Compute the function..... defined the target function.
         * @param in
         * @return
         */
        virtual Eigen::MatrixXd compute(Eigen::MatrixXd in1, Eigen::MatrixXd in2) {
            auto t = Eigen::MatrixXd(OutDim, 1);
            t.setZero();
            return t;
        }

        /**
         * @param in_vec
         * @return
         */
        Eigen::MatrixXd operator()(std::vector<Eigen::MatrixXd> in_vec) {
            return compute(in_vec[0], in_vec[1]);
        }


        /**
         * derivate the function.
         * @param in
         * @return
         */
        std::vector<Eigen::MatrixXd> derivate(Eigen::MatrixXd in1, Eigen::MatrixXd in2) {

            return d(compress(in1, in2));
        }


        /**
         * Minimize the function.
         * @param in
         * @param max_iter_num
         * @param learning_rate
         * @param method_type
         * @return
         */
        std::vector<Eigen::MatrixXd> minimize_error(Eigen::MatrixXd in1,
                                                    Eigen::MatrixXd in2,
                                                    int max_iter_num = 1000,
                                                    double learning_rate = 1e-5,
                                                    int method_type = 0) {
            return minimize(compress(in1, in2), max_iter_num, learning_rate, method_type);
        }

        /**
         * Transform input to std::vector<Eigen::MatrixXd>
         * @param in
         * @return
         */
        std::vector<Eigen::MatrixXd> compress(Eigen::MatrixXd in1, Eigen::MatrixXd in2) {
            std::vector<Eigen::MatrixXd> t = {};
            t.push_back(in1);
            t.push_back(in2);
            return t;
        }
    };
}


#endif //ALGORITHMWORKFLOWTOOLS_SINGLEINFUNCTION_H
