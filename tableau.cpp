#include "tableau.h"
using namespace std;
using namespace cimg_library;



Tableau::Tableau(int numCasc, int numSuits, int crdsPSuit)
{
	numberOfCascades_ = numCasc;
	numberOfSuits_ = numSuits;
	cardsPerSuit_ = crdsPSuit;
	numberOfCards_=numberOfSuits_ * cardsPerSuit_;
	rowsNeededPlusExtra_= 20;
	cardsRemaining_= numberOfCards_;
}

void Tableau::moveTo(int)
{
}

void Tableau::placeCardAt(int row, int cascade, Card c)
{
	if (!cardsInCascades[row][cascade].isActive())
	{
		// append values, card will now exist at this point
		cardsInCascades[row][cascade] = c;
	}
}

Card Tableau::retrieveCardAt(int row, int cascade) const
{
	return cardsInCascades[row][cascade];
}

void Tableau::deactivate(int cascade)
{
	int r = findRowIndexContainingExistingCard(cascade);
	cardsInCascades[r][cascade].makeInactive();
}
int Tableau::findRowIndexContainingExistingCard(int cascade) const
{
	assert(cascade>= 0 && cascade < numberOfCascades_);

	for (int i = rowsNeededPlusExtra_; i >= 0; i--)
	{
		if (cardsInCascades[i][cascade].isActive())
			return i;
	}

	return -1;
}

int Tableau::getNumberOfSuits() const
{
     return numberOfSuits_;
}

int Tableau::getNumberOfCardsPerSuit() const
{
	return cardsPerSuit_;
}

int Tableau::getRowsNeeded() const
{
	return rowsNeeded_;
}

int Tableau::getNumberOfCascades() const
{
	return numberOfCascades_;
}

void Tableau::decreaseTotalCards()
{
	cardsRemaining_ -= 1;
}

void Tableau::print()
{
	cout << endl;

	// display the cascade indices (!! one based)
	for (int i = 0; i < numberOfCascades_; i++)
	{
		cout << setw(WIDTH) << i + 1;
		cout << " ";
	}
	cout << endl;
	for (int i = 0; i < numberOfCascades_; i++)
	{
		cout << setw(WIDTH) << "--";
		cout << " ";
	}
	cout << endl;

	// display the cascades
	for (int r = 0; r < rowsNeededPlusExtra_; r++)
	{
		bool somethingPrinted = false;

		// loop through a row and display its elements
		for (int cascade = 0; cascade < numberOfCascades_; cascade++)
		{
			if (cardsInCascades[r][cascade].isActive())
			{
				// print the card
				cout << setw(WIDTH) << cardsInCascades[r][cascade].cardToString();
				somethingPrinted = true;
			}
			else
				cout << setw(WIDTH) << " ";

			cout << " ";
		}
		cout << endl;

		// is this a good use of a break statement? prevents MANY blank lines
		if (!somethingPrinted)
			break;
	} // end outer for

	cout << "Cards Remaining: " << cardsRemaining_ << endl;

}
	
void Tableau::drawTableau()
	{
	unsigned char back_color[3] = { 0,160,0 };
	grid.assign(1060, 800, 1, 3, 200);
	grid.begin();
	grid.draw_fill(0, 0, back_color);
	CImg<unsigned char> img("kingleft.bmp");
	grid.draw_image(515, 80, img);

	char a[5];
	itoa(cardsRemaining_, a, 10);
	grid.draw_text(30, 700, "Cards Remaining : ", grid_color, 0, 1, 20);
	grid.draw_text(200, 700, a, grid_color, 0, 1, 20);

	grid.draw_line(430, 650, 430, 700, grid_color);
	grid.draw_line(630, 650, 630, 700, grid_color);
	grid.draw_line(430, 650, 630, 650, grid_color);
	grid.draw_line(430, 700, 630, 700, grid_color);
	unsigned char color[] = { 0,0,0 };
	grid.draw_text(477, 666, "Exit Game", color, 0, 1, 20);

	for (int i = 0; i <= 3; i++) grid.draw_line(30 + 120 * i, 30, 30 + 120 * i, 170, grid_color);
	for (int j = 0; j <= 3; j++) grid.draw_line(130 + 120 * j, 30, 130 + 120 * j, 170, grid_color);
	for (int i = 0; i <= 3; i++) grid.draw_line(30 + 120 * i, 30, 130 + 120 * i, 30, grid_color);
	for (int j = 0; j <= 3; j++) grid.draw_line(30 + 120 * j, 170, 130 + 120 * j, 170, grid_color);

	for (int i = 0; i <= 3; i++) grid.draw_line(570 + 120 * i, 30, 570 + 120 * i, 170, grid_color);
	for (int j = 0; j <= 3; j++) grid.draw_line(670 + 120 * j, 30, 670 + 120 * j, 170, grid_color);
	for (int i = 0; i <= 3; i++) grid.draw_line(570 + 120 * i, 30, 670 + 120 * i, 30, grid_color);
	for (int j = 0; j <= 3; j++) grid.draw_line(570 + 120 * j, 170, 670 + 120 * j, 170, grid_color);
	
			for (int r = 0; r < rowsNeededPlusExtra_; r++)
			{
				for (int cascade = 0; cascade < numberOfCascades_; cascade++)
				{
					if (cardsInCascades[r][cascade].isActive())
					{
						if (cascade <= 3)
						{
							grid.draw_image(40 + 120 * (cascade), 180 + 20 * (r), cardsInCascades[r][cascade].getImg());
						}
						else
						{
							grid.draw_image(580 + 120 * (cascade - 4), 180 + 20 * (r), cardsInCascades[r][cascade].getImg());
						}
					}
				}

			}
}
bool Tableau::save(ofstream & file) const
{

	for (int r = 0; r < rowsNeededPlusExtra_; r++)
	{

		for (int cascade = 0; cascade < numberOfCascades_; cascade++)
		{
			if (!cardsInCascades[r][cascade].isActive())
			{
				file << "0" << endl;
			}
			else
			{
				file << cardsInCascades[r][cascade].cardToString() << endl;
			}
		}
	}
	return false;
}


void Tableau::charge(ifstream & filein)
{
	
	string str;
	for (int i = 0;i < rowsNeededPlusExtra_;i++)
	{
		for (int j = 0;j < numberOfCascades_;j++)
		{
			cardsInCascades[i][j].makeInactive();
			getline(filein, str);
			Card a;
			if (str != "0")
			{
				int face;
				char c = str[0];
				char s = str[1];
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

				a.setValues(face, s);
				cardsInCascades[i][j] = a;
			}
		}
	}
}