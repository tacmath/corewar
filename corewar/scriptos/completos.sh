#!/bin/bash

GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m'
error=0 
nb1=5
nb2=10

if [ $# -eq 2 ]
then
	nb1=$1
	nb2=$2
fi

make -C ../../
sh testos.sh $nb1
error=$?
sh dumpos.sh -r $nb2
((error+=$?))

printf "\n\n❤️ ❤️ ❤️ ❤️ ❤️ ❤️ ❤️ ❤️ ❤️ ❤️ ❤️ ❤️ ❤️ ❤️ ❤️ ❤️ ❤️ ❤️ ❤️ ❤️ ❤️ ❤️ ❤️ ❤️ ❤️ ❤️ ❤️ ❤️ ❤️ ❤️ ❤️ ❤️ ❤️ ❤️ ❤️ ❤️ ❤️ ❤️ ❤️ ❤️ ❤️ ❤️ ❤️ ❤️ ❤️ ❤️ ❤️ ❤️"
if [ $error -eq 0 ]
then
	echo ${GREEN}
else
	echo ${RED}
fi
printf '❤️                                                                                             ❤️ \n❤️\033[1m%50s \033[0m                                          ❤️ \n❤️                                                                                             ❤️ \n' "Errors = $error / $(($nb1 + $nb2))"
echo "❤️ ❤️ ❤️ ❤️ ❤️ ❤️ ❤️ ❤️ ❤️ ❤️ ❤️ ❤️ ❤️ ❤️ ❤️ ❤️ ❤️ ❤️ ❤️ ❤️ ❤️ ❤️ ❤️ ❤️ ❤️ ❤️ ❤️ ❤️ ❤️ ❤️ ❤️ ❤️ ❤️ ❤️ ❤️ ❤️ ❤️ ❤️ ❤️ ❤️ ❤️ ❤️ ❤️ ❤️ ❤️ ❤️ ❤️ ❤️"
exit $error
