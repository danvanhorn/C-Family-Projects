#ifndef DEALER_H
#define DEALER_H

#include "./hand.h"

class Dealer
{
	private:
		Hand d_hand;
		int card_total;
	public:
		int sum_d_hand();	//returns the sum of the cards in hand
		bool hit_or_stay();	//determines if the dealer will hit or stay
		Hand& get_d_hand();

};

#endif