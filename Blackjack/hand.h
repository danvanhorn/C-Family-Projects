#ifndef HAND_H
#define HAND_H

#include "./card.h"

class Hand 
{
	private:
		Card *cards;
 		int cards_in_hand;
	public:
		Hand();
		Hand(const Hand &);
		~Hand();
		void operator =(const Hand &);
		void set_card(Card);
		void set_cards_in_hand(const int);
		int get_cards_in_hand() const;
		//Card* get_card_pointer();
		Card* get_card_from_hand(int);
		void discard_hand();
};

#endif

