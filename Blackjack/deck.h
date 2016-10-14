#ifndef DECK_H
#define DECK_H

#include "./card.h"
#include <string>

using namespace std;

class Deck
{
	private:
		Card cards[52];
		int num_cards;
	public:
		Deck();
		Deck(const Deck &);
		void operator=(const Deck &);
		void set_deck();
		void set_suit_diamonds();
		void set_suit_clubs();
		void set_suit_spades();
		void set_suit_hearts();
		string int_to_str(int);
		void set_num_cards(int x);
		Card* get_deck();
		Card take_one();
		int get_num_cards();
		void shuffle();	
};

#endif





