#ifndef _UTILS_H_
#define _UTILS_H_

#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h> //labs, llabs
#include <sstream>
#include <cmath> //abs with overload for float
#include "my_vector.h"

/*Inner Product*/
//double my_inner_product(std::vector<int> v1, std::vector<int> v2);
/*

double my_inner_product(std::vector<int> v1, std::vector<int> v2) { //vi * v2 = sum(v1i * v2i) gia kathe i
	if (v1.size() != v2.size()) {
		//cerr << "Can't calculate distance, need same dimensions! Aborting...\n";
        exit(-1);
	}
	double temp=0.0;
	std::vector<int> products;
	for (unsigned int i = 0; i < v1.size(); ++i) { //std::inner_product
		temp = v1[i]*v2[i];
		products.push_back(temp);
	}
	temp = 0.0;
	for(std::vector<int>::iterator it = products.begin(); it != products.end(); ++it) {
		temp += *it; //to athroisma twn ginomenwn
	}
	return temp;
}
*/

/*Vector's Length*/
//double my_vector_metro(std::vector<int> v);
/*
double my_vector_metro(std::vector<int> v) {
	double temp=0.0;
	std::vector<int> squared;
	for (unsigned int i = 0; i < v.size(); ++i) {
		temp = v[i]*v[i];
		squared.push_back(temp);//tetragwna kathe thesis
	}
	temp = 0.0;
	for(std::vector<int>::iterator it = squared.begin(); it != squared.end(); ++it) {
		temp += *it; //to athroisma twn tetragwnwn
	}
	return sqrt(temp); //sqrt autwn
}
*/


/*Manhattan Distance*/
template <typename T> double manhattan_distance(std::vector<T> v1, std::vector<T> v2);

template <typename T> /*template <class//typename T>*/
double manhattan_distance(std::vector<T> v1, std::vector<T> v2) { //sum twn (apoluti timi twn diaforwn twn  (suntetagmeni i tou v1, syntetagmeni i tou v2) )
    if (v1.size() != v2.size()) {
		std::cerr << "Can't calculate distance, need same dimensions! Aborting...\n";
        exit(-1);
	}
    T temp;
	if ((typeid(temp) == typeid(float)) || (typeid(temp) == typeid(double))) {
		temp = 0.0;
	}
	else if (typeid(temp) == typeid(int)) {
		temp = 0;
	}

	std::vector<T> diffs;
	for (unsigned int i = 0; i < v1.size(); ++i) {
		temp = abs(v1[i]-v2[i]);
		diffs.push_back(temp);
        //ws edw leitourgei ok
	}
    double result = 0.0;

	for(typename std::vector<T>::iterator it = diffs.begin(); it != diffs.end(); ++it) {
		//std::cerr << *it << "\n";
        result = result + (double)*it; //to athroisma twn apol. diaforwn
        //std::cerr << result << "\n";
	}
    //std::cerr << "Ara telika exw " << result << "\n";
	return result;
}

#endif