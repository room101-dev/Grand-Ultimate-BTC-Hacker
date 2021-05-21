# get h160 addresses from found.txt, convert to base58 address, and get balance on addr

import pybitcointools

from coinkit import BitcoinKeypair
import logging

import argparse

from bitcoin import *

from bitcoin import bci

import os

#import hash160 # local user py script to get publickey2addr

skiplist=[ 
'b5bd079c4d57cc7fc28ecf8213a6b791625b8183', # NULL "" seed NADA
'371f197d5ba5e32bd98260eec7f0e51227b69690', # cat
'5bb7d22851413e1d61e8db5395a8c7c537256ea0', # dog
'31ede6667afdacf8ccda58805153de1db42db014', # chicken
'b311d5766f9623408747554bcdec1d8dc05eeaf0', # test
'0000000000000000000000000000000000000000', # ?????????? (unknown )
'ffffffffffffffffffffffffffffffffffffffff', # ?? ( unknown bounary in blf?)
'3e546d0acc0de5aa3d66d7a920900ecbc66c2031', # unknown, 45k trans
'801314cd462b98c64dd4c3f4d6474cad11ea39d5', # the
'9f3ecb56e8b3cf977b958b044b2b039f7ae6f036', # coffee
'cffe3e032a686cc3f2c9e417865afa8a52ed962b', # god
'2d6351944aa38af6aa46d4a74cbb9016cf19ee7e', # wallet
'000000c5d31b915f2a74c3f51259c09d21808d3e',
'5d14a857fce8da8edfb8f7d1c4bbc316622b7227', # password1

'cd1d7e863f891c493e093ada840ef5a67ad2d6cc', # peter
'3b4df4363caa9e3bd9da58020d3080be8230a4ae',
]

if __name__ == '__main__':

 
    rich='1Ki3WTEEqTLPNsN5cGTsMkL2sJ4m5mdCXT'

    hrich=bci.history(rich)
    print( "RICH", rich, len(hrich),len(bci.unspent(rich)) )

#    foundf = open( "found.txt", "a" )
    #h160_list = 'found-hot.hex'
    h160_list = 'found-uniq.hex'
    #h160_list = 'found-big.hex'

    print( '*** Reading: ', h160_list )

    lin = 1 # need to skip first line from chkblf
    with open(h160_list,'r') as f:
        lines = f.read().splitlines()

        print ( 'lines', len(lines) )

        for l in lines:

            if '(positive)' in l:
                l=l[0:40]   # strip the following "(positive)"
                pass            
            else: 
                if len(l) < 40 or  'false positive' in l or len(l)>40:  
                    continue

            #ls = l.split(':')
            # sometimes there is addr:hash160
            if ':' in l:
                print "ADDR:HASH160", l
                ls = l.split(':')[1] # addr:hex160
                if len(ls)<40 :
                    print "Hash Odd Lenght", len(ls), ls
                    continue
            else :
                ls = l.strip()

            #print('LS',ls)
            
            if ls in skiplist:
                print 'SKIPLIST', ls
                continue


            #u = ls[0] # first element is public-key
            #t = ls[1] # type, x,compr, uncompr
            #algo = ls[2] # algo
            #seed = ls[3] # seed, passphrase for private-key

            #kp=BitcoinKeypair.from_passphrase(seed)
            #priv=kp.private_key()    
            #pub=kp.public_key()        
            #print('PUB', u,t,seed,priv,pub)

            #addr = hash160.public_key_to_bc_address(pub.decode('hex_codec'))
            addr = pybitcointools.hex_to_b58check(ls)
            print('h160 ...', l )

            h = bci.history(addr)

            u = bci.unspent(addr)

            if h and any(h):
                with open("found-used.csv", "a") as myfile:
                    myfile.write("%s %s H%d U%d\n" % ( addr, ls,len(h),len(u)) )

            if u and any(u):
                print('u-LS ************************',u,ls)
                #u = unspent(addr)
                if ( len(u)>0 ) :

                    total=0
                    for i in u:
                        total=total+int(i['value'])


                    os.system("mplayer ~/bin/Cartoon-10.wav")
                    with open("found-unspent.csv", "a") as myfile:
                        myfile.write("Val %d Ul %d %s %s\n" % (total, len(u), addr, l) )
                    print "VAL-U tot/len ", total, len(u), addr, ls   

               # print( 'HISTORY(len),UNSPENT',len(h),u )
                


            print( 'u/h-ls [addr]', len(u),len(h), ls, addr  )

