#include "a.h"

using namespace std;

a::a(double w_to_be) { //pairnei san orisma to 4 * r opou r h mesi apostasi vectors
    w = w_to_be;

    //http://www.cplusplus.com/reference/random/uniform_real_distribution/
    const double range_from  = 0; //[
    const double range_to = w; //)
    std::random_device rand_dev;
    std::mt19937 generator(rand_dev());
    std::uniform_real_distribution<double>  distr(range_from, range_to);
    si = distr(generator); 
}

a::~a() {}


int a::get_a(double coordinate) { //pairnei san orisma ena coordinate enos vector (tupou double) kai epistrefei to ai(xi)
    double result = 0;
    result = coordinate - si;
    return floor(result / w);
}