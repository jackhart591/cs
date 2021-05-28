#include "./vector.hpp"
#include <vector>
#include <iostream>
#include <stdexcept>

//We do not want to include either statement. We wouldn't be able to compare our vector template to the Standard
//using namespace std;
//using std::vector;
using std::cout;
using std::endl;

int main ()
{
    try
    {
        vector<int> v1(23);   //Our vector class
        vector<int> v2 = v1;
        vector<int> v3(13);
        std::vector<int> stdv; //Standard vector

        //Compare operation of our vector to std
        v1.push_back(23);
        v1.push_back(24);
        stdv.push_back(23);
        v3 = v1;

        cout << "Our vector size: " << v1.size() << endl;
        cout << "Our vector capacity: " << v1.capacity() << endl;
        cout << "Our copied vector size: " << v2.size() << endl;
        cout << "Our overloaded vector size: " << v3.size() << endl;
        cout << "STL vector size: " << stdv.size() << endl;

        for(int i = 0; i < v1.size(); i++)
        {
            cout << "array element of vector 1: " << i << " " << v1[i] << endl;
            cout << "array element of vector 3: " << i << " " << v3[i] << endl;
        }
        
        v1.resize(200);
        cout << "Our vector size: " << v1.capacity() << endl;
        
        //cout << v1.at(201) << endl;
        
    }catch(int i)
    {
        cout << "ACCESSED OUTSIDE AN ARRAY" << endl;
    }

    return 0;
}