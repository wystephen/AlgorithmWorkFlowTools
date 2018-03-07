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
// Created by steve on 18-3-6.
//

#ifndef ALGORITHMWORKFLOWTOOLS_WRITETOCSV_H
#define ALGORITHMWORKFLOWTOOLS_WRITETOCSV_H

#include <vector>
#include <iostream>
#include <fstream>
#include <assert.h>

#include <Eigen/Dense>

#include "../UsefulTools/ErrorTools.h"

namespace AWF {
    /**
     * Output vector<vector<T>> data into a csv file.
     * @tparam T
     * @param file_name
     * @param src_data
     * @return
     */
    template<typename T>
    bool writeVectorsToCsv(std::string file_name,
                           std::vector<std::vector<T>> &src_data) {
        if (src_data.size() > 0) {
            for (int i(0); i < src_data.size(); ++i) {
                assert(src_data[i].size() == src_data[0].size());
            }
        }

        int rows = src_data[0].size();
        int cols = src_data.size();

        try {
            std::ofstream out_file(file_name);
            for (int i(0); i < rows; ++i) {
                for (int j(0); j < cols; ++j) {
                    out_file << src_data[j][i];
                    if (j < cols - 1) {
                        out_file << ",";
                    }
                }
                if (i < cols - 1) {
                    out_file << "\n";
                } else {
                    out_file << std::endl;
                }
            }

            out_file.close();

        } catch (std::exception &e) {

            ERROR_MSG_FLAG(e.what());
            return false;
        }

        return true;


    }


    /**
     *
     * @param file_name
     * @param matrix
     * @return
     */
    bool writeMatrixToCsv(std::string file_name,
                          Eigen::MatrixXd &matrix) {
        try {
            std::ofstream out_file(file_name);
            for (int i(0); i < matrix.rows(); i++) {
                out_file << matrix.block(i, 0, 1, matrix.cols());
                if (i < matrix.rows() - 1) {
                    out_file << "\n"
                }
            }
            out_file.flush();
            out_file.close();


        } catch (std::exception &e) {
            ERROR_MSG_FLAG(e.what());
            return false;
        }
        return true;

    }
}


#endif //ALGORITHMWORKFLOWTOOLS_WRITETOCSV_H
