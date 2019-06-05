#include "Randomize.h"


void Randomize::setDefaults_()
{
	char suitChar = 'x';
	// loop through each of the suits
	for (int suit = 0; suit < nSuits_; suit++)
	{
		switch (suit) {
		case 0:
			suitChar = 'H';
			break;
		case 1:
			suitChar = 'S';
			break;
		case 2:
			suitChar = 'D';
			break;
		case 3:
			suitChar = 'C';
			break;
		}
		// loop through all the card ranks
		for (int cardRank = ACE; cardRank <= cardsPSuit_; cardRank++)
		{
			cardsToShuffle_[suit][cardRank - 1].setValues(cardRank, suitChar);
		}
	}
}

void Randomize::shuffleDefaults_()
{
	Card temp;
	// randomize the cards in each suit
	for (int suit = 0; suit < nSuits_; suit++)
	{
		// loop through all but the last card
		for (int i = 0; i < cardsPSuit_- 1; i++)
		{
			// random int on [i,CARDS_PER_SUIT)
			int indexToSwithWith = (int)rand() % (cardsPSuit_ - i) + i;

			// swap cards at i and indexToSwitch for current suit
			temp = cardsToShuffle_[suit][i];
			cardsToShuffle_[suit][i] = cardsToShuffle_[suit][indexToSwithWith];
			cardsToShuffle_[suit][indexToSwithWith] = temp;
		}
	}
	// randomize the suits
	for (int i = 0; i < cardsPSuit_; i++)
	{
		// loop through all but the last card
		for (int suit = 0; suit < nSuits_ - 1; suit++)
		{
			// random int on [suit,nSuits)
			int suitIndexToSwitchWith = (int)rand() % (nSuits_- suit) + suit;

			// swap cards at suitIndexToSwitchW and i for current rank index
			temp = cardsToShuffle_[suit][i];
			cardsToShuffle_[suit][i] = cardsToShuffle_[suitIndexToSwitchWith][i];
			cardsToShuffle_[suitIndexToSwitchWith][i] = temp;
		}
	}

	return;
}

void Randomize::storeShuffledCards_(Tableau &d)
{
	int rowForShuffledCards = 0, colForShuffledCards = 0;
	int rowForTableau = 0, colForTableau = 0;

	int cardsLeft = d.getNumberOfCardsPerSuit() * d.getNumberOfSuits();
	while (cardsLeft > 0)
	{
		d.placeCardAt(rowForTableau, colForTableau, cardsToShuffle_[rowForShuffledCards][colForShuffledCards]);

		colForTableau += 1;
		if ((colForTableau) % d.getNumberOfCascades() == 0 && colForTableau != 0)
		{
			rowForTableau += 1;
			colForTableau = 0;
		}

		colForShuffledCards += 1;
		if ((colForShuffledCards) % (cardsPSuit_) == 0 && colForShuffledCards != 0)
		{
			colForShuffledCards = 0;
			rowForShuffledCards += 1;
		}

		cardsLeft--;
	}
}

Randomize::Randomize(Tableau & d)
{
	nSuits_= d.getNumberOfSuits();
	cardsPSuit_= d.getNumberOfCardsPerSuit();

	setDefaults_();
	shuffleDefaults_();
	shuffleDefaults_();
	storeShuffledCards_(d);
}
