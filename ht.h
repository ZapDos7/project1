#ifndef _HT_H_
#define _HT_H_

#include "g_funs.h"
#include <unordered_map>
#include "my_vector.h"



template <class T>
class ht
{
private:
    int size;
    //https://en.cppreference.com/w/cpp/container/unordered_map
    std::unordered_map<int, my_vector<T>> table; //key == int, mapped value == my_vectors
    g_funs my_g;
public:
    ht(int size_to_be, int k_to_be, int dimensions, int w_to_be);
    ~ht();
    void hash_vector(my_vector v);
    //int get_vector_bucket_number(my_vector v);
};

#endif