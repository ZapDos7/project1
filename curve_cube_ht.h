#ifndef CURVE_CUBE_HT_H_
#define CURVE_CUBE_HT_H_

#include "g_funs.h"
#include <unordered_map>
#include "my_vector.h"
#include <fstream>
#include <algorithm>
#include "curve.h"

template <class T>
class curve_cube_ht
{
private:
  int size;
  int k_ys = 3; //arithmos h sunarthsewn, prota8hke hardcoded sto eclass
  int d_tonos;
  //std::unordered_map<int, ht_cell<T> > table; //key == int, mapped value == my_vectors //https://en.cppreference.com/w/cpp/container/unordered_map
  //std::vector<std::vector<std::pair<my_vector<T> *, long int>>> cube; //o "pinakas" opoy kathe bucket einai mia korufh tou yperkybou
  //std::vector<std::vector<curve<T> *>> cube; //o "pinakas" opoy kathe bucket einai mia korufh tou yperkybou kai exei mesa deikth sto vector
  std::unordered_map<std::string, std::vector<curve<T> *> > cube; //key == int, mapped value == my_vectors
  std::vector<g_funs<T>> my_gs;              //oi sunarthseis g gia ton kybo
  std::vector<int> fi_seeds;                 //prokyptei apo uniform kai krata enan tetoio arithmo gia kathe f poy tha "dhmiourghsoyme"

  std::vector<std::string> verticizer;
  //std::set<std::string> verticizerx;

public:
  //int size;
  //std::vector< std::vector< std::pair<my_vector<T> * , long int> > > table; //pinakas (o hash table) apo pinakes (h lista ana bucket) apo zeugaria (zeugari dianusmatos kai timhs g)
  //g_funs<T> my_g;
  curve_cube_ht<T>(int d_ton, int vector_dimensions, double w_to_be); //constructor
  curve_cube_ht<T>(){};
  ~curve_cube_ht();
  int fi_function(long int gval, int index);
  void cubify_vector(my_vector<T> *v, curve<T> *cu);
  std::vector<int> cubify_query(my_vector<T> *q, int probes);
  //int get_vector_bucket_number(my_vector v);
  void hamming_magic(std::string str, int i, int changesLeft);
};

//supplementary function
//void hamming_magic(std::string str, int i, int changesLeft);
//boh8htikh metavlhth
//std::vector<std::string> verticizer;

#endif
