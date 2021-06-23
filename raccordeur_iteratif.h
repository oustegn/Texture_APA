#ifndef _RACCORDEUR_ITERATIF_H
#define	_RACCORDEUR_ITERATIF_H

#include "raccordeur.h"
#include "tools.h"
#include <limits>

class RaccordeurIteratif : public Raccordeur {

  /*!
   * le calcul du raccord (\see{Raccordeur#calculerRaccord}).
   * Le code effectif se trouve dans RaccordeurSimple.cpp
   */
  virtual int calculerRaccord(MatInt2* distances, int* coupe);

  virtual ~RaccordeurIteratif(); // destructeur

};

#endif	/* _RACCORDEUR_ITERATIF_H */