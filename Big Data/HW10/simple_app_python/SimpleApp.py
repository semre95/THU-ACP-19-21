from __future__ import print_function
import sys
from pyspark import SparkContext
from pyspark.streaming import StreamingContext
import time

def cumsum(current, history):
        return sum(current) + (history or 0)

sc = SparkContext(appName="Py_HDFSWordCount")
ssc = StreamingContext(sc, 60)
ssc.checkpoint("checkpoint")

lines = ssc.textFileStream("hdfs://bd-node1:9000/user/2019280513/stream")  #  you should change path to your own directory on hdfs

word_c = lines.flatMap(lambda line: line.split(" ")).map(lambda x: (x, 1)).reduceByKey(lambda a, b: a+b).updateStateByKey(cumsum)
sorted_word_c = wc.transform(lambda rdd: rdd.sortBy(lambda x: x[1], ascending=False))
sorted_word_c.pprint(100)
sorted_word_c.saveAsTextFiles("hdfs://bd-node1:9000/user/2019280513/output_res")
ssc.start()
ssc.awaitTermination()
