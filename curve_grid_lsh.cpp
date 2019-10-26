#include "curve_point.h"
#include "curve.h"
#include "pan_traversal.hpp"
#include "grid.h"
#include "my_vector.h"
//#include "traversal.h"
//#include "dtw.h"
//#include "utils.h"
//#include "NNpair.h"
#include <iostream>
#include <typeinfo>
//#include "h_funs.h"
//#include "g_funs.h"
//#include "ht.h"
#include <chrono> // time measurements
#include <fstream>
#include <stdlib.h>
//#include <algorithm> // std::count
#include <cstring>
#include <limits>
//#include <set>
//#include <cmath>

std::string repeat_answer = "n";

int main(int argc, char *argv[])
{
    //test chamber
    std::cout.precision(17);
    std::string inp = "1	3	(-6.4227999999999996, 53.288000000000004) (-6.4257099999999996, 53.289299999999997) (-6.4268099999999997, 53.290300000000002)";
    curve<double> crv1(inp);
    std::string inp2 = "6	2	(-6.2582100000000001, 53.347799999999999) (-6.4272499999999999, 53.290799999999997)";
    curve<double> crv2(inp2);

    //my_vector<double> mv("item_id1	1.1 25.1 23.1 1.1 ");
    grid<double> grd(2.2, 1);
    std::cerr << crv1.get_v_size() << '\n'; //3
    curve<double> lala = grd.gridify(&crv1);
    std::cerr << lala.get_v_size() << '\n'; //1
    my_vector<double> mv = vectorify(lala);
    std::cerr << mv.get_v().size() << '\n'; //2
    add_pad(&mv, 2.1, 10);
    std::cerr << mv.get_v().size() << '\n'; //10

    //main
    //$./curve_grid_lsh -d <input file> -k_vec <int> -L_grid <int> -ο <output file>
    int k_vec = -1;
    int L_grid = -1;
    bool dset, oset = false; ////an oxi orisma grammis entolon, 8a parw ta files apo path pou grafei o user
    char dataset_path[256];
    char output_path[256];


    for (int i = 0; i < argc; i++)
    {
        if (strcmp("-d", argv[i]) == 0)
        {
            strcpy(dataset_path, argv[i + 1]);
            dset = true;
        }
        if (strcmp("-o", argv[i]) == 0)
        {
            strcpy(output_path, argv[i + 1]);
            oset = true;
        }
        if (strcmp("-k_vec", argv[i]) == 0)
        {
            k_vec = atoi(argv[i + 1]);
        }
        else
        {
            k_vec = 1;
        }

        if (strcmp("-L_grid", argv[i]) == 0)
        {
            L_grid = atoi(argv[i + 1]);
        }
        else
        {
            L_grid = 4;
        }
    }
    do
    { //to programma tha ksanatreksei sto telos me alla orismata, an to epi8ymei o xrhsths

        if (repeat_answer == "y")
        {
            dset = false;
            oset = false;
            std::cout << "enter value for k_vec:\n";
            std::cin >> k_vec;
            std::cout << "enter value for L_grid:\n";
            std::cin >> L_grid;
        }
        //EAN DEN ORISTHKE APO GRAMMH ENTOLWN, DWSE MONOPATI DATASET:
        if (dset == false)
        {
            std::cout << "Define dataset path:\n";
            std::string inp1;
            std::cin >> dataset_path;
        }

        int n = 0;                          //plithos twn kampulwn tou input file
        std::ifstream infile(dataset_path); //dataset
        std::string line;
        std::vector<curve<double>> curves_array;
        while (std::getline(infile, line))
        { //read files
            curve<double> one_v_atime(line);
            //std::cout << one_v_atime.get_id()  <<"\n" ;
            curves_array.push_back(one_v_atime);
            n++;
        };
        infile.close();
        double delta = 0.0;                                         //mesi apostasi shmeiwn kampulws
        double inf = std::numeric_limits<double>::max();            //apeiro kai kala
        double max_coord = -1 * inf;                                //arxika -apeiro
        ;                                                           //h megisti metabliti pou uparxei sto dataset
        for (unsigned int i = 0; i < curves_array.size() - 86; i++) //an theloume ola & query, sbhnoume to "-86" kai ola popa
        {
            double tmp = 0.0;
            double plithos_athroismatwn = 0.0;
            std::vector<curve_point<double>> shmeia = curves_array[i].get_points(); //pairnw to vector apo shmeia kathe kampulhs
            if (shmeia.size() < 2)
            {
                if (shmeia[i].get_x() > max_coord)
                {
                    max_coord = shmeia[i].get_x();
                }
                if (shmeia[i].get_y() > max_coord)
                {
                    max_coord = shmeia[i].get_y();
                }
                continue;
            }
            else
            {
                if (shmeia[i].get_x() > max_coord)
                {
                    max_coord = shmeia[i].get_x();
                }
                if (shmeia[i].get_y() > max_coord)
                {
                    max_coord = shmeia[i].get_y();
                }
                for (unsigned int j = 0; j < shmeia.size() - 1; j++) //pairnw kathe shmeio tou vector ^
                {
                    tmp += true_euclidean<double>(shmeia[j], shmeia[j + 1]);
                    plithos_athroismatwn += 1.0;
                }
                tmp = tmp / plithos_athroismatwn;
                delta += tmp;
                //std::cerr << "Tmp delta is " << delta << '\n';
            }
        }
        delta = delta / (double)(curves_array.size() - 86); //ki edw sbhnw to "-86" an eimai stin periptosi pou thelw kai ta query
        /*std::cerr << "Oliko delta is " << delta << '\n';*/

        //std::cerr << "Max coord is " << max_coord << '\n';

        std::vector<curve<double>> query_curves_array;
        //ta teleutaia 86 einai ta query
        const int q = 86;
        for (unsigned int i = curves_array.size() -86; i < curves_array.size(); i++)
        {
            query_curves_array.push_back(curves_array[i]); //to teleutaio einai query
            //curves_array.pop_back();                       //remove from input vector
            //n--;
        }
        //std::cout << query_curves_array.size() ;
        for(unsigned int i = 0; i < query_curves_array.size(); i++){
            curves_array.pop_back();
            n--;
        }
        dtw<double> dtww; //klash metrikwn kai ergaleiwn

        auto start_of_distance_matrix = std::chrono::high_resolution_clock::now();
        /*Distance Matrix Input X Query vectors me tis apostaseis tous*/
        double Brute_Distance_Matrix[curves_array.size()][query_curves_array.size()]; // o pinakas twn apostasewn gia to brute force kommati pragmatikhs sugkrishs
        for (unsigned int i = 0; i < curves_array.size(); i++)
          for (unsigned int j = 0; j < query_curves_array.size(); j++)
            Brute_Distance_Matrix[i][j] = dtww.actual_dtw(&curves_array[i], &curves_array[j]);

        auto end_of_distance_matrix = std::chrono::high_resolution_clock::now() - start_of_distance_matrix;
        long long microseconds_DM = std::chrono::duration_cast<std::chrono::microseconds>(end_of_distance_matrix).count();

        fprintf(stderr, "Time needed for distance matrix calculation is %lld microseconds.\n\n", microseconds_DM);


        //euresi actual NNs
        auto start_of_w_calc = std::chrono::high_resolution_clock::now();
        std::vector<NNpair> input_actual_NNs; //pinakas apo zeugaria actual NNs me prwto stoixeio to p
        for (unsigned int i = 0; i < curves_array.size(); i++)
        { //prepei na brw ta zeugaria ap to input gia ypologismo w

          std::string min_id1;
          double min1 = std::numeric_limits<double>::max(); //min pairnei timh apeiro
          for (unsigned int j = 0; j < curves_array.size(); j++)
          {
            if (dtww.actual_dtw(&curves_array[i], &curves_array[j]) == 0) //einai to idio shmeio
              continue;

            if (dtww.actual_dtw(&curves_array[i], &curves_array[j])  < min1)
            {
              min1 = dtww.actual_dtw(&curves_array[i], &curves_array[j]);
              min_id1 = curves_array[j].get_id();
            }
          }
          NNpair single_pair1(curves_array[i].get_id(), min_id1);
          single_pair1.set_distance(min1);
          input_actual_NNs.push_back(single_pair1);
        }

        double tmp5 = 0.0;
        double mean_distance = 0.0;
        for (unsigned int i = 0; i < input_actual_NNs.size(); i++)
        {
          tmp5 += input_actual_NNs.at(i).get_distance();
        }
        mean_distance = tmp5 / input_actual_NNs.size(); //fp division
        auto end_of_w_calc = std::chrono::high_resolution_clock::now() - start_of_w_calc;
        long long microseconds_w = std::chrono::duration_cast<std::chrono::microseconds>(end_of_w_calc).count();

        fprintf(stderr, "Time needed for w calculation is %lld microseconds.\n\n", microseconds_w);
        fprintf(stderr, "Value of w = %f\n", mean_distance);

        //also test gia w = 10 * mean_distance
        /*const*/ double w = 4 * mean_distance; //to w pou vazw sta ai

        //prepei na brw ton actual nearest neighbour
        auto start_of_actual_NN_all = std::chrono::high_resolution_clock::now();
        std::vector<NNpair> actual_NNs; //pinakas apo zeugaria actual NNs me prwto stoixeio to q
        std::vector<std::chrono::duration<double>> times_of_actual_NNs;
        for (unsigned int i = 0; i < query_curves_array.size(); i++)
        {
          auto start_of_this_actual_NN = std::chrono::high_resolution_clock::now();
          std::string min_id;
          double min = std::numeric_limits<double>::max(); //min pairnei timh apeiro
          for (unsigned int j = 0; j < curves_array.size(); j++)
          {
            if (Brute_Distance_Matrix[j][i] < min)
            {
              min = Brute_Distance_Matrix[j][i];
              min_id = curves_array[j].get_id();
            }
          }
          NNpair single_pair(query_curves_array[i].get_id(), min_id);
          single_pair.set_distance(min);
          actual_NNs.push_back(single_pair);
          auto end_of_this_actual_NN = std::chrono::high_resolution_clock::now() - start_of_this_actual_NN;
          times_of_actual_NNs.push_back(end_of_this_actual_NN);
        }

        auto end_of_actual_NN_all = std::chrono::high_resolution_clock::now() - start_of_actual_NN_all;
        long long microseconds_act_NN_all = std::chrono::duration_cast<std::chrono::microseconds>(end_of_actual_NN_all).count();
        fprintf(stderr, "Time needed for brute force found NNs is %lld microseconds.\n\n", microseconds_act_NN_all);





        std::vector<grid<double>> grids_v; //o pinakas twn grids
        for(int i =0; i<L_grid; i++){
          grid<double> tmp(delta,2);  //2 einai oi diastaseis mas gia tis kampyles
          grids_v.push_back(tmp);
        }

        int Table_Size = floor(n / 16);

        for(int j=0; j<L_grid; j++){
          std::vector<my_vector<double>> input_vectors_array; //TA VECTORS POY PROEKYPSAN APO TIS KAMPYLES EISODOU
          int max_dims = -1;
          for(unsigned int i = 0; i < curves_array.size(); i++){
            curve<double> grid_curve;
            grid_curve = grids_v[j].gridify(&curves_array[i]);
            my_vector<double> converted_vec;
            converted_vec = vectorify(grid_curve);
            if(converted_vec.get_v().size() > max_dims)
              max_dims = converted_vec.get_v().size() ;
            input_vectors_array.push_back(converted_vec);
          }
          for(unsigned int i = 0; i < input_vectors_array.size(); i++){
            add_pad(&input_vectors_array[i], 100*max_coord, max_dims);
          }

        }
        //make L grids
        //pername apo auta tis input curves -> grid curves -> vectors
        //Twra kanoume LSH apo A erwthma sta vectors auta
        //analoga to ti epistrefoun apothikeuoume sta hash tables (posa?) tis antistoixes kampules
        //epeita pername apo ta grids tis query curves -> grid curves -> vectors
        //apo LSH blepoume pou 8a epefte kathe query kai kratame ena vector me curves ws pithanous geitones (opws A)
        //epeita sugkrinoume autes me DTW
        //pairnoyme ton kontinotero, profit

        //EAN DEN ORISTHKE APO GRAMMH ENTOLWN, DWSE MONOPATI OUTPUT FILE
        if (oset == false)
        {
            std::cout << "Define output file path:\n";
            std::string inp1;
            std::cin >> output_path;
        }
        //std::ofstream outfile(output_path);
        std::ofstream outfile;
        outfile.open(output_path);

        /*for (unsigned int i = 0; i < approx_NNs.size(); i++) //for each itemJ in queryset:
        {
            outfile << "Query: " << approx_NNs[i].getq_id() << '\n';
            outfile << "Nearest neighbor: " << actual_NNs[i].getp_id() << '\n';
            outfile << "distanceLSH: " << approx_NNs[i].get_distance() << '\n';
            outfile << "distanceTrue: " << actual_NNs[i].get_distance() << '\n';
            outfile << "tLSH: " << times_of_approx_NNs[i].count() << '\n';
            outfile << "tTrue: " << times_of_actual_NNs[i].count() << '\n';*/
        /*if (bonus)
    {
      outfile << "R-near neighbors: " << '\n';
      for (however many R near we found)
      {
        outfile << "item_id" << '\n';
      }
    }

    }*/
        outfile.close();
        infile.close();

        //when done all, ask if repeat with other dataset or exit ektelesi
        std::cout << "Would you like to repeat with new dataset? Type y for yes or n for no\n";
        std::cin >> repeat_answer;
        if (repeat_answer != "y")
            repeat_answer = "n";
    } while (repeat_answer == "y");
}
