#!/bin/bash

for f in $(find binary)
do
	string=$(file $f);
	if [[ $string =~ "x86_64" ]]
	then
		echo $f >> x86_64.txt
	elif [[ $string =~ "i386" ]]
	then
		echo $f >> i386.txt
	else
		echo $f >> unknown.txt
	fi
done
