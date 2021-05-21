#! Convert Hash160 address back to Bitcoin address

from bitcoin import *

hash160 = '010966776006953D5567439E5E39F86A0D273BEE'
addr = pubtoaddr(hash160)
print addr
