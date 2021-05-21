#prefix=$(python /media/robot/Miner/priv/gen-prefix.py)

#prefix=$(cat /media/master/EXT4-Linux/work/addr/addresses.txt /media/master/Miner/addr/pristine.txt | shuf -n 1 | cut -c-12)

#echo $prefix

pkey=$(cat /media/master/Miner/pub/pub_keys.txt | shuf -n 1 )

echo $pkey

ku $pkey > ku.txt

prefix=$( cat ku.txt |  grep "Bitcoin address uncomp" | cut -d: -f2 )

echo $prefix 

# run forever, then kill all to make sure nothing is holding up the GPU



./VanitySearch  -gpu -t 18  -r 1 -sp $pkey $prefix
