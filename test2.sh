#!/bin/bash

let count=0;
for f in $(ls ./tests/parser-tests/*.txt); do
	./a.out <$f > ./tests/parser-tests/`basename $f .txt`.output;
done;

for f in $(ls ./tests/parser-tests/*.output); do
	diff -Bw $f  ./tests/parser-tests/`basename $f .output`.txt.expected > ./tests/parser-tests/`basename $f .output`.diff;
done

for f in $(ls ./tests/parser-tests/*.diff); do
	echo -e "\n========================================================";
	echo "FILE:" `basename $f .output`;
	echo "========================================================";
	if [ -s $f ]; then
		cat ./tests/parser-tests/`basename $f .diff`.txt;
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

rm tests/parser-tests/*.output
rm tests/parser-tests/*.diff
