#!/bin/bash

###########################################################
if [ $# -ne 2 ]; then
	echo "Usage: $0 reposlist download_dir"
	exit 1
fi

###########################################################
reposlist=$1
dir=$2

###########################################################
mkdir $dir
cat $reposlist | while read line
do
	user=`echo -n $line | awk '{print $1}'`
	repos=`echo -n $line | awk '{print $2}'`
	url="https://api.github.com/repos/"$user"/"$repos
	wget -O $dir/$user-$repos.json -t 5 $url &
done
