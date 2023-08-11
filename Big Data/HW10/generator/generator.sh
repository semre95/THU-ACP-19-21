#!/bin/bash
username=$(whoami)
hdfs dfs -mkdir /user/$username/stream/
hdfs dfs -rm /user/$username/stream/*
while [ 1 ]; do
    tmplog="words.`date +'%s'`.txt"
    python data.py;
    hdfs dfs -put words.txt /user/$username/stream/$tmplog
    echo "`date +"%F %T"` generating $tmplog succeed"
    rm words.txt
    sleep 56;
done
