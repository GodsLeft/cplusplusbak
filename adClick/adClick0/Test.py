#!/usr/bin/env python
#coding:utf-8

fr = open('data_1000')
diffmen = set()
diffpos = set()
diffad = set()
count = 0
for line in fr.readlines():
    fields = line.strip().split(',')
    diffmen.add(fields[0])
    count += int(fields[8])
    diffpos.add(fields[3])
    diffad.add(fields[2])
print "用户：%d, 点击次数：%d" % (len(diffmen),count)
print len(diffpos),len(diffad)
fr.close()
