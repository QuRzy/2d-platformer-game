//
// Created by 73539 on 20.10.2021.
//

#ifndef MAIN_CPP_VECTOR_H
#define MAIN_CPP_VECTOR_H
#include <iostream>
template<class T>
class VECTOR {
private:
    T* array = nullptr;
    unsigned int sz;
public:
    VECTOR();
    VECTOR(unsigned int size);
    virtual ~VECTOR();
    unsigned  int size() const;
    void append();
    void append(T item);
    void erase(unsigned int index);
    operator T*&();
};
template<class T>
VECTOR<T>::VECTOR()
{
    array = nullptr;
    sz = 0;
}
template<class T>
VECTOR<T>::VECTOR(unsigned int size)
{
    sz = size;
    array = new  T[sz];
}
template<class T>
VECTOR<T>::~VECTOR()
{
    sz = 0;
    delete [] array;
}
template<class T>
unsigned int VECTOR<T>::size() const
{
    return sz;
}
template<class T>
void VECTOR<T>::append()
{
    T* newArray = new T[sz + 1];
    for(int i = 0; i < sz; ++i)
    {
        newArray[i] = array[i];
    }
    sz += 1;
    delete [] array;
    array = newArray;
}
template<class T>
void VECTOR<T>::append(T item)
{
    T* newArray = new T[sz + 1];
    for(int i = 0; i < sz; ++i)
    {
        newArray[i] = array[i];
    }
    newArray[sz] = item;
    sz += 1;
    delete [] array;
    array = newArray;
}
template<class T>
void VECTOR<T>::erase(unsigned int index)
{
    if(index >= sz) {
        std::cerr << "Wrong Index" << std::endl;
        exit(1);
    }
    T* newArray = new T[sz - 1];
    int j = 0;
    for(int i = 0; i < sz; ++i)
    {
        if(i != index)
        {
            newArray[j] = array[i];
            j++;
        }
    }
    sz--;
    delete [] array;
    array = newArray;
}
template<class T>
VECTOR<T>::operator T*&()
{
    return array;
}


#endif //MAIN_CPP_VECTOR_H
