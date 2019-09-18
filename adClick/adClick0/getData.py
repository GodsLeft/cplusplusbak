#!/usr/bin/env python
#coding:utf-8

import csv
import datetime
tL = datetime.datetime(2015,4,1,0,0,0)
fr = open('./z_kagg/data_100')
fw = open('data.tr','w')
fr.readline()
for line in fr.readlines():
    fields = line.split(',')
    tm = datetime.datetime.fromtimestamp(int(fields[7]))
    if tm >= tL:
        fw.write(line)
fr.close()
fw.close()
