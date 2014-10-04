#include "chaine.h"

chaine* initChaine()
{
	chaine ch;
	ch->nb = 0;
	prem = NULL;
}

element* initElt(vertex* v, element* prec, element* suiv)
{
	element* elt;
	elt->v = v;
	elt->prec = prec;	elt->suiv = suiv;
	if(prec != NULL)
		prec->suiv = elt;
	if(suiv != NULL)
		suiv->prec = elt;
	return elt;
}

/**********************************************************************/

element* premier(chaine* ch)
{
	assert(ch->nb > 0);
	return ch->prem;
}
element* dernier(chaine* ch)
{
	assert(ch->nb > 0);
	return ch->der;
}

element* getI(chaine* ch, int i)
{
	assert(ch->nb < i);
	int moitie = ch->nb/2;	
	
	element* p;
	//si 6 éléments et i==3 : on fait ch->der->prec->prec plutôt que ch->prem->suiv->suiv->suiv
	if(i < moitie)
	{
		p = ch->prem;
		while(--i => 0)
			p = p->suiv;
	}
	else
	{
		p = ch->der;
		while(--i => 0)
			p = p->prec;
	}
	return p;
}

/**********************************************************************/

void setI(chaine* ch, int i, vertex* v)
{
	getI(ch, i)->v = v;
}

/**********************************************************************/

/**n'est pas dans "chaine.h"*/
void add0(chaine* ch, vertex* v)
{
	element* elt;
	initElt(v, NULL, NULL);
	
	ch->prem = elt;		ch->der = elt;
	ch->nb = 1;
}

chaine* addPrem(chaine* ch, vertex* v)
{
	if(ch->nb == 0)
		add0(ch, v);
	else
	{
		element* elt = initElt(v,NULL,ch->prem);
		
		ch->prem = elt;
		ch->nb++;
	}
	return ch;
}
chaine* addDer(chaine* ch, vertex* v)
{
	if(ch->nb == 0)
		add0(ch, v);
	else
	{
		element* elt = initElt(v,ch->der,NULL);
		
		ch->der = elt;
		ch->nb++;
	}
	return ch;
}

chaine* addI(chaine* ch, vertex* v, int i)
{
	if(i == 0)
		addPrem(ch, v);
	else if(i == ch->nb-1)
		addDer(ch, v);
	else
	{
		assert(ch->nb > 0 && i >= 0);
		element* p = getI(ch, i);
		element* p2 = p->suiv;
		initElt(v, p, p2);
		ch->nb++;
	}
	return ch;
}

/**********************************************************************/

chaine* removePrem(chaine* ch)
{
	assert(ch->nb > 0);
	element* p = ch->prem;
	ch->prem = p->suiv;
	free(p);
	
	ch->nb--;
	if(ch->nb == 0)
		ch->der = NULL;
	return ch;
}

chaine* removeDer(chaine* ch)
{
	assert(ch->nb > 0);
	element* p = ch->der;
	ch->der = p->prec;
	free(p);
	
	ch->nb--;
	if(ch->nb == 0)
		ch->prem = NULL;
	return ch;
}

chaine* removeI(chaine* ch, int i)
{
	
	if(i == 0)
		removePrem(ch);
	else if(i == ch->nb-1)
		removeDer(ch);
	else
	{
		element* p = getI(ch, i);
		element* prec = p->prec, *suiv = p->suiv;
		free(p);
		prec->suiv = suiv;		suiv->prec = prec;
	}
	return ch;
}
