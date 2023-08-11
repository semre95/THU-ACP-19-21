#!/usr/bin/python
# reduce.py
import sys

key   = None
total = 0
for line in sys.stdin:
    k, v  = line.split('\t', 1)
    count = int(v.strip())

    if key == k:
        total += count
    else:
        if key:
            print('{}\t{}'.format(key, total))
        key   = k
        total = count

# do not forget this
if key:
    print ('{}\t{}'.format(key, total))
