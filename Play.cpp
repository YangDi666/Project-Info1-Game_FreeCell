#include "Play.h"

Play::Play(bool start,int a=0)
{
	start_ = start;
	a_ = a;
}

void Play::letsgo()
{
	if (start_)
	{
		
		srand((unsigned int)time(NULL));

		FreeCell game(8, 4, 13, 4);
	
		if (a_ ==1)
		{
			ifstream filein("game.txt");
			game.charge(filein);
		}
	
		game.print();
		game.drawReserce();
		game.drawFoundation();


		disp.move((CImgDisplay::screen_width() - disp.width()) / 1.2,
			(CImgDisplay::screen_height() - disp.height()) / 2.5);
		while (!game.isOver())
		{
			grid.display(disp);	
			cout << endl;
				// display promt and receive location of target card
				game.displayPromptAndReceiveInput(0);


				if (!game.playerResigned())
				{
					// prompt, receive destination for the card
					int cancel = game.displayPromptAndReceiveInput(1);
					if (cancel != 0)
					{
						continue;
					}
					// check for valid move. if it is move target card to desintaion
					game.moveCard();

					// place a Bunch of spaces. hope this helps with readibility
					cout << endl << endl << endl << endl << endl << endl << endl;

					//display the reserved cells, foundation cells, tableau cards, and cards remaining
					game.print();
					game.drawReserce();
					game.drawFoundation();

				}
		} // end while
		game.printEnding();

		ofstream file("game.txt");
		game.save(file);

	}
}
	