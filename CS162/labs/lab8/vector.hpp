#include <stdlib.h>
#include <iostream>

template <class T>
class vector {
private:
    T* v;
    int s;
    int capacity;

public:
    vector(){
        s=0;
        capacity = 0;
        v=NULL;
    }

    ~vector(){ delete [] v; }

    int size() { return s; }
    int Capacity() { return this->capacity; }

    /*doesn't work, try re-writing*/
    void push_back(T ele) {
        T* temp;

        if (this->capacity == this->s) {
            this->capacity++;
        }

        temp = new T[++s];
        
        for(int i=0; i<s-1; i++)
            temp[i]=v[i];

        if (v) { delete [] v; }

        v=temp;
        v[s-1]=ele;
    }

    void Resize(int x) {
        if (this->capacity >= x) {
            T* temp = new T[x];
            for (int i = 0; i < x; i++) {
                temp[i] = this->v[i];
            }
            delete [] this->v;
            this->v = temp;
            this->s = x;
        } else {
            T* temp = new T[x];
            for (int i = 0; i < this->capacity; i++) {
                temp[i] = this->v[i];
            }
            delete [] this->v;
            this->v = temp;
        }

        this->capacity = x;
    }

    T& operator[](int i) { return v[i]; }

    vector(vector<T> &other){
        this->v = new T[other.Capacity()];
        this->s = 0;
        capacity = other.Capacity();
        for (int i = 0; i < other.size(); i++) {
            this->v[i] = other[i];
            std::cout << i;
        }

        s = other.size();
    }

    void operator=(vector<T> &other){
        if (v) { delete v; }
        this->v = new T[other.Capacity()];
        this->capacity = other.Capacity();
        for(int i = 0; i < s; i++) {
            v[i] = other[i];
        }

        s = other.size();
    }

    T& at(int i) {
        if (i < this->size() && i >= 0) {
            return v[i];
        } else { return NULL; }
    }
};