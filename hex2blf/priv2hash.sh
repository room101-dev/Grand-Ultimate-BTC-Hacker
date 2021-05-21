# get only len=40 hash from ku on priv
ku 81E01B6EBB75D10FDA42620864C6293E5FF7344DC323C772D168B55AAF45EA8E | grep 'uncompressed' | cut -d: -f2 | awk 'length($0)>35'

# get only hash160
 ku 81E01B6EBB75D10FDA42620864C6293E5FF7344DC323C772D168B55AAF45EA8E | grep 'hash160' | cut -d: -f2

# drop lines containing 'false positive' or 'Processing BLF'
echo '77870869d937d913a400bd8f5a844560664cce01' | ./blfchk ../blf/test.blf ../blf/test.bin | grep -Ev '(false|Proc)'

###

# loop through all lines of file

while read p; do
  echo $p
done
