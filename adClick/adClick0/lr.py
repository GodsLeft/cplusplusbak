#!/usr/bin/env python
#coding:utf-8
import numpy as np
import pandas as pd
from sklearn import linear_model

df = pd.read_csv('fea_label1',header=None,index_col=0)
df1 = df.ix[:,1:7]
label = df.ix[:,8]
lr = linear_model.LogisticRegression()
lr.fit(df1,label)
X = lr.predict(df1)

#另外
import numpy as np
data = np.loadtxt('fea_label1',delimiter=',',usecols=(1,2,3,4,5,6,7,8))
X = data[:,:-1]
y = data[:,-1]

#数据归一化
from sklearn import preprocessing
norm_x = preprocessing.normalize(X)
stan_x = preprocessing.scale(X)

#特征选择
from sklearn import metrics
from sklearn.ensemble import ExtraTreesClassifier
model = ExtraTreesClassifier()
print(model.feature_importances_)

#逻辑回归
from sklearn.linear_model import LogisticRegression
lr = LogisticRegression()
lr.fit(X,y)
print(model)
expected = y
predicted = model.predict(X)
print(metrics.classification_report(expected,predicted))
print(metrics.confusion_matrix(expected,predicted))

