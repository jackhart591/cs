#!/bin/bash
python3 activity.py > my_results.txt
python3 activity.py
echo
echo "Solution"
echo
cat solution.txt
echo
diff -y -B -b --report-identical-files --suppress-common-lines my_results.txt solution.txt
echo

