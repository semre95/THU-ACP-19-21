import argparse
import numpy as np
from pyspark import SparkConf, SparkContext
import time

def split_edge(edge):
    source, dest = edge.strip().split(' ')
    return source, dest

def get_contrib(out_nodes, total):
    for out_node in out_nodes:
        yield (out_node, total / len(out_nodes))


if __name__ == '__main__':
    
    ap = argparse.ArgumentParser()
    ap.add_argument("--path", type=str, help="txt file to process")
    ap.add_argument("--num_iter", type=int, default=20)
    ap.add_argument("--dump_factor", type=float, default=0.8)
    ap.add_argument("--k_top", type=int, default=0, help="if k_top == 0, retrieve all")
    args = ap.parse_args()

    conf = SparkConf()
    sc = SparkContext(conf=conf)
    graph_data = sc.textFile(args.path)
    


    num_iter = args.num_iter
    d = args.dump_factor
    k_top = args.k_top
    
    start = time.time()

    # initialize edges of source_id and list of out-nodes
    nodes = graph_data.map(lambda x: split_edge(x)).distinct().groupByKey()
    n_nodes = nodes.count()
    if not k_top:
        k_top = n_nodes
    # getting ranks
    ranks = nodes.map(lambda x: (x[0], 1.0 / n_nodes))


    # updates ranks and gets node contributions to the rank of other nodes
    for i in range(num_iter):
        contribution = nodes.join(ranks).flatMap(lambda x: get_contrib(x[1][0], x[1][1]))         
        ranks = contribution.reduceByKey(lambda x, y: x + y).mapValues(lambda x: x * d + (1. - d) / n_nodes)         

    ranks = ranks.map(lambda x: (x[1], x[0])).sortByKey(False).map(lambda x: (x[1], x[0])).take(k_top)     

    np_ranks = np.array(ranks).astype(float)
    fmt = '%1u', '%1.9f'
    if not args.k_top:
        k_top = "all"
    np.savetxt(args.path.strip().split('/')[-1].split('_')[0] + "_pre_mapped_pagerank_top_" + str(k_top) + ".txt", np_ranks, fmt=fmt)

    print("Time: %.2f seconds" % (time.time() - start))
    print(f"Top-{k_top} nodes:", ranks[:5])
    sc.stop()