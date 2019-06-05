#include "Freecell.h"


FreeCell::FreeCell(int nCasc, int nSuits, int nCrdsPerSuit, int nRsvCells)
{
	
	assert(nSuits<= MAX_SUITS && nSuits> 0);
	assert(nCasc<= MAX_CASCADES && nCasc> 0);
	assert(nRsvCells <= MAX_RESERVED_CELLS && nRsvCells >= 0);
	assert(nCrdsPerSuit<= MAX_FACE && nCrdsPerSuit> 0);

	gameWon_= false;
	resigned_= false;

	numberOfReservedCells_= nRsvCells;
	numberOfFoundationPiles_= nSuits;

	// create a temporaty deck
	Tableau t(nCasc, nSuits, nCrdsPerSuit);

	// store the temp deck
	tableau_= t;

	// shuffle the tableau pile
	Randomize shuffle(tableau_);
}
// void FreeCell::printEnding() -- prints whether the player won or lost
void FreeCell::printEnding()
{
	if (resigned_)
		cout << "Player resigned. Please play again!";
	else
		cout << "WINNER! Woah!! I'm almost surprised YOU won. Awesome.";

	cout << endl;
}
bool FreeCell::playerResigned()  const
{
	return resigned_;
}
void FreeCell::drawReserce()
{      
		for (int g = 0; g < numberOfReservedCells_; g++)
		{
			if (reservedCells_[g].isActive())
				grid.draw_image(40 + 120 * (g), 40,reservedCells_[g].getImg());
		}

}

void FreeCell::drawFoundation()
{
	for (int g = 0; g < numberOfFoundationPiles_; g++)
	{
		if (foundationPile_[g].isActive())
		{
			grid.draw_image(580 + 120 * (g), 40, foundationPile_[g].getImg());
		}
	}
}

// void FreeCell::moveToFoundation( Card cardToMove )
//
// PRE: none
// POST: moves given card to the foundation stack.
void FreeCell::moveToFoundation(Card cardToMove)
{
	// since we are removing a card from play, we can decrease the number of playing cards
	tableau_.decreaseTotalCards();

	for (int i = 0; i < numberOfFoundationPiles_; i++)
	{
		if (!foundationPile_[i].isActive())
		{
			if (cardToMove.getFace() == ACE)
			{
				// if the card is an ace and the foundation is empty, we will store the card
				foundationPile_[i] = cardToMove;
				return;
			}
		}
		else if (foundationPile_[i].getSuit() == cardToMove.getSuit())
		{
			// the incoming card must be one HIGHER than the card with the same suit
			if (foundationPile_[i].getFace() == cardToMove.getFace() - 1)
			{

				foundationPile_[i]= cardToMove;
				return;
			}
		}
	}
}
// bool FreeCell::canMoveToFoundation( Card cardToMove )
// -- this function is the checker for the one above.
// PRE: none
// POST: returns true if a given card can be placed into the tableau
bool FreeCell::canMoveToFoundation(Card cardToMove)
{
	for (int i = 0; i < numberOfFoundationPiles_; i++)
	{
		if (!foundationPile_[i].isActive())
		{
			if (cardToMove.getFace() == ACE)
			{
				return true;
			}
		}
		else if (foundationPile_[i].getSuit() == cardToMove.getSuit())
		{
			if (foundationPile_[i].getFace() == cardToMove.getFace() - 1)
			{
				return true;
			}
		}
	}
	return false;
}

// void FreeCell::moveCard() -- moves a card from target to destination
//
// PRE: there is a checker function that was already called (called validateDestination)
// POST: moves a card to target.
void FreeCell::moveCard()
{
	convertTarget();
	convertDestination();

	Card replacement;
	int oldRow;
	int newRow;
	if (fromReserved_)
	{
		if (isToFoundation_)
		{
			// save the card
			replacement = reservedCells_[target_];

			// since we are moving to the foundation, we call that fctn
			moveToFoundation(replacement);

			// disables the card that we just moved
			reservedCells_[target_].makeInactive();
		}
		else if (isToReserved_)
		{
			replacement = reservedCells_[target_];
			reservedCells_[target_].makeInactive();

			// store the card to the reserved cell
			reservedCells_[targetDestination_] = replacement;
		}
		else if (isToTableau_)
		{
			replacement = reservedCells_[target_];
			reservedCells_[target_].makeInactive();

			// find the row that the destination card will fall on
			newRow = tableau_.findRowIndexContainingExistingCard(targetDestination_) + 1;

			// places the card at given location
			tableau_.placeCardAt(newRow, targetDestination_, replacement);
		}
	}
	// move the card from the tableau to...
	else if (fromTableau_)
	{
		if (isToFoundation_)
		{
			int row = tableau_.findRowIndexContainingExistingCard(target_);
			replacement = tableau_.retrieveCardAt(row, target_);
			moveToFoundation(replacement);
			tableau_.deactivate(target_);
		}
		else if (isToReserved_)
		{

			// find the row that the target card is on
			oldRow = tableau_.findRowIndexContainingExistingCard(target_);

			// copy the card that needs to be moved
			replacement = tableau_.retrieveCardAt(oldRow, target_);
			// deactivate that card
			tableau_.deactivate(target_);

			reservedCells_[targetDestination_] = replacement;
		}
		else if (isToTableau_)
		{
			// find the row that the card that is moving is on
			oldRow = tableau_.findRowIndexContainingExistingCard(target_);

			// copy the card that needs to be moved
			replacement = tableau_.retrieveCardAt(oldRow, target_);
			// deactivate that card
			tableau_.deactivate(target_);

			// find the row that the destination card will fall on
			newRow = tableau_.findRowIndexContainingExistingCard(targetDestination_) + 1;
			tableau_.placeCardAt(newRow, targetDestination_, replacement);
		}
	}// end else-if
}
// bool FreeCell::validTableauMove( int trgt, Card destinationCard )
//
// PRE:
// PRE: returns true if card can be placed onto the tableau
bool FreeCell::validTableauMove(int trgt, Card destinationCard)
{
	assert(trgt >= 0);
	int row;

	row = tableau_.findRowIndexContainingExistingCard(trgt);
	Card targetCard = tableau_.retrieveCardAt(row, trgt);

	// compare colors of the cards
	if (targetCard.getColor() == destinationCard.getColor())
	{
		return false;
	}

	// target card MUST be one less than the rank of destination card
	else if (!(targetCard.getFace() == destinationCard.getFace() - 1))
	{
		return false;
	}

	return true;
}
// void FreeCell::validateTarget( int prompt)
// ---This is a little confusing b/c we need to check all the rules of FreeCell
// PRE: promt must be 0 or 1
// POST: This will continuously ask for a valid card to move and will store this value (NOT zero based) when it finds it
void FreeCell::validateTarget(int prompt)
{
	assert(prompt == 0 || prompt == 1);

	// this means the player has RESIGNED.
	if (target_== 0)
		resigned_= true;

	// if target is a reserved cell, check that it is an actual tableau AND it has a card
	else if (target_>= 10 && target_<= 10 * numberOfReservedCells_)
	{
		// if there is a remained then this indicates the operator input something like 11
		if (target_% 10 != 0)
		{
			cout << endl << "!! Location " << target_<< " is invalid. " << endl;
			displayPromptAndReceiveInput(prompt);
		}
		else if (!reservedCells_[target_/ 10 - 1].isActive())
		{
			cout << endl << "!! There isn't a card at Location " << target_ << ". " << endl;
			displayPromptAndReceiveInput(prompt);
		}
		// possible bad values have been checked so we know this is true
		else
		{
			fromReserved_ = true;
			fromTableau_ = false;
		}
	}
	// this ensures that the card to be moved is at an actual place. must be on [1,numCascades]
	else if (target_ > 0 && target_ <= tableau_.getNumberOfCascades())
	{
		// if the cascade chosen doesn't have a card, request a new one
		if (tableau_.findRowIndexContainingExistingCard(target_ - 1) < 0)
		{
			cout << endl << "Cascade " << target_ << " does not contain a card." << endl;
			displayPromptAndReceiveInput(prompt);
		}
		else
		{
			fromReserved_ = false;
			fromTableau_ = true;
		}
	}
	else
	{
		cout << endl << "!! Location " << target_<< " is invalid. " << endl;
		displayPromptAndReceiveInput(prompt);
	}

}

// void FreeCell::validateDestination(int prompt) -- this checks that both the target card and destination card are compatible for the move
// !!!--- This is a little confusing b/c we need to check all the rules of FreeCell
// PRE:
// POST: will store boolean values to respective destinations
void FreeCell::validateDestination(int prompt)
{
	// if they decide the do not want to move the same card they can input 0 to select a new one
	if (targetDestination_ == 0)
	{
		// ditch the original target and get a new one.
		displayPromptAndReceiveInput(0);
	}

	// card destination is a foundation
	if (targetDestination_ == FOUNDATION_INPUT_IDENTITY)
	{
		Card replacement;
		// determines where the target originated so these if statemenst can determine if a legal move is available
		if (fromReserved_)
		{
			replacement = reservedCells_[target_ / 10 - 1];
		}
		else  if (fromTableau_)
		{
			int row = tableau_.findRowIndexContainingExistingCard(target_ - 1);
			replacement = tableau_.retrieveCardAt(row, target_ - 1);
		}
		if (canMoveToFoundation(replacement))
		{
			isToFoundation_ = true;
			isToTableau_ = false;
			isToReserved_= false;
		}
		else
		{
			cout << "!! Cannot move card at " << target_ << " to a foundaion pile" << endl;
			displayPromptAndReceiveInput(prompt);
		}



	}// end if for destination Foundation cards

	 // if targetDestination is a potential reserved cell...
	else if (targetDestination_ >= 10 && targetDestination_ <= 10 * numberOfReservedCells_)
	{
		// Ensure that it is an actual location AND does NOT have a card
		if (targetDestination_ % 10 != 0)
		{
			cout << endl << "!! Location " << targetDestination_ << " is invalid. " << endl;
			displayPromptAndReceiveInput(prompt);
		}
		else if (reservedCells_[targetDestination_ / 10 - 1].isActive())
		{
			cout << endl << "!! There is already a card at Location " << targetDestination_ << ". " << endl;
			displayPromptAndReceiveInput(prompt);
		}
		else
		{

			isToFoundation_= false;
			isToTableau_ = false;
			isToReserved_ = true;

		}

	}
	// this is the case for destination as a tableau card
	else if (targetDestination_ > 0 && targetDestination_ <= tableau_.getNumberOfCascades())
	{
		if (fromTableau_)
		{
			int row = tableau_.findRowIndexContainingExistingCard(targetDestination_- 1);
			// indicates that the destination cascade is empty so we can add the card without checking anything.
			if (row < 0)
			{

				isToFoundation_ = false;
				isToTableau_ = true;
				isToReserved_ = false;

				// this is needed to prevent errors that would occur if destinationCard attempted to be created
				return;
			}

			Card destinationCard = tableau_.retrieveCardAt(row, targetDestination_ - 1);
			// moving from tableau to tablueu so make them zero based
			if (validTableauMove(target_- 1, destinationCard))
			{
				isToFoundation_ = false;
				isToTableau_= true;
				isToReserved_ = false;
			}
			else
			{
				cout << "That is not a legal move" << endl;
				displayPromptAndReceiveInput(prompt);
			}
		}
		// moving reserved card to tableau
		else if (fromReserved_)
		{
			// make a copy of cascade card
			int row = tableau_.findRowIndexContainingExistingCard(targetDestination_ - 1);
			if (row < 0)
			{
				isToFoundation_= false;
				isToTableau_ = true;
				isToReserved_= false;
				return;
			}
			Card destinationCard = tableau_.retrieveCardAt(row, targetDestination_ - 1);

			// make a copy of reserved cell card
			Card targetCard = reservedCells_[target_ / 10 - 1];

			// compare colors of the cards
			if (targetCard.getColor() == destinationCard.getColor())
			{
				cout << "That is not a legal move" << endl;
				displayPromptAndReceiveInput(prompt);
			}
			// target card MUST be one less than the rank of destination card
			else if (!(targetCard.getFace() == destinationCard.getFace() - 1))
			{
				cout << "That is not a legal move" << endl;
				displayPromptAndReceiveInput(prompt);
			}
			else
			{
				isToFoundation_ = false;
				isToTableau_ = true;
				isToReserved_ = false;
			}
		}


	}
	else
	{
		cerr << endl << "!! Location " << targetDestination_<< " is invalid";
		displayPromptAndReceiveInput(prompt);
	}
}
int FreeCell::displayPromptAndReceiveInput(int prompt)
{
	if (cin.fail())
		exit(1);

	string inputStuff = "";
	bool flag1 = false;
	bool flag2 = false;
	switch (prompt)
	{
	case 0: {
		// prompt
		cout << "From which pile do you wish to take a card? (1-" << tableau_.getNumberOfCascades()
			<< ", 10-" << 10 * numberOfReservedCells_ << ", 0 to resign): ";
		// receive
		//************************************************
		disp._button = 0;
		while (!flag1 && !flag2)
		{
			if (disp.button() & 1) { // Left button clicked.
				flag1 = true;
				if ((disp.mouse_x() > 30)&(disp.mouse_x() < 130)&(disp.mouse_y() < 400)&(disp.mouse_y() >150))
				{
					target_ = 1; flag1 = true; flag2 = true; break;
				}
				else if ((disp.mouse_x() > 150)&(disp.mouse_x() < 250)&(disp.mouse_y() < 400)&(disp.mouse_y() >150))
				{
					target_ = 2; flag1 = true; flag2 = true; break;
				}
				else if ((disp.mouse_x() > 270)&(disp.mouse_x() < 370)&(disp.mouse_y() < 400)&(disp.mouse_y() >150))
				{
					target_ = 3; flag1 = true; flag2 = true; break;
				}
				else if ((disp.mouse_x() > 390)&(disp.mouse_x() < 490)&(disp.mouse_y() < 400)&(disp.mouse_y() >150))
				{
					target_ = 4; flag1 = true; flag2 = true; break;
				}
				else if ((disp.mouse_x() > 570)&(disp.mouse_x() < 670)&(disp.mouse_y() < 400)&(disp.mouse_y() >150))
				{
					target_ = 5; flag1 = true; flag2 = true; break;
				}
				else if ((disp.mouse_x() > 690)&(disp.mouse_x() < 790)&(disp.mouse_y() < 400)&(disp.mouse_y() >150))
				{
					target_ = 6; flag1 = true; flag2 = true; break;
				}
				else if ((disp.mouse_x() > 810)&(disp.mouse_x() < 910)&(disp.mouse_y() < 400)&(disp.mouse_y() >150))
				{
					target_ = 7; flag1 = true; flag2 = true; break;
				}
				else if ((disp.mouse_x() > 930)&(disp.mouse_x() < 1030)&(disp.mouse_y() < 400)&(disp.mouse_y() >150))
				{
					target_ = 8; flag1 = true; flag2 = true; break;
				}
				if ((disp.mouse_x() > 30)&(disp.mouse_x() < 130)&(disp.mouse_y() > 30)&(disp.mouse_y() < 170))
				{
					target_ = 10; flag1 = true; flag2 = true; break;
				}
				else if ((disp.mouse_x() > 150)&(disp.mouse_x() < 250)&(disp.mouse_y() > 30)&(disp.mouse_y() < 170))
				{
					target_ = 20; flag1 = true; flag2 = true; break;
				}
				else if ((disp.mouse_x() > 270)&(disp.mouse_x() < 370)&(disp.mouse_y() > 30)&(disp.mouse_y() < 170))
				{
					target_ = 30; flag1 = true; flag2 = true; break;

				}
				else if ((disp.mouse_x() > 390)&(disp.mouse_x() < 490)&(disp.mouse_y() > 30)&(disp.mouse_y() < 170))
				{
					target_ = 40; flag1 = true; flag2 = true; break;
				}
				else if ((disp.mouse_x() > 430)&(disp.mouse_x() < 630)&(disp.mouse_y()> 650)&(disp.mouse_y() < 700))
				{
					target_ = 0; flag1 = true; flag2 = true; break;
				}
			}
		}
		//************************************************
		//cin >> target_;//
		validateTarget(prompt);
		break;
	} // end switch, case: 0
	case 1: {
		// prompt
		cout << endl << "Moving card from " << target_ << ". Where do you wish to place this card? (0 to cancel) ";
		// receive
		//*******************************************
		disp._button = 0;
		while (!flag1 && !flag2)
		{
			if (disp.button() & 2)
			{
			  targetDestination_ = 0; flag1 = true; flag2 = true; break;
			}
			if (disp.button() & 1) { // Left button clicked.

				if ((disp.mouse_x() > 30)&(disp.mouse_x() < 130)&(disp.mouse_y() > 30)&(disp.mouse_y() < 170))
				{
					targetDestination_ = 10; flag1 = true; flag2 = true; break;
				}
				else if ((disp.mouse_x() > 150)&(disp.mouse_x() < 250)&(disp.mouse_y() > 30)&(disp.mouse_y() < 170))
				{
					targetDestination_ = 20; flag1 = true; flag2 = true; break;
				}
				else if ((disp.mouse_x() > 270)&(disp.mouse_x() < 370)&(disp.mouse_y() > 30)&(disp.mouse_y() < 170))
				{
					targetDestination_ = 30; flag1 = true; flag2 = true; break;

				}
				else if ((disp.mouse_x() > 390)&(disp.mouse_x() < 490)&(disp.mouse_y() > 30)&(disp.mouse_y() < 170))
				{
					targetDestination_ = 40; flag1 = true; flag2 = true; break;
				}
				if ((disp.mouse_x() > 30)&(disp.mouse_x() < 130)&(disp.mouse_y() >200)&(disp.mouse_y() < 400))
				{
					targetDestination_ = 1; flag1 = true; flag2 = true; break;
				}
				else if ((disp.mouse_x() > 150)&(disp.mouse_x() < 250)&(disp.mouse_y() >200)&(disp.mouse_y() < 400))
				{
					targetDestination_ = 2; flag1 = true; flag2 = true; break;
				}
				else if ((disp.mouse_x() > 270)&(disp.mouse_x() < 370)&(disp.mouse_y() >200)&(disp.mouse_y() < 400))
				{
					targetDestination_ = 3; flag1 = true; flag2 = true; break;
				}
				else if ((disp.mouse_x() > 390)&(disp.mouse_x() < 490)&(disp.mouse_y() >200)&(disp.mouse_y() < 400))
				{
					targetDestination_ = 4; flag1 = true; flag2 = true; break;
				}
				else if ((disp.mouse_x() > 570)&(disp.mouse_x() < 670)&(disp.mouse_y() >200)&(disp.mouse_y() < 400))
				{
					targetDestination_ = 5; flag1 = true; flag2 = true; break;
				}
				else if ((disp.mouse_x() > 690)&(disp.mouse_x() < 790)&(disp.mouse_y() >200)&(disp.mouse_y() < 400))
				{
					targetDestination_ = 6; flag1 = true; flag2 = true; break;
				}
				else if ((disp.mouse_x() > 810)&(disp.mouse_x() < 910)&(disp.mouse_y() >200)&(disp.mouse_y() < 400))
				{
					targetDestination_ = 7; flag1 = true; flag2 = true; break;
				}
				else if ((disp.mouse_x() > 930)&(disp.mouse_x() < 1030)&(disp.mouse_y() >200)&(disp.mouse_y() < 400))
				{
					targetDestination_ = 8; flag1 = true; flag2 = true; break;
				}
				else
				{
					targetDestination_ = 100; 
					flag1 = true; flag2 = true; break;
				}
			}
		}
		//*******************************************
		if (targetDestination_ < 0)
		{
			return -1;
		}
		validateDestination(prompt);

		break;
	} // end switch, case: 1
	} // end switch

	return 0;

}
void FreeCell::convertTarget()
{
	if (fromReserved_)
		target_ = target_ / 10 - 1;
	else if (fromTableau_)
		target_-= 1;
}
void FreeCell::convertDestination()
{
	if (isToFoundation_)
		targetDestination_ = 0;
	else if (isToTableau_)
		targetDestination_ -= 1;
	else if (isToReserved_)
		targetDestination_ = targetDestination_/ 10 - 1;
}
bool FreeCell::isOver()
{
	// if the player resigned, the game is over
	if (resigned_)
		return true;

	// checks if one of the foundation cards aren't equal to the max rank
	for (int i = 0; i < numberOfFoundationPiles_; i++)
	{
		if (foundationPile_[i].getFace() != tableau_.getNumberOfCardsPerSuit())
			return false;
	}
	// if the above for doesn't return false, then all reserved cells have the max values. gameWon
	gameWon_ = true;
	return true;
}
void FreeCell::print()

{
	
	// display reserved cells
	for (int g = 0; g < numberOfReservedCells_; g++)
	{
		cout << 10 * (g + 1) << ":";
		if (reservedCells_[g].isActive())
		{
			cout << setw(RCELL_WIDTH) << reservedCells_[g].cardToString();
		}
		else
			cout << setw(RCELL_WIDTH) << "__";
		cout << " ";
	}

	cout << "   ";

	// display foundation stacks
	cout << FOUNDATION_INPUT_IDENTITY << ":";
	for (int g = 0; g < numberOfFoundationPiles_; g++)
	{
		if (foundationPile_[g].isActive())
		{
			cout << left << setw(RCELL_WIDTH) << foundationPile_[g].cardToString();
		}
		else
			cout << left << setw(WIDTH) << "__";
		cout << " ";
	}
	cout << endl;

	tableau_.print();
	tableau_.drawTableau();
}
bool FreeCell::save(ofstream & file) const
{
	tableau_.save(file);
	for (int g = 0; g < numberOfReservedCells_; g++)
	{
		if (!reservedCells_[g].isActive())
		{
			file << "0" << endl;
		}
		else
		{
			file << reservedCells_[g].cardToString() << endl;
		}
	}
	for (int g = 0; g < numberOfFoundationPiles_; g++)
	{
		if (!foundationPile_[g].isActive())
		{
			file << "0" << endl;
		}
		else
		{
			file << foundationPile_[g].cardToString() << endl;
		}
	}
	return false;
}
void FreeCell::charge(ifstream & filein)
{
	tableau_.charge(filein);
	string str1;
	string str2;
	for (int j = 0;j < numberOfReservedCells_;j++)
	{
		reservedCells_[j].makeInactive();
		getline(filein, str1);
		Card b;
		if (str1 != "0")
		{
			int face;
			char c = str1[0];
			char s = str1[1];
			switch (c) {
			case 'A':
				face = 1;
				break;
			case '2':
				face = 2;
				break;
			case '3':
				face = 3;
				break;
			case '4':
				face = 4;
				break;
			case '5':
				face = 5;
				break;
			case '6':
				face = 6;
				break;
			case '7':
				face = 7;
				break;
			case '8':
				face = 8;
				break;
			case '9':
				face = 9;
				break;
			case 'T':
				face = 10;
				break;
			case 'J':
				face = 11;
				break;
			case 'Q':
				face = 12;
				break;
			case 'K':
				face = 13;
				break;
			}


			b.setValues(face, s);
			reservedCells_[j] = b;

		}
	}
	for (int j = 0;j < numberOfReservedCells_;j++)
	{
		foundationPile_[j].makeInactive();
		getline(filein, str2);
		Card d;
		if (str2 != "0")
		{
			int face;
			char c = str2[0];
			char s = str2[1];
			switch (c) {
			case 'A':
				face = 1;
				break;
			case '2':
				face = 2;
				break;
			case '3':
				face = 3;
				break;
			case '4':
				face = 4;
				break;
			case '5':
				face = 5;
				break;
			case '6':
				face = 6;
				break;
			case '7':
				face = 7;
				break;
			case '8':
				face = 8;
				break;
			case '9':
				face = 9;
				break;
			case 'T':
				face = 10;
				break;
			case 'J':
				face = 11;
				break;
			case 'Q':
				face = 12;
				break;
			case 'K':
				face = 13;
				break;
			}


			d.setValues(face, s);
			foundationPile_[j] = d;

		}
	}
}