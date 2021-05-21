'''
m = -n*ln(p) / (ln(2)^2) the number of bits
k = m/n * ln(2) the number of hash functions
'''

def exact_pfp(n, m, k):
  return ( 1 - (1 - (1/m))**(k*n) )**k   

m_bytes = 512*1024*1024
m_bits = m_bytes * 8
k = 20

print('m_bytes,mbits,k',m_bytes,m_bits,k)
print(exact_pfp(440*(10**6), m_bits, k)) # ~0.063
print(exact_pfp(220*(10**6), m_bits, k)) # ~0.000137
print(exact_pfp(110*(10**6), m_bits, k)) # ~1.14e-08
print(exact_pfp(80*(10**6), m_bits, k))  # ~7.16e-11



m_bytes = 4*512*1024*1024
m_bits = m_bytes * 8
k = 25

print('m_bytes,mbits,k',m_bytes,m_bits,k)
print(exact_pfp(130*(10**6), m_bits, k)) # ~1.14e-08
print(exact_pfp(260*(10**6), m_bits, k)) # ~1.14e-08
