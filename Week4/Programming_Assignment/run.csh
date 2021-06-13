#! /bin/csh -f

make clean
make


#run formal released case
#./main ./test1.true.txt > ./ans.test1.log
#./main ./test2.true.txt > ./ans.test2.log
#./main ./test3.true.txt > ./ans.test3.log
#./main ./test4.false.txt > ./ans.test4.log
./main ./2sat1.txt > ./ans.log
./main ./2sat2.txt >> ./ans.log
./main ./2sat3.txt >> ./ans.log
./main ./2sat4.txt >> ./ans.log
./main ./2sat5.txt >> ./ans.log
./main ./2sat6.txt >> ./ans.log
