#include "traversal.h"

template <class T>
traversal<T>::traversal(curve<T> *c1, curve<T> *c2)
{
  curve_ids.first = c1->get_id();
  curve_ids.second = c2->get_id();
  unsigned int m1 = c1->get_size(); //size of posa traversals exw?
  unsigned int m2 = c2->get_size();
  if ((m1 == 0) || (m2 == 0)) //at least one is empty
  {
    std::cerr << "Curves have no points, therefore there are no traversals\n";
    indices.clear();
  }
  else
  {
    //edw 8a baloume traversal_tree
  }
}

template <class T>
traversal<T>::~traversal() {}

template <class T>
std::vector<std::pair<int, int>> traversal<T>::get_all_possible_travs()
{
  return indices;
}

//TRAVERSAL TREE

traversal_tree::traversal_tree(int curve1_length, int curve2_length)
{
  traversal_node seed_of_life;
  root = seed_of_life;
  root.zeugos.first = 0;
  root.zeugos.second = 0;
  root.left = NULL;
  root.center = NULL;
  root.right = NULL;
  root.recursive_builder(curve1_length, curve2_length);
}

void traversal_node::recursive_builder(int curve1_length, int curve2_length)
{
  bool left_ok, center_ok, right_ok = true; //shmainei oti tha ginoyn anadromikes klhseis-dhmiourgia gia autes
  //ypopshfio aristero paidi
  traversal_node *left = new traversal_node();
  left->zeugos.first = zeugos.first + 1;
  left->zeugos.second = zeugos.second;
  left->left = NULL;
  left->right = NULL;
  left->center = NULL;

  //ypopshfio kentriko paidi
  traversal_node *center = new traversal_node();
  center->zeugos.first = zeugos.first + 1;
  center->zeugos.second = zeugos.second + 1;
  center->left = NULL;
  center->right = NULL;
  center->center = NULL;

  //ypopshfio deksio paidi
  traversal_node *right = new traversal_node();
  right->zeugos.first = zeugos.first;
  right->zeugos.second = zeugos.second + 1;
  right->left = NULL;
  right->right = NULL;
  right->center = NULL;

  if (zeugos.first == curve1_length - 1) //ftasame sto telos ths 1hs kampylhs
  {
    delete left;
    left = NULL;
    left_ok = false;
    delete center;
    center = NULL;
    center_ok = false;
  }

  if (zeugos.second == curve2_length - 1) //ftasame sto telos ths 1hs kampylhs
  {
    delete right;
    right = NULL;
    right_ok = false;
    delete center;
    center = NULL;
    center_ok = false;
  }

  if (left_ok)
    left->recursive_builder(curve1_length, curve2_length);

  if (center_ok)
    center->recursive_builder(curve1_length, curve2_length);

  if (right_ok)
    right->recursive_builder(curve1_length, curve2_length);
}
