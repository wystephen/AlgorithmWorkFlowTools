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

        GetSize();

        LoadFile();
    }

    inline FileReader::~FileReader() {
        delete[]file_buf_;
    }

    inline bool FileReader::test() {
        GetSize();
        return true;
    }

    inline bool FileReader::set_file(std::string file_name) {
        if (!file_name.empty()) {
            file_name_ = file_name;
            return true;
        } else {
            return false;
        }
    }

    inline std::string FileReader::GetString() const {
        return std::string(file_buf_);
    }

    inline long FileReader::GetSize() {

        try {
            std::ifstream tmp_f(file_name_);
            tmp_f.seekg(0, std::ios::end);
            std::streampos ps = tmp_f.tellg();

            file_size_ = ps;

//		std::cout << "file_size :" << file_size_ << std::endl;

            return ps;
        }
        catch (...) {
            std::cerr << "Error in open file." << std::endl;
        }
        return -1;
    }

    inline bool FileReader::LoadFile() {
        try {
            if (file_size_ < 0 && GetSize() < 0) {
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
            std::cerr << "Error in FileReader::LoadFile()." << std::endl;
        }
        return false;
    }
}

