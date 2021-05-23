#! /bin/csh -f

make clean
make


#run formal released case
#./main ./test.txt > ./ans_test.log
#./main ./test2.txt > ./ans_test2.log 
#./main ./test3.txt > ./ans_test3.log
./main ./nn.txt > ./ans.log
