import re
import sys
from pyspark import SparkConf, SparkContext
import time


if __name__ == '__main__':
    conf = SparkConf()
    sc = SparkContext(conf=conf)
    lines = sc.textFile(sys.argv[1])

    first = time.time()

    # Students: Implement Word Count!

    num_of_words = lines.flatMap(lambda line: re.split(r'[^\w]+', line))
    num_of_pairs = num_of_words.map(lambda word: (word, 1))
    num_of_counts = num_of_pairs.reduceByKey(lambda a, b: a + b)
    sorting = num_of_counts.sortBy(lambda a: -a[1])
    print(sorting.take(10))

    last = time.time()

    print("Total program time: %.2f seconds" % (last - first))
    sc.stop()

