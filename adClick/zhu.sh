:<<!
#产生va文件
javac GetVa.java
java GetVa ../data.tr ../va

#提取特征
javac GetFea.java
java GetFea ../data.tr ../tr.f ../va ../va.f
!

:<<!
#切分文件，并哈希
javac HashFea.java
java HashFea ../tr.f ../va.f

echo "============Cat file======================"
rm *.class

for i in {1..350}
do
    cat .tr_f_$i >> tr.allf
done

for i in {1..350}
do
    cat .va_f_$i >> va.allf
done
echo "===========ALL FINANSH====================="
!

./mark1 -r 0.03 -s 1 -t 13 va.allf tr.allf

echo "===========C finash======================="
