#include "a.h"

using namespace std;

template <class T>
a<T>::a(double w_to_be) { //pairnei san orisma to 4 * r opou r h mesi apostasi vectors
    w = w_to_be;

    //http://www.cplusplus.com/reference/random/uniform_real_distribution/
    const double range_from  = 0; //[
    const double range_to = w; //)
    std::random_device rand_dev;
    std::mt19937 generator(rand_dev());
    std::uniform_real_distribution<double>  distr(range_from, range_to);
    si = distr(generator);
    //fprintf(stderr, "My si is %f\n", si);
}

template <class T>
a<T>::~a() {}

template <class T>
int a<T>::get_a(T coordinate) { //pairnei san orisma ena coordinate enos vector kai epistrefei to ai(xi)
    double result = 0;
    result = coordinate - si;
    return (int)floor(result / w);
}

template class a<float>;
template class a<int>;
template class a<double>;