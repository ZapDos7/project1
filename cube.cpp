#include <iostream>
#include "my_vector.h"
#include "h_funs.h"
#include "g_funs.h"
#include "utils.h"
#include <typeinfo>
#include <string.h>
#include <fstream>


int main (int argc, char*argv[]) {
        //DWSE MONOPATI DATASET:
      int k = -1; //
      int d=0; //diastasi d'
      //default d=3;
      int M=0; //to max allowed plithos ypopsifiwn shmeiwn
      //default M=10;
      int probes=0; //megisto epitrepomeno plithos korifwn tou hypercube pou 8a elegx8oun
      //default probes=2;
      bool dset, qset, oset = false; ////an oxi orisma grammis entolos, 8a parw ta files apo path pou grafei o user
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
        else
        {
          M = 10;
        }

        if (strcmp("-probes", argv[i]) == 0) //plithos Hash Tables ara Plithos G
        {
          probes = atoi(argv[i + 1]);
        }
        else
        {
          probes = 2;
        }
      }
        //EAN DEN ORISTHKE APO GRAMMH ENTOLWN, DWSE MONOPATI DATASET:
        if (dset == false)
        {
          std::cout << "Define dataset path:\n";
          std::string inp1;
          std::cin >> dataset_path;
        }


    int n = 0;                  //plithos twn vectors tou input file
    std::ifstream infile(dataset_path);
    std::string line;
    std::vector <my_vector<int> > vectors_array;
    while (std::getline(infile, line)){
        my_vector<int> one_v_atime(line);
        //std::cout << one_v_atime.get_id()  <<"\n" ;
        vectors_array.push_back(one_v_atime);
        n++;
    };
    infile.close();
    //upologizw to dimensions tou kosmou mou
    int diastaseis_vector = vectors_array[0].get_v().size();

    for(int i=0; i<vectors_array.size(); i++)
        std::cout << vectors_array[i].get_id() << "\n";
    //DWSE MONOPATH QUERIES
    if (qset == false)
    {
      std::cout << "Define query dataset path:\n";
      std::string inp1;
      std::cin >> query_dataset_path;
    }
    std::ifstream qfile(query_dataset_path);
    std::vector <my_vector<int> > query_vectors_array;
    //vector<vector<double>> DistanceMatrix;
    while (std::getline(qfile, line)){
        my_vector<int> one_v_atime2(line);
        //std::cout << one_v_atime.get_id()  <<"\n" ;
        query_vectors_array.push_back(one_v_atime2);
    };
    infile.close();
    //DWSE MONOPATI OUTPUT FILE
    std::cout << "Define output file path:\n";
    std::cin >> output_path;
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
    //hypercube for vectors





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
}
