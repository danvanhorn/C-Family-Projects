#include "./dealer.h"
#include <iostream>

using namespace std;

/*********************************************************************
** Function: sum_d_hand
** Description: returns the sum of the dealer's hand
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
*********************************************************************/ 

int Dealer::sum_d_hand(){
	int sum_of_hand = 0;
	for (int i = 0; i < d_hand.get_cards_in_hand(); ++i)
	{
		sum_of_hand += d_hand.get_card_from_hand(i)->get_value();
	}
	return sum_of_hand;
}

/*********************************************************************
** Function: hit_or_stay
** Description: bool to control whether the dealer hits or stay
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
*********************************************************************/ 

bool Dealer::hit_or_stay(){
	//cout << "in dealer hit or stay" << endl;
	if (sum_d_hand()>=17)
	{
		return false;
	}
	return true;
}

/*********************************************************************
** Function: get_d_hand
** Description: returns the address of the dealer's hand
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
*********************************************************************/

Hand& Dealer::get_d_hand() 
{
	return d_hand;
}


