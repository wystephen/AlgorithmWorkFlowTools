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

#include "FileReader.h"

namespace AWF {

    inline FileReader::FileReader() {
        file_name_ = std::string("");
    }

    inline FileReader::FileReader(std::string file_name) {
        file_name_ = file_name;

        getSize();

        loadFile();
    }

    inline FileReader::~FileReader() {
        delete[]file_buf_;
    }

    inline bool FileReader::test() {
        getSize();
        return true;
    }

    inline bool FileReader::setFileName(std::string file_name) {
        if (!file_name.empty()) {
            file_name_ = file_name;
            return true;
        } else {
            std::cerr << "file name is empty" << std::endl;
            return false;
        }
    }

    inline std::string FileReader::getString() const {
        return std::string(file_buf_);
    }

    inline long FileReader::getSize() {

        try {
            std::ifstream tmp_f(file_name_);
            tmp_f.seekg(0, std::ios::end);
            std::streampos ps = tmp_f.tellg();

            file_size_ = ps;

            return ps;
        }
        catch (...) {
            std::cerr << "Error in open file." << std::endl;
        }
        return -1;
    }

    inline bool FileReader::loadFile() {
        try {
            if (file_size_ < 0 && getSize() < 0) {
                std::cerr << "File " << file_name_ << " is empty !" << std::endl;
            }

            file_buf_ = new char[file_size_ + 1];

            FILE *file;
            file = fopen(file_name_.c_str(), "r");

            fread(file_buf_, file_size_, 1, file);

            fclose(file);

            file_buf_[file_size_] = '\0';

            return true;
        }
        catch (...) {
            std::cerr << "Error in FileReader::loadFile()." << std::endl;
        }
        return false;
    }


    Eigen::MatrixXd FileReader::extractDoulbeMatrix(std::string delimiter) {
        int rows = 0;
        int cols = 0;

        std::string tmp_str = std::string(file_buf_);

        long tmpIndex = 0;
        // find rows and cols
        try {
            while (tmpIndex < tmp_str.size()) {
                if (rows == 0) {
                    // first line
                    if (tmp_str.find(delimiter, tmpIndex) < tmp_str.find("\n", tmpIndex)) {
                        // delimiter befoer the first '\n'
                        cols++;
                        tmpIndex = tmp_str.find(delimiter, tmpIndex) + 1;
                    } else {
                        tmpIndex = tmp_str.find("\n", tmpIndex) + 1;
                        cols++;
                        rows++;
                    }
                } else {
                    // others

                    tmpIndex = tmp_str.find("\n", tmpIndex) + 1;
                    rows++;
//                std::cout << rows << std::endl;
                }
            }
        } catch (...) {
            std::cout << __FILE__ << ":" << __LINE__ << std::endl;
        }




        // extract data

        Eigen::MatrixXd localMatrix(rows, cols);
        localMatrix.setZero();
        int the_row(0), the_col(0);

        int l_index(0), r_index(0);
        try {
            for (int index(0); index < tmp_str.size(); ++index) {

                if (tmp_str.compare(index, delimiter.size(), delimiter) ==
                    0 //index == tmp_str.substr(index,delimiter.size()) //tmp_str.find_first_of(delimiter,index)//,index+delimiter.size()+1)
                    || tmp_str[index] == '\n') {
                    r_index = index;
                    localMatrix(the_row, the_col) = std::stod(tmp_str.substr(l_index, r_index - l_index).c_str());
                    if (tmp_str[index] == '\n') {
                        ++the_row;
                        the_col = 0;

                    } else {
                        ++the_col;
                        assert(the_col < cols);
                    }
                    if (the_row == rows - 1 && the_col == cols - 1) {
                        localMatrix(the_row, the_col) = std::stod(
                                tmp_str.substr(r_index + 1, file_size_ - r_index - 1).c_str());
                        break;
                    }
                    l_index = r_index + 1;
                }
            }
        }catch(std::exception e){
            std::cout << __FUNCTION__
                      << ":"
                      << __FILE__ << ":" << __LINE__
                                         << " :"
                                         << e.what() << std::endl;
        }


        return localMatrix;


    }
}

