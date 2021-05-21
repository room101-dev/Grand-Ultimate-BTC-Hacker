make gpu=1 CCAP=6.0  all

g++ -c -fpermissive -o bloom/bloom.o bloom/bloom.c

# new gpu card 3070 is 8.6

make gpu=1 CCAP=8.6  all
