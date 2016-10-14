#include "./card.h"

//card constructor

Card::Card()
{
	value = 0;
}

//card copy constructor

Card::Card(const Card &other)
{
	value = other.value;
	face_val = other.face_val;
	suit = other.suit;
}



Card::~Card()
{

}

//card assignment operator overload

void Card::operator=(const Card &other)
{
	value = other.value;
	face_val = other.face_val;
	suit = other.suit;	
}

/*********************************************************************
** Function: set_value
** Description: sets the cards int value
** Parameters: int
** Pre-Conditions: none
** Post-Conditions: none
*********************************************************************/ 

void Card::set_value(const int x)
{
	value = x;
}

/*********************************************************************
** Function: set_face_val
** Description: sets the face value of each card
**				(the part of the card which is displayed to the user)
** Parameters: string
** Pre-Conditions: none
** Post-Conditions: none
*********************************************************************/ 

void Card::set_face_val(string c)
{
	face_val = c;
}

/*********************************************************************
** Function: set_suit
** Description: sets the suit
** Parameters: string
** Pre-Conditions: none
** Post-Conditions: none
*********************************************************************/ 

void Card::set_suit(string c)
{
	suit = c;
}

/*********************************************************************
** Function: get_value
** Description: returns the int value of the card
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
*********************************************************************/ 

int Card::get_value()
{
	return value;
}

/*********************************************************************
** Function: get_face_val
** Description: returns the cards string value
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
*********************************************************************/ 

string Card::get_face_val()
{
	return face_val;
}

/*********************************************************************
** Function: get_suit
** Description: return the string suit
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
*********************************************************************/ 

string Card::get_suit()
{
	return suit;
}