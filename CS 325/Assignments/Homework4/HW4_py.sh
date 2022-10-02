#!/bin/bash
python3 mst.py > my_results.txt
python3 mst.py
echo
echo "Solution"
echo
cat HW4solution.txt
echo
diff -y -B -b --report-identical-files --suppress-common-lines my_results.txt HW4solution.txt
echo

