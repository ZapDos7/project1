#include "curve_cube_ht.h"
#include <string>
#include <random> // uniform_real_distribution

template <class T>
void curve_cube_ht<T>::hamming_magic(std::string str, int i, int changesLeft)
{
  if (changesLeft == 0)
  {
    //printf("%s\n", str.c_str());

    if (std::find(verticizer.begin(), verticizer.end(), str) != verticizer.end())
    {
      /* v contains x */
    }
    else
    {
      verticizer.push_back(str);
    }
    //verticizerx.insert(str);
  }
  if (i < 0)
    return;
  // flip current bit
  str[i] = str[i] == '0' ? '1' : '0';
  hamming_magic(str, i - 1, changesLeft - 1);
  // or don't flip it (flip it again to undo)
  str[i] = str[i] == '0' ? '1' : '0';
  hamming_magic(str, i - 1, changesLeft);
}

template <class T>
curve_cube_ht<T>::curve_cube_ht(int d_ton, int vector_dimensions, double w_to_be)
{
  d_tonos = d_ton;
  size = (int)floor(pow(2, (double)d_ton));
  /*cube.clear();
  cube.resize(size);
  for (int i = 0; i < size; i++)
  {
    cube[i].clear();
  }*/

  fi_seeds.clear();

  std::random_device rand_dev;
  std::mt19937 generator(rand_dev());
  std::uniform_real_distribution<double> distr(0, w_to_be);
  for (int i = 0; i < d_ton; i++)
  {

    double gasmas = distr(generator);
    gasmas = floor(gasmas);
    fi_seeds.push_back((int)gasmas); //pairnei times o pinakas
  }

  my_gs.clear();
  for (int i = 0; i < d_ton; i++)
  {
    g_funs<T> a_g_fun(k_ys, vector_dimensions, w_to_be);
    my_gs.push_back(a_g_fun);
  }

  verticizer.clear();
}

template <class T>
curve_cube_ht<T>::~curve_cube_ht() {}

template <class T>
int curve_cube_ht<T>::fi_function(long int gval, int index)
{
  //long int mix = gval + fi_seeds[index];
  long int mix = (gval + fi_seeds[index]) / 10;
  //int fi = our_mod(mix, 2); //isws thelei %
  int fi = mix % 2;
  //std::cout << gval << " " << fi_seeds[index] << "\n";
  return fi;
}

template <class T>
void curve_cube_ht<T>::cubify_vector(my_vector<T> *v, curve<T> *cu)
{
  /*std::cout << "etsi hto o pinax prin hasharw to " << v->get_id_as_int() <<":";
    for(int i =0; i< table.size(); i++)
      for(int j =0; j< table[i].size(); j++)
        std::cout << table[i][j].first->get_id_as_int();
    std::cout << "\n";*/

  std::string vertex = ""; //arxika adeio bitstring, einai h korufh tou yperkuvou sthn opoia tha brethei
  for (unsigned int i = 0; i < my_gs.size(); i++)
  {                                                  //gia kathe gi
    long int gival = my_gs[i].actual_g_function(*v); //ypologise thn timh ths gi gia to vector v
    int fi = fi_function(gival, i);                  //perase thn apo thn fi wste na pareis 0 h 1
    std::string fi_str = std::to_string(fi);
    vertex += fi_str; //concatenate to apotelesma sto teliko bitstring - korufh yperkuvou
    //std::cout << fi;
  }
  unsigned long long key_vertex = std::stoull(vertex, NULL, 2); //metafrazei to bitstring-korufh yperkuvou se thesh pinaka

  //std::pair<my_vector<T> * , long int> thepair;
  //thepair.first = v;
  //thepair.second = keyv;
  cube[vertex].push_back(cu); //apo8hkeuse to deikth sto dianusma
                                 //std::cout << "my id is " << thepair.first->get_id_as_int() << "\n";
  //std::cout << "inputvec  " << v->get_id() << " sto bucket " <<  key_vertex << '\n';
}



template <class T>
std::vector<int> curve_cube_ht<T>::cubify_query(my_vector<T> *q, int probes)
{

  int check_probes = probes;
  std::string vertex = "";
  for (unsigned int i = 0; i < my_gs.size(); i++)
  {
    long int gival = my_gs[i].actual_g_function(*q); //ypologise thn timh ths gi gia to query vector q
    int fi = fi_function(gival, i);
    std::string fi_str = std::to_string(fi);
    vertex += fi_str;
  }
  unsigned long long key_vertex = std::stoull(vertex, NULL, 2); //metafrazei to bitstring-korufh yperkuvou se thesh pinaka
  std::string matroska = "";
  //std::cout << "QUERYtvec  " << q->get_id() << " sto bucket " <<  key_vertex << '\n';
  matroska = vertex + " ";

  std::vector<int> this_q_potential_neighbs;
  this_q_potential_neighbs.clear();
  //GIA AUTO TO BUCKET/KORUFH
  if(!(cube.find(vertex) == cube.end()) ){ //YPARXEI KAPOIOS se authn thn korufh
    for (unsigned int i = 0; i < cube[vertex].size(); i++)
    {
      //std::cout << table[modded_keyv][i].first->get_id_as_int() << "\n";
      this_q_potential_neighbs.push_back(cube[vertex][i]->get_id_as_int()); //valto sth lista pithanwn geitonwn
                                                                                //std::cout << "my id is " << table[modded_keyv][i].first->get_id_as_int() << "\n";
    }
  }

  check_probes--; //sto eclass eipw8hke oti sta probes sumperilamvanetai kai h idia h korufh
  verticizer.clear();
  std::string tempver = vertex;
  size_t len = vertex.length();
  size_t maxHammingDistance = len;
  for (size_t i = 1; i <= maxHammingDistance; ++i)
  {
    //printf("Computing for distance %d from %s\n", i, vertex.c_str());
    hamming_magic(tempver, len - 1, i);
    //printf("----------------\n");
  }
  //std::vector<std::string> verticizer(verticizerx.begin(), verticizerx.end());

  //if (check_probes > d_tonos - 1) //den yparxoyn panw apo d_tonos-1 korufes gia na koitaksei
  //check_probes = d_tonos - 1;
  //std::cout << "checku probes = " << check_probes << std::endl;
  if (check_probes <= 0)
  {
    //std::cout << "QUERYtvec  " << q->get_id() << " sto bucket " <<  matroska << '\n';
    /*for(unsigned int ife=0; ife< this_q_potential_neighbs.size(); ife++)
      std::cout << this_q_potential_neighbs[ife] << " " ;
    std::cout << std::endl;*/
    return this_q_potential_neighbs;
  }

  //o verticizer periexei ta bitstrings twn korufwn poy mporoyn na koitaxtoun -alla de tha koitaxtoyn oles-
  unsigned long long vert_key;
  //std::vector<std::string> verticizer(verticizerx.begin(), verticizerx.end());
  for (unsigned int i = 0; i < verticizer.size(); i++)
  {
    if (check_probes <= 0)
    {
      //std::cout << "QUERYtvec  " << q->get_id() << " sto bucket " <<  matroska << '\n';
      /*for(unsigned int ife=0; ife< this_q_potential_neighbs.size(); ife++)
        std::cout << this_q_potential_neighbs[ife] << " " ;
      std::cout << std::endl;*/
      return this_q_potential_neighbs;
    }

    vert_key = std::stoull(verticizer[i], NULL, 2); //metafrazei to bitstring-korufh yperkuvou se thesh pinaka
    matroska +=  verticizer[i] + " ";
    //std::cout << verticizer[i] << "\n";
    if(!(cube.find(verticizer[i]) == cube.end()) ){ //YPARXEI KAPOIOS se authn thn korufh
      for (unsigned int j = 0; j < cube[verticizer[i]].size(); j++)
      {
        //std::cout << table[modded_keyv][i].first->get_id_as_int() << "\n";
        this_q_potential_neighbs.push_back(cube[verticizer[i]][j]->get_id_as_int()); //valto sth lista pithanwn geitonwn
                                                                                  //std::cout << "my id is " << table[modded_keyv][i].first->get_id_as_int() << "\n";
      }
    }
    check_probes--;
  }

  /*std::cout << "brhka tous: ";
    std::cout << "oi ypopshfioi geitonoi moy einai : ";
    for(unsigned int yod = 0; yod < this_HT_potential_neighbs.size(); yod++)
      std::cout << this_HT_potential_neighbs[yod];
    std::cout << "\n";*/
  verticizer.clear();
  //std::cout << "QUERYtvec  " << q->get_id() << " sto bucket " <<  matroska << '\n';
  /*for(unsigned int ife=0; ife< this_q_potential_neighbs.size(); ife++)
    std::cout << this_q_potential_neighbs[ife] << " " ;
  std::cout << std::endl;*/
  return this_q_potential_neighbs;
}

template class curve_cube_ht<float>;
template class curve_cube_ht<int>;
template class curve_cube_ht<double>;
