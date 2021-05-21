from bitcoinrpc.authproxy import AuthServiceProxy, JSONRPCException


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

	long_value = 0
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


def address2hash():
# address written as base58.txt because b58.perl generates hex.txt which is  fed to blf
#    al=[]
    i=0
    hfile = open('address.hex', 'w')
    with open( 'address.txt', 'r' ) as f:
        for line in f:
#           al.append(line.strip())
            i = i + 1
            if ( i%10000 == 0 ) :
                print (i)

            al = line.strip()
            if ( len(al) == 34 ) :
#                print (al)
                hl = bc_address_to_hash_160(al).encode('hex_codec')
#                print (hl)
                hfile.write("%s\n" % hl )
    hfile.close()
    f.close()
    return(al)

def addrlistVout( txid ):
#    rpc_connection = AuthServiceProxy("http://%s:%s@192.168.1.8:8332"%(rpc_user, rpc_password))
    addrlist = []
    raw = rpc_connection.getrawtransaction(txid)
    decode =rpc_connection.decoderawtransaction(raw)
    for vl in decode['vout']:
        if ( 'scriptPubKey' in vl ) and vl['value']>0 :
            sl = vl['scriptPubKey']
#            print(vl['scriptPubKey'])
            if ( 'addresses' in sl ) :
                for al in sl['addresses']:
                    addrlist.append(al)
#                    print ( al )
    return ( addrlist )


def writeaddresslist(addrlist):
# address written as base58.txt because b58.perl generates hex.txt which is  fed to blf
    thefile = open('address.txt', 'a')
    for i in addrlist:
#                print( i )
                thefile.write("%s\n" % i )
    thefile.close()

def updatehexlist():
# address written as base58.txt because b58.perl generates hex.txt which is  fed to blf
    import fileinput
    with open('/media/master/Crypto/all-blocks/addr.hex', 'a') as fout:
        fin = fileinput.input('address.hex')
        for line in fin:
            fout.write(line)
    fin.close()

def updateaddresslist():
# address written as base58.txt because b58.perl generates hex.txt which is  fed to blf
    import fileinput
    with open('/media/master/Crypto/all-blocks/addr.txt', 'a') as fout:
        fin = fileinput.input('address.txt')
        for line in fin:
            fout.write(line)
    fin.close()

if __name__ == '__main__':

# rpc here means your bitcoind running on your server

    rpc_user = "hacker"
    rpc_password = "your-pass-word"
    rpc_connection = AuthServiceProxy("http://%s:%s@127.0.0.1:8332"%(rpc_user, rpc_password),timeout=1200)


# dump current block count height

    print( "getblockcount = ", rpc_connection.getblockcount() )

    for height in range(677587,1,-1): # start last, stop first, decrement
        print( "height = ", height )

        block_hash = rpc_connection.getblockhash(height)
        blk = rpc_connection.getblock(block_hash)

        txlist=[]
        alist=[]

        for txid in blk['tx']:
            txlist.append( txid )
            al=addrlistVout( txid )
            alist.append( al )

    # make list & remove duplicates in list
        newlist=[]
        for i in alist:
            for j in i:
                newlist.append(j)

        uni = list(set(newlist))

        print( "%d Transactions in block" % len(txlist) )

        print( "Uniq Addresses Added to List %d" % len(uni) )



    # *** write the UNIQUE address list to text file

        writeaddresslist(uni)   # write to address.txt
        address2hash()          # address.txt to address.hex
        updatehexlist()         # catenate address.hex to addr.hex
        #updateaddresslist()     # catenate address.txt to addr.txt

        with open("height.txt", "w") as file:
            file.write(str(height))


