//
// Created by steve on 18-1-13.
//

#ifndef ALGORITHMWORKFLOWTOOLS_ALGORITHMLOGGER_H
#define ALGORITHMWORKFLOWTOOLS_ALGORITHMLOGGER_H


class AlgorithmLogger{
public:
    static AlgorithmLogger* getInstance();

private:
    AlgorithmLogger();
    //把复制构造函数和=操作符也设为私有,防止被复制
    AlgorithmLogger(const AlgorithmLogger&);
    AlgorithmLogger& operator=(const AlgorithmLogger&);

    static AlgorithmLogger* instance;
};


#endif //ALGORITHMWORKFLOWTOOLS_ALGORITHMLOGGER_H
