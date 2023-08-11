import numpy as np
import argparse

if __name__ == '__main__':
    ap = argparse.ArgumentParser()
    ap.add_argument("--input_path", type=str)
    ap.add_argument("--mapping", type=str)
    args = ap.parse_args()

    input_path = args.input_path
    white_list = np.loadtxt(input_path, dtype=np.int32)
    map_file = args.mapping
    map = np.loadtxt(map_file, dtype=np.int32)

    vertices = map[:, 0]
    ids = map[:, 1]
    map_table = dict(zip(ids, vertices))

    white_list_raw = np.vectorize(lambda x: map_table[x])(white_list)

    name = input_path.replace('_white', '_white_post_mapped_')
    np.savetxt(name, white_list_raw, fmt='%1u')

    print("WhiteList Done")