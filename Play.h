#ifndef _PLAY_H
#define	_PLAY_H
#include "Card.h"
#include "Tableau.h"
#include"Randomize.h"
#include "FreeCell.h"
#include <iostream>
#include <cassert>
#include <stdexcept>
#include <iomanip>
#include <time.h>
#include <cstdlib>
#include <sstream>
#include <string>
#include <cmath>
#pragma once



class Play //// auteur : YANG
{
	bool start_;
	int a_;
public:
	Play(bool start,int a);
	void letsgo();   
};
#endif	/* _PLAY_H */


