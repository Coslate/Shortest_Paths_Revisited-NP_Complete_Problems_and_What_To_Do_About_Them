#! /bin/csh -f

make clean
make


#run formal released case
 ./main ./g1.txt ./g2.txt ./g3.txt > ans_g1_g2_g3.log
