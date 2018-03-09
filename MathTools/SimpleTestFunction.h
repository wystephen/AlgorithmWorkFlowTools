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
    class SimpleTestFunction : public FunctionAbstract<2, 2> {
    public:
        SimpleTestFunction() : FunctionAbstract() {

        }

        Eigen::MatrixXd operator()(std::vector<Vec> in_vec) {
            return compute(in_vec[0], in_vec[1]);
        }

        Eigen::MatrixXd compute(Eigen::MatrixXd xy, Eigen::MatrixXd zt) {
            Eigen::MatrixXd out(2,1);
            Eigen::Matrix2d p1, p2;
            p1 << 2.0, 0.0, 0.0, 3.0;
            p2 << 4.0, 0.0, 0.0, 5.0;
            out = p1 * xy + p2 * zt;
            return out;
        }


    };
}


#endif //ALGORITHMWORKFLOWTOOLS_SIMPLETESTFUNCTION_H
