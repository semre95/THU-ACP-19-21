#!/bin/bash

OUTPUTPATH="wc_res/"
echo ===== Simple Word Count Python Version =====

echo ===== Clear old output files on HDFS =====
hdfs dfs -rm -r $OUTPUTPATH
echo
echo ===== RUN ======
mapred streaming \
  -input /hw4/temp.txt \
  -output $OUTPUTPATH \
  -mapper wcMapper.py \
  -reducer wcReducer.py \
  -file wcMapper.py \
  -file wcReducer.py
echo
echo 
echo DONE!
echo You can use "hdfs dfs -get wc_res/ {your_local_path}" to get the result file
echo 

