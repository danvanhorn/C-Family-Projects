#include <iostream>
#include <cstdlib>
#include "./game.h"

using namespace std;

//Game default Constructor

Game::Game() : num_players(1)
{
	players = new Player[1];
}

//Game non-default Constructor

Game::Game(int p)
{
	num_players = p;
	players = new Player [num_players];	
}

//Game Copy Constructor

Game::Game(const Game &other)
{
	num_players = other.num_players;
	players = new Player[other.num_players];
	for (int i = 0; i < other.num_players; ++i)
	{
		players[i]=other.players[i];
	}
}

//Game destructor

Game::~Game()
{
	delete [] players;
}

//Game assignment operator overload

void Game::operator=(const Game &other)
{
	num_players = other.num_players;
	delete [] players;
	players = new Player[other.num_players];
	for (int i = 0; i < other.num_players; ++i)
	{
		players[i]=other.players[i];
	}
}

/*********************************************************************
** Function: set_num_players
** Description: sets the number of players for the game
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
*********************************************************************/ 

void Game::set_num_players()
{
	int num=0;
	do
	{
		cout << "How many players are there? ";
		cin >> num;
	}
	while(!(num > 0));
	num_players = num;
	mk_player_array();
}

/*********************************************************************
** Function: mk_player_array
** Description: creates a dynamic array the sixe of the number of players
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
*********************************************************************/ 

void Game::mk_player_array()
{
	players = new Player[num_players];
}

/*********************************************************************
** Function: remove_player
** Description: removes a player with a playing_total == 0
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
*********************************************************************/

void Game::remove_player()
{
	int size = 0;
	for (int i = 0; i < num_players; ++i)
	{
		if (!(players[i].get_playing_total() == 0))
		{
			size++;
		}
	}
	Player *temp = new Player[size];
	for (int i = 0; i < num_players; ++i)
	{
		if(!(players[i].get_playing_total() == 0))
		{
			fill_temp(players[i], temp);
		}
	}
	num_players = size;
	players = new Player[size];
	players = temp;

}

/*********************************************************************
** Function: fill_temp
** Description: a function for adding player objects to a temp array
** Parameters: Player, Player *
** Pre-Conditions: there must be a player with a playing_total == 0
** Post-Conditions: a new array is formed excluding the players with no more money
*********************************************************************/

void Game::fill_temp(Player toAdd, Player *temp)
{
	for (int i = 0; i < num_players-1; ++i)
	{
		if (!(temp[i].get_playing_total() == 0))
		{
			temp[i] = toAdd;
		}
	}
}

/*********************************************************************
** Function: play_game
** Description: the function through which the "game" is routed
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
*********************************************************************/ 

void Game::play_game()
{
	cards.shuffle();
	set_num_players();
	set_players_playing_total();
	while(num_players != 0)
	{
		set_players_bet();
		deal_cards();	
		player_turn();
		dealer_turn();
		resolve_winnings();
		clear_bets();
		discard_hands();
		discard_dealer_hand();
		if (has_no_cheddar())
			remove_player();
		if (num_players == 0)
			break;
		if (cards.get_num_cards() < 20)
			reset_deck();
	}
}

/*********************************************************************
** Function: reset_deck
** Description: resets and shuffles the game deck
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
*********************************************************************/ 

void Game::reset_deck()
{
	cout << endl;
	cout << "Shuffling a new deck..." << endl;
	cout << endl;
	cards.set_deck();
	cards.shuffle();
	cards.set_num_cards(52);
}

/*********************************************************************
** Function: has_no_cheddar
** Description: checks if there are players with playing_total==0
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
*********************************************************************/ 

bool Game::has_no_cheddar()
{
	for (int i = 0; i < num_players; ++i)
	{
		if(players[i].get_playing_total() == 0)
		{
			return true;
		}
	}
	return false;
}

/*********************************************************************
** Function: clear_bets
** Description: resets each players bet to 0
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
*********************************************************************/ 

void Game::clear_bets()
{
	for (int i = 0; i < num_players; ++i)
	{
		players[i].set_bet(0);
	}
}

/*********************************************************************
** Function: resolve_winnings
** Description: This function is responsible for giving money and taking money from each player's
**				playing_total after each round of blackjack is played.
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
*********************************************************************/ 

void Game::resolve_winnings()
{
	if(game_dealer.sum_d_hand() > 21)
	{
		for (int i = 0; i < num_players; ++i)
		{
			int winnings = players[i].get_bet();
			cout << "Player " << i+1 << " wins $" << players[i].get_bet() << endl;
			players[i].increment_playing_total(winnings * 2);
		}
	}
	else if (game_dealer.sum_d_hand() < 21)
	{
		for (int i = 0; i < num_players; ++i)
		{
			int winnings = players[i].get_bet();
			if(players[i].sum_p_hand() > game_dealer.sum_d_hand() && players[i].sum_p_hand() != 21)
			{
				cout << "Player " << i+1 << " wins $" << winnings * 2 << endl;
				players[i].increment_playing_total(winnings * 2);
			}
			else if (players[i].sum_p_hand() != 21)
			{
				cout << "Player " << i+1 << " loses $" << winnings << endl;
				cout << endl;
			}
			else if (players[i].sum_p_hand() == game_dealer.sum_d_hand())
			{
				cout << "Dealer push for Player " << i+1 << endl;
				players[i].increment_playing_total(winnings);
			}
		}
	}
}

/*********************************************************************
** Function: set_players_playing_total
** Description: Promts each player for their playing_total
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
*********************************************************************/ 

void Game::set_players_playing_total()
{
	for (int i = 0; i < num_players; ++i)
	{
		double input;
		do
		{
			cout << "Player " << i + 1 << " : How much money would you like to start with? ";
			cin >> input;
		}while(input < 0);
		players[i].set_playing_total(input);	
	}
}

/*********************************************************************
** Function: set_players_bet
** Description: prompts each player for a betting amount for the round
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
*********************************************************************/ 

void Game::set_players_bet()
{
	for (int i = 0; i < num_players; ++i)
	{
		double input;
		do
		{
			cout << "Player " << i + 1 << " : How much money would you like to bet? ";
			cin >> input;
		}while(input < 0);
		players[i].set_bet(input);	
	}	
}

/*********************************************************************
** Function: deal_cards
** Description:	the initial dealing of two cards to each player including the dealer
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
*********************************************************************/ 

void Game::deal_cards()
{
	Card c, d;
	for (int i = 0; i <= num_players; i++)
	{
		c = cards.take_one();
		d = cards.take_one();
		if(i == num_players)
		{
			game_dealer.get_d_hand().set_card(c);
			game_dealer.get_d_hand().set_card(d);			
		}else
		{
			players[i].get_p_hand().set_card(c);
			players[i].get_p_hand().set_card(d);
		}
	}
}

/*********************************************************************
** Function: discard_hands
** Description: removes each card from each players hand
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
*********************************************************************/ 


void Game::discard_hands()
{ 
	for (int i = 0; i < num_players; ++i)
	{
		players[i].get_p_hand().discard_hand();

	}
}

/*********************************************************************
** Function: discard_dealer_hand
** Description: removes each card in the dealer's hand
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
*********************************************************************/ 

void Game::discard_dealer_hand()
{
	//cout << "discarding the dealer's hand..." << endl;
	game_dealer.get_d_hand().discard_hand();
}

/*********************************************************************
** Function: player_turn
** Description: the function through which each player plays out their turn
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
*********************************************************************/ 

void Game::player_turn()
{
	show_init_dealer_hand();
	for (int i = 0; i < num_players; i++)
	{
		hit_or_stay(i);
	}
}

/*********************************************************************
** Function: dealer_turn
** Description: makes the dealer hit if they have less than 17 or stay if they have > 17
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
*********************************************************************/ 

void Game::dealer_turn()
{
	bool flag = true;
	set_ace_value();
	if (game_dealer.sum_d_hand()==21)
	{
		cout << "Dealer gets Blackjack..." << endl;
		show_dealer_hand();
		flag = false;
	}
	while(flag)
	{		
		while(game_dealer.sum_d_hand() < 21)
		{
			set_ace_value();
			show_dealer_hand();				
			if(game_dealer.sum_d_hand() < 17)
			{
				cout << "Dealer hits..." << endl;
				cout << endl;
				dealer_hit();
			}else
			{
				cout << "Dealer stays..." << endl;
				cout << endl;
				break;
			}
		}
		if (has_aces())
		{
			set_ace_value();
			show_dealer_hand();
			flag = false;
		}
		else if (game_dealer.sum_d_hand() == 21)
		{
			cout << "Dealer gets Blackjack..." << endl;
			cout << endl;
			show_dealer_hand();
			flag = false;
		}
		else if (game_dealer.sum_d_hand() > 21)
		{
			show_dealer_hand();
			cout << "Dealer busts...." << endl;
			cout << endl;
			flag = false;
		}
		break;
	}
}

/*********************************************************************
** Function: dealer_hit
** Description: adds one card to the dealers hand when hitting
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
*********************************************************************/

void Game::dealer_hit()
{
	Card draw = cards.take_one();
	game_dealer.get_d_hand().set_card(draw);
}

/*********************************************************************
** Function: hit_or_stay
** Description: promts the player to hit or stay
** Parameters: int
** Pre-Conditions: none
** Post-Conditions: none
*********************************************************************/

void Game::hit_or_stay(int x)
{

	int input=0;
	double wager = players[x].get_bet();
	bool flag = true;
	set_ace_value(x);
	if (players[x].sum_p_hand() == 21)
	{
		blackjack(x, wager);
		flag = false;
	}
	while(flag==true)
	{
		while(players[x].sum_p_hand() < 21)
		{
			set_ace_value(x);
			show_player_hand(x);
			do{
				cout << "Hit (1) or Stay (2): " << endl;
				cin >> input;
			}while(!(input == 1 || input == 2));
			if (input == 1)
			{
				player_hit(x);
			}
			else if (input == 2)
			{
				flag = false;
				break;
			}
		}
		if(has_aces(x))
		{
			set_ace_value(x);
			show_player_hand(x);
		}
		else if (players[x].sum_p_hand() == 21)
		{
			blackjack(x, wager);
			flag = false;
			break;
		}
		else if (players[x].sum_p_hand() > 21)
		{
			if (has_aces(x))
			{
				set_ace_value(x);
				show_player_hand(x);
			}else
				bust(x, wager);
				flag = false;
				break;
		}
		
	}
}

/*********************************************************************
** Function: set_ace_value
** Description: makes sure all of the aces in a players hand are the most adventageous value 1 or 11
** Parameters: int
** Pre-Conditions: none
** Post-Conditions: none
*********************************************************************/

void Game::set_ace_value(int x)
{
	if (has_aces(x))
	{
		for (int i = 0; i < players[x].get_p_hand().get_cards_in_hand(); ++i)
		{
			if(players[x].get_p_hand().get_card_from_hand(i)->get_value()==1)
			{
				if (players[x].sum_p_hand()-1 >= 11)
				{
					players[x].get_p_hand().get_card_from_hand(i)->set_value(1);
				}
				else if (players[x].sum_p_hand()-1 < 11)
				{
					players[x].get_p_hand().get_card_from_hand(i)->set_value(11);
				}
			}
			else if(players[x].get_p_hand().get_card_from_hand(i)->get_value()==11)
			{
				if (players[x].sum_p_hand()-10 < 21)
				{
					players[x].get_p_hand().get_card_from_hand(i)->set_value(1);
				}
			}
		}
	}
}

/*********************************************************************
** Function: set_ace_value
** Description: makes sure all of the aces in the dealer hand are the most adventageous value 1 or 11
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
*********************************************************************/

void Game::set_ace_value()
{
	if (has_aces())
	{
		for (int i = 0; i < game_dealer.get_d_hand().get_cards_in_hand(); ++i)
		{
			if(game_dealer.get_d_hand().get_card_from_hand(i)->get_value()==1)
			{
				if (game_dealer.sum_d_hand()-1 > 11)
				{
					game_dealer.get_d_hand().get_card_from_hand(i)->set_value(1);
				}
				else if (game_dealer.sum_d_hand()-1 < 11)
				{
					game_dealer.get_d_hand().get_card_from_hand(i)->set_value(11);
				}
			}
		}
	}
}

/*********************************************************************
** Function: has_aces
** Description: returns true if there is at least one ace in a players hand
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
*********************************************************************/

bool Game::has_aces(int x)
{
	for (int i = 0; i < players[x].get_p_hand().get_cards_in_hand(); ++i)
	{
		if (players[x].get_p_hand().get_card_from_hand(i)->get_value()==1)
		{
			return true;
		}else if (players[x].get_p_hand().get_card_from_hand(i)->get_value()==11)
		{
			return true;
		}
	}return false;
}

/*********************************************************************
** Function: has_aces
** Description: returns true if there is at least one ace in a dealers hand
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
*********************************************************************/

bool Game::has_aces()
{
	for (int i = 0; i < game_dealer.get_d_hand().get_cards_in_hand(); ++i)
	{
		if (game_dealer.get_d_hand().get_card_from_hand(i)->get_value()==1)
		{
			return true;
		}
	}return false;
}

/*********************************************************************
** Function: blackjack
** Description: when the player draws 21, prints a message and increments their playing_total
** Parameters: int, double
** Pre-Conditions: none
** Post-Conditions: none
*********************************************************************/

void Game::blackjack(int x, double wager)
{
	show_player_hand(x);
	cout << "_______Blackjack!________" << endl;
	cout << "You win $" << wager + (wager * 1.5) << endl;
	players[x].increment_playing_total(wager + (wager * 1.5));
}

/*********************************************************************
** Function: bust
** Description: when the player busts, prints a message and 
** Parameters: int, double
** Pre-Conditions: none
** Post-Conditions: none
*********************************************************************/

void Game::bust(int x, double wager)
{
	show_player_hand(x);
	cout << "Player " << x + 1 <<" busted..." << endl;
	cout << "They lose $" << wager << endl;
	cout << endl;
	players[x].set_bet(0);
}

/*********************************************************************
** Function: player_hit
** Description: adds a card to the players hand when they hit
** Parameters: int
** Pre-Conditions: none
** Post-Conditions: none
*********************************************************************/

void Game::player_hit(int x)
{
	Card draw = cards.take_one();
	players[x].get_p_hand().set_card(draw);
}

/*********************************************************************
** Function: show_player_hand
** Description: displays the players hand to the screen and total
** Parameters: int
** Pre-Conditions: none
** Post-Conditions: none
*********************************************************************/

void Game::show_player_hand(int j)
{
	int num = players[j].get_p_hand().get_cards_in_hand();
	cout << "Player " << j+1 << "'s hand:"<< endl;
	cout << "Total money: $" << players[j].get_playing_total() << " Current Bet: $" << players[j].get_bet() << endl;
	for (int i = 0; i <num ; ++i)
	{
		cout << players[j].get_p_hand().get_card_from_hand(i)->get_face_val() << " of ";
		cout << players[j].get_p_hand().get_card_from_hand(i)->get_suit() << endl;
	}
	cout << "Total: " << players[j].sum_p_hand() << endl;
	cout << endl;
}

/*********************************************************************
** Function: show_init_dealer_hand
** Description: displays the dealers hand to the screen with one card "face down"
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
*********************************************************************/

void Game::show_init_dealer_hand()
{
	cout << "Dealer's hand:" << endl;
	cout << game_dealer.get_d_hand().get_card_from_hand(0)->get_face_val() << " of ";
	cout << game_dealer.get_d_hand().get_card_from_hand(0)->get_suit() << endl;
	cout << "Face Down Card" << endl;
	cout << endl;
}

/*********************************************************************
** Function: show_dealer_hand
** Description: displays the dealers hand and total
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
*********************************************************************/

void Game::show_dealer_hand()
{
	cout << "Dealer's hand:" << endl;
	for (int i = 0; i < game_dealer.get_d_hand().get_cards_in_hand(); ++i)
	{
		cout << game_dealer.get_d_hand().get_card_from_hand(i)->get_face_val() << " of ";
		cout << game_dealer.get_d_hand().get_card_from_hand(i)->get_suit() << endl;
	}
	cout << "Total: " << game_dealer.sum_d_hand() << endl;
	cout << endl;
}

/*********************************************************************
** Function: get_player
** Description: for default game, returns the player
** Parameters:	none
** Pre-Conditions: none
** Post-Conditions: none
*********************************************************************/

Player Game::get_player()
{
	return players[0];
}

/*********************************************************************
** Function: get_player
** Description: for non-default game, returns the player at x
** Parameters: int 
** Pre-Conditions: none
** Post-Conditions: none
*********************************************************************/

Player Game::get_player(int x)
{
	return players[x];
}

/*********************************************************************
** Function: get_dealer
** Description: returns the game_dealer
** Parameters: none
** Pre-Conditions: none 
** Post-Conditions: none
*********************************************************************/

Dealer Game::get_dealer()
{
	return game_dealer;
}

/*********************************************************************
** Function: get_deck
** Description: returnd the deck of cards
** Parameters: none
** Pre-Conditions: none 
** Post-Conditions: none
*********************************************************************/

Deck Game::get_deck()
{
	return cards;
}