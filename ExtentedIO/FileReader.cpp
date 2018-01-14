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


    Eigen::MatrixXd FileReader::extractDoulbeMatrix(std::string delimiter ) {
        int rows = 0;
        int cols = 0;

        std::string localString = std::string(file_buf_);

        long tmpIndex = 0;
        // find rows and cols
        try{
        while (tmpIndex < localString.size()) {
            if (rows == 0) {
                // first line
                if (localString.find(delimiter, tmpIndex) < localString.find("\n", tmpIndex)) {
                    // delimiter befoer the first '\n'
                    cols++;
                    tmpIndex = localString.find(delimiter, tmpIndex) + 1;
                } else {
                    tmpIndex = localString.find("\n", tmpIndex) + 1;
                    cols++;
                    rows++;
                }
            } else {
                // others

                tmpIndex = localString.find("\n", tmpIndex) + 1;
                rows++;
//                std::cout << rows << std::endl;
            }
        }
        }catch(...){
            std::cout << __FILE__ << ":" << __LINE__ << std::endl;
        }



        // extract data

        Eigen::MatrixXd localMatrix(rows, cols);
        localMatrix.setZero();
        tmpIndex = 0;
        long nextIndex = 0;
        long rowIndex(0), colIndex(0);
        while (tmpIndex < localString.size() ) {
            nextIndex = std::min(localString.find(delimiter, tmpIndex), localString.find("\n", tmpIndex));
            std::cout << "index:" << tmpIndex<< "next Index :" << nextIndex << std::endl;
            if (nextIndex > 0) {
                localMatrix(rowIndex, colIndex) =
                        std::stod(localString.substr(tmpIndex, nextIndex-tmpIndex));
//                if(std::isnan(localMatrix(rowIndex,colIndex))){
//                    std::cout << "error sub string: " << localString.substr(tmpIndex,nextIndex-tmpIndex)
//                            << "  ---error str end" << std::endl;
//                }
                colIndex++;
                if (colIndex >= cols) {
                    colIndex = 0;
                    rowIndex++;
                }
                tmpIndex = nextIndex+1;
                if(localMatrix.hasNaN()){
                    std::cout << "has nan" << std::endl;
                }
            } else {
                break;
            }

        }

        return localMatrix;


    }
}

