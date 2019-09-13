#!/bin/bash

if [ ! -d "cor" ]
then
	echo "cor folder is missing"
	exit
fi

arr=(./cor/*)
p1=$((RANDOM%${#arr[@]}))
p2=$((RANDOM%${#arr[@]}))
p3=$((RANDOM%${#arr[@]}))
p4=$((RANDOM%${#arr[@]}))
echo ${arr[$p1]} "VS" ${arr[$p2]} "VS" ${arr[$p3]} "VS" ${arr[$p4]}
./corewar -g ${arr[$p1]} ${arr[$p2]} ${arr[$p3]} ${arr[$p4]}
