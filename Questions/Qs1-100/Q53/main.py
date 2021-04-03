"""
There are exactly ten ways of selecting three from five, 12345:

123, 124, 125, 134, 135, 145, 234, 235, 245, and 345

In combinatorics, we use the notation, 
.

In general, 
 
, where , , and .

It is not until , that a value exceeds one-million: 
.

How many, not necessarily distinct, values of nCr
 for n in 1:100, are greater than one-million?
"""

import operator as op
from functools import reduce

def ncr(n, r):
    # Fast reduced ncr function
    r = min(r, n-r)
    numer = reduce(op.mul, range(n, n-r, -1), 1)
    denom = reduce(op.mul, range(1, r+1), 1)
    return numer // denom

total = 0

for n in range(1,101):
    for r in range(1,n+1):
        ncr_val = ncr(n,r)
        if ncr_val > 1e6:
            total += 1
            

print(total)
