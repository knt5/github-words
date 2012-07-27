#!/bin/bash

###########################################################
if [ $# -ne 2 ]; then
	echo "Usage: $0 tarball_dir filelist_dir"
	exit 1
fi

###########################################################
tarball_dir=$1
filelist_dir=$2

###########################################################
mkdir $filelist_dir
find $tarball_dir -name "*.tar.gz" | while read line
do
	size=`wc -c < $line`
	if [ $size -ge 200 ]
	then
		echo $line
		tar ztf $line > $filelist_dir/`basename $line`.txt
	fi
done
