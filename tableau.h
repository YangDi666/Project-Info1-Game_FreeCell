#ifndef _TABLEAU_H
#define	_TABLEAU_H
#include "Card.h"
#pragma once

const int MAX_SUITS = 4; // also used in class tableau
const int MAX_FACE = 13;
const int ACE = 1;
const int MAX_CASCADES = 9; // used in FreeCell
const int MAX_ROWS = 30;
const int WIDTH = 3;
using namespace std;
using namespace cimg_library;

extern unsigned char grid_color[];
extern CImg<unsigned char> grid;
extern CImgDisplay disp;

class Tableau // auteurs : YANG & LI
{
	int cardsPerSuit_;
	int numberOfSuits_;
	int numberOfCards_;
	int numberOfCascades_;
	int rowsNeeded_;
	int rowsNeededPlusExtra_;

	Card cardsInCascades[MAX_ROWS][MAX_CASCADES];
	int cardsRemaining_;

public:
	Tableau(int numCasc = 4, int numSuits = 4, int crdsPSuit = 13);
	void moveTo(int);
	void placeCardAt(int row, int cascade, Card c);
	Card retrieveCardAt(int row, int cascade) const;
	void deactivate(int cascade);
	int findRowIndexContainingExistingCard(int cascade) const; // given column, find row
	int getNumberOfSuits() const;
	int getNumberOfCardsPerSuit() const;
	int getRowsNeeded() const;
	int getNumberOfCascades() const;
	void decreaseTotalCards();
	void print();
	void drawTableau();
	void charge(ifstream & filein);
	bool save(ofstream & file)const;
};

#endif	/* _TABLEAU_H */