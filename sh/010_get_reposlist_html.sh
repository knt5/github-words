#!/bin/bash

###########################################################
if [ $# -ne 2 ]; then
	echo "Usage: $0 url download_dir"
	exit 1
fi

###########################################################
langlist=$1
dir=$2

###########################################################
mkdir $dir
cat $langlist | while read line
do
	i=1
	while [ $i -le 10 ]
	do
		wget -O $dir/$line-`printf %02d $i`.html "https://github.com/languages/"$line"/most_watched?page="$i &
		i=`expr $i + 1`
	done
done
