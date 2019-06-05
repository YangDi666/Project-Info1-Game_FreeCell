#ifndef _CARD_H
#define	_CARD_H
#include "CImg.h"
#include <iostream>
#include <cassert>
#include <stdexcept>
#include <iomanip>
#include <time.h>
#include <cstdlib>
#include<fstream>
#include <sstream>
#include <string>
#include <cmath>
using namespace std;
using namespace cimg_library;

class Card // auteurs : YANG & LI
{
	char suit_;
	bool exists_;
	int face_;


public:
	Card();
	void print() const;
	string cardToString() const;
	int getFace() const;
	char getSuit() const;
	string getColor() const;
	CImg<unsigned char>  const getImg();
	bool isActive() const;
	void makeInactive();
	void setValues(int face, char suit);
};

#endif	