# Grand-Ultimate-BTC-Hacker

Two parts here random key search of bitcoin, and ECDLP high-level math analysis to map public-keys to private.

Here we are NOV 2022, and ETH has gone stake, and billions of GPU cards have NOTHING to do with their lives;

**

Recently I have re-deployed my RTX-3070's from hacking btc do mining ETH, which is very profiitable now

These old GTX1060-3gb cards are worthless, but just experimenting around I made an interesting discovery.

Normally the 1060-3 would do about 50MH/sec, but when I put the hacking tool on its own NVME m.2. on the MOBO I found that the 8gb bloom filter was almost 100% allowing the GPU to run at max

Now I have 300M addresses from BTC that have value, placed in my 8gb bloom filter gives a false positive of one in a trillion-trillion-trillion, so not often

The 250 MH/sec is how often a private key is created ( more on this later ), and then all possible (comp/uncomp) addresses (h160)  are ran through the bloom-filter, so the through-put is really 250 M & 300M , or almost 1,000 TH/SEC address compares, but really higher because I'm doing 4 different combinations so its 4,000 TH/sec, on just one card, but I'm doing six on a rig, so its 24 PH/sec

This yields about one lost address per week to be found

For the record the rtx-3070 was doing 1,000MH/sec, but I was just running the bloom-filter off of an SSD, but it was shared, I have never tested a standalone NVME with the RTX, I could imagine they would do 1TH/sec easily.

WHat's all this mean? Well in BTC secp256k1 you got 10e77 combos, 1/2 that to birthday you got 10e36, divide that by 10e15, and you get 10e15, that many seconds tells you how often you should have a hit in real time, old calculations were on the order of  one every 1,000 days.

But on a rig I'm see way more often, because I guess for the simple matter is the napkin, is always different than real world.

So what are the tools?

1.) hack up vanity-search, which  is the best gpu solution for generating keys
2.) add the 8gb bloom filter, note that linux only support 4gb shared memory, so the bloom must be cascaded, note that brain-flayer only used a 512mb bloom, so creating a 8gb bloom is a major task in software engineering
3.) hack up vanity-search so that on every new key, its runs through the bloom-filter for every possible address that can be generated, comp, un-comp, h160, eth,...

The Gtx-1060 only uses 970mb of memory, so in effect even the older gtx750 could be used here Smiley

I spent a few years ago spending time putting the bloom-filter on the gtx-1070, but even though there is only 8gb, you can only allocate 700mb max at a time in CUDA dev, so I found near impossible to get a working 4gb bloom running on a GPU, so I fell back to doing it on the CPU.

Note in my rig here I'm just using an 2core i3 ( $50 cpu ), with 4gb memory, as this is essentially 100% gpu

I'm just sharing this cuz well its my hobby, and I have to report.

Lastly, just for the record, like the original brain-flayer dude, I don't spend the coin, I don't even own a single exchange on earth, what I do when I find btc, is I put it in a database, and watch how long it takes be spent after I find it, I have found to date, that almost all coins are gone < 1 yr, which tells me I'm not the only one playing this game.

The selection of random-keys in vanity-search is very critical, of course all that code has to be stripped, as your not looking for prefix, I use a baby-step/giant-step algo that runs through public-keys, where I have 100's of 1,000's every 20 minutes randomly search for a new key from that public hash ( of known high-value ), I do this to make sure that my private key search space is within known valuable addresses, as I'm not looking for a prefix like vanity, I'm looking for a random public address of known value. The 20 min idea, is that time try another, because of scale of the pool, there isn't much duplication.

...

Lastly, on hacking btc, I spent years working on hacking the original public-key coins hold +50 btc, there used to be 1,000's, now there are < 900, and its dropping a few per month, so there being hacked. I was very close to getting a public key mapped to private, using various techniques, but had to move on other projects. Essentially the trick is p is the prime, and n is the order, if you can get n-1, n, or n+1 == p, then you can use a linear discrete log tool (cado-nfs) to get the private-key. The tough nut to crack, is finding the p just close enough to secp26k1 p, to put you in the ballpark for using kangaroo where you need to be within 2^40

I have crack these public high-value keys, but given that I dont' actually touch them, sweep them, its just a mental puzzle and move-on, but the cado-nfs, and finding n+1 is a very difficult & tedious process, of which a few months I get burned out and move onto other projects.

Mapping public-keys ( not hashed pre 2013 bitcoin was not sha'd ) is a real thing, but it takes tremendous knowledge of graduate-math in crypto; The ECDLP is one of the most difficult problems in mathematics; There are many steps, its not like normal hacking; There are no tools, everything is roll-your-own; There is no such thing on GITHUB, as the only thing you'll find there is junk; Like they say, if it made money, they wouldn't be giving it away for free.
