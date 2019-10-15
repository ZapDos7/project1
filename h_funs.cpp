#include "h_funs.h"

template <class T>
h_funs<T>::h_funs(int k, int dimens, int w_to_be) {
    M = floor(pow(2,(double)(32/k)));
    dimensions = dimens;
    w = w_to_be;
    //now si's
    //http://www.cplusplus.com/reference/random/uniform_real_distribution/
    std::random_device rand_dev;
    std::mt19937 generator(rand_dev());
    std::uniform_real_distribution<double>  distr(0, w);
    for (int i=0; i<dimensions; ++i) {
        sis[i] = distr(generator);
        fprintf(stderr, "%f\n", sis[i]);
    }
}

template <class T>
h_funs<T>::~h_funs() {}

template <class T>
long int actual_function(my_vector<T> x) {
    /*
    double result = 0;
    result = coordinate - si;
    return (int)floor(result / w);
    */
   long int result = 0;
   return result;
}

template class h_funs<float>;
template class h_funs<int>;
template class h_funs<double>;