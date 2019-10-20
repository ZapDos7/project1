#ifndef _HT_H_
#define _HT_H_

#include "g_funs.h"
#include <unordered_map>
#include "my_vector.h"

//HT_CELL
template <class T>
class ht_cell {
private:
  my_vector<T> my_v;
  long int g_value;
public:
  ht_cell<T>(my_vector<T> vector_in_cell, long int g_val_to_be);
  ht_cell<T>(){};
  ~ht_cell();
  my_vector<T> get_vector();
  long int get_g_value();
  void set_vector(my_vector<T> my_v_to_be);
  void set_g_value(long int my_g_val_to_be);
};

//HT

template <class T>
class ht
{
private:
    int size;
    //std::unordered_map<int, ht_cell<T> > table; //key == int, mapped value == my_vectors //https://en.cppreference.com/w/cpp/container/unordered_map
    //std::vector< std::vector< std::pair<my_vector<T> * , long int> > > table; //pinakas (o hash table) apo pinakes (h lista ana bucket) apo zeugaria (zeugari dianusmatos kai timhs g)
    g_funs<T> my_g;
public:
    //int size;
    std::vector< std::vector< std::pair<my_vector<T> * , long int> > > table; //pinakas (o hash table) apo pinakes (h lista ana bucket) apo zeugaria (zeugari dianusmatos kai timhs g)
    //g_funs<T> my_g;
    ht<T>(int size_to_be, int k_to_be, int dimensions, int w_to_be);
    ~ht();
    void hash_vector(my_vector<T> *v);
    std::vector<int> hash_query(my_vector<T> q);
    //int get_vector_bucket_number(my_vector v);
};


#endif
