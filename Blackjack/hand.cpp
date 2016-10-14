#include <iostream>
#include "./hand.h"

using namespace std;

//hand constructor

Hand::Hand(){
	cards = NULL;
	cards_in_hand = 0;
}

//hand copy constructor

Hand::Hand(const Hand &other){
	cards = new Card[other.cards_in_hand];
	for (int i = 0; i < other.cards_in_hand; i++)
	{
		cards[i] = other.cards[i];
	}
	cards_in_hand = other.cards_in_hand;
}

//hand destructor

Hand::~Hand(){
	delete [] cards;
}

//hand assignment operator overload

void Hand::operator=(const Hand &other){
	delete [] cards;
	cards = new Card[other.cards_in_hand];
	for (int i = 0; i < other.cards_in_hand; i++)
	{
		cards[i] = other.cards[i];
	}
	cards_in_hand = other.cards_in_hand;
}

/*********************************************************************
** Function: set_card
** Description: adds a Card to the players hand
** Parameters: Card
** Pre-Conditions: none
** Post-Conditions: none
*********************************************************************/ 

void Hand::set_card(Card new_card)
{
	Card *temp;
	cards_in_hand++;
	temp = new Card [cards_in_hand];
	temp=cards;
	cards=new Card[cards_in_hand];
	for(int i=0; i<cards_in_hand-1; i++)
	{
		cards[i]=temp[i];
	}
	delete [] temp;
	cards[cards_in_hand-1]=new_card;
}           

/*********************************************************************
** Function: set_cards_in_hand
** Description: sets cards_in_hand
** Parameters: int
** Pre-Conditions: none
** Post-Conditions: none
*********************************************************************/ 

void Hand::set_cards_in_hand(int x)
{
	cards_in_hand = x;
}

/*********************************************************************
** Function: get_cards_in_hand
** Description: returns the number of cards in the hand
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
*********************************************************************/ 

int Hand::get_cards_in_hand() const
{
	return cards_in_hand;
}

/*********************************************************************
** Function: get_card_from_hand
** Description: returns an address of a card
** Parameters: const int
** Pre-Conditions: none
** Post-Conditions: none
*********************************************************************/

Card* Hand::get_card_from_hand(const int x)
{
	return &cards[x];
}

/*********************************************************************
** Function: discard_hand
** Description: deletes the array that cards points to and sets the number of cards in hand to 0
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
*********************************************************************/

void Hand::discard_hand()
{
	delete [] cards;
	cards = NULL;
	cards_in_hand = 0;
}


