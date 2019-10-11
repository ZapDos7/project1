#include <iostream>
#include "my_vector.h"
#include <string.h>
#include <fstream>
#include <typeinfo>
#include "utils.h"
#include <cmath>
#include "a.h"

template <class T>
T lousy_metric(std::vector<T> v1, std::vector<T> v2){

  T result =31;

	return result;

}

int main (int argc, char*argv[]) {

    /*
    AUTO LEITOURGEI - TESTING GIA MANHATTAN FUNCTION
    NOT USED
    std::vector<int> v1;
    for (int i = 1; i <= 5; i++)
        v1.push_back(i);
    std::vector<int> v2;
    for (int j = 8; j <= 12; j++)
        v2.push_back(j);

    double res = manhattan_distance(v1,v2);
    printf("\nManh Dist is %f...\n", res);
    */

    a a1(1.0);
    std::cerr << a1.get_a(1.2) << "\n";

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
    int qlines_num =0;
    while (std::getline(qfile, line)){
      qlines_num++ ;

    };
    //qfile.close();
    qfile.clear();
    qfile.seekg(0, qfile.beg);
    double Brute_Distance_Matrix[qlines_num][vectors_array.size()]; // o pinakas twn apostasewn gia to brute force kommati pragmatikhs sugkrishs
    int qline_curr =0;
    while (std::getline(qfile, line)){

        my_vector<int> one_v_atime2(line);
        for(unsigned int i=0; i<vectors_array.size(); i++)
          Brute_Distance_Matrix[qline_curr][i] = manhattan_distance(vectors_array[i].get_v(), one_v_atime2.get_v());

        qline_curr++ ;
    };
    qfile.close();
    for(int i=0; i<qline_curr; i++)
      for(unsigned int j=0; j< vectors_array.size(); j++)
        std::cout << Brute_Distance_Matrix[qline_curr][i] << "\n";
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
