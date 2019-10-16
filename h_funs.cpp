#include "h_funs.h"

/*
template <class T>
int our_mod(T a, T b){ //returns remainder as it should
	return (a % b + b) % b;
}
*/


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
        //sis[i].push_back(distr(generator);
        sis.push_back(distr(generator));
        //fprintf(stderr, "%f\n", sis[i]);
    }
}

template <class T>
h_funs<T>::~h_funs() {}

template <class T>
long int h_funs<T>::actual_function(my_vector<T> x) {
    /*
    double result = 0;
    result = coordinate - si;
    return (int)floor(result / w);
    */
    std::vector<T> the_v = x.get_v();
    long int result_part =0; //h ontothta m^d * ai mod M, sto telos 8a a8roistoun auta gia to teliko apotelesma ths h
    long int ai =0;
    long int result = 0;
    for(int i=0; i<dimensions; i++){
        ai = floor((the_v[i] - sis[i])/w);
        result_part = floor(pow(m, (double)(dimensions - i) ));
        result_part *= ai;
        result_part = our_mod(result_part, M);
        result += result_part;
    }

   return result;
}

int our_mod (int a, int b){ //returns remainder as it should
	return (a % b + b) % b;
}


int mod_pow(int b, int e, int m) {
	int c = 1;
	if (m==1) {
		return 0;
	}
	else {
		for (int i = 0; i < e; i++) {
			c = our_mod(c*b, m);
		}
		return c;
	}
}


template class h_funs<float>;
template class h_funs<int>;
template class h_funs<double>;
