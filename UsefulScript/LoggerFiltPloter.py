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

from pandas import DataFrame,Series

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

            # if type-group-name isn't in dict, added it to self.data_h_dict
            if not type_str in self.data_h_dict:
                # self.data_h_list.append(type_str)
                # self.data_h_list
                self.data_h_dict[type_str] = dict()

            if not group_str in self.data_h_dict[type_str]:
                self.data_h_dict[type_str][group_str] = list()

            if not name_str in self.data_h_dict[type_str][group_str]:
                self.data_h_dict[type_str][group_str].append(name_str)

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

    def pd_series_to_numpy(self, the_series:Series)->np.array:
        data_list = the_series
        tmp_data = np.zeros([data_list.values.shape[0], len(data_list.values[0])])
        print(tmp_data)
        print(tmp_data.shape)

        for i in range(tmp_data.shape[0]):
            for j in range(tmp_data.shape[1]):
                tmp_data[i, j] = data_list.values[i][j]
        return tmp_data

    def shwo_all(self):
        # print(self.data_frame[self.data_frame['type'] == 'trace2d'])
        # print(self.data_h_dict)
        for key, value in self.data_h_dict.items():
            print('key', key, 'val', value)
            if 'trace2d' in key:
                for group_name, name_list in value.items():
                    print('---------------')
                    print(group_name, '|', name_list)
                    print('---------------')
                    # fig = plt.Figure()
                    # ax = fig.add_subplot(111)
                    # ax.set_title(group_name)
                    plt.figure()
                    plt.title(group_name)
                    # print(group_name)
                    # print(type(group_name))
                    # print(self.data_h_dict.items())

                    # print(self.data_frame[self.data_frame['group']==group_name])
                    for data_name in name_list:
                        data_list = self.data_frame[(self.data_frame['type'] == 'trace2d') & \
                                                    (self.data_frame['group'] == group_name) & \
                                                    (self.data_frame['name'] == data_name)]['data']



                        tmp_data = self.pd_series_to_numpy(data_list)
                        # print(tmp_data)
                        # print('tmp data', tmp_data.shape)
                        plt.plot(tmp_data[:, 0], tmp_data[:, 1], label=data_name)
                    plt.legend()
                    plt.grid
            if 'plot' in key:
                for group_name,name_list in value.items():
                    plt.figure()
                    plt.title(group_name)
                    for data_name in name_list:
                        data_list = self.data_frame[(self.data_frame['type']=='plot')&\
                                                    (self.data_frame['group']==group_name)&\
                                                    (self.data_frame['name']==data_name)]['data']
                        tmp_data = self.pd_series_to_numpy(data_list)
                        plt.plot(tmp_data,label=data_name)
                    plt.grid()
                    plt.legend()

            # plt.plot()


if __name__ == '__main__':
    lfp = LoggerFilePlotting("logger_2018-04-01-15:50:45.log")
    lfp.shwo_all()
    plt.show()
