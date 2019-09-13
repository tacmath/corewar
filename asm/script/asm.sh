#!/bin/bash

BLUE='\033[0;36m'
GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m' # No Color

if [ ! -d "bin" ]
then
    echo "bin folder is missing"
    exit 1
fi

if [ ! -e "./bin/asm" ]
then
    echo "asm file is missing"
    exit 1
fi

if [ ! -e "./bin/asm-o" ]
then
    echo "asm-o file is missing"
    exit 1
fi

if [ ! -d "files" ]
then
    echo "files folder is missing"
    exit 1
fi

for filename in files/*.s
do
    error1=0
    error2=0
    cor_file="`echo $filename | rev | cut -c 2- | rev`cor"
    
    if ./bin/asm $filename > /dev/null 2>&1
    then
        if ! hexdump $cor_file > .tmp1  2> /dev/null
        then 
            error1=1
        fi
    else
        error1=1
    fi

    if ./bin/asm-o $filename > /dev/null 2>&1
    then 
        if ! hexdump $cor_file > .tmp2 2> /dev/null
        then 
            error2=1
        fi
    else
        error2=1
    fi

    printf -- "- $BLUE$(printf $filename | cut -d '/' -f 2)$NC:"
    if [ $error1 -eq 0 ] && [ $error2 -eq 0 ]
    then
        if diff ".tmp1" ".tmp2" > /dev/null
        then
            echo -e "$GREEN[OK]$NC"
        else
            echo -e "$RED[KO]$NC"
        fi
    else
        echo ""
        if [ $error1 -ne 0 ]
        then
            echo -e "    compile error asm"
        fi
        if [ $error2 -ne 0 ]
        then
            echo -e "    compile error asm-o"
        fi
    fi
    echo ""
done

rm -f .tmp1 .tmp2
rm -f files/*.cor
rm -f *.cor