#!/bin/sh
for i in $(seq 1 100);
do
  ./generate ${i} > ../data/H${i}.DAT
done
