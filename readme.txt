
blockparser
Not really useful, but one simple way to get 300M hex addresses from the blockchain fairly quickly.

Brain-Flayer3

A complete re-write of the original, now support up to 4gb bloom-filer, orginal only supported 512mb bloom ( or 15M btc addresses )

hex2blf

This is a big deal, this is all the engine and glue to build 8gb bloom-filter and deploy, also the binchk to kick out false postives. 
See make-bin.sh to see how to make bin file.

new-block

basic python routine to read memory-pool ( latest block ) and update bloom-filter every 10 minutes, so you always have the newest btc addresses.

vanity-flayer

This is 3+ year old, its bloom-filter onboard the GPU its opencl, meaning  it works on AMD & NVIDIA.

vanity-search

This is the new stuff CUDA only.

README.md

get-bal-hex.py

This is ran by loop2.sh in the vanity-search, it takes the found hex/priv and looks to see if there is any balance when found it rings a bell.

make-bin.sh

An example of how to turn hex files into bin files for the binchk routine inside of hex2blf.

readme.txt

rich.hex
A list of high value hex addresses so you can test your stuff and make you know you didn't break anything, like run this through blf8chk time to time and make sure your bloom
sees the high-val addresses.

loop2.sh

This is the automated script to continously run your miner's who control the gpu cards, I like to reset every 20minutes and use another address template, reset the private key scan every 100M keys is a good-idea, and use a random seed so the random number generator never runs the same.
