#ifndef __CHAINE_H__
#define __CHAINE_H__

#include "two.h"

//liste doublement chainée
typedef struct
{
	struct element* prem;	//pointeur sur le premier élément
	struct element* der;	//pointeur sur le dernier élément
	int nb;
} chaine;

typedef struct
{
	vertex v;
    struct element* prec;
	struct element* suiv;	//pointeur vers le prochain élément 

} element;

chaine* initChaine();
element* initElt(vertex* v, element* prec, element* suiv);

/**********************************************************************/

element* premier(chaine* ch);
element* dernier(chaine* ch);
element* getI(chaine* ch, int i);

/**********************************************************************/

void setI(chaine* ch, int i, vertex* v);

/**********************************************************************/

/**n'est pas dans "chaine.h"*/
void add0(chaine* ch, vertex* v);
chaine* addPrem(chaine* ch, vertex* v);
chaine* addDer(chaine* ch, vertex* v);
chaine* addI(chaine* ch, vertex* v, int i);

/**********************************************************************/

chaine* removePrem(chaine* ch);
chaine* removeDer(chaine* ch);
chaine* removeI(chaine* ch, int i);

#endif
