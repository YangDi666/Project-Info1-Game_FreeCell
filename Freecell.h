#ifndef _FREECELL_H
#define	_FREECELL_H
#include "Card.h"
#include "Tableau.h"
#include"Randomize.h"
#pragma once


const int MAX_RESERVED_CELLS = 8;
const int DEFAULT_NUMBER_OF_CASCADES = 8;
const int DEFAULT_NUMBER_OF_SUITS = 4;
const int DEFAULT_NUMBER_OF_CARDS_PER_SUIT = 13;
const int DEFAULT_NUMBER_OF_RESERVED_CELLS = 4;
const bool LOST = false;

const int FOUNDATION_INPUT_IDENTITY = 100;
const int RCELL_WIDTH = 2;

class FreeCell // auteurs : YANG & LI
{
	Tableau tableau_;
	Card foundationPile_[MAX_SUITS];
	Card reservedCells_[MAX_RESERVED_CELLS];
	int numberOfFoundationPiles_;
	int numberOfReservedCells_;
	int target_;
	int targetDestination_;

	bool gameWon_, resigned_;
	bool isToFoundation_;
	bool isToTableau_;
	bool isToReserved_;
	bool fromReserved_;
	bool fromTableau_;
public:
	FreeCell(int = DEFAULT_NUMBER_OF_CASCADES, int = DEFAULT_NUMBER_OF_SUITS,
		int = DEFAULT_NUMBER_OF_CARDS_PER_SUIT, int = DEFAULT_NUMBER_OF_RESERVED_CELLS);
	void print();
	void printEnding();
	int displayPromptAndReceiveInput(int);
	void convertTarget();
	void convertDestination();
	void moveCard();
	void validateTarget(int);
	void validateDestination(int);
	bool canMoveToFoundation(Card);
	bool validTableauMove(int targ, Card destC);
	void moveToFoundation(Card);
	bool isOver();
	//bool isAvailable(int inputTarget);
	bool playerResigned() const;
	void drawReserce();
	void drawFoundation();
	void charge(ifstream & filein);
	bool save(ofstream & file) const;


};
#endif	/* _FREECELL_H */
