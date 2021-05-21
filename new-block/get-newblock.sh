#!/bin/bash

while [ 1 ]
do 

#sleep 10

blkcnt=$(bitcoin-cli getblockcount)

echo 'getblockcount', $blkcnt

# script to apply passwords to all new transactions on bitcoin
# python routine to get most recent block and harvest all addresses

python get-newhex.py

sort -u base58.txt > addr.txt

# change addresses to base 58 form, make-h160 addr.txt->addr.hex
# input is base58.txt ( addr.txt ), output is addr.hex

python make-hash160.py

# update bin file

cat addr.txt >> address.txt
cat addr.hex >> address.hex


# generate bloom filter from base58 addresses 

hex2blf8 addr.hex ~/Crypto/hex2blf/monster8.blf 

#sort -u address.hex > address-uniq.hex
#cat address-uniq.hex | xxd -r -p > addr.bin

# wait until next block available, 4M delay, on average the python step above takes 5 min, and 10min per btc block

newblk=$(bitcoin-cli getblockcount)
delay=1
echo $delay,$newblk
while [ "$delay" -gt "0" ];
do
    if [ "$blkcnt" -eq "$newblk" ]; then
        sleep 4m
        newblk=$(bitcoin-cli getblockcount)
        echo 'newblk/wait',$newblk
    else
        delay=0
    fi
done


done
