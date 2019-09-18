#!/usr/bin/env python
#coding:utf-8
import csv
import datetime
Pos={}    #监测点：点击总次数、广告个数、用户个数
Usr={}    #用户  ：点击总次数、广告个数、检点个数
for fields in csv.reader(open('data_1000')):
    if fields[8] != '1':
        continue

    posId = fields[3]
    if posId not in Pos:
        Pos[posId] = [0,set(),set()]
    Pos[posId][0] += 1
    Pos[posId][1].add(fields[2])
    Pos[posId][2].add(fields[0])

    usrId = fields[0]
    if usrId not in Usr:
        Usr[usrId] = [0,set(),set()]
    Usr[usrId][0] += 1
    Usr[usrId][1].add(fields[2])
    Usr[usrId][2].add(fields[3])

#取得数据完成，整合特征
#fr = open('fea')
fw = open('fea_01','w')

sep = ','
for line in csv.reader(open('fea')):
    uId,pId = line[0].split('_')
    if uId in Usr:
        line[2] = str(Usr[uId][0])
        line[3] = str(len(Usr[uId][1]))
        line[4] = str(len(Usr[uId][2]))
    if pId in Pos:
        line[5] = str(Pos[pId][0])
        line[6] = str(len(Pos[pId][1]))
        line[7] = str(len(Pos[pId][2]))
    fw.write(sep.join(line) + '\n')
#fr.close()
fw.close()

