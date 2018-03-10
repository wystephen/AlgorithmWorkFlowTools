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
//    template<int OutDim, int InNumber>
    class FunctionAbstract {
    public:

//        typedef Eigen::MatrixXd Vec;
//        typedef Eigen::MatrixXd OVec;
//        typedef Eigen::MatrixXd JacM;

        double epsilon_ = 1e-5;
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


        virtual Eigen::MatrixXd operator()(std::vector<Eigen::MatrixXd> in_vec) {
            std::cout << "empty operator function" << std::endl;
//            return OVec::Zero();
            Eigen::MatrixXd t(1, 1);
            return t;
        }

        std::vector<Eigen::MatrixXd> d(std::vector<Eigen::MatrixXd> in_vec) {
            std::vector<Eigen::MatrixXd> jac_vec = {};

            auto src_value = operator()(in_vec);
            for (int i(0); i < InNumber; ++i) {
                Eigen::MatrixXd tmp_jac(OutDim, in_vec[i].rows());
                for (int j(0); j < tmp_jac.cols(); ++j) {
                    in_vec[i](j) += epsilon_;
                    auto tmp_value = operator()(in_vec);
                    tmp_jac.block(0, j, tmp_jac.rows(), 1) = (tmp_value - src_value) / epsilon_;
                    in_vec[i](j) -= epsilon_;
                }
                jac_vec.push_back(tmp_jac);
            }
            return jac_vec;

        }


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
