# Created by steve on 18-4-1 下午2:30
'''
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
'''

import matplotlib.pyplot as plt

import numpy as np
import scipy as sp

from pandas import DataFrame

import re
import os

import time


class LoggerFilePlotting:
    def __init__(self, file_name):
        self.log_file = open(file_name)

        all_lines = self.log_file.readlines()

        self.num_re = re.compile('[-]{0,1}[0-9][.]{0,1}[0-9]{0,100}')

        self.data_frame = DataFrame(data=None, columns=['type', 'group', 'name', 'data'])
        # self.data_frame.reindex(index=len(all_lines))
        # self.data_frame.
        the_index = 0

        # self.data_dict =

        start_time = time.time()
        # search over all lines
        for line in all_lines:
            # print(line)
            time_str = line.split(':')[0]
            cate_str = line.split(':')[1]
            vec_str = line.split(':')[2]
            # print(time_str, cate_str, vec_str)
            # print(self.num_re.findall(vec_str))
            num_str_list = self.num_re.findall(vec_str)
            # self.data_frame.
            # print(cate_str)
            self.data_frame.loc[the_index]={'type': cate_str.split('_')[0],
                                    'group': cate_str.split('_')[1],
                                    'name': cate_str.split('_')[2],
                                    'data': num_str_list}
            # the_index+=1
        end_time = time.time()

        print(self.data_frame)
        print('totla time', end_time-start_time)


if __name__ == '__main__':
    lfp = LoggerFilePlotting("logger_2018-04-01-15:50:45.log")
