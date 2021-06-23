#include "permuteur.h"
#include <stdlib.h>
#include <algorithm>
using namespace std ;
Permuteur::Permuteur(int max){
	this->max = max;
	this->perm= (int *) calloc(max, sizeof(int));
	for(int i = 0;i<max;i++){
		this->perm[i]=i;
	}
	//initiation par défaut, ça pourrait changer
	this->indices = (int*) calloc(max,sizeof(int));
	this->i_perm=0;
	//on fait random_shuffle sur la premièrec config
	random_shuffle(this->perm,this->perm+this->max);

}

Permuteur::~Permuteur(){
  if (perm) delete perm;
  if (indices) delete indices;
}

int Permuteur::suivant(){
	if(this->i_perm>=this->max){
		this->i_perm=0;
		random_shuffle(this->perm,this->perm+this->max);
	}
	return this->perm[this->i_perm++];
}
