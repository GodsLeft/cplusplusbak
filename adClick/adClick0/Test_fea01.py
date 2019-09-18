#!/usr/bin/env python
#coding:utf-8
"""
分析特征，取出label为1的记录，肉眼观察特点
"""
fr = open('fea_01')
fw  = open('fea_label_x','w')
#fw2 = open('fea_label_2','w')
count = 0
count1 = 0
count2 = 0
count3 = 0
countx = 0
for line in fr.readlines():
    fields = line.strip().split(',')
    if fields[8] == '0':
        continue
    if fields[8] == '1':
        count1 += 1
    if fields[8] == '2':
        count2 += 1
    if fields[8] == '3':
        count3 += 1
    if int(fields[8]) > 3:
        fw.write(line)
    count += int(fields[8])
#    fw.write(line)
print count,count1,count2,count3
fr.close()
fw.close()
