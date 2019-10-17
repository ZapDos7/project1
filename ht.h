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
    g_funs<T> my_g;
public:
    ht(int size_to_be, int k_to_be, int dimensions, int w_to_be);
    ~ht();
    void hash_vector(my_vector<T> v);
    //int get_vector_bucket_number(my_vector v);
};

template <class T>
class ht_cell {
private:
  my_vector<T> my_v;
  long int g_value;
public:
  ht_cell(my_vector<T> vek, long int tsan);
  ~ht_cell();
};


#endif
