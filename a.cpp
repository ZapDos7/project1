#include "a.h"

using namespace std;

a::a(double w_to_be) {
    w = w_to_be;

    const double range_from  = 0; //[
    const double range_to = w; //)
    std::random_device rand_dev;
    std::mt19937 generator(rand_dev());
    std::uniform_int_distribution<double>  distr(range_from, range_to);
    si = distr(generator); //http://www.cplusplus.com/reference/random/uniform_real_distribution/
}

a::~a() {}


int a::get_a(double coordinate) {
    double result = 0;
    result = coordinate - si;
    return floor(result / w);
}