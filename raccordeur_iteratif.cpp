#include "raccordeur_iteratif.h"

int RaccordeurIteratif::calculerRaccord(MatInt2* distances, int* coupe){
	typedef struct {int cout; int parent;} erreurCumulative;
	erreurCumulative* E=new erreurCumulative[distances->nLignes()*distances->nColonnes()];
	int tailleLigne=distances->nColonnes();
	int cout, derniereLigne, indice;
	int tMin=std::numeric_limits<int>::max();

	//On copie la première ligne
	for(int j=0; j<tailleLigne; j++){
		E[j].cout=distances->get(0,j);//Pas sur pour l'ordre des paramètres
		E[j].parent=-1;
	}

	//Calcul du cout
  	for (int y = 0; y < distances->nLignes(); y++) {
    	for (int x = 0; x < distances->nColonnes(); x++) {
      		cout += distances->get(y, x);
    	}
  	}

	//Calcul des éléments de E ligne par ligne
	for(int i=1; i<distances->nLignes(); i++){
		for(int j=1; j<tailleLigne-1; j++){//Cas général
			E[j+i*tailleLigne].cout=distances->get(i,j);
			switch(ind_min_double(E[(j-1)+(i-1)*tailleLigne].cout, E[j+(i-1)*tailleLigne].cout, E[(j+1)+(i-1)*tailleLigne].cout)){
				case -1:
					E[j+i*tailleLigne].cout+=E[(j-1)+(i-1)*tailleLigne].cout;
					E[j+i*tailleLigne].parent=j-1;
					break;
				case 0:
					E[j+i*tailleLigne].cout+=E[j+(i-1)*tailleLigne].cout;
					E[j+i*tailleLigne].parent=j;
					break;
				case 1:
					E[j+i*tailleLigne].cout+=E[(j+1)+(i-1)*tailleLigne].cout;
					E[j+i*tailleLigne].parent=j+1;
					break;
			}
		}

		//Cas aux bords
		//1ere colonne
		if(ind_min_double(E[(i-1)*tailleLigne].cout, E[1+(i-1)*tailleLigne].cout)==-1){
			E[i*tailleLigne].cout=distances->get(i,0) + E[(i-1)*tailleLigne].cout;
			E[i*tailleLigne].parent=0;
		}
		else{
			E[i*tailleLigne].cout=distances->get(i,1) + E[1+(i-1)*tailleLigne].cout;
			E[i*tailleLigne].parent=1;
		}
		//Dernière colonne
		if(ind_min_double(E[i*tailleLigne-1].cout, E[i*tailleLigne-2].cout)==-1){
			E[(i+1)*tailleLigne-1].cout=distances->get(i,tailleLigne-1)+E[i*tailleLigne-1].cout;
			E[(i+1)*tailleLigne-1].parent=tailleLigne-1;
		}
		else{
			E[(i+1)*tailleLigne-1].cout=distances->get(i,tailleLigne-2)+E[i*tailleLigne-2].cout;
			E[(i+1)*tailleLigne-1].parent=tailleLigne-2;
		}
	}
	//Fin du calcul de E

	//On cherche l'indice le plus petit sur la dernière ligne
	derniereLigne=(distances->nLignes()-1)*tailleLigne;
	for(int j=0; j<tailleLigne; j++){
		if(E[derniereLigne+j].cout<tMin){
			tMin=E[derniereLigne+j].cout;
			indice=j;
		}
	}
	
	//On remonte pour remplir le tableau coupe
  	for(int y=distances->nLignes()-1; y>=0; y--){
    	coupe[y]=indice;
    	indice=E[indice+y*tailleLigne].parent;
  	}

  	return cout;
}

RaccordeurIteratif::~RaccordeurIteratif(){
	//Pas de ressources à libérer
}