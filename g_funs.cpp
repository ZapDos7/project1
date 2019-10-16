#include "g_funs.h"

template <class T>
g_funs<T>::g_funs(int k_to_be) {
    k = k_to_be;
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