#!/usr/bin/env python3
#coding:utf-8

import argparse,csv,sys,pickle,collections,time,datetime

parser = argparse.ArgumentParser()
parser.add_argument('src_path')
parser.add_argument('dst_path')
args = vars(parser.parse_args())

FIELDS = ['uId','st','adId','posId','os','bw','ip','tm','click']
NEW_FIELDS = FIELDS + ['uId_cnt','adId_cnt','posId_cnt','ip_cnt','click_history']

uId_cnt = collections.defaultdict(int)
adId_cnt = collections.defaultdict(int)
posId_cnt = collections.defaultdict(int)
ip_cnt = collections.defaultdict(int)

start = time.time()

def scan(path):
    for i, row in enumerate(csv.DictReader(open(path)),start = 1):
        uId_cnt[row['uId']] += 1
        adId_cnt[row['adId']] += 1
        posId_cnt[row['posId']] += 1
        ip_cnt[row['ip']] += 1

history = collections.defaultdict(lambda:{'history':'','buffer':'','prev_hour':''})

## 每读取一行，就添加数据
def gen_data(src_path,dst_path,is_train):
    reader = csv.DictReader(open(src_path))
    writer = csv.DictWriter(open(dst_path,'w'),NEW_FIELDS)
    writer.writeheader()

    tL = datetime.datetime(2015,6,24,0,0,0)
    for i, row in enumerate(reader,start=1):
        new_row = {}
        for field in FIELDS:
            new_row[field] = row[field]
        new_row['uId_cnt'] = uId_cnt[row['uId']]
        new_row['adId_cnt'] = adId_cnt[row['adId']]
        new_row['posId_cnt'] = posId_cnt[row['posId']]
        new_row['ip_cnt'] = ip_cnt[row['ip']]

        hour = int((time.mktime(tL.timetuple()) - int(row['tm'])) / (3600))
        # 这段代码,!!!
        if history[row['uId']]['prev_hour'] != hour:
            history[row['uId']]['history'] = (history[row['uId']]['history']+history[row['uId']]['buffer'])[-4:]
            history[row['uId']]['buffer'] = ''
            history[row['uId']]['prev_hour'] = hour #row['hour'] #原始数据中并没有这个字段，自己通过tm字段构造

        new_row['click_history'] = history[row['uId']]['history']
        if is_train:
            history[row['uId']]['buffer'] += row['click']

        writer.writerow(new_row)

scan(args['src_path'])
print('=============================scan complete======================================')
gen_data(args['src_path'],args['dst_path'],True)
print('=============================finsh        ======================================')
