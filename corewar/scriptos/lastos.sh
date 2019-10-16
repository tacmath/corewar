#!/bin/bash

BLUE='\033[0;36m'
GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m' # No Color

arr=(../cor/*)

p1=$((RANDOM%${#arr[@]}))
p2=$((RANDOM%${#arr[@]}))
p3=$((RANDOM%${#arr[@]}))

files="${arr[$p1]} ${arr[$p2]}  ${arr[$p3]}"
echo $files

last_cycle=`../../resources/corewar -v 2 $files | grep "It is now cycle" | tail -n 1 | cut -d ' ' -f 5`
let "last_cycle = $last_cycle - 1"
echo "last_cycle = $last_cycle"

../corewar $files -d $last_cycle > .tmp1
../../resources/corewar $files -d $last_cycle > .tmp2
if diff .tmp1 .tmp2 > /dev/null
    then
        echo -e "$GREEN[OK]$NC"
    else
        echo -e "$RED[KO]$NC"
        diff .tmp1 .tmp2
fi
