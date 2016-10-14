#include <cstdlib>
#include <iostream>
#include <time.h>
#include <string>
#include <sstream>
#include "./deck.h"
#include "./card.h"


using namespace std;

//deck constructor

Deck::Deck()
{
	Card cards[52];
	set_deck();
	shuffle();
	num_cards = 52;
}

//deck copy constructor

Deck::Deck(const Deck &other)
{
	for(int i=0; i<other.num_cards; i++)
	{
		cards[i] = other.cards[i];
	}
	num_cards = other.num_cards;
}

//deck assignment operator overload

void Deck::operator=(const Deck &other)
{
	for(int i=0; i<other.num_cards; i++)
	{
		cards[i] = other.cards[i];
	}
	num_cards = other.num_cards;
}

/*********************************************************************
** Function: set deck
** Description: sets up the deck of cards
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
*********************************************************************/ 

void Deck::set_deck(){
	set_suit_diamonds();
	set_suit_clubs();
	set_suit_spades();
	set_suit_hearts();

}


/*********************************************************************
** Function: set_suit_hearts
** Description: sets the hearts suit 
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
*********************************************************************/ 

void Deck::set_suit_hearts()
{
	for (int i = 39; i < 52; ++i)
	{
		if (i==39)
		{
			cards[i].set_value(1);
			cards[i].set_face_val("A");
			cards[i].set_suit("Hearts");
		}else if (i==48)
		{
			cards[i].set_value(10);
			cards[i].set_face_val("10");
			cards[i].set_suit("Hearts");
		}else if (i==49)
		{
			cards[i].set_value(10);
			cards[i].set_face_val("J");
			cards[i].set_suit("Hearts");
		}else if (i==50)
		{
			cards[i].set_value(10);
			cards[i].set_face_val("Q");
			cards[i].set_suit("Hearts");
		}else if (i==51)
		{
			cards[i].set_value(10);
			cards[i].set_face_val("K");
			cards[i].set_suit("Hearts");
		}
		else
		{
			string x = int_to_str(i-38);
			cards[i].set_value(i-38);
			cards[i].set_face_val(x);
			cards[i].set_suit("Hearts");
		}
	}
}


/*********************************************************************
** Function: set_suit_spades
** Description: sets the spades suit
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
*********************************************************************/ 

void Deck::set_suit_spades()
{
	for (int i = 26; i < 39; ++i)
	{
		if (i==26)
		{
			cards[i].set_value(1);
			cards[i].set_face_val("A");
			cards[i].set_suit("Spades");
		}else if (i==35)
		{
			cards[i].set_value(10);
			cards[i].set_face_val("10");
			cards[i].set_suit("Spades");
		}else if (i==36)
		{
			cards[i].set_value(10);
			cards[i].set_face_val("J");
			cards[i].set_suit("Spades");
		}else if (i==37)
		{
			cards[i].set_value(10);
			cards[i].set_face_val("Q");
			cards[i].set_suit("Spades");
		}else if (i==38)
		{
			cards[i].set_value(10);
			cards[i].set_face_val("K");
			cards[i].set_suit("Spades");
		}
		else
		{
			string x = int_to_str(i-25);
			cards[i].set_value(i-25);
			cards[i].set_face_val(x);
			cards[i].set_suit("Spades");
		}
	}
}


/*********************************************************************
** Function: set_suit_clubs
** Description: sets the clubs suit
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
*********************************************************************/ 

void Deck::set_suit_clubs()
{
	for (int i = 13; i < 26; ++i)
	{
		if (i==13)
		{
			cards[i].set_value(1);
			cards[i].set_face_val("A");
			cards[i].set_suit("Clubs");
		}else if (i==22)
		{
			cards[i].set_value(10);
			cards[i].set_face_val("10");
			cards[i].set_suit("Clubs");
		}else if (i==23)
		{
			cards[i].set_value(10);
			cards[i].set_face_val("J");
			cards[i].set_suit("Clubs");
		}else if (i==24)
		{
			cards[i].set_value(10);
			cards[i].set_face_val("Q");
			cards[i].set_suit("Clubs");
		}else if (i==25)
		{
			cards[i].set_value(10);
			cards[i].set_face_val("K");
			cards[i].set_suit("Clubs");
		}
		else
		{
			string x = int_to_str(i-12);
			cards[i].set_value(i-12);
			cards[i].set_face_val(x);
			cards[i].set_suit("Clubs");
		}
	}
}


/*********************************************************************
** Function: set_suit_diamonds
** Description: sets the diamonds suit
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
*********************************************************************/ 

void Deck::set_suit_diamonds()
{
	for (int i = 0; i < 13; ++i)
	{
		if (i==0)
		{
			cards[i].set_value(i+1);
			cards[i].set_face_val("A");
			cards[i].set_suit("Diamonds");
		}else if (i==9)
		{
			cards[i].set_value(10);
			cards[i].set_face_val("10");
			cards[i].set_suit("Diamonds");
		}else if (i==10)
		{
			cards[i].set_value(10);
			cards[i].set_face_val("J");
			cards[i].set_suit("Diamonds");
		}else if (i==11)
		{
			cards[i].set_value(10);
			cards[i].set_face_val("Q");
			cards[i].set_suit("Diamonds");
		}else if (i==12)
		{
			cards[i].set_value(10);
			cards[i].set_face_val("K");
			cards[i].set_suit("Diamonds");
		}
		else
		{
			string x = int_to_str(i+1);
			cards[i].set_value(i+1);
			cards[i].set_face_val(x);
			cards[i].set_suit("Diamonds");
		}
	}
}

/*********************************************************************
** Function: int_to_str
** Description: takes an integer and returns a string version of that int
** Parameters: int
** Pre-Conditions: none
** Post-Conditions: none
*********************************************************************/ 

string Deck::int_to_str(int x)
{
	stringstream ss;
	ss << x;
	string str = ss.str();
	return str;
}



/*********************************************************************
** Function: set_num_cards
** Description: sets the number of cards in the deck
** Parameters: int
** Pre-Conditions: none
** Post-Conditions: none
*********************************************************************/ 

void Deck::set_num_cards(int x)
{
	num_cards = x;
}

/*********************************************************************
** Function: get_deck
** Description: returns cards
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
*********************************************************************/ 

Card* Deck::get_deck()
{
	return cards;
}

/*********************************************************************
** Function: get_num_cards
** Description: returns the number of cards in the deck
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
*********************************************************************/ 

int Deck::get_num_cards()
{
	return num_cards;
}

/*********************************************************************
** Function: take_one
** Description: returns a cards from the "top" of the deck, decrements num_cards
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
*********************************************************************/ 

Card Deck::take_one()
{
	Card c = cards[num_cards-1];
	num_cards--;
	return c;
}

/*********************************************************************
** Function: shuffle
** Description: shuffles the deck by switching each card in the deck with a 
**				random card 50 times
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
*********************************************************************/ 

void Deck::shuffle()
{
	Card temp;
	int z;
	srand (time(NULL));
	for (int i = 0; i < 50; ++i)
	{
		for(int i=0; i<num_cards; i++)
		{
			z = rand()%(num_cards-1);
			temp = cards[i];
			cards[i] = cards[z];
			cards[z] = temp;
		}
	}
}