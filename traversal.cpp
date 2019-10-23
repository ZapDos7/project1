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

  }
}

template <class T>
traversal<T>::~traversal() {}

template <class T>
std::string traversal<T>::get_c_id_1() { return curve_ids.first; }

template <class T>
std::string traversal<T>::get_c_id_1() { return curve_ids.second; }

template <class T>
std::vector<std::pair<int, int>> traversal<T>::get_my_traversal()
{
  return my_traversal;
}

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
void traversal_tree<T>::recursive_search(traversal_node * rut, std::vector<traversal_node *> tool){
  std::vector<traversal_node *> tool2;
  tool2.clear();
  tool2 = tool;
  tool2.push_back(rut);
  if(rut->is_leaf()) //einai fyllo, pernaw th diadromh ston MEGALO pinaka
    draft_traversals.push_back(tool2);
  else{
    if(rut->left != NULL)
      recursive_search(rut->left, tool2);
    if(rut->center != NULL)
      recursive_search(rut->center, tool2);
    if(rut->right != NULL)
      recursive_search(rut->right, tool2);
  }
}


bool traversal_node::is_leaf(){
  if((left==NULL)&&(center==NULL)&&(right ==NULL))
    return true;
  else
    return false;
}

void traversal_node::recursive_builder(int curve1_length, int curve2_length)
{
  bool left_ok, center_ok, right_ok = true; //shmainei oti tha ginoyn anadromikes klhseis-dhmiourgia gia autes
  //ypopshfio aristero paidi
  left = new traversal_node();
  left->zeugos.first = zeugos.first + 1;
  left->zeugos.second = zeugos.second;
  left->left = NULL;
  left->right = NULL;
  left->center = NULL;

  //ypopshfio kentriko paidi
  center = new traversal_node();
  center->zeugos.first = zeugos.first + 1;
  center->zeugos.second = zeugos.second + 1;
  center->left = NULL;
  center->right = NULL;
  center->center = NULL;

  //ypopshfio deksio paidi
  right = new traversal_node();
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
