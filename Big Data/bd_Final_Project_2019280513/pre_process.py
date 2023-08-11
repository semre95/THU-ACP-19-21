import argparse
import numpy as np
import os

if __name__ == '__main__':
    ap = argparse.ArgumentParser()
    ap.add_argument("--path", type=str, help="path to txt file")
    ap.add_argument("-u", "--undirected", default=False, action='store_true')
    args = ap.parse_args()

    path = args.path
    edges = np.loadtxt(path, dtype=np.int32)

    # creating map table
    vertices = np.unique(edges.flatten())
    ids = np.arange(len(vertices))
    map = np.vstack([vertices, ids]).T
    f_name = path.split(os.path.sep)[-1]
    np.savetxt(f_name.split(".")[0] + "_map.txt", map, fmt='%1u')

    # map2IDs
    map_table = dict(zip(vertices, ids))
    if args.undirected:
        reversed_edges = edges[:, [1, 0]]
        edges = np.vstack([edges, reversed_edges])
    edges = np.vectorize(lambda x: map_table[x])(edges)  # convert to ID
    np.savetxt(f_name.split(".")[0] + "_pre_mapped.txt", edges, fmt='%1u')

    print("Preprocessed")
