#include "g_funs.h"

template <class T>
g_funs<T>::g_funs(int k_to_be, int dimensions, int w_to_be) {
    k = k_to_be;
    for (unsigned int i = 0; i < k; i++) {
        h_funs<T> temp_h_fun(k_to_be, dimensions, w_to_be);
        my_h_funs.push_back(temp_h_fun);
    }
}

template <class T>
g_funs<T>::~g_funs(){}

template <class T>
int g_funs<T>::actual_g_function() {//epistrefei int >= 0
    //pairnw tis k h_funs gia ena vector v
    //tis kanw concat (me left shift + addition)
    //to apotelesma to kanw mod Table_Size (blepe lsh.cpp)
    //auto kathorize pou bazw to v sto Hash Table m
}