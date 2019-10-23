#include "curve_point.h"
#include "curve.h"
#include "traversal.h"
#include "utils.h"
#include "NNpair.h"
#include <iostream>
#include <typeinfo>
#include "h_funs.h"
#include "g_funs.h"
#include "ht.h"
#include <chrono> // time measurements
#include <fstream>
#include <stdlib.h>
//#include <algorithm> // std::count
#include <cstring>
//#include <limits>
//#include <set>
//#include <cmath>

std::string repeat_answer = "n";

int main(int argc, char *argv[])
{
    //test chamber
    //std::cout.precision(17);
    //std::string inp = "1	7	(-6.4227999999999996, 53.288000000000004) (-6.4257099999999996, 53.289299999999997) (-6.4268099999999997, 53.290300000000002) (-6.4268099999999997, 53.290300000000002) (-6.4268099999999997, 53.290300000000002) (-6.4271699999999994, 53.290599999999998) (-6.4271699999999994, 53.290599999999998)";
    //curve<double> crv(inp);
    //std::cout << crv.get_points()[0].get_x();

    //main
    //$./curve_grid_lsh -d <input file> -k_vec <int> -L_grid <int> -ο <output file>
    int k_vec = -1;
    int L_grid = -1;
    bool dset, oset = false; ////an oxi orisma grammis entolos, 8a parw ta files apo path pou grafei o user
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
        std::vector<curve<double>> query_curves_array;
        //ta teleutaia 86 einai ta query
        for (unsigned int i = curves_array.size(); i >= -curves_array.size() - 87; i--)
        {
            query_curves_array.push_back(curves_array[i]); //to teleutaio einai query
            curves_array.pop_back();                       //remove from input vector
        }

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