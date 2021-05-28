#include <stdlib.h>
#include <iostream>
#include <stdexcept>
template <class T>
class vector {
    private:
        T *v;
        int s;
        int c;
    public:
        vector()
        {
            s=0;
            v=NULL;
            c=0;
        }

        vector(int size)
        {
            c = size;
            s = 0;
            v = new T[size];
        }

        ~vector()
        {
            delete [] v;
        }

        int capacity()
        {
            return c;
        }
        
        int size() 
        {
            return s;
        }

        void push_back(T ele) 
        {
            if(s == c)
            {
                c *= 2;
        
                T* temp;
                for(int i = 0; i <= this->s; i++)
                {
                    temp[i] = v[i];
                }
                delete[] v;

                this->v = new T[c];
                v=temp;
            }

            s++;
            v[s-1]=ele;
        }

        vector(vector<T> &other)
        {
            std::cout << "Copy Constructor" << std::endl;

            this->c = other.c;
            this->s = other.s;
            this->v = new T[this->c];

            for(int i = 0; i < this->s; i++)
            {
                this->v[i] = other.v[i];
            }
        }

        void operator=(vector<T> &other)
        {
            if(this != &other)
            {
                std::cout<< "Assignment Overload Operator" << std::endl;
                if(v)
                {
                    delete[] v;
                    v = NULL;
                    s = 0;
                }

                this->c = other.c;
                this->s = other.s;
                this->v = new T[this->c];

                for(int i = 0; i < this->s; i++)
                {
                    this->v[i] = other.v[i];
                }
            }
        }

        T& operator[](int i)
        {
            return v[i];
        }

        T& at(int i)
        {
            if(i > c)
            {
                throw 1;
            }
            return v[i];  
        }

        void resize(int size)
        {
            T *temp;
            temp = new T[size];
            for(int i=0; i<s-1; i++)
            {
                temp[i]=v[i];
            }
            delete [] v;
            
            this->c = size;
            v=temp;
        }
};