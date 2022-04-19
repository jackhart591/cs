/******************************************************************************
CS 325 Activity 3 Canoe
Example input
input: number of trading posts (n) and an nxn table of rental costs	R. 
	R[i][j] is the cost to rent a canoe at trding post i and return it to 
	trading post j.	R[i][i] = 0  R[i][j] = -1 if i > j. 
output: the minimium cost a list of trading posts that were stopped at. 
note: there is a newline "endl" at end of the output
Extra: If there are more than one mode list them of seperate lines. List in order the value first appear in the original list
For example:    4
                0 10 15 40
				-1 0 5 15
				-1 -1 0 8
				-1 -1 -1 0
output: 23 1 3 4
submit to Gradescope as act3.cpp
*******************************************************************************/
#include <iostream>
#include <fstream>

void printTradingPosts(int* prev, int num) {
	for (int i = 0 ; i < num; i++)
		if (prev[i] != 0) {
			int temp = i;
			if (i != 1)
				temp++;
			std::cout << " " << temp;
		}
}

int main() {
	int R[100][100];
    int M[100]; // Minimum total penalty when you stop at place j from i
	int num;
	int minCost;   // minimum cost
	int prev[100]; // back pointer to the previous post in the optimal solution

	std::cin >> num;
    for (int i = 1; i <= num; i++)
		for(int j = 1; j <= num; j++)
			std::cin >> R[i][j];

	// find the minimum cost
	M[0] = 0;
    prev[0] = -1;
	for (int j = 1; j <= num; j++) {
        M[j] = 2147483647;
		for (int i = 0; i < j; i++) {
            if ((M[i] + R[i][j]) < M[j] || M[j] == 0) {
                M[j] = (M[i] + R[i][j]);
                prev[j] = i;
            }
        }
    }
	
	std::cout << M[num] << " ";

    int seen[100];
    bool isBeen = true;
    int k = 0;
    for (int i = 1; i < 100; i++) {
        if (prev[i] != 0 && prev[i] != -1) {
            isBeen = false;
            for (int j = 0; j < 100; j++) {
                if (seen[j] == prev[i])
                    isBeen = true;
            }

            if (isBeen)
                continue;
            else {
                std::cout << prev[i] << " ";
                seen[k] = prev[i];
                k++;
            }
        }
    }

    std::cout << num;
	return 1;
}