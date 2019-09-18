#!/usr/bin/env python
#coding:utf-8
fr = open('fea_01')
fw = open('label_3','w')
for line in fr.readlines():
    fields = line.strip().split(',')
    if int(fields[8]) >= 3:
        fw.write(line)
fr.close()
fw.close()
