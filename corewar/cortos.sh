#!/bin/bash

if [ $# -ne 2 ]
then
	echo "Le 1er parametre doit etre le chemin vers le dossier contenant les .s"
	echo "Le 2e parametre doit etre le chemin vers l'asm"
	exit
fi

dir=$1
asm=$2

if [ ! -d $dir ]
then
	echo "Le chemin vers le dossier est invalide"
	exit
fi

if [ ! -f $asm ]
then
	echo "Le chemin vers l'asm est invalide"
	exit
fi

for file in $dir/*.s
do
	$asm $file > /dev/null 2>&1
done

if [ ! -d "cor" ]
then
	mkdir "cor"
fi

mv $dir/*.cor "cor"
echo "Done."
