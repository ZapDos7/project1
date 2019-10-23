#include "cube_ht.h"
#include <string>
#include <random> // uniform_real_distribution


template <class T>
void cube_ht<T>::hamming_magic(std::string str, int i, int changesLeft){
        if (changesLeft == 0) {
                printf("%s\n", str.c_str());
                verticizer.push_back(str);
        }
        if (i < 0) return;
        // flip current bit
        str[i] = str[i] == '0' ? '1' : '0';
        hamming_magic(str, i-1, changesLeft-1);
        // or don't flip it (flip it again to undo)
        str[i] = str[i] == '0' ? '1' : '0';
        hamming_magic(str, i-1, changesLeft);
}


template <class T>
cube_ht<T>::cube_ht(int d_ton, int vector_dimensions, int w_to_be){
    d_tonos = d_ton;
    size = (int) floor(pow(2,(double)d_ton ));
    cube.clear();
    cube.resize(size);
    for (int i = 0; i < size; i++) {
        cube[i].clear();
    }

    fi_seeds.clear();

    for(int i = 0; i < d_ton; i++){
      std::default_random_engine generator;
      std::uniform_int_distribution<int> distribution(0,w_to_be);
      fi_seeds.push_back(distribution(generator)); //pairnei times o pinakas

    }

    my_gs.clear();
    for(int i=0; i<d_ton; i++){
      g_funs<T> a_g_fun(k_ys, vector_dimensions, w_to_be);
      my_gs.push_back(a_g_fun);
    }

    verticizer.clear();

}

template <class T>
cube_ht<T>::~cube_ht(){}


template <class T>
int cube_ht<T>::fi_function(long int gval, int index) {
    long int mix = gval + fi_seeds[index] ;
    //int fi = our_mod(mix, 2); //isws thelei %
    int fi = mix%2;
    return fi;
}



template <class T>
void cube_ht<T>::cubify_vector(my_vector<T> *v) {
    /*std::cout << "etsi hto o pinax prin hasharw to " << v->get_id_as_int() <<":";
    for(int i =0; i< table.size(); i++)
      for(int j =0; j< table[i].size(); j++)
        std::cout << table[i][j].first->get_id_as_int();
    std::cout << "\n";*/

    std::string vertex = ""; //arxika adeio bitstring, einai h korufh tou yperkuvou sthn opoia tha brethei
    for(unsigned int i=0; i<my_gs.size(); i++){ //gia kathe gi
      long int gival = my_gs[i].actual_g_function(*v); //ypologise thn timh ths gi gia to vector v
      int fi = fi_function(gival, i); //perase thn apo thn fi wste na pareis 0 h 1
      std::string fi_str = std::to_string(fi);
      vertex += fi_str;   //concatenate to apotelesma sto teliko bitstring - korufh yperkuvou
    }
    unsigned long long key_vertex = std::stoull(vertex, NULL, 2); //metafrazei to bitstring-korufh yperkuvou se thesh pinaka

    //std::pair<my_vector<T> * , long int> thepair;
    //thepair.first = v;
    //thepair.second = keyv;
    cube[key_vertex].push_back(v); //apo8hkeuse to deikth sto dianusma
    //std::cout << "my id is " << thepair.first->get_id_as_int() << "\n";
}



template <class T>
std::vector<int> cube_ht<T>::cubify_query(my_vector<T> *q, int probes) {

  int check_probes = probes;
  std::string vertex = "";
  for(unsigned int i=0; i<my_gs.size(); i++){
    long int gival = my_gs[i].actual_g_function(*q); //ypologise thn timh ths gi gia to query vector q
    int fi = fi_function(gival, i);
    std::string fi_str = std::to_string(fi);
    vertex += fi_str;
  }
  unsigned long long key_vertex = std::stoull(vertex, NULL, 2); //metafrazei to bitstring-korufh yperkuvou se thesh pinaka

  std::vector<int> this_q_potential_neighbs;
  this_q_potential_neighbs.clear();
  //GIA AUTO TO BUCKET/KORUFH
  for(unsigned int i =0; i<cube[key_vertex].size(); i++){
      //std::cout << table[modded_keyv][i].first->get_id_as_int() << "\n";
    this_q_potential_neighbs.push_back(cube[key_vertex][i]->get_id_as_int()); //valto sth lista pithanwn geitonwn
      //std::cout << "my id is " << table[modded_keyv][i].first->get_id_as_int() << "\n";
  }
  check_probes-- ;//sto eclass eipw8hke oti sta probes sumperilamvanetai kai h idia h korufh
  verticizer.clear();
  std::string tempver = vertex;
  size_t len = vertex.length();
  size_t maxHammingDistance = len;
  for (size_t i = 1 ; i <= maxHammingDistance ; ++i) {
                printf("Computing for distance %d\n", i);
                hamming_magic(tempver, len-1, i);
                printf("----------------\n");
  }

  if(check_probes > d_tonos-1) //den yparxoyn panw apo d_tonos-1 korufes gia na koitaksei
    check_probes = d_tonos-1;
  if(check_probes <=0)
    return this_q_potential_neighbs;

  //o verticizer periexei ta bitstrings twn korufwn poy mporoyn na koitaxtoun -alla de tha koitaxtoyn oles-
  unsigned long long vert_key;
  for(unsigned int i=0; i< verticizer.size(); i++){
    if(check_probes <=0)
      return this_q_potential_neighbs;
    vert_key = std::stoull(verticizer[i], NULL, 2); //metafrazei to bitstring-korufh yperkuvou se thesh pinaka
    for(unsigned int j =0; j<cube[vert_key].size(); j++){
        //std::cout << table[modded_keyv][i].first->get_id_as_int() << "\n";
      this_q_potential_neighbs.push_back(cube[vert_key][j]->get_id_as_int()); //valto sth lista pithanwn geitonwn
        //std::cout << "my id is " << table[modded_keyv][i].first->get_id_as_int() << "\n";
    }
    check_probes--;
  }

    /*std::cout << "brhka tous: ";
    std::cout << "oi ypopshfioi geitonoi moy einai : ";
    for(unsigned int yod = 0; yod < this_HT_potential_neighbs.size(); yod++)
      std::cout << this_HT_potential_neighbs[yod];
    std::cout << "\n";*/
  verticizer.clear();
  return this_q_potential_neighbs;
}







//template class cube_ht<float>;
template class cube_ht<int>;
//template class cube_ht<double>;
