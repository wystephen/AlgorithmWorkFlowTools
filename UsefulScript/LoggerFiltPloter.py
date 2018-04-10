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
from mpl_toolkits.mplot3d import axes3d

import numpy as np
import scipy as sp

from pandas import DataFrame, Series

import re
import os

import time


class LoggerFilePlotting:
    def __init__(self, file_name):
        self.log_file = open(file_name)

        all_lines = self.log_file.readlines()

        # sameple target for re
        # [1522653075.146236]:plot@angle_correct@world_value:{[0.921896; 0.260512; 0.286776]}
        # [1522653075.146358]:trace3d@right_foot@simple:{[ 4.26695e-07; -2.23405e-06; -1.50273e-06]}
        self.num_re = re.compile(r'\d+\.?\d*e?[-+]?\d*')

        # standard dict
        self.tmp_dict = {'type': list(), 'group': list(), 'name': list(), 'data': list()}

        self.data_h_dict = dict()

        self.time_list = list()

        start_time = time.time()
        # search over all lines
        for line in all_lines:
            # print(line)
            time_str = line.split(':')[0]
            cate_str = line.split(':')[1]
            vec_str = line.split(':')[2]

            self.time_list.append(float(time_str.split('[')[1].split(']')[0]))

            num_str_list = self.num_re.findall(vec_str)

            type_str = cate_str.split('@')[0]
            group_str = cate_str.split('@')[1]
            name_str = cate_str.split('@')[2]

            # print(vec_str)
            # from str to float.
            data_float_list = [float(x) for x in num_str_list]

            # if type-group-name isn't in dict, added it to self.data_h_dict
            if not type_str in self.data_h_dict:
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

        plt.figure()
        plt.title('time')
        plt.plot(self.time_list)
        plt.grid()

        # print(self.data_frame)
        print('load data totally time', end_time - start_time)

    def pd_series_to_numpy(self, the_series: Series) -> np.array:
        data_list = the_series
        tmp_data = np.zeros([data_list.values.shape[0], len(data_list.values[0])])
        # print(tmp_data)
        # print(tmp_data.shape)

        for i in range(tmp_data.shape[0]):
            for j in range(tmp_data.shape[1]):
                tmp_data[i, j] = data_list.values[i][j]
        return tmp_data

    def shwo_all(self):
        '''
        show all data.
        find data according to self.data_h_dict
        which is a tree as following struct:
        type->group_name->data_name
        :return:
        '''
        # print(self.data_frame[self.data_frame['type'] == 'trace2d'])
        # print(self.data_h_dict)
        for key, value in self.data_h_dict.items():
            print('key', key, 'val', value)
            if 'trace2d' in key:
                for group_name, name_list in value.items():
                    # print('---------------')
                    # print(group_name, '|', name_list)
                    # print('---------------')
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

                        try:
                            tmp_data = self.pd_series_to_numpy(data_list)
                            # print(tmp_data)
                            # print('tmp data', tmp_data.shape)
                            plt.plot(tmp_data[:, 0], tmp_data[:, 1], '-+', label=data_name)
                        except IndexError:
                            print(IndexError)
                            print(data_list)
                    plt.legend()
                    plt.grid()
            if 'plot' in key:
                for group_name, name_list in value.items():
                    plt.figure()
                    plt.title(group_name)
                    index = 1
                    for data_name in name_list:
                        data_list = self.data_frame[(self.data_frame['type'] == 'plot') & \
                                                    (self.data_frame['group'] == group_name) & \
                                                    (self.data_frame['name'] == data_name)]['data']
                        try:
                            tmp_data = self.pd_series_to_numpy(data_list)
                            plt.subplot(len(name_list), 1, index)
                            index += 1
                            # plt.plot(tmp_data, label=data_name)
                            for i in range(tmp_data.shape[1]):
                                plt.plot(tmp_data[:, i], '-', label=data_name + str(i))
                            plt.grid()
                            plt.legend()
                        except IndexError:
                            print(IndexError)
                            print(data_list)

                    plt.title(group_name)
            if 'trace3d' in key:
                for group_name, name_list in value.items():
                    fig = plt.figure()
                    ax = fig.add_subplot(111, projection='3d')
                    ax.set_title(group_name)
                    data_save_list = list()
                    for data_name in name_list:
                        data_list = self.data_frame[(self.data_frame['type'] == 'trace3d') & \
                                                    (self.data_frame['group'] == group_name) & \
                                                    (self.data_frame['name'] == data_name)]['data']
                        try:
                            data_save_list.append(self.pd_series_to_numpy(data_list))

                            ax.plot(data_save_list[-1][:, 0],
                                    data_save_list[-1][:, 1],
                                    data_save_list[-1][:, 2], '-+', label=data_name)
                        except IndexError:
                            print(IndexError)
                            print(data_list)

                    ax.grid()
                    ax.legend()

            # plt.plot()


if __name__ == '__main__':
    import sys
    from os import environ

    environ['MPLBACKEND'] = 'module://gr.matplotlib.backend_gr'
    # import matplotlib
    # matplotlib.use('GTKAgg')
    lfp = LoggerFilePlotting(sys.argv[1])
    # lfp = LoggerFilePlotting("/home/steve/Code/ComplexityPositioning/logger_2018-04-02-19:43:21.log")
    lfp.shwo_all()
    plt.show()
