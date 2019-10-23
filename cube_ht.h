#ifndef CUBE_HT_H_
#define CUBE_HT_H_

#include "g_funs.h"
#include <unordered_map>
#include "my_vector.h"


template <class T>
class cube_ht
{
private:
  int size;
  int k_ys = 3; //arithmos h sunarthsewn, prota8hke hardcoded sto eclass
  int d_tonos;
  //std::unordered_map<int, ht_cell<T> > table; //key == int, mapped value == my_vectors //https://en.cppreference.com/w/cpp/container/unordered_map
  //std::vector<std::vector<std::pair<my_vector<T> *, long int>>> cube; //o "pinakas" opoy kathe bucket einai mia korufh tou yperkybou
  std::vector<std::vector<my_vector<T> *>> cube; //o "pinakas" opoy kathe bucket einai mia korufh tou yperkybou kai exei mesa deikth sto vector
  std::vector< g_funs<T> > my_gs; //oi sunarthseis g gia ton kybo
  std::vector<int> fi_seeds; //prokyptei apo uniform kai krata enan tetoio arithmo gia kathe f poy tha "dhmiourghsoyme"

  std::vector<std::string> verticizer;

public:
  //int size;
  //std::vector< std::vector< std::pair<my_vector<T> * , long int> > > table; //pinakas (o hash table) apo pinakes (h lista ana bucket) apo zeugaria (zeugari dianusmatos kai timhs g)
  //g_funs<T> my_g;
  cube_ht<T>(int d_ton, int vector_dimensions, int w_to_be); //constructor
  ~cube_ht();
  int fi_function(long int gval, int index);
  void cubify_vector(my_vector<T> *v);
  std::vector<int> cubify_query(my_vector<T> *q, int probes);
  //int get_vector_bucket_number(my_vector v);
  void hamming_magic(std::string str, int i, int changesLeft);
};

//supplementary function
//void hamming_magic(std::string str, int i, int changesLeft);
//boh8htikh metavlhth
//std::vector<std::string> verticizer;



#endif
