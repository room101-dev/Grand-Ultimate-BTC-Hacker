from bitcoinrpc.authproxy import AuthServiceProxy, JSONRPCException
import pickle

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

def findunique( nl, ol ):
    newlist=[]
    for i in nl:
        if ( i not in ol ):
            newlist.append(i)
    return( newlist )

def loadaddrlist():
    addrList=[]
    with open('addrlist.pkl','rb') as fp:
        addrlist=pickle.load(fp)
    fp.close()
    return(addrlist)

def saveaddrlist(addrlist):
    with open('addrlist.pkl','wb') as fp:
        pickle.dump(addrlist,fp)
    fp.close()

# remove duplicates if needed, as needed
def cleanaddrlist() :
    addrlist = loadaddrlist()
    newlist=[]
    for i in addrlist:
        for j in i :
            if len(j)>32:
                newlist.append(j)
    al = list(set(newlist))
    saveaddrlist(al)

def writeaddresslist(addrlist):
# address written as base58.txt because b58.perl generates hex.txt which is  fed to blf
    thefile = open('address.txt', 'w')
    for i in addrlist:
#                print( i )
                thefile.write("%s\n" % i )
    thefile.close()

if __name__ == '__main__':
# your bitcoin daemon on your server running full-node
    rpc_user = "hacker"
    rpc_password = "your-password"
    rpc_connection = AuthServiceProxy("http://%s:%s@127.0.0.1:8332"%(rpc_user, rpc_password),timeout=1200)

    best_block_hash = rpc_connection.getbestblockhash()
    blk = rpc_connection.getblock(best_block_hash)

# dump current block count height

    print( "getblockcount = %s" % rpc_connection.getblockcount() )

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
    #print( "Unique Address %d in block" % len(addrl) )

    #addrlist=loadaddrlist()


    #uni = findunique( addrl, addrlist )

    print( "New Addresses Added to List %d" % len(uni) )
    #addrlist.append(uni)

    #saveaddrlist(addrlist)


# *** write the UNIQUE address list to text file

    thefile = open('base58.txt', 'w')

    for i in uni:
#                print( i )
        if ( len(i)==34 ) :            
            thefile.write("%s\n" % i )
    thefile.close()

