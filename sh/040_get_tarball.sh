#!/bin/bash

###########################################################
if [ $# -ne 2 ]; then
	echo "Usage: $0 reposlist download_dir"
	exit 1
fi

###########################################################
reposlist=$1
dir=$2
mu=20

###########################################################
mkdir $dir
cat $reposlist | while read line
do
	user=`echo -n $line | awk '{print $1}'`
	repos=`echo -n $line | awk '{print $2}'`
	url="https://api.github.com/repos/"$user"/"$repos"/tarball"
	
	while [ 1 ]
	do
		num=`ps -ef | grep curl | grep -v grep | wc -l`
		if [ $num -lt $mu ]
		then
			curl -L $url > $dir/$user-$repos.tar.gz &
			break
		fi
		sleep 1
	done
done
