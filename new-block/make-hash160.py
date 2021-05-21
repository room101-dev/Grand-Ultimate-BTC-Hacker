#!/usr/bin/env python

"""encode/decode base58 in the same way that Bitcoin does"""

import math
import hashlib

__b58chars = '123456789ABCDEFGHJKLMNPQRSTUVWXYZabcdefghijkmnopqrstuvwxyz'
__b58base = len(__b58chars)


def b58encode(v):
	""" encode v, which is a string of bytes, to base58.		
	"""

	long_value = int(v.encode("hex_codec"), 16)

	result = ''
	while long_value >= __b58base:
		div, mod = divmod(long_value, __b58base)
		result = __b58chars[mod] + result
		long_value = div
	result = __b58chars[long_value] + result

	# Bitcoin does a little leading-zero-compression:
	# leading 0-bytes in the input become leading-1s
	nPad = 0
	for c in v:
		if c == '\0': nPad += 1
		else: break

	return (__b58chars[0]*nPad) + result

def b58decode(v, length):
	""" decode v into a string of len bytes
	"""

	long_value = 0L
	for (i, c) in enumerate(v[::-1]):
		long_value += __b58chars.find(c) * (__b58base**i)
	
	result = ''
	while long_value >= 256:
		div, mod = divmod(long_value, 256)
		result = chr(mod) + result
		long_value = div
	result = chr(long_value) + result

	nPad = 0
	for c in v:
		if c == __b58chars[0]: nPad += 1
		else: break

	result = chr(0)*nPad + result
	if length is not None and len(result) != length:
		return None

	return result

def sha_256(data):
	return hashlib.sha256(data).digest()

def checksum(data):
	return sha_256(sha_256(data))

def ripemd_160(data):
	return hashlib.new("ripemd160", data).digest()

def hash_160(public_key):
	h1 = sha_256(public_key)
	h2 = ripemd_160(h1)
	return h2

def public_key_to_bc_address(public_key):
	h160 = hash_160(public_key)
	return hash_160_to_bc_address(h160)

def hash_160_to_bc_address(h160):
	vh160 = "\x00"+h160  # \x00 is version 0
	h3 = sha_256(sha_256(vh160))
	addr=vh160+h3[0:4]
	return b58encode(addr)

def bc_address_to_hash_160(addr):
	bytes = b58decode(addr, 25)
	return bytes[1:21]
###
def writeaddresslist(addrlist):
# address written as base58.txt
    hfile = open('addr.txt', 'w')
    for i in addrlist:
                hfile.write("%s\n" % i )
    hfile.close()
###

def address2hash():
# address written as base58.txt because b58.perl generates hex.txt which is  fed to blf
#    al=[]
    i=0
    hfile = open('addr.hex', 'w')
    with open( 'addr.txt', 'r' ) as f:
        for line in f:
#           al.append(line.strip())
            i = i + 1
            if ( i%10000 == 0 ) :
                print i

            al = line.strip()
            if ( len(al) == 34 ) :
#                print al
                hl = bc_address_to_hash_160(al).encode('hex_codec')
#                print hl
                hfile.write("%s\n" % hl )
    hfile.close()
    f.close()
    return(al)

if __name__ == '__main__':


    h = 'EC42AD7FD54F931274B83F6137379206E458B1063EC89E96'
    a = '1NYEM85RpgkSofLqDfwjb21o3MD4ibSo49'

    print 'test address = ', a	
    x = h.decode('hex_codec')
    encoded = b58encode(x)
    print encoded, a
    print b58decode(encoded, len(x)).encode('hex_codec'), x.encode('hex_codec')

    print '(verification) bca2hash160 ', bc_address_to_hash_160(a).encode('hex_codec')
###

    address2hash()


