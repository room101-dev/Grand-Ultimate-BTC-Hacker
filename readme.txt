Note on all basis software, I have left the original name, but note all these programs have been completely re-written over the years, e.g. 
the vanity-search can no long search for vanity addresses that code is long gone.

Same for brain-flayer, its been completely re-written and re-purposed.

Hex2Blf as well is now hex2blf, hex2blf2, hex2blf4, hex2blf8; 8 of course means 8gb, there is also a chkblf8 to go with it, all is in the makefile. Everything
happens in the .h files, you modify it, you break it, it will no longer work. It's your problem.

blockparser
Not really useful, but one simple way to get 300M hex addresses from the blockchain fairly quickly. Written in C fast.

Brain-Flayer3

A complete re-write of the original, now support up to 4gb bloom-filer, orginal only supported 512mb bloom ( or 15M btc addresses )

hex2blf

This is a big deal, this is all the engine and glue to build 8gb bloom-filter and deploy, also the binchk to kick out false postives. 
See make-bin.sh to see how to make bin file.

all-block

This is a first time use to collect all hex address from the blockchain full-node, if you don't already have the 300M hex h160 addresses then this is one one to do it, slow, but simple and easy to configure. You must have bitcoind running on your machine. Written python slow.
I prefer this method over 'block-parser' or all the C++ stuff, here is why they all break, bitcoin has changed the format of the blocks so many time that no parser can scan the blockchain from 1.0 to today, but the python library can, so this way you get all the hex160 addresses and never miss a beat.

new-block

basic python routine to read memory-pool ( latest block ) and update bloom-filter every 10 minutes, so you always have the newest btc addresses. This is a must, you have to udpdate your bloom filter everyday to stay on top of mining bitcoin.

vanity-flayer

This is 3+ year old, its bloom-filter onboard the GPU its opencl, meaning  it works on AMD & NVIDIA.

This is very interesting because here I put the bloom-filter on the GPU card, super fast, the downside is that CUDA&OPENCL only support 600MB chunks, so it gets real ugly to have a 2GB blf on the gpu, but it can be done. Also debugging is a nightmare with 4,096 cores all spitting back 'found' hashes, you have to use 'valgrind' to debug this software if you decide to explore.

vanity-search

This is the new stuff CUDA only. Note, compiling cuda is not easy, you need to know the -sm on your card, you need to be an expert; You break anything you fix it, nobody is going to help you 

The code is hardwired for  the bloom-filter at at common home path, you'll need to modify the source so that the blf is found at run, but the message will be seen, and the mod is just easy C++. ( This is not production code, in production the blf is kept on its own NVME drive, so the path would be /media/Fast/Monster8.blf )

I call 'monster' cuz long ago I had these monster bitcoin address files (h160)

README.md

Generic philosophy of hacking btc.

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

make-bin.sh

This is an example of making the .bin file for the binchk ( in hex2blf ) this is the fast way to 100% ask is an H160 here or not, no file search required, don't use 'grep' for anything, if you must, use the perl binary2.pl, its pretty good. Note all these search engines require that you pre-sort your data, and make it unique, so "sort -uniq bigdata.hex > bigdata-uniq.hex", on a 500gb file, reduced to a 100GB file, is a major super-computer task, your system needs massive NVME drives and large 32+ GB ram for caching.

Examples of how all this is used is in the loop2.sh file, where miner is called, and then results analyzed, an then repeated every 20 minutes in this example.

****The generic file folder map is 

~/Crypto 
work area for all the code in this project

~/Crypto/vanity-search 

  writes the .txt & .hex files to .. the above path ( ~/Crypto ), .txt is the private-key, and the .hex is the h160 only; all this is required so that when you do find a hot-hex, you can easily find the private-key, normally I build 5TB database of these and keep forever, always popping back up this stuff. Just like brainflayer3, you play with this stuff you'll have 20TB of data in no time.
