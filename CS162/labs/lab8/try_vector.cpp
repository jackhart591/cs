#include "./vector.hpp"
#include <vector>
#include <iostream>

//We do not want to include either statement. We wouldn't be able to compare our vector template to the Standard
//using namespace std;
//using std::vector;
using std::cout;
using std::endl;

int main (){
   vector<int> v;   //Our vector class
   vector<int> v1;
   std::vector<int> stdv; //Standard vector

   v1.push_back(1);
   v1.push_back(2);

   cout << v1[0] << " " << v[1] << endl;

   v = v1;
   vector<int> v2 = v1;

   //Compare operation of our vector to std
   v.push_back(23);
   stdv.push_back(23);

   cout << "Should be 1: " << v[0] << endl;
   cout << "Should be 2: " << v2[1] << endl << endl;

   cout << "Our vector size: " << v.size() << endl;
   cout << "STL vector size: " << stdv.size() << endl;

   return 0;
}