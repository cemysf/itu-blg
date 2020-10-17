##
## Script to print groups of processes in /proc
##
#! /bin/bash
PID_LIST=$(ls /proc/ | awk '/[0-9]/ {print}')		## awk finds numbers in /proc

for PID in $PID_LIST	
do
	echo -e "pid: $PID  \t $(cat /proc/$PID/status | grep Groups)"
done
