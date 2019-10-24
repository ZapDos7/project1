#ifndef _UTILS_H_
#define _UTILS_H_

#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>
#include <typeinfo>
#include <stdlib.h> //labs, llabs
#include <sstream>
#include <cmath> //abs with overload for float
#include <limits>
/*#include "curve_point.h"
#include "curve.h"
#include "traversal.h"*/

/*Manhattan Distance*/
template <typename T>
double manhattan_distance(std::vector<T> v1, std::vector<T> v2);

template <typename T> /*template <class//typename T>*/
double manhattan_distance(std::vector<T> v1, std::vector<T> v2)
{ //sum twn (apoluti timi twn diaforwn twn  (suntetagmeni i tou v1, syntetagmeni i tou v2) )
	if (v1.size() != v2.size())
	{
		std::cerr << "Can't calculate distance, need same dimensions! Aborting...\n";
		exit(-1);
	}
	T temp;
	if ((typeid(temp) == typeid(float)) || (typeid(temp) == typeid(double)))
	{
		temp = 0.0;
	}
	else if (typeid(temp) == typeid(int))
	{
		temp = 0;
	}

	std::vector<T> diffs;
	for (unsigned int i = 0; i < v1.size(); ++i)
	{
		temp = abs(v1[i] - v2[i]);
		diffs.push_back(temp);
		//ws edw leitourgei ok
	}
	double result = 0.0;

	for (typename std::vector<T>::iterator it = diffs.begin(); it != diffs.end(); ++it)
	{
		//std::cerr << *it << "\n";
		result = result + (double)*it; //to athroisma twn apol. diaforwn
									   //std::cerr << result << "\n";
	}
	//std::cerr << "Ara telika exw " << result << "\n";
	return result;
}

#endif