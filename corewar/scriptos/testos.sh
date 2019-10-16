#!/bin/bash

if [ ! -d "../cor" ]
then
	echo "cor folder is missing"
	exit
fi

GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m'

arr=(../cor/*)
error=0 
nb=1
if [ $# -gt 0 ]
then
	if [ $1 -gt $nb ]
	then
		nb=$1
	fi
fi
if [ $# -gt 1 ]
then
	if [ $2 -gt $nb ]
	then
		nb=$2
	fi
fi
for (( n=0; n<$nb; n++ ))
do
	p1=$((RANDOM%${#arr[@]}))
	p2=$((RANDOM%${#arr[@]}))
	p3=$((RANDOM%${#arr[@]}))
	p4=$((RANDOM%${#arr[@]}))
	echo ${arr[$p1]} "VS" ${arr[$p2]} "VS" ${arr[$p3]} "VS" ${arr[$p4]}
	../corewar ${arr[$p1]} ${arr[$p2]} ${arr[$p3]} ${arr[$p4]} -v > .tmp1
	../../resources/corewar ${arr[$p1]} ${arr[$p2]} ${arr[$p3]} ${arr[$p4]} -v 31 > .tmp2
	diff .tmp1 .tmp2 > resdiff
	if [ $? -eq 0 ]
	then
		echo "${GREEN}OK${NC}"
	else
		echo "${RED}/!\\KO/!\\${NC}"
		((error++))
	fi
done
if [ $error -eq 0 ]
then
	echo ${GREEN}
else
	echo ${RED}
fi
echo "\033[1mErrors = $error / $nb${NC}\033[0m"
if [ "$1" = "-d" ]
then
	rm -rf .tmp1 .tmp2 resdiff
fi
exit $error
