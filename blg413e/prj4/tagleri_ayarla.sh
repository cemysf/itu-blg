###
### Script to assign tags
###
#! /bin/bash

FOLDER="test1"

LS_COMMAND="ls $FOLDER"
FILENAMES=$($LS_COMMAND)

# clear all existing keys
iptc -d Keywords:all $FOLDER/*
iptc -d SubjectRef:all $FOLDER/*

a=1
# write new values
for FILE in $FILENAMES
do
	iptc  -a Keywords -v "key$a" "$FOLDER/$FILE"
	iptc  -a SubjectRef -v "subject$a" "$FOLDER/$FILE"
	let "a +=1"
done