#!/usr/bin/env python
#coding:utf-8
"""
只用来提取label和最近一周的点击次数
"""
import csv
import datetime
tL = datetime.datetime(2015,6,15,0,0,0)
tL1 = datetime.datetime(2015,6,8,0,0,0) #一周之前
reader = csv.reader(open('data_1000'))
diffmen = set()
afterCount = 0
beforCount = 0
feature = {} #保存特征
for fields in reader:
    key = fields[0]+'_'+fields[3]
    tm = datetime.datetime.fromtimestamp(int(fields[7]))

    if key not in feature:
        feature[key] = [0]*8

    #提取最近一周的点击次数,!!!!有错
    if tL1 < tm < tL:
        feature[key][0] += 1

    #提取label
    if tm >= tL:
        feature[key][7] += int(fields[8])

    diffmen.add(fields[0])
    if tm >= tL and fields[8] == '1':
        afterCount += 1
    if tm < tL and fields[8] == '1':
        beforCount += 1

fw = open('fea','w')
sep = ','
for key in feature:
    fw.write(key);
    for ii in range(8):
        fw.write(',' + str(feature[key][ii]))
    fw.write('\n')
fw.close()
print len(diffmen)
print afterCount,beforCount
