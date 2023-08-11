#!/usr/bin/python
"""reducer.py"""

import sys
from heapq import nlargest

counter = {}

for line in sys.stdin:
    k, v  = line.strip().split('\t', 1)
    count = int(v)

    if k in counter:
        counter[k] += count
    else:
        counter[k] = count
        
Top20 = nlargest(20, counter, key = counter.get) 
  
for val in Top20: 
    print(val, ":", counter.get(val)) 