/*********************************************************************
** Program Filename: game.h
** Author: Dan Van Horn
** Date: 05/16/2016
** Description: game class
** Input: none
** Output: none
*********************************************************************/

#ifndef GAME_H
#define GAME_H

#include "./room.h"
#include "./player.h"

class Game
{
protected:
	// keeps track of our cave dimensions
	int dimension; 

	Player p;  

	// 2-d array of Rooms for the Cave		
	Room **cave;
	Room **save_cave;	

public:
	Game();
	Game(int);
	~Game();
	void save();
	void play();
	bool game();
	void new_game();
	void replay();
	bool player_dead();
	void check_game_state();
	void init_events();
	void display_save_cave();
	void display_cave();
	void display_percepts();
	void print_percepts(int, int);
	void print_side_percepts(int, int);
	int move_or_shoot();
	void player_move();
	void prompt_move(int, int);
	void move_prompt_all(int, int);
	void move_prompt_top(int, int);
	void move_prompt_left(int, int);
	void move_prompt_bot(int, int);
	void move_prompt_right(int, int);
	void move_prompt_top_left(int, int);
	void move_prompt_top_right(int, int);
	void move_prompt_bot_left(int, int);
	void move_prompt_bot_right(int, int);
	void move_player_left(int, int);
	void move_player_down(int, int);
	void move_player_right(int, int);
	void move_player_up(int, int);
	void player_shoot();
	void shoot_right();
	void shoot_left();
	void shoot_up();
	void shoot_down();
	void wumpus_wake(int, int);
	void wumpus_escape();
};

#endif