//
// Created by steve on 18-1-13.
//

#include "AlgorithmLogger.h"

namespace AWF {


    AlgorithmLogger::AlgorithmLogger(const AlgorithmLogger &) {

    }


    AlgorithmLogger &AlgorithmLogger::operator=(const AlgorithmLogger &) {

    }

    AlgorithmLogger *AlgorithmLogger::instance = nullptr; //new AlgorithmLogger();

//    std::mutex AlgorithmLogger::queue_mutex_ ;

//    int thread_counter = 0;

    /**
     * get or create new instance.
     * @return
     */
    AlgorithmLogger *AlgorithmLogger::getInstance() {
        static std::once_flag oc;// call once local static variable.
        // call once , to avoid some complexity process of multi-thread DCLP.
        if (instance == nullptr) {
            std::call_once(oc, [] {
                if (instance == nullptr) {
                    instance = new AlgorithmLogger();
                }
            });
        }

        return instance;
    }

    int AlgorithmLogger::getThread_counter() const {
        return thread_counter;
    }

    void AlgorithmLogger::setThread_counter(int thread_counter) {
        AlgorithmLogger::thread_counter = thread_counter;
    }


    inline bool AlgorithmLogger::addEvent(AbstractEvent &e) {
        try {
//            AbstractEvent tmp_e = e;
//            auto e_func = [&]() {
//                    std::unique_lock<std::mutex> ulock(queue_mutex_);
                try {
//                    queue_mutex_.lock();
//                        std::cout << thread_counter++
//                                  << ":"
//                                  << logger_name_
//                                  << tmp_e.toString()<<'\n';
//                                  << std::endl;
//                        std::cout.flush();
	                std::lock_guard<std::mutex> l(queue_mutex_);
                    event_queue_.push_back(e);
//                    queue_mutex_.unlock();

                } catch (std::exception &e) {
                    ERROR_MSG_FLAG(e.what());
                }


//            };
//            t.detach();
//                t.join();
//	        e_func();
            return true;

        } catch (std::exception &e) {
            ERROR_MSG_FLAG(e.what());
            return false;
        }
    }

    bool AlgorithmLogger::addTrace3dEvent(std::string group_name, std::string value_name, const Eigen::MatrixXd &matrix) {

        AWF::AbstractEvent t_event("trace3d@" + group_name + "@" + value_name);
        t_event.setData(matrix);
        return addEvent(t_event);


    }

    bool AlgorithmLogger::addTraceEvent(std::string group_name, std::string value_name, const Eigen::MatrixXd &matrix) {
        AWF::AbstractEvent t_event("trace2d@" + group_name + "@" + value_name);
        t_event.setData(matrix);
        return addEvent(t_event);

    }

    bool AlgorithmLogger::addPlotEvent(std::string group_name, std::string value_name, const Eigen::MatrixXd &matrix) {
        AWF::AbstractEvent t_event("plot@" + group_name + "@" + value_name);
        t_event.setData(matrix);
        return addEvent(t_event);

    }

}