#!/bin/bash

if [ ! -d "../cor" ]
then
	echo "cor folder is missing"
	exit
fi


arr=(../cor/*)
p1=$((RANDOM%${#arr[@]}))
p2=$((RANDOM%${#arr[@]}))
p3=$((RANDOM%${#arr[@]}))
p4=$((RANDOM%${#arr[@]}))

error=0
GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m'

if [ "$1" = "-r" ]
then
	for (( n=0; n<$2; n++ ))
	do
		cycle=$((RANDOM%100000))
		p1=$((RANDOM%${#arr[@]}))
		p2=$((RANDOM%${#arr[@]}))
		p3=$((RANDOM%${#arr[@]}))
		p4=$((RANDOM%${#arr[@]}))
		echo ${arr[$p1]} "VS" ${arr[$p2]} "VS" ${arr[$p3]} "VS" ${arr[$p4]} "cycle" $cycle
		../corewar -d $cycle ${arr[$p1]} ${arr[$p2]} ${arr[$p3]} ${arr[$p4]} > .tmp1
		../../resources/corewar -d $cycle ${arr[$p1]} ${arr[$p2]} ${arr[$p3]} ${arr[$p4]} > .tmp2
		diff .tmp1 .tmp2 >> resdiff
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
	echo "\033[1mErrors = $error / $2${NC}\033[0m"
	exit $error
fi
if [ $# -eq 0 ]
then
	cycle=$((RANDOM%100000))
else
	cycle="$1"
fi
if [ $# -le 1 ]
then
	echo ${arr[$p1]} "VS" ${arr[$p2]} "VS" ${arr[$p3]} "VS" ${arr[$p4]} "cycle" $cycle
	../corewar -d $cycle ${arr[$p1]} ${arr[$p2]} ${arr[$p3]} ${arr[$p4]} > .tmp1
	../../resources/corewar -d $cycle ${arr[$p1]} ${arr[$p2]} ${arr[$p3]} ${arr[$p4]} > .tmp2
	diff .tmp1 .tmp2 >> resdiff
	if [ $? -eq 0 ]
	then
		echo "${GREEN}OK${NC}"
	else
		echo "${RED}/!\\KO/!\\${NC}"
		((error++))
	fi
else
	echo ${arr[$p1]} "VS" ${arr[$p2]} "VS" ${arr[$p3]} "VS" ${arr[$p4]} "cycle" $cycle "to" $(( $cycle + $2 ))
	for (( n=$cycle; n<($cycle+$2); n++ ))
	do
		../corewar -d $n ${arr[$p1]} ${arr[$p2]} ${arr[$p3]} ${arr[$p4]} > .tmp1
		../../resources/corewar -d $n ${arr[$p1]} ${arr[$p2]} ${arr[$p3]} ${arr[$p4]} > .tmp2
		diff .tmp1 .tmp2 >> resdiff
		if [ $? -ne 0 ]
		then
			echo "${RED}/!\\KO/!\\ cycle $n${NC} "
			((error++))
		fi
	done
	if [ $error -eq 0 ]
	then
		echo ${GREEN}
	else
		echo ${RED}
	fi
	echo "\033[1mErrors = $error / $2${NC}\033[0m"
fi
exit $error
