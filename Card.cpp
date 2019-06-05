#include"card.h"

Card::Card()
{
	exists_ = false;
	face_ = 123;
	suit_ = '.';
}
int Card::getFace() const
{
	return face_;
}
char Card::getSuit() const
{
	return suit_;
}
string Card::getColor() const
{
	if (suit_ == 'S' || suit_ == 'C')
		return "BLACK";
	else if (suit_ == 'H' || suit_ == 'D')
		return "RED";


	throw runtime_error("ERROR: Card::getColor has invalid member value set on 'suit'");
	return "";
}
CImg<unsigned char> const Card::getImg()
{
	CImg<unsigned char> img;
	switch (face_)
	{
	case 1:
		switch (suit_)
		{
		case 'H':
			img.load("h01.ppm");
			break;
		case'D':
			img.load("d01.ppm");
			break;
		case'S':
			img.load("s01.ppm");
			break;
		case'C': 
			img.load("c01.ppm");
			break;
		}
		break;
	case 2:
		switch (suit_)
		{
		case 'H':
			img.load("h02.ppm");
			break;
		case'D':
			img.load("d02.ppm");
			break;
		case'S':
			img.load("s02.ppm");
			break;
		case'C':
			img.load("c02.ppm");
			break;
		}
		break;
	case 3:
		switch (suit_)
		{
		case 'H':
			img.load("h03.ppm");
			break;
		case'D':
			img.load("d03.ppm");
			break;
		case'S':
			img.load("s03.ppm");
			break;
		case'C':
			img.load("c03.ppm");
			break;
		}
		break;
	case 4:
		switch (suit_)
		{
		case 'H':
			img.load("h04.ppm");
			break;
		case'D':
			img.load("d04.ppm");
			break;
		case'S':
			img.load("s04.ppm");
			break;
		case'C':
			img.load("c04.ppm");
			break;
		}
		break;
	case 5:
		switch (suit_)
		{
		case 'H':
			img.load("h05.ppm");
			break;
		case'D':
			img.load("d05.ppm");
			break;
		case'S':
			img.load("s05.ppm");
			break;
		case'C':
			img.load("c05.ppm");
			break;
		}
			break;
	case 6:
		switch (suit_)
	    {
		case 'H':
			img.load("h06.ppm");
			break;
		case'D':
			img.load("d06.ppm");
			break;
		case'S':
			img.load("s06.ppm");
			break;
		case'C':
			img.load("c06.ppm");
			break;
		}
			break;
      case 7:
		switch (suit_)
		{
		case 'H':
			img.load("h07.ppm");
			break;
		case'D':
			img.load("d07.ppm");
			break;
		case'S':
			img.load("s07.ppm");
			break;
		case'C':
			img.load("c07.ppm");
			break;
		}
		break;
	  case 8:
		  switch (suit_)
		  {
		  case 'H':
			  img.load("h08.ppm");
			  break;
		  case'D':
			  img.load("d08.ppm");
			  break;
		  case'S':
			  img.load("s08.ppm");
			  break;
		  case'C':
			  img.load("c08.ppm");
			  break;
		  }
		  break;
	  case 9:
		  switch (suit_)
		  {
		  case 'H':
			  img.load("h09.ppm");
			  break;
		  case'D':
			  img.load("d09.ppm");
			  break;
		  case'S':
			  img.load("s09.ppm");
			  break;
		  case'C':
			  img.load("c09.ppm");
			  break;
		  }
		  break;
	  case 10:
		  switch (suit_)
		  {
		  case 'H':
			  img.load("h10.ppm");
			  break;
		  case'D':
			  img.load("d10.ppm");
			  break;
		  case'S':
			  img.load("s10.ppm");
			  break;
		  case'C':
			  img.load("c10.ppm");
			  break;
		  }
		  break;
	  case 11:
		  switch (suit_)
		  {
		  case 'H':
			  img.load("h11.ppm");
			  break;
		  case'D':
			  img.load("d11.ppm");
			  break;
		  case'S':
			  img.load("s11.ppm");
			  break;
		  case'C':
			  img.load("c11.ppm");
			  break;
		  }
		  break;
	  case 12:
		  switch (suit_)
		  {
		  case 'H':
			  img.load("h12.ppm");
			  break;
		  case'D':
			  img.load("d12.ppm");
			  break;
		  case'S':
			  img.load("s12.ppm");
			  break;
		  case'C':
			  img.load("c12.ppm");
			  break;
		  }
		  break;
	  case 13:
		  switch (suit_)
		  {
		  case 'H':
			  img.load("h13.ppm");
			  break;
		  case'D':
			  img.load("d13.ppm");
			  break;
		  case'S':
			  img.load("s13.ppm");
			  break;
		  case'C':
			  img.load("c13.ppm");
			  break;
		  }
		  break;	

	}
return img;
}

void Card::print() const
{
	cout << face_ << suit_;
}
void Card::setValues(int face, char suit)
{
	// this cannot take over an existing card.
	assert(!exists_);

	exists_= true;
	face_= face;
	suit_ = suit;
}
void Card::makeInactive()
{
	exists_= false;
}
string Card::cardToString() const
{
	assert(isActive());

	string name = "";

	// card name begins with rank.
	switch (face_)
	{
	case 1:
		name = "A";
		break;
	case 10:
		name = "T";
		break;
	case 11:
		name = "J";
		break;
	case 12:
		name = "Q";
		break;
	case 13:
		name = "K";
		break;
	default:
	{
		// i couldn't find a better way to do this. The itoa() didn't work and C++ doesn't have .toString() as java
		ostringstream someObj;

		// sorta works like cout...
		someObj << face_;
		name = someObj.str();
	}
	}
	name += suit_;

	return name;

}
bool Card::isActive() const
{
	return exists_;
}

/* _CARD_H */

