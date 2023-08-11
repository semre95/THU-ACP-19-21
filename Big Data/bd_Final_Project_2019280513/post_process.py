import numpy as np
import argparse

if __name__ == '__main__':
    ap = argparse.ArgumentParser()
    ap.add_argument("--input_path", type=str)
    ap.add_argument("--mapping", type=str)
    args = ap.parse_args()

    input_file = args.input_path
    rank = np.loadtxt(input_file, dtype=np.float32)
    map_file = args.mapping
    map = np.loadtxt(map_file, dtype=np.int32)

    vertices = map[:, 0]
    ids = map[:, 1]
    map_table = dict(zip(ids, vertices))

    ranked_vertices_id = rank[:, 0]
    raw_vertices = np.vectorize(lambda x: map_table[x])(ranked_vertices_id)
    rank[:, 0] = raw_vertices

    fmt = '%1u', '%1.9f'
    name = input_file.replace('_pre_mapped', '_post_mapped')
    np.savetxt(name, rank, fmt=fmt)

    print("PostMapped")
