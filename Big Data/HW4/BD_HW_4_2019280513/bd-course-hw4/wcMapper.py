#!/usr/bin/python

# map.py
import sys

for line in sys.stdin:
    word = line.strip()
    print('{}\t{}'.format(word, 1))
