# take a gander at recent found check if valid in search list


while [ 1 ]
do

echo 'time'

date

echo 'generate address prefix'

pkey=$(cat /media/master/Miner/pub/pub_keys.txt | shuf -n 1 )

echo $pkey

ku $pkey > ku.txt

prefix=$( cat ku.txt |  grep "Bitcoin address uncomp" | cut -d: -f2 )

echo $prefix 

# run 1 hour, then kill all to make sure nothing is holding up the GPU

#timeout 30m ./VanitySearch  -gpu -t 18 -b -r 1000 -sp $pkey $prefix
timeout 20m ./VanitySearch  -gpu -t 18  -r 1 -sp $pkey $prefix

#killall gpuflay

cat found.txt | sort -u >> found-vg.txt

wc found-vg.txt

# reset found.txt so we don't re-process the old.
rm found.txt

# backup and copy current found-vg
cat found-vg.txt  >> ../found-vg-gpu.txt

cut -d: -f2 found-vg.txt |  sort -u > found-vg.hex
# LC_LOCAL=C fgrep -f found-vg.hex /media/robot/Miner/hex/highval.hex /media/robot/Miner/hex/pristine.hex >> found-uniq.hex
cat found-vg.hex | ~/Crypto/hex2blf/blfchk4 ~/Crypto/hex2blf/monster4.blf  > found-uniq.hex

# get response from blfchk and drop first two lines
fn=$(wc found-uniq.hex  |  awk '{print $1}')
fn=$(echo $fn "-2" | bc)

echo 'found', $fn

if   [ "$fn" -gt "0" ]; then
# make sure we're getting keys
python ../get-bal-hex.py 
fi

# give some time to kill all processes ( oclvanflay ) before they start up again

echo 'wait 5 seconds'
sleep 5


done

