#!/bin/bash

OUTPUTPATH="od_res/"
echo ===== Outdegree Python Version =====

echo ===== Clear old output files on HDFS =====
hdfs dfs -rm -r $OUTPUTPATH
echo
echo ===== RUN CASE1 ======
mapred streaming \
  -input /hw4/case1 \
  -output $OUTPUTPATH"case1_res" \
  -mapper outdegreeMapper.py \
  -reducer outdegreeReducer.py \
  -file outdegreeMapper.py \
  -file outdegreeReducer.py
echo
echo ===== RUN CASE2 =====
mapred streaming \
  -input /hw4/case2 \
  -output $OUTPUTPATH"case2_res" \
  -mapper outdegreeMapper.py \
  -reducer outdegreeReducer.py \
  -file outdegreeMapper.py \
  -file outdegreeReducer.py
echo 
echo DONE!
echo You can use "hdfs dfs -get od_res/ {your_local_path}" to get the result file
echo 

