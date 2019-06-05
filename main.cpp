#include "Play.h"

#include <iostream>
#include <cassert>
#include <stdexcept>
#include <iomanip>
#include <time.h>
#include <cstdlib>
#include <sstream>
#include <string>
#include <cmath>
using namespace std;
unsigned char grid_color[3] = { 255,255,255 };
CImg<unsigned char> grid(1060, 800, 1, 3, 200);
CImgDisplay disp(grid, "freecell");

int main()
{
	unsigned char back_color[3] = { 0,160,0 };
	CImg<unsigned char> scene = grid;
	CImgDisplay menu(grid, "freecell");


	menu.move((CImgDisplay::screen_width() - menu.width()) / 1.2,
		(CImgDisplay::screen_height() - menu.height()) / 2.5);
	disp.move((CImgDisplay::screen_width() - disp.width()) / 1.2,
		(CImgDisplay::screen_height() - disp.height()) / 2.5);
	//Draw playing grid**********************************************
	scene.draw_fill(0, 0, back_color);

	scene.draw_line(430, 350, 630, 350, grid_color);
	scene.draw_line(430, 400, 630, 400, grid_color);
	scene.draw_line(430, 450, 630, 450, grid_color);
	scene.draw_line(430, 500, 630, 500, grid_color);
	scene.draw_line(430, 550, 630, 550, grid_color);
	scene.draw_line(430, 600, 630, 600, grid_color);

	scene.draw_line(430, 350, 430, 400, grid_color);
	scene.draw_line(630, 350, 630, 400, grid_color);
	scene.draw_line(430, 450, 430, 500, grid_color);
	scene.draw_line(630, 450, 630, 500, grid_color);
	scene.draw_line(430, 550, 430, 600, grid_color);
	scene.draw_line(630, 550, 630, 600, grid_color);

	unsigned char color[] = { 0,0,0 };
	scene.draw_text(410, 220, ">>WELCOME TO FREECELL<<", color, 0, 1, 20);
	scene.draw_text(477, 366, "New Game", color, 0, 1, 20);
	scene.draw_text(460, 466, "Continue Playing", color, 0, 1, 20);
	scene.draw_text(477, 566, "Exit Game", color, 0, 1, 20);
	CImg<unsigned char> img1("kingleft.bmp");
	scene.draw_image(513, 270, img1);

	//**********************************************************
	menu._button = 0;
	while (!menu.is_closed() && !menu.is_keyESC() && !menu.is_keyQ()) {
		scene.display(menu);
		//system("pause");
		if (menu.button() & 1) { // Left button clicked.

			if ((menu.mouse_x() > 430)&(menu.mouse_x() < 630)&(menu.mouse_y() > 350)&(menu.mouse_y() < 400))
			{
				menu.close();
				Play a(true, 0);
				a.letsgo();
			}
			else if ((menu.mouse_x() > 430)&(menu.mouse_x() < 630)&(menu.mouse_y() > 550)&(menu.mouse_y() < 600))
			{
				menu.close();
				return 1;
			}
			else if ((menu.mouse_x() > 430)&(menu.mouse_x() < 630)&(menu.mouse_y() > 450)&(menu.mouse_y() < 500))
			{
				menu.close();
				Play a(true, 1);
				a.letsgo();
			}
		}
		menu.wait();
		if (menu.is_resized()) menu.resize();
	}
	int goon = 1;
	while (goon)
	{
		int replay;
		CImg<unsigned char> grid2(320, 250, 1, 3, 200);
		CImgDisplay menu2(grid2, "freecell");
		menu2.move((CImgDisplay::screen_width() - menu2.width()) / 1.6,
			(CImgDisplay::screen_height() - menu2.height()) / 1.8);
		CImg<unsigned char> scene2 = grid2;
		scene2.draw_fill(0, 0, back_color);

		scene2.draw_line(100, 100, 210, 100, grid_color);
		scene2.draw_line(100, 130, 210, 130, grid_color);
		scene2.draw_line(100, 160, 210, 160, grid_color);
		scene2.draw_line(100, 190, 210, 190, grid_color);

		unsigned char color[] = { 0,0,0 };
		scene2.draw_text(80, 50, ">> Do You Want ? <<", color, 0, 1, 20);
		scene2.draw_text(100, 110, "Start a New Game", color, 0, 1, 15);
		scene2.draw_text(110, 170, "Save and Exit", color, 0, 1, 15);
		menu2._button = 0;
		while (!menu2.is_closed() && !menu2.is_keyESC() && !menu2.is_keyQ()) {
			scene2.display(menu2);

			if (menu2.button() & 1) { // Right button clicked.

				if ((menu2.mouse_x() > 100)&(menu2.mouse_x() < 210)&(menu2.mouse_y() > 100)&(menu2.mouse_y() < 130))
				{
					replay = 1;
					menu2.close();
					break;
				}
				else if ((menu2.mouse_x() > 100)&(menu2.mouse_x() < 210)&(menu2.mouse_y() > 160)&(menu2.mouse_y() < 190))
				{
					replay = 0;
					menu2.close();
					break;
				}
			}
			menu2.wait();
			if (menu2.is_resized()) menu.resize();
		}

		//cin >> replay;
		if (replay)
		{
			Play a(true,0);
			a.letsgo();
		}
		else goon = 0;
	}
	return 1;
}

