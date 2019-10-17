#include "g_funs.h"

template <class T>
g_funs<T>::g_funs(int k_to_be, int dimensions, int w_to_be) {
    k = k_to_be;
    for (int i = 0; i < k; i++) {
        h_funs<T> temp_h_fun(k_to_be, dimensions, w_to_be);
        my_h_funs.push_back(temp_h_fun);
    }
}

template <class T>
g_funs<T>::~g_funs(){}

template <class T>
long int g_funs<T>::actual_g_function(my_vector<T> x) {//epistrefei int >= 0
    //pairnw tis k h_funs gia ena vector v
    //tis kanw concat (me left shift + addition)
    //to apotelesma to kanw mod Table_Size (blepe lsh.cpp)
    //auto kathorize pou bazw to v sto Hash Table m
    //std::vector<T> the_v = x.get_v();
    //long int g_value=0;
    //long int g_value2=0;
    //std::bitset<32> g_value(0);
    std::bitset<8> g_value2(0);
    long int temp;
    for(int i =0; i<k; i++){
        temp = my_h_funs[i].actual_h_function(x);
        std::bitset<8> x(temp);
        std::cout << x << '\n';
        x = x >> i+1;
        //g_value += x;
        g_value2 = g_value2 | x;
    }

    std::cout /*<< g_value*/ << " " << g_value2 << "\n";
    long int num = 0;
    int tempInt;
    for(int i=0; i<8; i++){
        tempInt=g_value2[i]-'0';
        num |= (1 << (8-1-i)) * tempInt;
        //num=num+tempInt * pow(2,(sLength-1-i));
    }

    return num;
    //return g_value;

}

template class g_funs<int>;
