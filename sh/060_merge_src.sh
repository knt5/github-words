#!/bin/bash

###########################################################
if [ $# -ne 6 ]; then
	echo "Usage: $0 tarball_dir filelist_dir output_src_dir output_filelist_dir searchlist reposlist"
	exit 1
fi

###########################################################
tarball_dir=$1
filelist_dir=$2
output_src_dir=$3
output_filelist_dir=$4
searchlist=$5
reposlist=$6
unit=200

###########################################################
mkdir $output_src_dir
mkdir $output_filelist_dir
i=1
cat $searchlist | while read line
do
	lang=`echo -n $line | cut -d: -f1`
	suffix=`echo -n $line | cut -d: -f2`
	args=''
	for x in $suffix
	do
#		 do not add "'"
		args="$args -e .*\.$x$" 
	done
	
	echo -n > "$output_filelist_dir/$lang.txt"
	echo -n > "$output_src_dir/$lang.txt"
	num=`expr $unit \* $i`
	head -n $num "$reposlist" | tail -n $unit | while read rec
	do
		uname=`echo -n $rec | awk '{print $1}'`
		repos=`echo -n $rec | awk '{print $2}'`
		fname="$uname-$repos.tar.gz"
		if [ -e "$filelist_dir/$fname.txt" ]
		then
			grep $args "$filelist_dir/$fname.txt" >> "$output_filelist_dir/$lang.txt"
			grep $args "$filelist_dir/$fname.txt" | tar xf "$tarball_dir/$fname" -T - -O >> "$output_src_dir/$lang.txt"
		fi
	done
	
	i=`expr $i + 1`
done
