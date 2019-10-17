#include "ht.h"

template <class T>
ht<T>::ht(int size_to_be, int k_to_be, int dimensions, int w_to_be){
    g_funs<T> my_g_to_be(k_to_be, dimensions, w_to_be);
    my_g = my_g_to_be;
    size = size_to_be;
}

template <class T>
ht<T>::~ht(){}

template <class T>
void ht<T>::hash_vector(my_vector<T> v) {

}

template <class T>
ht_cell<T>::ht_cell(my_vector<T> vek, long int tsan){
  my_vector<T> ji = vek;
  my_v = ji;
  g_value = tsan;
}

/*
template <class T>
int ht<T>::get_vector_bucket_number(my_vector<T> v) {}
*/
