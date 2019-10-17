#include <iostream>
#include <string.h>
#include <fstream>
#include <typeinfo>
#include <stdlib.h>
#include <cstring>
#include <limits>
#include <cmath>
#include "my_vector.h"
#include "utils.h"
#include "NNpair.h"
#include "h_funs.h"
#include "g_funs.h"
#include "ht.h"


int main (int argc, char*argv[]) {
  
  //test
  ht<int> a_table(10,20,3,40);
  //

  int k=-1;
  int L=-1;
  bool dset, qset, oset = false; ////an oxi orisma grammis entolos, 8a parw ta files apo path pou grafei o user
  char dataset_path[256];
  char query_dataset_path[256];
  char output_path[256];
  //    $./lsh -d <input file> -q <query file> -k <int> -L <int> -ο <output file>
  for(int i=0; i<argc; i++){
    if(strcmp("-d",argv[i])==0)
      {strcpy(dataset_path,argv[i+1]); dset = true; /*std::cout <<"toxw\n";*/} //pairnw to swsto onoma arxeiou apo to command line

    if(strcmp("-q",argv[i])==0)
      {strcpy(query_dataset_path,argv[i+1]); qset=true;/*std::cout <<"toxw\n";*/}  //dinw timh sto K bash command line

    if(strcmp("-o",argv[i])==0)
      {strcpy(output_path,argv[i+1]); oset=true;/*std::cout <<"toxw\n";*/}

    if(strcmp("-k",argv[i])==0) //plithos hi functions gia dimiourgia twn g
      {k = atoi(argv[i+1]);}
    else {k = 4;}

    if(strcmp("-L",argv[i])==0) //plithos Hash Tables ara Plithos G
      {L = atoi(argv[i+1]);}
    else {L = 5;}
  }
    //EAN DEN ORISTHKE APO GRAMMH ENTOLWN, DWSE MONOPATI DATASET:
    if(dset == false){
      std::cout << "Define dataset path:\n";
      std::string inp1;
      std::cin >> dataset_path;
    }

    int n=0; //plithos twn vectors tou input file
    std::ifstream infile(dataset_path);//dataset: me tabs anamesa, ka8e grammi: id1    x11     x12     x13...
    std::string line;
    std::vector <my_vector<int> > vectors_array;
    while (std::getline(infile, line)){//read files
        my_vector<int> one_v_atime(line);
        //std::cout << one_v_atime.get_id()  <<"\n" ;
        vectors_array.push_back(one_v_atime);
        n++;
    };
    infile.close();
    //fprintf(stderr, "Input vectors = %d\n\n", n);

    const int Table_Size = floor(n/16);

    //EAN DEN ORISTHKE APO GRAMMH ENTOLWN, DWSE MONOPATH QUERIES
    if(qset == false){
      std::cout << "Define query dataset path:\n";
      std::string inp1;
      std::cin >> query_dataset_path;
    }
    int q = 0; //to plithos twn query vectors
    std::ifstream qfile(query_dataset_path);//queryset: toulax 1 vector & panw panw 1 8etiko double R, an R = 0 tote mono 1 NN, an R>1, tote bonus
    //std::vector <my_vector<int> > query_vectors_array;
    //vector<vector<double>> DistanceMatrix;
    std::vector <my_vector<int> > query_vectors_array;
    while (std::getline(qfile, line)){    //ka8e grammi meta: idS1    x11     x12     x13...
      my_vector<int> one_v_atime2(line);
      query_vectors_array.push_back(one_v_atime2);
      q++;
    };
    qfile.close();
    //fprintf(stderr, "Query vectors = %d\n\n", q);


    /*Distance Matrix Input X Query vectors me tis apostaseis tous*/
    double Brute_Distance_Matrix[vectors_array.size()][query_vectors_array.size()]; // o pinakas twn apostasewn gia to brute force kommati pragmatikhs sugkrishs
    for(unsigned int i=0; i<vectors_array.size(); i++)
      for(unsigned int j=0; j<query_vectors_array.size(); j++)
        Brute_Distance_Matrix[i][j] = manhattan_distance(vectors_array[i].get_v(), query_vectors_array[j].get_v());



    /*std::ofstream myfile;
    myfile.open ("example.txt");
    for(int i=0; i<vectors_array.size(); i++)
      for(int j=0; j< query_vectors_array.size(); j++)
        myfile << Brute_Distance_Matrix[i][j] << "\n";
    myfile.close();*/

    std::vector<NNpair> input_actual_NNs; //pinakas apo zeugaria actual NNs me prwto stoixeio to q
    for(unsigned int i=0; i<vectors_array.size(); i++){

      std::string min_id1;
      double min1 = std::numeric_limits<double>::max();//min pairnei timh apeiro
      for(unsigned int j=0; j<vectors_array.size(); j++){
        if(manhattan_distance(vectors_array[i].get_v(), vectors_array[j].get_v()) ==0) //einai to idio shmeio
          continue;

        if(manhattan_distance(vectors_array[i].get_v(), vectors_array[j].get_v()) < min1){
          min1 = manhattan_distance(vectors_array[i].get_v(), vectors_array[j].get_v());
          min_id1 =  vectors_array[j].get_id();
        }
      }
      NNpair single_pair1(vectors_array[i].get_id(), min_id1);
      single_pair1.set_distance(min1);
      input_actual_NNs.push_back(single_pair1);
    }

    //prepei na brw ta zeugaria ap to input gia ypologismo w???
    double tmp = 0.0;
    double mean_distance = 0;
    for (unsigned int i = 0; i < input_actual_NNs.size(); i++) {
      tmp+=input_actual_NNs.at(i).get_distance();
    }
    mean_distance = tmp/input_actual_NNs.size(); //fp division
    fprintf(stderr, "Mesi apostasi = %f\n", mean_distance);

    //also test gia w = 10 * mean_distance
    const double w = 4*mean_distance; //to w pou vazw sta ai

    //prepei na brw ton actual nearest neighbour
    std::vector<NNpair> actual_NNs; //pinakas apo zeugaria actual NNs me prwto stoixeio to q
    for(unsigned int i=0; i<query_vectors_array.size(); i++){
      std::string min_id;
      double min = std::numeric_limits<double>::max();//min pairnei timh apeiro
      for(unsigned int j=0; j<vectors_array.size(); j++){
        if(Brute_Distance_Matrix[j][i] < min){
          min = Brute_Distance_Matrix[j][i];
          min_id =  vectors_array[j].get_id();
        }
      }
      NNpair single_pair(query_vectors_array[i].get_id(), min_id);
      single_pair.set_distance(min);
      actual_NNs.push_back(single_pair);

    }

    /*std::ofstream myfile2;
    myfile2.open ("example2.txt");
    for(int i=0; i<actual_NNs.size(); i++)
        myfile2 << actual_NNs[i].getq_id() << " " << actual_NNs[i].getp_id() << " " << actual_NNs[i].get_distance() <<"\n";
    myfile2.close();*/

    /*std::ofstream myfile3;
    myfile3.open ("example3.txt");
    for(int i=0; i<input_actual_NNs.size(); i++)
        myfile3 << input_actual_NNs[i].getq_id() << " " << input_actual_NNs[i].getp_id() << " " << input_actual_NNs[i].get_distance() << "\n";
    myfile3.close();*/

/////////////////////////////LSH TIME////////////////////////////////






////////////////////////output///////////////////////////////////////
//EAN DEN ORISTHKE APO GRAMMH ENTOLWN, DWSE MONOPATI OUTPUT FILE
    if(oset == false){
      std::cout << "Define output file path:\n";
      std::string inp1;
      std::cin >> output_path;
    }

    //output.txt:
    //for each itemJ in queryset:
    /*
    Query: itemJ
    Nearest neighbor: itemY
    distanceLSH: <double>
    distanceTrue: <double>
    tLSH: <double>
    tTrue: <double>
    R-near neighbors: //bonus
    itemJ //bonus
    itemK //bonus
    . . .
    itemW //bonus
    */

////////////////////////////METRISEIS///////////////////////////////
/*
Compare apotelesmata twn 4 parallagwn:{
LSH for curves / LSH L1,
LSH for curves / Hypercube,
Random Projection / LSH L1,
Random Projection / Hypercube}
ws pros: {
    a) max klasma proseggisis = {approx NN distance } / {actual NN distance}
    b) mean time euresis tou approx NN
}
*/

//when done all, ask if repeat with other dataset or exit ektelesi
}
