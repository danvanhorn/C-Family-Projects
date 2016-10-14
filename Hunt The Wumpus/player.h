
/*********************************************************************
** Program Filename: player.h
** Author: Dan Van Horn
** Date: 05/16/2016
** Description: Player class for the game "Hunt the Wumpus"
** Input: none
** Output: none
*********************************************************************/

#ifndef PLAYER_H
#define PLAYER_H

class Player
{
private:
	int arrows; 		// num of arrows the player has
	int i,j;			// keeps track of the player's position in the cave
	int x,y;
	bool gold;
	bool wump;
public:
	Player();
	//Player(int);
	~Player();
	void set_player_position(int, int);
	void set_player_start_position(int, int);
	void back_to_start();
	int get_row_pos();
	int get_col_pos();
	void set_arrows();
	int get_num_arrows();
	void decrement_arrow();
	void get_gold();
	void kill_wumpus();
	bool has_gold();
	bool wumpus_dead();
	bool has_won();
	bool at_escape_rope();
	bool is_on_side(int);
	
};

#endif