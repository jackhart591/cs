#!/bin/bash
if [ -f stoogesort.cpp ];
then
    echo "C++ file"

	echo "Merge Sort 3"
	g++ mergesort3.cpp -std=c++11 -o mergesort3
	mergesort3 > merge3.txt
	mergesort3
	echo	
	
	echo "Stooge Sort"
	g++ stoogesort.cpp -std=c++11 -o stoogesort
	stoogesort > stooge.txt
	stoogesort
	echo	
	echo "Merge Sort 3 Comparison"
	diff -y -B -b --report-identical-files --suppress-common-lines merge3.txt sorted.txt

	echo "Stooge Sort Comparison"
	diff -y -B -b --report-identical-files --suppress-common-lines stooge.txt sorted.txt
	echo
	echo
	echo "Merge Sort 3 times"
	g++ ./merge3Time.cpp -std=c++11 -o merge3Time
	timeout 60s ./merge3Time
	echo
	echo "Stooge Sort times"
	g++ ./stoogeTime.cpp -std=c++11 -o stoogeTime
	timeout 60s ./stoogeTime
else
    echo "No C++ file"	
fi
if [ -f stoogesort.c ];
then
    echo "C file"
	echo "Stooge Sort"

	gcc -std=c99 -o stoogesort stoogesort.c 
	./stoogesort > stooge.txt
	stoogesort
	echo

	echo "Merge Sort 3"
	gcc -std=c99 -o mergesort3 mergesort3.c 
	./mergesort3 > merge3.txt
	mergesort3

	echo "Stooge Sort Comparison"

	diff -y -B -b --report-identical-files --suppress-common-lines stooge.txt sorted.txt
	echo "Merge Sort 3 Comparison"
	diff -y -B -b --report-identical-files --suppress-common-lines merge3.txt sorted.txt
	echo
	echo "Stooge Sort times"
	gcc -std=c99 -o stoogeTime stoogeTime.c 
	timeout 60s ./stoogeTime
	echo
	echo "Merge Sort 3 times"
	gcc -std=c99 -o merge3Time merge3Time.c 
	timeout 60s ./merge3Time
else
    echo "No C file"	
fi
if [ -f stoogesort.py ];
then
    echo "Python file"
	echo "Stooge Sort"

	python3 stoogesort.py > stooge.txt
	python3 stoogesort.py
	echo
	echo "Merge Sort 3"

	python3 mergesort3.py > merge3.txt
	python3 mergesort3.py
	echo "Stooge Sort Comparison"
	diff -y -B -b --report-identical-files --suppress-common-lines stooge.txt sorted.txt
	echo "Merge Sort 3 Comparison"
	diff -y -B -b --report-identical-files --suppress-common-lines merge3.txt sorted.txt
	echo
	echo "Stooge Sort times"
	timeout 60s python3 stoogeTime.py
	echo
	echo "Merge Sort 3 times"
	timeout 60s python3 merge3Time.py
else
    echo "No Python file"	
fi