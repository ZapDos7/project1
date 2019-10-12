#include <iostream>
#include "my_vector.h"
#include <string.h>
#include <fstream>
#include <typeinfo>
#include "utils.h"
#include <limits>
#include "NNpair.h"
#include <cmath>
//#include "a.h"


int main (int argc, char*argv[]) {


////////////////////////////A - VECTORS//////////////////////////////
    //read files
    //an oxi apo path pou grafei o user
    //    $./lsh –d <input file> –q <query file> –k <int> -L <int> -ο <output file>
    //dataset: me tabs anamesa, ka8e grammi: id1    x11     x12     x13...
    //N to plithos twn
    //ids mporei na einai mondaikoi akeraioi h strings

    //queryset: toulax 1 vector & panw panw 1 8etiko double R, an R = 0 tote mono 1 NN, an R>1, tote bonus
    //ka8e grammi meta: idS1    x11     x12     x13...
    //q to plithos twn

    //define path to dataset & path to output file???
    //when done all, ask if repeat with other dataset or exit ektelesi

    //g functions for HTs
    //creation of L HTs

    //LSH for vectors
    //int k=0; //plithos hi functions gia dimiourgia twn g
    //default int k=4;
    //int L=0; //posa hash tables
    //default int L=5;



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

    //DWSE MONOPATI DATASET:
    std::string dataset_path;
    std::cout << "Define dataset path:\n";
    std::cin >> dataset_path;
    std::ifstream infile(dataset_path.c_str());
    std::string line;
    std::vector <my_vector<int> > vectors_array;
    while (std::getline(infile, line)){
        my_vector<int> one_v_atime(line);
        //std::cout << one_v_atime.get_id()  <<"\n" ;
        vectors_array.push_back(one_v_atime);
    };
    infile.close();
    /*for(int i=0; i<vectors_array.size(); i++)
        std::cout << vectors_array[i].get_id() << "\n";*/
    std::string query_dataset_path;
    std::string output_path;
    //DWSE MONOPATH QUERIES
    std::cout << "Define query dataset path:\n";
    std::cin >> query_dataset_path;
    std::ifstream qfile(query_dataset_path.c_str());
    //std::vector <my_vector<int> > query_vectors_array;
    //vector<vector<double>> DistanceMatrix;
    std::vector <my_vector<int> > query_vectors_array;
    while (std::getline(qfile, line)){
      my_vector<int> one_v_atime2(line);
      query_vectors_array.push_back(one_v_atime2);

    };
    qfile.close();

    double Brute_Distance_Matrix[vectors_array.size()][query_vectors_array.size()]; // o pinakas twn apostasewn gia to brute force kommati pragmatikhs sugkrishs
    for(int i=0; i<vectors_array.size(); i++)
      for(int j=0; j<query_vectors_array.size(); j++)
        Brute_Distance_Matrix[i][j] = manhattan_distance(vectors_array[i].get_v(), query_vectors_array[j].get_v());


    std::ofstream myfile;
    myfile.open ("example.txt");
    for(int i=0; i<vectors_array.size(); i++)
      for(int j=0; j< query_vectors_array.size(); j++)
        myfile << Brute_Distance_Matrix[i][j] << "\n";
    myfile.close();

    //prepei na brw ton actual nearest neighbour
    std::vector<NNpair> actual_NNs; //pinakas apo zeugaria actual NNs me prwto stoixeio to q
    for(int i=0; i<query_vectors_array.size(); i++){
      std::string min_id;
      double min = std::numeric_limits<double>::max();//min pairnei timh apeiro
      for(int j=0; j<vectors_array.size(); j++){
        if(Brute_Distance_Matrix[j][i] < min){
          min = Brute_Distance_Matrix[j][i];
          min_id =  vectors_array[j].get_id();
        }
      }
      NNpair single_pair(query_vectors_array[i].get_id(), min_id);
      actual_NNs.push_back(single_pair);
    }

    std::ofstream myfile2;
    myfile2.open ("example2.txt");
    for(int i=0; i<actual_NNs.size(); i++)
        myfile2 << actual_NNs[i].getq_id() << " " << actual_NNs[i].getp_id() << "\n";
    myfile2.close();

    //DWSE MONOPATI OUTPUT FILE
    std::cout << "Define output file path:\n";
    std::cin >> output_path;

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


}
