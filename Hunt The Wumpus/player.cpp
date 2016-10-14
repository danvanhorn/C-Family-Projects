
/*********************************************************************
** Program Filename: player.cpp
** Author: Dan Van Horn
** Date: 05/16/2016
** Description: Player class implentation for the game "Hunt the Wumpus"
** Input: none
** Output: none
*********************************************************************/


#include <time.h>
#include <cstdlib>
#include "./player.h"

Player::Player()
{
	arrows = 3;
	i = 0;
	j = 0;
	x = 0;
	y = 0;
	gold = false;
	wump = false;
}


Player::~Player(){}

/*********************************************************************
** Function: set_player_position
** Description: sets the Player's position on a row x column grid
** Parameters: int, int
** Pre-Conditions: none
** Post-Conditions: none
*********************************************************************/ 

void Player::set_player_position(int i, int j)
{
	this->i = i;
	this->j = j;
}

/*********************************************************************
** Function: set_player_start_position
** Description: sets the Player to their starting position and the 
**				gold and wump booleans to false
** Parameters: int, int
** Pre-Conditions: none
** Post-Conditions: none
*********************************************************************/ 

void Player::set_player_start_position(int i, int j)
{
	this->i = i;
	this->j = j;
	x = i;
	y = j;
	gold = false;
	wump = false;
}

/*********************************************************************
** Function: back_to_start
** Description: returns the Player to their starting position and sets 
**				the wump and gold booleans back to false;
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
*********************************************************************/ 

void Player::back_to_start()
{
	i = x;
	j = y;
	gold = false;
	wump = false;
}

/*********************************************************************
** Function: get_num_arrows
** Description: returns the number of arrows the Player has
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
*********************************************************************/ 

int Player::get_num_arrows()
{
	return arrows;
}

/*********************************************************************
** Function: set_arrows
** Description: sets the number of arrows that the Player has to 3
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
*********************************************************************/ 

void Player::set_arrows()
{
	arrows = 3;
}

/*********************************************************************
** Function: decrement_arrow
** Description: When the user "shoots" an arrow, decrement the number 
**				of arrows by one
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
*********************************************************************/

void Player::decrement_arrow()
{
	if(arrows >= 1)
		arrows--;
}

/*********************************************************************
** Function: get_gold
** Description: sets the gold boolean to true if the player has gold
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
*********************************************************************/ 

void Player::get_gold()
{
	gold = true;
}

/*********************************************************************
** Function: kill_wumpus
** Description: sets the wump boolean to false
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
*********************************************************************/ 

void Player::kill_wumpus()
{
	wump = true;
}

/*********************************************************************
** Function: has_gold
** Description: returns true if the Player has collected the gold, 
**				otherwise return false.
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
*********************************************************************/ 

bool Player::has_gold()
{
	return gold;
}

/*********************************************************************
** Function: wumpus_dead
** Description: returns true if the Player has shot the Wumpus else, 
**				otherwise return false;
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
*********************************************************************/ 

bool Player::wumpus_dead()
{
	return wump;
}

/*********************************************************************
** Function: get_row_pos
** Description: returns the Player's row position in the cave
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
*********************************************************************/ 

int Player::get_row_pos()
{
	return i;
}

/*********************************************************************
** Function: get_col_pos
** Description: returns the Player's column position in the cave
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
*********************************************************************/ 

int Player::get_col_pos()
{
	return j;
}

/*********************************************************************
** Function: is_on_side
** Description: returns true if the player is located on the perimeter 
**				of the cave
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
*********************************************************************/

bool Player::is_on_side(int dimension)
{
	if(i == 0)
	{
		return true;
	}else if(i == dimension-1)
	{
		return true;
	}else if (j == 0)
	{
		return true;
	}else if (j == dimension-1)
	{
		return true;
	}else
	{
		return false;
	}
}

/*********************************************************************
** Function: has_won
** Description: if the wumpus is dead (wump == true) and the gold has 
**				been picked up (gold == true) return true, else return 
**				false
** Parameters: none
** Pre-Conditions: none
** Post-Condition: none
*********************************************************************/

bool Player::has_won()
{
	if(wump == true && gold == true)
	{
		return true;
	}
	return false;
}

/*********************************************************************
** Function: at_escape_rope
** Description: if the Player has won the game and thay are at the 
**				escape rope, return true
** Parameters: none 
** Pre-Conditions: none
** Post-Conditions: none
*********************************************************************/

bool Player::at_escape_rope()
{
	if(wump == true && gold == true)
	{
		if(i == x && j == y)
		{
			return true;
		}
	}return false;
}



