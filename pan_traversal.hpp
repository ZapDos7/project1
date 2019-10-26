#ifndef _PAN_TRAVERSAL_H
#define _PAN_TRAVERSAL_H

#include "curve.h"
#include "curve_point.h"
#include <cmath>
#include <limits>
#include <typeinfo>

template <class T>
class traversal
{
private:
  std::pair<std::string, std::string> curve_ids;
  std::vector<std::pair<int, int>> my_traversal;

public:
  traversal<T>(){};
  traversal<T>(curve<T> *c1, curve<T> *c2);
  ~traversal<T>();
  std::string get_c_id_1();
  std::string get_c_id_2();
  std::vector<std::pair<int, int>> get_my_traversal();
  void add_pair(int, int);
  void set_c_id_1(std::string);
  void set_c_id_2(std::string);
};

class traversal_node
{
public:
  std::pair<int, int> zeugos;
  traversal_node *left;   //aristera shmainei kineitai o first
  traversal_node *center; //kentro shmainei kinountai kai oi 2
  traversal_node *right;  //deksia shmainei kineitai o second

  traversal_node(){};
  ~traversal_node(){};                                          //DOULITSA
  void recursive_builder(int curve1_length, int curve2_length); //sunexizei to dentro me riza ton idio ton komvo
  bool is_leaf();
};

template <class T>
class traversal_tree
{
private:
  traversal_node root;                                         //h riza tou dentrou me ta traversals
  std::vector<std::vector<traversal_node *>> draft_traversals; //pinakas apo pinakes komvwn tou dentrou. Enas pinakas komvwn einai ena traversal.
public:
  traversal_tree<T>(curve<T> *c1, curve<T> *c2);
  ~traversal_tree<T>(){}; //DOULITSA
  traversal_node *access_root();
  //get all traversals
  void recursive_search(traversal_node *rut, std::vector<traversal_node *> tool);
  /*MIA ENDEIKTIKH KLHSH THS EINAI: (apo to dentro)
    std::vector<traversal_node *> vek;
    vek.clear();
    recursive_search(&root, vek);
    twra tha prepei na exei gemisei o draft_traversals
    */
  std::vector<traversal<T>> objectify_travs(curve<T> *c1, curve<T> *c2); //kanei to draft traversals --> proper vector apo traversals!
};

template <class T>
class dtw
{
private:
  /* data */
public:
  dtw(){};
  ~dtw(){};
  double euclidean(curve_point<T> cp1, curve_point<T> cp2);
  double actual_dtw(curve<T> *c1, curve<T> *c2);
};

template <class T>
double dtw<T>::actual_dtw(curve<T> *c1, curve<T> *c2)
{
  //gia kathe pithano traversal metaksu twn 2 kampulwn
  //pairnw to min sum twn apolutwn diaforwn kapoiwn shmeiwn pk, qk (idio indice gia ta 2 curves)
  traversal_tree<T> my_tree(c1, c2);
  std::vector<traversal_node *> tool;
  tool.clear();
  my_tree.recursive_search(my_tree.access_root(), tool); //gemise o draft_traversals mou
  std::vector<traversal<T>> vec_trav;
  vec_trav = my_tree.objectify_travs(c1, c2);
  std::vector<double> apostaseis;
  for (unsigned int i = 0; i < vec_trav.size(); i++) //gia kathe pithano traversal metaksu twn 2 kampulwn
  {
    std::vector<std::pair<int, int>> ena_traversal;
    ena_traversal = vec_trav[i].get_my_traversal();
    double sum_eucl = 0.0;
    double eucl = 0.0;
    for (unsigned int j = 0; j < ena_traversal.size(); j++) //gia kathe zeugari apo indices
    {
      curve_point<T> shmeio_ths_c1 = c1->get_points()[ena_traversal[j].first];  //c1[first] = curvepoimt1
      curve_point<T> shmeio_ths_c2 = c2->get_points()[ena_traversal[j].second]; //c2[second] = curvepoint2
      eucl = euclidean(shmeio_ths_c1, shmeio_ths_c2);                           //euclidean apostasi (cp1, cp2)
      sum_eucl += eucl;                                                         //a8roizw tis euclidean ana index gia auto to traversal
    }
    eucl = 0.0; //ksanamhdenizw to eucl pou einai o metritis kathe apostasis
    apostaseis.push_back(sum_eucl);
    sum_eucl = 0.0;
  }
  double result = std::numeric_limits<double>::max();  //pairnei timh apeiro;
  for (unsigned int i = 0; i < apostaseis.size(); i++) //get min of apostaseis
  {
    if (apostaseis[i] <= apostaseis[i + 1])
    {
      if (result > apostaseis[i])
      {
        result = apostaseis[i];
      }
    }
    else //(apostaseis[i] > apostaseis[i+1])
    {
      if (result > apostaseis[i + 1])
      {
        result = apostaseis[i + 1];
      }
    }
  }
  return result;
}

template <class T>
traversal<T>::~traversal() {}

template <class T>
std::string traversal<T>::get_c_id_1() { return curve_ids.first; }

template <class T>
std::string traversal<T>::get_c_id_2() { return curve_ids.second; }

template <class T>
std::vector<std::pair<int, int>> traversal<T>::get_my_traversal() { return my_traversal; }

template <class T>
void traversal<T>::add_pair(int i, int j)
{
  std::pair<int, int> tmppair;
  tmppair.first = i;
  tmppair.second = j;
  my_traversal.push_back(tmppair);
}
template <class T>
void traversal<T>::set_c_id_1(std::string id) { curve_ids.first = id; }

template <class T>
void traversal<T>::set_c_id_2(std::string id) { curve_ids.second = id; }

//TRAVERSAL TREE
template <class T>
traversal_tree<T>::traversal_tree(curve<T> *c1, curve<T> *c2)
{
  draft_traversals.clear();
  traversal_node seed_of_life;
  root = seed_of_life;
  root.zeugos.first = 0;
  root.zeugos.second = 0;
  root.left = NULL;
  root.center = NULL;
  root.right = NULL;
  root.recursive_builder((int)c1->get_size(), (int)c2->get_size());
}

template <class T>
void traversal_tree<T>::recursive_search(traversal_node *rut, std::vector<traversal_node *> tool)
{
  std::vector<traversal_node *> tool2;
  tool2.clear();
  tool2 = tool;
  tool2.push_back(rut);
  if (rut->is_leaf()) //einai fyllo, pernaw th diadromh ston MEGALO pinaka
  {
    draft_traversals.push_back(tool2);
    for (unsigned int mama = 0; mama < tool2.size(); mama++)
    {
      std::cout << tool2[mama]->zeugos.first << ' ' << tool2[mama]->zeugos.second << '\t';
    }
    std::cout << '\n';
  }

  else
  {
    if (rut->left != NULL)
      recursive_search(rut->left, tool2);
    if (rut->center != NULL)
      recursive_search(rut->center, tool2);
    if (rut->right != NULL)
      recursive_search(rut->right, tool2);
  }
}

bool traversal_node::is_leaf()
{
  if ((left == NULL) && (center == NULL) && (right == NULL))
    return true;
  else
    return false;
}

void traversal_node::recursive_builder(int curve1_length, int curve2_length)
{
  //shmainei oti tha ginoyn anadromikes klhseis-dhmiourgia gia autes
  //ypopshfio aristero paidi
  //std::cout << zeugos.first << " " << zeugos.second << curve1_length <<"\n";
  left = new traversal_node();
  left->zeugos.first = zeugos.first + 1;
  left->zeugos.second = zeugos.second;
  left->left = NULL;
  left->right = NULL;
  left->center = NULL;
  bool left_ok = true;

  //ypopshfio kentriko paidi
  center = new traversal_node();
  center->zeugos.first = zeugos.first + 1;
  center->zeugos.second = zeugos.second + 1;
  center->left = NULL;
  center->right = NULL;
  center->center = NULL;
  bool center_ok = true;

  //ypopshfio deksio paidi
  right = new traversal_node();
  right->zeugos.first = zeugos.first;
  right->zeugos.second = zeugos.second + 1;
  right->left = NULL;
  right->right = NULL;
  right->center = NULL;
  bool right_ok = true;

  if ((zeugos.first == curve1_length - 1) || (zeugos.second == curve2_length - 1))
  {

    delete center;
    center = NULL;
    center_ok = false;
  }

  if (zeugos.first == curve1_length - 1) //ftasame sto telos ths 1hs kampylhs
  {

    delete left;
    left = NULL;
    left_ok = false;
  }

  if (zeugos.second == curve2_length - 1) //ftasame sto telos ths 1hs kampylhs
  {
    delete right;
    right = NULL;
    right_ok = false;
  }

  if (left_ok)
    left->recursive_builder(curve1_length, curve2_length);

  if (center_ok)
    center->recursive_builder(curve1_length, curve2_length);

  if (right_ok)
    right->recursive_builder(curve1_length, curve2_length);
}
template <class T>
traversal_node *traversal_tree<T>::access_root() { return &root; }

template <class T>
std::vector<traversal<T>> traversal_tree<T>::objectify_travs(curve<T> *c1, curve<T> *c2)
{
  std::vector<traversal<T>> to_be_returned;
  //theloume kathe vector apo <tr_node*> na to kanoume traversal
  for (unsigned int i = 0; i < draft_traversals.size(); i++)
  {
    traversal<T> temp_trav;
    for (unsigned int j = 0; j < draft_traversals[i].size(); j++) //i,j == ena node
    {
      temp_trav.add_pair(draft_traversals[i][j]->zeugos.first, draft_traversals[i][j]->zeugos.second);
    }
    temp_trav.set_c_id_1(c1->get_id());
    temp_trav.set_c_id_2(c2->get_id());
    to_be_returned.push_back(temp_trav);
  }
  return to_be_returned;
}

template <class T>
double dtw<T>::euclidean(curve_point<T> cp1, curve_point<T> cp2)
{
  T x1 = cp1.get_x();
  T y1 = cp1.get_y();

  T x2 = cp2.get_x();
  T y2 = cp2.get_y();

  T x = x1 - x2; //calculating number to square in next step
  T y = y1 - y2;
  double dist;

  if (typeid(x) != typeid(y))
  {
    std::cerr << "Incompatible curve point types (What are you doing?!)\n";
    exit(-1);
  }
  if (typeid(x) == typeid(int))
  {
    int x_faux = x;
    int y_faux = y;
    dist = pow((double)x_faux, 2) + pow((double)y_faux, 2); //calculating Euclidean distance
    dist = sqrt(dist);
  }
  else if (typeid(x) == typeid(double))
  {
    double x_faux = x;
    double y_faux = y;
    dist = pow(x_faux, 2) + pow(y_faux, 2); //calculating Euclidean distance
    dist = sqrt(dist);
  }

  return dist;
}

template <typename T>
double true_euclidean(curve_point<T> cp1, curve_point<T> cp2)
{
  T x1 = cp1.get_x();
  T y1 = cp1.get_y();

  T x2 = cp2.get_x();
  T y2 = cp2.get_y();

  T x = x1 - x2; //calculating number to square in next step
  T y = y1 - y2;
  double dist;

  if (typeid(x) != typeid(y))
  {
    std::cerr << "Incompatible curve point types (What are you doing?!)\n";
    exit(-1);
  }
  if (typeid(x) == typeid(int))
  {
    int x_faux = x;
    int y_faux = y;
    dist = pow((double)x_faux, 2) + pow((double)y_faux, 2); //calculating Euclidean distance
    dist = sqrt(dist);
  }
  else if (typeid(x) == typeid(double))
  {
    double x_faux = x;
    double y_faux = y;
    dist = pow(x_faux, 2) + pow(y_faux, 2); //calculating Euclidean distance
    dist = sqrt(dist);
  }

  return dist;
}

#endif
