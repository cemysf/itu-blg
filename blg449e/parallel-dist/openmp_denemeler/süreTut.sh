#!/bin/bash
start=$(date +%s.%N)
# do some stuff here
./out

dur=$(echo "$(date +%s.%N) - $start" | bc)

echo "Execution time:" $dur
