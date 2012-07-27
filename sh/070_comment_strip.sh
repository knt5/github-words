#!/bin/bash

###########################################################
if [ $# -ne 3 ]; then
	echo "Usage: $0 input_dir output_dir searchlist"
	exit 1
fi

###########################################################
input_dir=$1
output_dir=$2
searchlist=$3

###########################################################
mkdir $output_dir
cat $searchlist | while read line
do
	lang=`echo -n $line | cut -d: -f1`
	suffix=`echo -n $line | cut -d: -f2`
	strip=`echo -n $line | cut -d: -f3`
	
	if [ "$strip" != "" ]
	then
		"$strip" "$input_dir/$lang.txt" > "$output_dir/$lang.txt"
	else
		echo strip not found: $line
	fi
done
