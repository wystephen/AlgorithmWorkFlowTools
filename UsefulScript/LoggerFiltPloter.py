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

        # standard dict
        self.tmp_dict = {'type': list(), 'group': list(), 'name': list(), 'data': list()}

        self.data_h_dict = dict()

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
            type_str = cate_str.split('_')[0]
            group_str = cate_str.split('_')[1]
            name_str = cate_str.split('_')[2]
            data_float_list = [float(x) for x in num_str_list]

            self.tmp_dict['type'].append(type_str)
            self.tmp_dict['group'].append(group_str)
            self.tmp_dict['name'].append(name_str)
            self.tmp_dict['data'].append(data_float_list)
            # the_index+=1
        # get DataFrame
        self.data_frame = DataFrame(self.tmp_dict)
        end_time = time.time()

        print(self.data_frame)
        print('totla time', end_time - start_time)

    def shwo_all(self):
        print(self.data_frame[self.data_frame['type'] == 'trace2d'])


if __name__ == '__main__':
    lfp = LoggerFilePlotting("logger_2018-04-01-15:50:45.log")
    lfp.shwo_all()
