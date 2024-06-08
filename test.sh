#!/bin/bash

tests="type-checking"
let count=0;

for f in $(ls ./tests/$tests/*.txt); do
	./a.out <$f > ./tests/$tests/`basename $f .txt`.output;
done;

for f in $(ls ./tests/$tests/*.output); do
	diff -Bw $f  ./tests/$tests/`basename $f .output`.txt.expected > ./tests/$tests/`basename $f .output`.diff;
done

for f in $(ls ./tests/$tests/*.diff); do
	echo -e "\n========================================================";
	echo "FILE:" `basename $f .output`;
	echo "========================================================";
	if [ -s $f ]; then
		cat ./tests/$tests/`basename $f .diff`.txt;
		echo "--------------------------------------------------------";
		cat $f
		echo "========================================================";
	else
		count=$((count+1));
		echo "NO ERRORS HERE!";
		echo "========================================================";
	fi
done

echo -e "\nTESTS PASSED:" $count"/12\n";

rm tests/$tests/*.output
rm tests/$tests/*.diff
