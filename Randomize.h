#ifndef _RANDOMIZE_H
#define	_RANDOMIZE_H
#include "Card.h"
#include "Tableau.h"
#pragma once

class Randomize // auteurs : YANG & LI
{
	Card cardsToShuffle_[MAX_SUITS][MAX_FACE];
	int nSuits_;
	int cardsPSuit_;
	void setDefaults_();
	void shuffleDefaults_();
	void storeShuffledCards_(Tableau &d);
public:
	Randomize(Tableau &d);
};
#endif	/* _RANDOMIZE_H */
