#ifndef _CURVE_HT_H
#define _CURVE_HT_H
#include "curve.h"

template <class T>
class curve_ht
{
private:
  int size;
  std::vector<std::vector<std::pair<curve<T> *, long int>>> table; //pinakas (o hash table) apo pinakes (h lista ana bucket) apo zeugaria (zeugari dianusmatos kai timhs g)
  g_funs<T> my_g;

public:
  ht<T>(int size_to_be, int k_to_be, int dimensions, int w_to_be);
  ~ht();
  void hash_vector(my_vector<T> *v, curve<T> *cu);
  std::vector<int> hash_query(my_vector<T> *q);
  //int get_vector_bucket_number(my_vector v);
};

#endif
