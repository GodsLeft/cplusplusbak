#!/usr/bin/env python3
#coding:utf-8
import argparse,csv,sys,pickle,collections
from common import *

parser = argparse.ArgumentParser()
parser.add_argument('src_path')
parser.add_argument('dst_path')
args = vars(parser.parse_args())
#           0     1     2       3     4    5    6    7      8       9         10         11          12          13
#fields = ['uId','st','adId','posId','os','bw','ip','tm','click','uId_cnt','adId_cnt','posId_cnt','ip_cnt','click_history']
fields = ['uId','adId','posId','os','bw','ip','click_history']

def convert(src_path,dst_path,is_train):
    with open(dst_path,'w') as f:
        for row in csv.DictReader(open(src_path)):
            feats = []
            for field in fields:
                feats.append(hashstr(row[field]))

            if int(row['ip_cnt']) > 1000:
                feats.append(hashstr(row['ip']))
            else:
                feats.append(hashstr(row['ip_cnt']))

            if int(row['uId_cnt']) > 1000:
                feats.append(hashstr(row['uId']))
            else:
                feats.append(hashstr(row['uId_cnt']))

            if int(row['adId_cnt']) > 1000:
                feats.append(hashstr(row['adId']))
            else:
                feats.append(hashstr(row['adId_cnt']))

            if int(row['posId_cnt']) > 1000:
                feats.append(hashstr(row['posId']))
            else:
                feats.append(hashstr(row['posId_cnt']))

            if int(row['uId_cnt']) > 30:
                feats.append(hashstr(row['uId_cnt']))
            else:
                feats.append(hashstr(row['uId_cnt']+row['click_history']))

            f.write('{0} {1} {2}\n'.format(row['uId'],row['click'],' '.join(feats)))

convert(args['src_path'],args['dst_path'],True)
