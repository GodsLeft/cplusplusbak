#gen_data.py data_100 tr.csv

#parallelizer.py -s 12 ./2.py tr.csv tr.sp

make -C mark/mark1 && ln -sf mark/mark1/mark1

cp tr.sp va.sp

./mark1 -r 0.03 -s 1 -t 13 tr.sp va.sp
