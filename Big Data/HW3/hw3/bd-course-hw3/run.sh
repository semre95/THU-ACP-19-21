#!/bin/bash
echo "======== compiling ==========\n"
make 
echo "======== running with 2 processes on 2 nodes (a single process on each node)  ==========\n"
mpirun -f host1 --np 2  ./reduce

echo "======== running with 4 processes on 4 nodes (a single process on each node)  ==========\n"
mpirun -f host2 --np 4  ./reduce
