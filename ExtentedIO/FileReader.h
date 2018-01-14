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

#ifndef ALGORITHMWORKFLOWTOOLS_FILEREADER_H
#define ALGORITHMWORKFLOWTOOLS_FILEREADER_H

#include <iostream>
#include <fstream>
#include <cstdio>

#include <Eigen/Dense>

namespace AWF {
    /**
     * Extremely quick non-parallel file reader.
     */
    class FileReader {
    public:
        /**
         * File reader
         */
        FileReader();

        /**
         *
         * @param file_name
         */
        FileReader(std::string file_name);

        ~FileReader();

        bool test();

        /**
         * set file name
         * @param file_name
         * @return
         */
        bool setFileName(std::string file_name);

        /**
         *
         * @return std::string generator by content in file_buf_.
         */
        std::string getString() const;


        /**
         * Extract a Eigen::MatrixXd from the file.
         * @param delimiter typically value: ","," "
         * @return
         */
        Eigen::MatrixXd extractDoulbeMatrix(std::string delimiter);

    private:
        std::string file_name_;

    protected:
        long file_size_ = -1;//Defaul value is -1,when get size from file false set value as -1.

        char *file_buf_;// buffer of file.

        /**
         *
         * @return Get size of the file(according to file_name_).
         */
        long getSize();

        /**
         *
         * @return Load file to memory,file_buf is the point.
         */
        bool loadFile();

    };
}


#endif //ALGORITHMWORKFLOWTOOLS_FILEREADER_H
