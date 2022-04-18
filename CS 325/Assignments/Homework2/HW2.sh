#!/bin/bash
if [ -f knapsack.cpp ];
then
    echo "C++ file"

	echo "Knapsack DP vs Recursive"
	g++ knapsack.cpp -std=c++11 -o knapsack
	timeout 60s ./knapsack

	echo "Shopping Spree"
	echo

	g++ shopping.cpp -std=c++11 -o shopping
	./shopping > my_results.txt
	./shopping

	echo "Comparing results "
	diff -y -B -b --report-identical-files --suppress-common-lines my_results.txt HW2Solution.txt
	echo
else
    echo "No C++ file"	
fi
if [ -f knapsack.c ];
then
    echo "C file"
	echo "Knapsack DP vs Recursive"
	gcc -std=c99 -o knapsack knapsack.c 
	timeout 60s ./knapsack

	echo "Shopping Spree"
	echo

	gcc -std=c99 -o shopping shopping.c 
	./shopping > my_results.txt
	./shopping

	echo "Comparing results "
	diff -y -B -b --report-identical-files --suppress-common-lines my_results.txt HW2Solution.txt
	echo
else
    echo "No C file"	
fi
if [ -f knapsack.py ];
then
    echo "Python file"
	echo "Knapsack Recursive vs DP"
	echo

	timeout 60s python3 knapsack.py
	echo

	python3 shopping.py > my_results.txt
	python3 shopping.py

	echo "Comparing results "
	diff -y -B -b --report-identical-files --suppress-common-lines my_results.txt HW2Solution.txt
	echo
else
    echo "No Python file"	
fi