#ifndef GAME_H
#define GAME_H

#include "./deck.h"
#include "./player.h"
#include "./dealer.h"

class Game
{
	private:
		Deck cards;
		Player *players;
		Dealer game_dealer;
		int num_players;
	public:
		Game();
		Game(int);
		Game(const Game &);
		~Game();
		void operator=(const Game &);
		void set_num_players();
		void mk_player_array();
		void remove_player();
		void fill_temp(Player, Player*);
		Player get_player();
		Player get_player(int);
		Dealer get_dealer();
		Deck get_deck();
		void play_game();
		void reset_deck();
		bool has_no_cheddar();
		void resolve_winnings();
		void clear_bets();
		void set_players_playing_total();
		void set_players_bet();
		void deal_cards();
		void discard_hands();
		void discard_dealer_hand();
		void player_turn();
		void dealer_turn();
		void hit_or_stay(int);
		bool has_aces(int);
		bool has_aces();
		void set_ace_value(int);
		void set_ace_value();
		void blackjack(int, double);
		void bust(int, double);
		void player_hit(int);
		void dealer_hit();
		void show_player_hand(int);
		void show_dealer_hand();
		void show_init_dealer_hand();
};

#endif