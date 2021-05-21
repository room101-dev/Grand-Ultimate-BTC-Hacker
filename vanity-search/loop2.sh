# take a gander at recent found check if valid in search list


while [ 1 ]
do

echo 'time'

date

echo 'generate address prefix'

#pkey=$(cat /media/master/Miner/pub/pub_keys.txt | shuf -n 1 )

#echo $pkey

#ku $pkey > ku.txt

#prefix=$( cat ku.txt |  grep "Bitcoin address uncomp" | cut -d: -f2 )

prefix=$(cat /media/master/NTFS-Windows/addr/addresses.txt /media/master/NTFS-Windows/addr/pristine.txt | shuf -n 1 | cut -c-12)


echo $prefix 

# use the timestamp as a unique seed
#d = $(date -d @0), date --date='@0'
d=$(date -u)
h=$(echo $d | sha256 -n 32 -x )

# run 1 hour, then kill all to make sure nothing is holding up the GPU

#timeout 30m ./VanitySearch  -gpu -t 18 -b -r 1000 -sp $pkey $prefix

#timeout 20m  ./VanitySearch -gpu -s "$h" -gpu -t 12 -r 5000 -s "$(echo $d)" $prefix

# cpu mode, 50m/sec/ 1g/sec reset key
timeout 20m  ./VanitySearch -s "$h" -t 8 -r 100 -s "$(echo $d)" $prefix

#killall gpuflay

#cat found.txt | sort -u > found-vg.txt

wc found.txt

# backup and copy current found-vg .txt & .hex 
cat found.txt  >> /media/master/NTFS-Windows/found
cat found.txt  >> ../found-vg-new.txt

cut -d: -f2 found.txt  > found.hex

cat found.hex  >> /media/master/NTFS-Windows/found
cat found.hex  >> ../found-vg-new.hex

# LC_LOCAL=C fgrep -f found-vg.hex /media/robot/Miner/hex/highval.hex /media/robot/Miner/hex/pristine.hex >> found-uniq.hex
#cat found-vg.hex | ~/Crypto/hex2blf/blfchk8 ~/Crypto/hex2blf/monster8.blf | binchk /media/master/Seed/hex/uniq/addr-uniq.bin  > found-uniq.hex
#cat found-vg.hex | ~/Crypto/hex2blf/blfchk8 ~/Crypto/hex2blf/monster8.blf | binchk ../gt-uniq.bin  >> found-uniq.hex
#fgrep -F -a -w -f found.hex /media/master/Seed/hex/uniq/all-uniq.hex  > found-uniq.hex
cat found.hex | binchk ../uniq-bal.bin  > found-uniq.hex
cat found.hex | binchk ../monster-uniq.bin  >> found-uniq.hex

sort -u found-uniq.hex > found-uniq.tmp
grep positive found-uniq.tmp > found-uniq.hex
LC_LOCAL=C fgrep -f found.hex -w /media/master/Seed/hex/uniq/bc-uniq.hex >>found-uniq.hex 
#mv found-uniq.tmp found-uniq.hex


# get response from blfchk and drop first two lines
fn=$(wc found-uniq.hex  |  awk '{print $1}')
#fn=$(echo $fn "-4" | bc)

echo 'found', $fn

if   [ "$fn" -gt "0" ]; then
# make sure we're getting keys
python ../get-bal-hex.py 
fi

# give some time to kill all processes ( oclvanflay ) before they start up again

echo 'wait 5 seconds'
sleep 5

# reset found.txt so we don't re-process the old.
rm found.txt

done

