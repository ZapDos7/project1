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
    my_g.actual_g_function(v);
}

template <class T>
ht_cell<T>::ht_cell(my_vector<T> vector_in_cell, long int g_val_to_be){
  my_vector<T> ji = vector_in_cell;
  my_v = ji;
  g_value = g_val_to_be;
}

template <class T>
my_vector<T> ht_cell<T>::get_vector() {
    return my_v;
}

template <class T>
long int ht_cell<T>::get_g_value() {
    return g_value;
}

template <class T>
void ht_cell<T>::set_vector(my_vector<T> my_v_to_be) {
    my_v = my_v_to_be;
    return;
}

template <class T>
void ht_cell<T>::set_g_value(long int my_g_val_to_be) {
    g_value = my_g_val_to_be;
    return;
}
