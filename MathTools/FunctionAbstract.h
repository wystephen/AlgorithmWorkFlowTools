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

namespace AWF {
    class FunctionAbstract {
    public:

        double epsilon_ = 1e-8;
        int OutDim = 1;
        int InNumber = 1;

        double getEpsilon_() const {
            return epsilon_;
        }

        void setEpsilon_(double epsilon_) {
            FunctionAbstract::epsilon_ = epsilon_;
        }


        FunctionAbstract(int out_dim, int in_number) {
            OutDim = out_dim;
            InNumber = in_number;

        }


        /**
         * Interface for derivate function.
         * @param in_vec
         * @return
         */
        virtual Eigen::MatrixXd operator()(std::vector<Eigen::MatrixXd> in_vec) {
            std::cout << "empty operator function" << std::endl;
//            return OVec::Zero();
            Eigen::MatrixXd t(1, 1);
            return t;
        }

        /**
         * derivate.
         * @param in_vec std::vector<Eigen::MatrixXd>
         * @return
         */
        std::vector<Eigen::MatrixXd> d(std::vector<Eigen::MatrixXd> in_vec) {
            std::vector<Eigen::MatrixXd> jac_vec = {};


            auto src_value = operator()(in_vec);
            for (int i(0); i < InNumber; ++i) {
                assert(in_vec[i].cols()==1);
                Eigen::MatrixXd tmp_jac;
                tmp_jac.resize(OutDim, in_vec[i].rows());
                for (int j(0); j < tmp_jac.cols(); ++j) {
                    in_vec[i](j) += epsilon_;
                    auto tmp_value = operator()(in_vec);
                    auto t_d = tmp_value-src_value;

//                    std::cout << "t_d:" << t_d << std::endl;
//                    std::cout << "epsilon:" << epsilon_ << std::endl;
//                    std::cout << "res:" << t_d / epsilon_ << std::endl;
                    tmp_jac.block(0, j, tmp_jac.rows(), 1) = t_d / double(epsilon_);
//                    for(int k(0);k<tmp_jac.rows();++k){
//                        tmp_jac(k,j) = (tmp_value(k,0)-src_value(k,0))/epsilon_;
//                    }
                    in_vec[i](j) -= epsilon_;
                }
                jac_vec.push_back(tmp_jac);
            }
            return jac_vec;

        }


//        virtual std::vector<Eigen::MatrixXd> d()


        /**
         * minimize target function. GD (classical)
         * @param in_vec
         * @param max_iter_num
         * @param learning_rate
         * @param method_type
         * @return
         */
        std::vector<Eigen::MatrixXd> minimize(std::vector<Eigen::MatrixXd> in_vec,
                                              int max_iter_num = 1000,
                                              double learning_rate = 1e-5,
                                              int method_type = 0) {
            auto init_vec(in_vec);

            Eigen::MatrixXd weight(OutDim, 1);
            weight.setOnes();
            weight /= weight.sum();

            Eigen::MatrixXd update_res(OutDim, 1);

            int iter_num = 0;
            while (iter_num < max_iter_num) {
                auto jac_vec = d(init_vec);
                for (int i(0); i < jac_vec.size(); ++i) {
                    init_vec[i] -= learning_rate * jac_vec[i].transpose() * weight;
                }
                iter_num++;
            }

            return init_vec;

        }


    };

}


#endif //ALGORITHMWORKFLOWTOOLS_FUNCTIONABSTRACT_H
