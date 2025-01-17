#include <iostream>
#include "my_vector.h"
#include "h_funs.h"
#include "g_funs.h"
#include "utils.h"
#include "NNpair.h"
#include "cube_ht.h"
#include <typeinfo>
#include <string.h>
#include <fstream>
#include <limits>
#include <set>
#include <cmath>
#include <chrono> // time measurements

std::string repeat_answer = "n";

int main(int argc, char *argv[])
{
  //DWSE MONOPATI DATASET:
  //std::cout << "to phra";
  int k = -1; //
  //int d=0; //diastasi d'
  //default d=3;
  int M = 10; //to max allowed plithos ypopsifiwn shmeiwn
  //default M=10;
  int probes = 2; //megisto epitrepomeno plithos korifwn tou hypercube pou 8a elegx8oun
  //default probes=2;
  bool dset = false; ////an oxi orisma grammis entolos, 8a parw ta files apo path pou grafei o user
  bool qset = false;
  bool oset = false;
  char dataset_path[256];
  char query_dataset_path[256];
  char output_path[256];
  //    $./lsh -d <input file> -q <query file> -k <int> -L <int> -ο <output file>
  for (int i = 0; i < argc; i++)
  {
    if (strcmp("-d", argv[i]) == 0)
    {
      strcpy(dataset_path, argv[i + 1]);
      dset = true; /*std::cout <<"toxw\n";*/
    }              //pairnw to swsto onoma arxeiou apo to command line

    if (strcmp("-q", argv[i]) == 0)
    {
      strcpy(query_dataset_path, argv[i + 1]);
      qset = true; /*std::cout <<"toxw\n";*/
    }              //dinw timh sto K bash command line

    if (strcmp("-o", argv[i]) == 0)
    {
      strcpy(output_path, argv[i + 1]);
      oset = true; /*std::cout <<"toxw\n";*/
    }

    if (strcmp("-k", argv[i]) == 0) //k = d' apo ekfwnhsh. An de ginei set, tha ginei logn
    {
      k = atoi(argv[i + 1]);
    }

    if (strcmp("-M", argv[i]) == 0) //plithos Hash Tables ara Plithos G
    {
      M = atoi(argv[i + 1]);
    }

    if (strcmp("-probes", argv[i]) == 0) //plithos Hash Tables ara Plithos G
    {
      probes = atoi(argv[i + 1]);
    }

  }
  do
  { //to programma tha ksanatreksei sto telos me alla orismata, an to epi8ymei o xrhsths

    if (repeat_answer == "y")
    {
      dset = false;
      qset = false;
      oset = false;
      std::cout << "enter value for k (d'). If none inserted, unexpected behaviour will occur\n";
      std::cin >> k;
      std::cout << "enter value for M. If none inserted, unexpected behaviour will occur\n";
      std::cin >> M;
    }
    //EAN DEN ORISTHKE APO GRAMMH ENTOLWN, DWSE MONOPATI DATASET:
    if (dset == false)
    {
      std::cout << "Define dataset path:\n";
      std::string inp1;
      std::cin >> dataset_path;
    }

    //std::cout << "to phra";

    int n = 0; //plithos twn vectors tou input file
    std::ifstream infile(dataset_path);
    std::string line;
    std::vector<my_vector<int>> vectors_array;
    while (std::getline(infile, line))
    {
      my_vector<int> one_v_atime(line);
      //std::cout << one_v_atime.get_id()  <<"\n" ;
      vectors_array.push_back(one_v_atime);
      n++;
    };
    infile.close();
    //upologizw to dimensions tou kosmou mou
    int diastaseis_vector = vectors_array[0].get_v().size();

    //DWSE MONOPATH QUERIES
    if (qset == false)
    {
      std::cout << "Define query dataset path:\n";
      std::string inp1;
      std::cin >> query_dataset_path;
    }
    std::ifstream qfile(query_dataset_path);
    std::vector<my_vector<int>> query_vectors_array;
    //vector<vector<double>> DistanceMatrix;
    while (std::getline(qfile, line))
    {
      my_vector<int> one_v_atime2(line);
      //std::cout << one_v_atime.get_id()  <<"\n" ;
      query_vectors_array.push_back(one_v_atime2);
    };
    infile.close();

    auto start_of_distance_matrix = std::chrono::high_resolution_clock::now();
    /*Distance Matrix Input X Query vectors me tis apostaseis tous*/
    double Brute_Distance_Matrix[vectors_array.size()][query_vectors_array.size()]; // o pinakas twn apostasewn gia to brute force kommati pragmatikhs sugkrishs
    for (unsigned int i = 0; i < vectors_array.size(); i++)
      for (unsigned int j = 0; j < query_vectors_array.size(); j++)
        Brute_Distance_Matrix[i][j] = manhattan_distance(vectors_array[i].get_v(), query_vectors_array[j].get_v());

    auto end_of_distance_matrix = std::chrono::high_resolution_clock::now() - start_of_distance_matrix;
    long long microseconds_DM = std::chrono::duration_cast<std::chrono::microseconds>(end_of_distance_matrix).count();

    fprintf(stderr, "Time needed for distance matrix calculation is %lld microseconds.\n\n", microseconds_DM);

    //euresi actual NNs
    auto start_of_w_calc = std::chrono::high_resolution_clock::now();
    std::vector<NNpair> input_actual_NNs; //pinakas apo zeugaria actual NNs me prwto stoixeio to p
    for (unsigned int i = 0; i < vectors_array.size(); i++)
    { //prepei na brw ta zeugaria ap to input gia ypologismo w

      std::string min_id1;
      double min1 = std::numeric_limits<double>::max(); //min pairnei timh apeiro
      for (unsigned int j = 0; j < vectors_array.size(); j++)
      {
        if (manhattan_distance(vectors_array[i].get_v(), vectors_array[j].get_v()) == 0) //einai to idio shmeio
          continue;

        if (manhattan_distance(vectors_array[i].get_v(), vectors_array[j].get_v()) < min1)
        {
          min1 = manhattan_distance(vectors_array[i].get_v(), vectors_array[j].get_v());
          min_id1 = vectors_array[j].get_id();
        }
      }
      NNpair single_pair1(vectors_array[i].get_id(), min_id1);
      single_pair1.set_distance(min1);
      input_actual_NNs.push_back(single_pair1);
    }

    double tmp = 0.0;
    double mean_distance = 0;
    for (unsigned int i = 0; i < input_actual_NNs.size(); i++)
    {
      tmp += input_actual_NNs.at(i).get_distance();
    }
    mean_distance = tmp / input_actual_NNs.size(); //fp division
    auto end_of_w_calc = std::chrono::high_resolution_clock::now() - start_of_w_calc;
    long long microseconds_w = std::chrono::duration_cast<std::chrono::microseconds>(end_of_w_calc).count();

    fprintf(stderr, "Time needed for w calculation is %lld microseconds.\n\n", microseconds_w);
    fprintf(stderr, "Value of w = %f\n", mean_distance);

    //also test gia w = 4 * mean_distance
    /*const*/ double w = 1164.091700; //to w pou vazw sta ai
    //prepei na brw ton actual nearest neighbour
    auto start_of_actual_NN_all = std::chrono::high_resolution_clock::now();
    std::vector<NNpair> actual_NNs; //pinakas apo zeugaria actual NNs me prwto stoixeio to q
    std::vector<std::chrono::duration<double>> times_of_actual_NNs;
    for (unsigned int i = 0; i < query_vectors_array.size(); i++)
    {
      auto start_of_this_actual_NN = std::chrono::high_resolution_clock::now();
      std::string min_id;
      double min = std::numeric_limits<double>::max(); //min pairnei timh apeiro
      for (unsigned int j = 0; j < vectors_array.size(); j++)
      {
        if (Brute_Distance_Matrix[j][i] < min)
        {
          min = Brute_Distance_Matrix[j][i];
          min_id = vectors_array[j].get_id();
        }
      }
      NNpair single_pair(query_vectors_array[i].get_id(), min_id);
      single_pair.set_distance(min);
      actual_NNs.push_back(single_pair);
      auto end_of_this_actual_NN = std::chrono::high_resolution_clock::now() - start_of_this_actual_NN;
      times_of_actual_NNs.push_back(end_of_this_actual_NN);
    }

    auto end_of_actual_NN_all = std::chrono::high_resolution_clock::now() - start_of_actual_NN_all;
    long long microseconds_act_NN_all = std::chrono::duration_cast<std::chrono::microseconds>(end_of_actual_NN_all).count();
    fprintf(stderr, "Time needed for brute force found NNs is %lld microseconds.\n\n", microseconds_act_NN_all);

    //////////////////////////////HYPERCUBE TIME///////////////////////////////////
    auto start_of_hprcb_all = std::chrono::high_resolution_clock::now();
    std::vector<std::chrono::duration<double>> times_of_approx_NNs;

    if (k < 0) //to k=d' den egine set ara einai iso me log2(n)
      k = floor(log2((double)n));

    //std::cout << "kappa is " << k << "\n";

    cube_ht<int> hypercube(k, diastaseis_vector, w); //dhmiourgei th domh tou kubou
    for (unsigned int i = 0; i < vectors_array.size(); i++)
      hypercube.cubify_vector(&vectors_array[i]); //pernaei ta input dianusmata mesa ston kubo

    std::vector<NNpair> approx_NNs;          //pinakas apo zeugaria cube approx NNs me prwto stoixeio to q
    std::vector<int> full_potential_neighbs; //major metavlhth, anaferetai se ena q
    for (unsigned int i = 0; i < query_vectors_array.size(); i++)
    {
      auto start_of_this_approx_NN = std::chrono::high_resolution_clock::now();
      full_potential_neighbs.clear();
      full_potential_neighbs = hypercube.cubify_query(&query_vectors_array[i], probes); //epistrefei vector me ta int ids twn dianusmatwn sthn idia korufh me to q (kai se alles probes-1)
      //std::cout << "kappa is " << k << "\n";
      if (full_potential_neighbs.size() <= (unsigned int)M)
      {                                                  //oi pithanoi geitones einai ligoteroi apo to M
        double min = std::numeric_limits<double>::max(); //min pairnei timh apeiro arxika
        std::string min_id;                              //to id tou aNN
        for (unsigned int yod = 0; yod < full_potential_neighbs.size(); yod++)
        { //gia kathe pithano aNN
          //std::cout << "i am q " << query_vectors_array[i].get_id_as_int() << "and this is a prob neighb" << full_potential_neighbs[yod] << "\n" ;
          if (Brute_Distance_Matrix[full_potential_neighbs[yod] - 1][i] < min)
          {                                                                   //if dist(pi,q) < min
            min = Brute_Distance_Matrix[full_potential_neighbs[yod] - 1][i];  //this is minimum distance
            min_id = vectors_array[full_potential_neighbs[yod] - 1].get_id(); //this is min pi
          }
        }
        NNpair approx_pair(query_vectors_array[i].get_id(), min_id);
        approx_pair.set_distance(min);
        approx_NNs.push_back(approx_pair);
      }
      else
      {                                                  //tha psaksoume mono mexri M
        double min = std::numeric_limits<double>::max(); //min pairnei timh apeiro
        std::string min_id;
        for (int yod = 0; yod < M; yod++)
        { //but stop
          //std::cout << vectors_array[full_potential_neighbs[yod] - 1].get_id() << " ";
          if (Brute_Distance_Matrix[full_potential_neighbs[yod] - 1][i] < min)
          {
            min = Brute_Distance_Matrix[full_potential_neighbs[yod] - 1][i];
            min_id = vectors_array[full_potential_neighbs[yod] - 1].get_id();
          }
        }
        NNpair approx_pair(query_vectors_array[i].get_id(), min_id);
        approx_pair.set_distance(min);
        approx_NNs.push_back(approx_pair);
      }
      auto end_of_this_approx_NN = std::chrono::high_resolution_clock::now() - start_of_this_approx_NN;
      times_of_approx_NNs.push_back(end_of_this_approx_NN);
    }
    auto end_of_hprcb_all = std::chrono::high_resolution_clock::now() - start_of_hprcb_all;
    long long microseconds_hprcb_all = std::chrono::duration_cast<std::chrono::microseconds>(end_of_hprcb_all).count();

    fprintf(stderr, "Time needed for Hypercube is %lld microseconds.\n\n", microseconds_hprcb_all);

    /*std::ofstream myfile3;
      myfile3.open("../approxNNs.txt");
      for (unsigned int i = 0; i < approx_NNs.size(); i++)
        myfile3 << approx_NNs[i].getq_id() << " " << approx_NNs[i].getp_id() << " " << approx_NNs[i].get_distance() << "\n";
      myfile3.close();*/

    //EAN DEN ORISTHKE APO GRAMMH ENTOLWN, DWSE MONOPATI OUTPUT FILE
    if (oset == false)
    {
      std::cout << "Define output file path:\n";
      std::string inp1;
      std::cin >> output_path;
    }

    std::ofstream outfile;
    outfile.open(output_path);

    for (unsigned int i = 0; i < approx_NNs.size(); i++) //for each itemJ in queryset:
    {
      outfile << "Query: " << approx_NNs[i].getq_id() << '\n';
      outfile << "Actual nearest neighbor: " << actual_NNs[i].getp_id() << '\n';
      outfile << "Approximate nearest neighbor: " << approx_NNs[i].getp_id() << '\n';
      outfile << "distanceHypercube: " << approx_NNs[i].get_distance() << '\n';
      outfile << "distanceTrue: " << actual_NNs[i].get_distance() << '\n';
      outfile << "tHyprcube: " << times_of_approx_NNs[i].count() << '\n';
      outfile << "tTrue: " << times_of_actual_NNs[i].count() << "\n\n";
      /*if (bonus)
    {
      outfile << "R-near neighbors: " << '\n';
      for (however many R near we found)
      {
        outfile << "item_id" << '\n';
      }
    }
    */
    }
    outfile.close();

    infile.close();
    qfile.close();
    //when done all, ask if repeat with other dataset or exit ektelesi

    std::cout << "Would you like to repeat with new dataset? Type y for yes or n for no\n";
    std::cin >> repeat_answer;
    if (repeat_answer != "y")
      repeat_answer = "n";

  } while (repeat_answer == "y");
}
