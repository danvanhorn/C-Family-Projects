#ifndef PLAYER_H
#define PLAYER_H

#include "./hand.h"

using namespace std;

class Player
{
	private:
		Hand p_hand;
		double playing_total;
		int card_total;
		double bet;
	public:
		Player();
		Player(const int, const Card, const Card);
		Player(const Player &);
		void operator=(const Player &);
		void set_playing_total(double);//set playing total
		void decrement_playing_total(double);
		void increment_playing_total(double);
		void set_bet(double);	
		Hand& get_p_hand();		
		double get_playing_total() const;	//get playing total
		double get_bet() const;				//get bet
		int sum_p_hand();			//returns the sum of the values of the cards in the hand
		//get card_total function that returns the sum of the cards in hand
		
};

#endif

