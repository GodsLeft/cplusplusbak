#!/usr/bin/env python
#coding:utf-8
import numpy as np

data = np.loadtxt('fea_label1',delimiter=',',usecols=(1,2,3,4,5,6,7,8))
X = data[:,:-1]
Y = data[:,-1]

dat = []
for ii in range(len(Y)):
    for jj in range(len(data[ii])):
        if data[ii,jj] >= 400:
            dat.append(data[ii])
            break
dat = np.array(dat)
m,n = dat.shape
count = 0
for ii in dat[:,-1]:
    if ii == 1:count+=1
print count

#计算p,r
t = 0
for ii in Y:
    if ii == 1:
        t += 1
print '实际点击次数:',t
r = count / float(t)
p = count/float(m)

f = 2*r*p / (r + p)
print f

t1=0
for ii in X:
    if ii[0]==1:
        t1 += 1
print '上周点击次数:',t1

##使用上一周预测下一周
count = 0
m = 0
for ii in data:
    if ii[0] == 1:
        m += 1
        if ii[-1] == 1:
            count += 1
p = count/float(m)
r = count / float(t)
f1 = 2*p*r/(p + r)
print count
print 'f1:',f1
