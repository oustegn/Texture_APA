#ifndef RACORDEUR_REC
#define RACORDEUR_REC 

#include <iostream>
#include "raccordeur.h"
#include <algorithm>
#include <vector>
#include <cstdlib>
#include <stdbool.h>
using namespace std ;

class RaccordeurRecursif: public Raccordeur {

public:
int coupe_recursive(int i, int j);
virtual int calculerRaccord(MatInt2* distances, int* coupe);
virtual ~RaccordeurRecursif();

private:
   MatInt2* tab;
  int **sans_redondance; 
};

#endif
