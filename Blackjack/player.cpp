#include "./hand.h"
#include "./player.h"
#include "./hand.h"
#include <iostream>

using namespace std;

//player constructing

Player::Player()
{
	playing_total=1000;
	card_total=0;
	bet=0;
}

//player copy constructor

Player::Player(const Player &other)
{
	p_hand = other.p_hand;
	playing_total = other.playing_total;
	card_total = other.card_total;
	bet = other.bet;
}

//player assignment operator overload

void Player::operator=(const Player &other)
{
	p_hand = other.p_hand;
	playing_total = other.playing_total;
	card_total = other.card_total;
	bet = other.bet;
}

/*********************************************************************
** Function: set_playing_total
** Description: sets the the players "bank"
** Parameters: double
** Pre-Conditions: none
** Post-Conditions: none
*********************************************************************/ 

void Player::set_playing_total(double funds)
{
	playing_total = funds;
}

/*********************************************************************
** Function: decrement_playing_total
** Description: subtracts an amount from the playing_total
** Parameters: double
** Pre-Conditions: none
** Post-Conditions: none
*********************************************************************/ 

void Player::decrement_playing_total(double amt_lost)
{
	playing_total -= amt_lost;
}

/*********************************************************************
** Function: increment_plainy_total
** Description: adds an amount to the playing total
** Parameters: double
** Pre-Conditions: none
** Post-Conditions: none
*********************************************************************/ 

void Player::increment_playing_total(double amt_won)
{
	playing_total += amt_won;
}

/*********************************************************************
** Function: set_bet
** Description: sets the player's bet amount and subracts it from the playing total
** Parameters: double
** Pre-Conditions: none
** Post-Conditions: none
*********************************************************************/ 

void Player::set_bet(double wager)
{
	while(wager > playing_total)
	{
		cout << "Please enter an amount that is less than $" << playing_total << endl;
		cin >> wager;
	}
	bet = wager;
	decrement_playing_total(wager);
}

/*********************************************************************
** Function: get_p_hand
** Description: returns the address of a hand
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
*********************************************************************/ 

Hand& Player::get_p_hand() 
{
	return p_hand;
}

/*********************************************************************
** Function: get_playing_total
** Description: return the playing_total (bank)
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
*********************************************************************/ 

double Player::get_playing_total() const
{
	return playing_total;
}

/*********************************************************************
** Function: get_bet
** Description: returns the bet amount
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
*********************************************************************/ 

double Player::get_bet() const
{
	return bet;
}

/*********************************************************************
** Function: sum_p_hand
** Description: returns the sum of the players hand
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
*********************************************************************/ 

int Player::sum_p_hand() 
{
	int sum_of_hand=0;
	for (int i = 0; i < p_hand.get_cards_in_hand(); ++i)
	{
		sum_of_hand += p_hand.get_card_from_hand(i)->get_value();
	}
	return sum_of_hand;
}
