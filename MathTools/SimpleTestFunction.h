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
// Created by steve on 18-3-9.
//

#ifndef ALGORITHMWORKFLOWTOOLS_SIMPLETESTFUNCTION_H
#define ALGORITHMWORKFLOWTOOLS_SIMPLETESTFUNCTION_H


namespace AWF {
    class SimpleTestFunction : public FunctionAbstract {
    public:
        SimpleTestFunction() : FunctionAbstract(1, 2) {

        }

        Eigen::MatrixXd operator()(std::vector<Eigen::MatrixXd> in_vec) {
            return compute(in_vec[0], in_vec[1]);
        }

        Eigen::MatrixXd compute(Eigen::MatrixXd xy, Eigen::MatrixXd zt) {
            Eigen::MatrixXd out(1, 1);
            Eigen::Matrix2d p1, p2;
            p1 << 2.0, 0.0, 0.0, 3.0;
            p2 << 4.0, 0.0, 0.0, 5.0;
            out = xy.transpose() * xy + zt.transpose() * zt;
            return out;
        }

        std::vector<Eigen::MatrixXd> derivative(Eigen::MatrixXd in1, Eigen::MatrixXd in2) {
            std::vector<Eigen::MatrixXd> in_vec;
            in_vec.push_back(in1);
            in_vec.push_back(in2);
            return d(in_vec);
        }


    };
}


#endif //ALGORITHMWORKFLOWTOOLS_SIMPLETESTFUNCTION_H
