#include "my_vector.h"

template <typename T>
T awful_metric(T n1, T n2){
	return (n1 > n2) ? n1 : n2;
}
