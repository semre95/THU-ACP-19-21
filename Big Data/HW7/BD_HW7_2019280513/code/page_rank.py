import sys
from pyspark import SparkConf, SparkContext
import time

def readLine(l):
    splitLine = l.split('\t')
    return (int(splitLine[0]), int(splitLine[1]))

def distributeScores(recipients, score):
    l = len(recipients)
    if l:
        scoreToRecipient = score / l
        for recipient in recipients:
            yield (recipient, scoreToRecipient)

if __name__ == '__main__':

    # Create Spark context.
    conf = SparkConf()
    sc = SparkContext(conf=conf)
    lines = sc.textFile(sys.argv[1])

    first = time.time()

    # Students: Implement PageRank!

    #formula from the assignment ========
    d = 0.8
    vertices = lines.map(lambda line: readLine(line)).distinct().groupByKey().cache()
    N = vertices.count()

    dampling = (1-d)/N
    init = 1/N
    scores = vertices.mapValues(lambda vertex: init)
    #=======================================

    for _ in range(100):
        #1.distribution of scores, 
        #2.then combine them with vertex and lastly distribute sum all scores
        #3.scale it again.
        newScores = vertices.join(scores).flatMap(lambda vertex: distributeScores(vertex[1][0], vertex[1][1]))
        scores = newScores.reduceByKey(lambda s1, s2: s1+s2)
        scores = scores.mapValues(lambda s: dampling + d * s)

    print(scores.sortBy(lambda a: -a[1]).take(5))

    last = time.time()

    print("Total program time: %.2f seconds" % (last - first))
    sc.stop()
