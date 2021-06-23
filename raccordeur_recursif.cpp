#include "raccordeur_recursif.h"
#include <algorithm>
#include <vector>
#include <cstdlib>
#include "tools.h"
using namespace std ;

RaccordeurRecursif::~RaccordeurRecursif(){}

int RaccordeurRecursif::coupe_recursive(int i, int j){

	if (this->sans_redondance[i][j]==-1){ //cette cellule n'est pas encore faite
		if(j==0){ //on aura pas de parent pour l'élément i,j car c'est la ligne 0 donc on le recopie
	      this->sans_redondance[j][j]=this->tab->get(j,i);
	  	}
	  	else
	    	if (i==0){//si on est à la colonne 0, alors on aura 
	    		this->sans_redondance[i][j]=this->tab->get(j,i)+min(coupe_recursive(i,j-1),coupe_recursive(i+1,j-1));
	    	}else{
	    		if (i==this->tab->nColonnes()-1){ // si nous sommes dans la derniere colonne, on peut pas avoir j+1
	      			this->sans_redondance[i][j]=this->tab->get(j,i)+min(coupe_recursive(i-1,j-1),coupe_recursive(i,j-1));
	      		}
				else{
	        		this->sans_redondance[i][j]=this->tab->get(j,i)+min(min(coupe_recursive(i-1,j-1),coupe_recursive(i,j-1)),coupe_recursive(i+1,j-1));
	      		}
	    	}
	}//renvoyer l'élément ij de E

	return this->sans_redondance[i][j];
}

int RaccordeurRecursif::calculerRaccord(MatInt2* distances, int* coupe){

  int cout = 0;
  int ligne = distances->nLignes();
  int colonne = distances->nColonnes();
  auto val = 0;
  int elem,index;
  std::vector<int> vect;
  this->tab=distances;

//Initialise le tableau de controle de redondance
  sans_redondance = new int*[ligne];
  for(int i = 0; i < ligne; ++i)
	sans_redondance[i] = new int[colonne];

  for (int i=0;i<ligne;i++){
	for (int j=0;j<colonne;j++){
	    sans_redondance[i][j]=-1;
	    }
  }

//Calcul recursif des élément de la coupe(c à d E)
	for (int i = 0; i < ligne; i++) {
		for (int j = 0; j < colonne; j++){
			elem=coupe_recursive(j,i);
			distances->set(i,j,elem); //on insere cet element dans la coupe
		}
	}

	//calcul du coup et le remplissage du tableau int* coupe
	//Calcule du premier element de coupe et recuperaation de son index(min de la derniere ligne)
	for (int i = 0; i < colonne; i++){
		//on recopie toute la ligne dans un vecteur puis trouver son min
		vect.push_back(distances->get(ligne-1,i));
	}
	val = *min_element(vect.begin(),vect.end());
	cout+=val;
	//recuperer l'iterateur sur ce min
	vector<int>::iterator it=find(vect.begin(),vect.end(),val);
	//puisque coupe est unidimentionnelle, il nous faut le nbr d'itération pour avoir l'indice de l'élém
	coupe[ligne-1]=distance(vect.begin(),it);
	vect.clear();

	//Maintenant, calculons les autres éléments de coupe
	for (int i = ligne-2; i >= 0; i--){ //on part de la lige-2 puisqu'on a déjà celui de ligne-1
		elem=coupe[i+1];
		if(elem==0){ //le min de la ligne d'avant est sur la premiere colonne
			//Recuperation de l'index du minimum de la ligne superieure(entre l'élém tout en dessus et celui à droite de celui-ci)
			index= ind_min_double(10000,distances->get(i,elem), distances->get(i,elem+1));
			cout+=distances->get(i,elem+index);
			coupe[i]=elem+index;
		}
		else{
			if(elem==colonne-1){//le min de la ligne d'avant est sur la dernière colonne
			   //entre l'élément en dessus et celui à gauche de celui-ci
				index= ind_min_double(distances->get(i,elem-1), distances->get(i,elem),10000);
				cout+=distances->get(i,elem+index);
				coupe[i]=elem+index;
			}
			else{// le min de la linge est ailleurs
				//Recuperation de l'index du minimum entre l'élém en dessus et celui à droite&gauche
				index= ind_min_double(distances->get(i,elem-1),distances->get(i,elem), distances->get(i,elem+1) );
				cout+=distances->get(i,elem+index);
				coupe[i]=elem+index;
			}
		}

	}

	return cout;
}
