/*********************************************************************
** Program Filename: game.cpp
** Author: Dan Van Horn
** Date: 05/16/2016
** Description: game class implentation
**				This is where the game is actually played
** Input: none
** Output: none
*********************************************************************/

#include <iostream>
#include <time.h>
#include <cstdlib>
#include "./errorcheck.h"
#include "./game.h"
#include "./player.h"
#include "./room.h"
#include "./event.h"
#include "./bat.h"
#include "./gold.h"
#include "./wumpus.h"
#include "./pit.h"

using namespace std;

Game::Game()
{
	dimension = 0;
	save_cave = NULL;	
	cave = NULL;
}

// non-default constructor

Game::Game(int d)
{
	dimension = d;
	cave = new Room*[d];
	for (int i = 0; i < d; i++)
	{
		cave[i] = new Room[d];
	}
	save_cave = new Room*[d];
	for(int i = 0; i < d; i++)
	{
		save_cave[i] = new Room[d];
	}
	init_events();
}

// destructor

Game::~Game()
{
	if (cave != NULL)
	{
		for (int i = 0; i < dimension; ++i)
		{
			delete [] cave[i];
		}
		delete [] cave;
		cave = NULL;
	}
	if (save_cave != NULL)
	{
		for (int i = 0; i < dimension; ++i)
		{
			delete [] save_cave[i];
		}
		delete [] save_cave;
		save_cave = NULL;
	}
}

/*********************************************************************
** Function: play
** Description: This is where the game takes place
** Parameters: none
** Pre-Conditions: game object has been created
** Post-Conditions: none
*********************************************************************/

void Game::play()
{
	int s;
	do{
		while(!(player_dead()))
		{
			s = 0;
			//display_save_cave();
			display_cave();
			display_percepts();
			if (p.has_won())
			{
				cout << "You have the gold, the Wumpus is dead...\n";
				cout << "Now might be a good time to get out of here...\n";
			}
			s = move_or_shoot();			//ask player for move or shoot
			if (s == 1)
			{
				player_move();				//move function
			}	
			else if(s == 2)
			{
				player_shoot();			//shoot function
		
			}
			check_game_state();
			if(p.at_escape_rope())
			{
				cout << "You found the escape rope! \n";
				cout << "Taste that sweet fresh air...\n";
				break;
			}
		}
	}while (game() == true);
}

/*********************************************************************
** Function: game()
** Description: When the game is over reprompt the player to play again
**				with the same cave, a new cave, or quit
** Parameters: none
** Pre-Conditions: game is over
** Post-Conditions: game will be played again, or exit program
*********************************************************************/

bool Game::game()
{	
	
	char inp[20]; 
	do{
		cout << "Would you like to play again?\n";
		cout << "1/Play again with the same cave...\n";
		cout << "2/Play again with a new cave...\n";
		cout << "3/Exit Game...\n";
		cin.getline(inp,19);
	}while(!(is_num(inp) && is_1_3(inp)));
	if(atoi(inp) == 1)
	{
		replay();
		//play again with the same cave
		//init original cave & player to orig starting position
		return true;
	}
	else if(atoi(inp) == 2)
	{
		new_game();
		// play again with new cave, new event locs
		// new player starting loc 
		return true;

	}
	else
	{
		return false;
	}
}

/*********************************************************************
** Function: replay
** Description: Initialize the original cave back to it's original state
**				using the save_cave we had from the beginning
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
*********************************************************************/

void Game::replay()
{
	for (int i = 0; i < dimension; i++)
	{
		for (int j = 0; j < dimension; j++)
		{
			if (cave[i][j].get_event() != NULL)
			{
				cave[i][j].clear_event();			
			}	
		}
	}for (int i = 0; i < dimension; i++)
	{
		for (int j = 0; j < dimension; j++)
		{
			if(save_cave[i][j].get_event() != NULL)
			{
				if((char)save_cave[i][j].get_event_name() == 'W')
				{
					cave[i][j].set_event(new Wumpus);
				}
				else if ((char)save_cave[i][j].get_event_name() == 'B')
				{
					cave[i][j].set_event(new Bat);
				}
				else if ((char)save_cave[i][j].get_event_name() == 'G')
				{
					cave[i][j].set_event(new Gold);
				}else
				{
					cave[i][j].set_event(new Pit);
				}
			}
		}
	}
	p.set_arrows();
	p.back_to_start();

}


/*********************************************************************
** Function: new_game
** Description: if the user wants to play a game with a new cave, this 
**				function prompts for the size and inits both cave and
**				save_cave based on those dimensions
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
*********************************************************************/

void Game::new_game()
{
	char inp[20];
	p.set_arrows();
	p.set_player_start_position(0,0); 
	for (int i = 0; i < dimension; ++i)
	{
		delete [] cave[i];
	}delete [] cave;
	for (int i = 0; i < dimension; ++i)
	{
		delete [] save_cave[i];
	}delete [] save_cave;
	do
	{
		cout << "Enter new cave dimensions: ";
		cin.getline(inp,19);
	}while(!(is_num(inp) && atoi(inp) > 4));
	dimension = atoi(inp);
	cave = new Room*[dimension];
	for (int i = 0; i < dimension; ++i)
	{
		cave[i] = new Room[dimension];
	}save_cave = new Room*[dimension];
	for (int i = 0; i < dimension; ++i)
	{
		save_cave[i] = new Room[dimension];
	}
	init_events();
}

/*********************************************************************
** Function: player_dead
** Description: if the player's position is -1, -1 or the number of 
**				arrows == 0 and the wumpus has not been killed
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
*********************************************************************/ 

bool Game::player_dead()
{
	if(p.get_row_pos() == -1 && p.get_col_pos() == -1)
	{
		return true;
	}
	else if(p.get_num_arrows() == 0 && p.wumpus_dead() == false)
	{
		return true;
	}else 
	{
	return false;
	}
}

/*********************************************************************
** Function: check_game_state
** Description: After the player has moved, this function will call the 
**				Room::check_current_room function to act on the player 
**				if they are in the same Room as an event
** Parameters: none
** Pre-Conditions: Player has moved or shot an arrow
** Post-Conditions: Player is still alive, or Player is dead
*********************************************************************/

void Game::check_game_state()
{
	int i = p.get_row_pos();
	int j = p.get_col_pos();
	if(cave[i][j].get_event() != NULL)
	{
		cave[i][j].check_current_room(&p, dimension);
	}
}

/*********************************************************************
** Function: init_events
** Description: This function will initialize the Event ptrs in each Room
**				with 2x Bats, 2x Pits, 1x Gold and 1x Wumpus.
**				The Player's starting position will be set once all of the 
**				event ptrs have been set (to avoid starting in the same room as an event)
** Parameters: none
** Pre-Conditions: game is about to be played
** Post-Conditions: cave is initialized
*********************************************************************/ 

// TESTING TO INIT BOTH CAVES WITH DYNAMIC MEM

void Game::init_events()
{
	srand(time(NULL));
	int rand1 = 0, rand2 = 0;
	for(int i = 0; i < 2;)
	{
		rand1 = rand()%dimension;
		rand2 = rand()%dimension;
		if (cave[rand1][rand2].get_event() == NULL)
		{
			
			cave[rand1][rand2].set_event(new Bat);

			save_cave[rand1][rand2].set_event(new Bat);

			i++;
		}
	}
	for(int i = 0; i < 2;)
	{
		rand1 = rand()%dimension;
		rand2 = rand()%dimension;
		if (cave[rand1][rand2].get_event() == NULL)
		{
			cave[rand1][rand2].set_event(new Pit);

			save_cave[rand1][rand2].set_event(new Pit);

			i++;
		}
	}
	for(int i = 0; i < 1;)
	{
		rand1 = rand()%dimension;
		rand2 = rand()%dimension;
		if (cave[rand1][rand2].get_event() == NULL)
		{
			cave[rand1][rand2].set_event(new Gold);
			save_cave[rand1][rand2].set_event(new Gold);

			i++;
		}		
	}
	for(int i = 0; i < 1;)
	{
		rand1 = rand()%dimension;
		rand2 = rand()%dimension;
		if (cave[rand1][rand2].get_event() == NULL)
		{
			cave[rand1][rand2].set_event(new Wumpus);

			save_cave[rand1][rand2].set_event(new Wumpus);

			i++;
		}			
	}
	rand1 = rand()%dimension;
	rand2 = rand()%dimension;
	while(cave[rand1][rand2].get_event() != NULL)
	{
		rand1 = rand()%dimension;
		rand2 = rand()%dimension;
	}	
	p.set_player_start_position(rand1, rand2);
}

#ifdef DEBUG

void Game::display_save_cave()
{
	int x = p.get_row_pos();
	int y = p.get_col_pos();
	for (int i = 0; i < dimension; i++)
	{
		for (int j = 0; j < dimension; j++)
		{
			if (!(i == x && j == y) && save_cave[i][j].get_event() != NULL)
			{
				cout << "|"<< (char)save_cave[i][j].get_event_name();
			}
			else if (i == x && j == y)
			{
				cout << "|X"; 
			}
			else
			{
				cout << "| ";
			}
			 
		}
		cout << "|" << endl;
	}
	cout << endl;	
}

#endif

/*********************************************************************
** Function: display_cave
** Description: Displays the cave and the player's current position in it.
**				We also have a debug mode which shows the position of the 
**				events for testing purposes.
** Parameters: none
** Pre-Conditions: game in progress
** Post-Conditions: position is displayed on a grid
*********************************************************************/ 

void Game::display_cave()
{
	int x = p.get_row_pos();
	int y = p.get_col_pos();
	for (int i = 0; i < dimension; i++)
	{
		for (int j = 0; j < dimension; j++)
		{
			                    //complile w/o debug for normal mode
			//#ifndef DEBUG
			if (i == x && j == y)
			{
				cout << "|X";
			}
			//#endif
			#ifdef DEBUG   					//complile w/debug for debug mode
			else if (cave[i][j].get_event() != NULL)
			{
				if((char)cave[i][j].get_event_name() == 'W')
				{
					cout << "|W";
				}	
				else if((char)cave[i][j].get_event_name() == 'B')
				{
					cout << "|B";
				}
				else if((char)cave[i][j].get_event_name() == 'G')
				{
					cout << "|G";
				}
				else if((char)cave[i][j].get_event_name() == 'P')
				{
					cout << "|P";
				}				
			}	
			#endif
			else
			{
				cout << "| "; 
			}

			 
		}
		cout << "|" << endl;
	}
}

/*********************************************************************
** Function: display_percepts
** Description: get's the current position of the player within the cave
**              call's print_percepts function with that information as 
**				parameters
** Parameters: none
** Pre-Conditions: game in progress
** Post-Conditions: call print_percepts
*********************************************************************/ 

void Game::display_percepts()
{
	int i = p.get_row_pos();
	int j = p.get_col_pos();
	if (p.is_on_side(dimension))
	{
		print_side_percepts(i, j);		
	}else
	{
		print_percepts(i,j);
	}
}

/*********************************************************************
** Function: print_percepts
** Description: if the player is in the middle of the cave, we check 
**				each adjacent space for a percept
** Parameters: int, int
** Pre-Conditions: Player is not in a corner
** Post-Conditions: Percepts will be checked
*********************************************************************/

void Game::print_percepts(int i, int j)
{
	cout << cave[i][j+1].get_event_percept() << "";
	cout << cave[i+1][j].get_event_percept() << "";
	cout << cave[i][j-1].get_event_percept() << "";
	cout << cave[i-1][j].get_event_percept() << "\n";
}

/*********************************************************************
** Function: print_percepts
** Description: This function will, based on the position of the player,
**				check in all four directions to retrieve event percepts.
**				Will not check out of bounds.
** Parameters: int i, int j
** Pre-Conditions: game must be in progress
** Post-Conditions: percepts are displayed to screen
*********************************************************************/ 

void Game::print_side_percepts(int i, int j)
{
	if (i == 0)			// we are on the top side
	{ 
		if (j == 0)		// top left corner
		{
			cout << cave[i][j+1].get_event_percept() << "";
			cout << cave[i+1][j].get_event_percept() << " \n";		
		}
		else if (j == dimension-1)		// top right corner		
		{
			cout << cave[i+1][j].get_event_percept() << "";
			cout << cave[i][j-1].get_event_percept() << " \n";
		}
		else if (j > 0)			// on top side, not in a corner
		{
			cout << cave[i][j+1].get_event_percept() << "";
			cout << cave[i+1][j].get_event_percept() << "";
		    cout << cave[i][j-1].get_event_percept() << "\n";				
		}
	}
	else if (j == 0)		// we are on the left side
	{
		if (i == dimension-1) 		// bottom left corner
		{
			cout << cave[i][j+1].get_event_percept() << "";
		    cout << cave[i-1][j].get_event_percept() << "\n";
		}
		else if (i > 0)			// left side, not in a corner
		{
			cout << cave[i][j+1].get_event_percept() << "";
			cout << cave[i+1][j].get_event_percept() << "";
			cout << cave[i-1][j].get_event_percept() << "\n";
		}
	}
	else if (i == dimension-1)		// we are on the bottom side
	{
		if (j == dimension-1)		// bottom right corner
		{
			cout << cave[i-1][j].get_event_percept() << "";
		    cout << cave[i][j-1].get_event_percept() << "\n";	
		}
		else if (j < dimension-1)		// bottom side, not in a corner
		{
			cout << cave[i][j+1].get_event_percept() << "";
			cout << cave[i][j-1].get_event_percept() << "";
			cout << cave[i-1][j].get_event_percept() << "\n";	
		}
	}
	else if (j == dimension-1)		//we are on the right side
	{
		if (i > 0 && i < dimension-1)		//right side, not in a corner
		{
			cout << cave[i+1][j].get_event_percept() << "";
			cout << cave[i][j-1].get_event_percept() << "";
			cout << cave[i-1][j].get_event_percept() << "\n";		
		}
	}

}



/*********************************************************************
** Function: move_or_shoot
** Description: prompts the user for 1 of 2 choices:
**				- move to a new room
**				- shoot an arrow
**				validates the user's input and returns int
** Parameters: none
** Pre-Conditions: 
** Post-Conditions:
*********************************************************************/ 

int Game::move_or_shoot()
{
	char inp[20];
	do
	{
		cout << "Would you like to move or shoot and arrow?\n";
		cout << "(1: move or 2: shoot): ";
		cin.getline(inp, 19);
	}while(!(is_num(inp) && is_1_2(inp)));
	return atoi(inp);
}

/*********************************************************************
** Function: player_move
** Description: gets the Player's current position and calls the 
**				prompt_move funtion with the position as parameters
** Parameters: none
** Pre-Conditions: Player chose to move
** Post-Conditions: none
*********************************************************************/ 

void Game::player_move()
{
	int i = p.get_row_pos();
	int j = p.get_col_pos();
	prompt_move(i,j);
}

/*********************************************************************
** Function: prompt_move
** Description: checks if the Player is in a corner first, then checks 
**				if they are on the perimeter of the cave, lastly if they
**				are in the middle of the cave
** Parameters: int, int
** Pre-Conditions: Player has chosen to move
** Post-Conditions: Player will be prompted to move based on their position
*********************************************************************/

void Game::prompt_move(int i, int j)
{
	if(i == 0 && j == 0)
	{
		move_prompt_top_left(i,j);		// prompt to move down and right
	}else if (i == dimension-1 && j == dimension-1)
	{
		move_prompt_bot_right(i,j);		// prompt to move left and up
	}else if(i == 0 && j == dimension-1)
	{
		move_prompt_top_right(i,j); 	// prompt to move down and left
	}else if(i == dimension-1 && j == 0)
	{
		move_prompt_bot_left(i,j);		// prompt to move right and up
	}else if(i == 0)
	{
		move_prompt_top(i,j);
	}else if(j == 0)
	{
		move_prompt_left(i,j);
	}else if(i == dimension-1)
	{
		move_prompt_bot(i,j);
	}else if(j == dimension-1)
	{
		move_prompt_right(i,j);
	}else
	{
		move_prompt_all(i, j);
	}
}

/*********************************************************************
** Function: move_prompt_all
** Description: prompts the player to move in all directions
** Parameters: int, int
** Pre-Conditions: Player is in NOT on the perimeter of cave
** Post-Conditions: Player will be prompted to move all directions
*********************************************************************/

void Game::move_prompt_all(int i, int j)
{
	char inp[20];
	do
	{
		cout << "Move right, down, left, or up? (1/right, 2/down, 3/left 4/up): ";
		cin.getline(inp, 19);
	}while(!(is_num(inp) && is_1_4(inp)));
	if (atoi(inp) == 1)
	{
		move_player_right(i,j);
	}else if (atoi(inp) == 2)
	{
		move_player_down(i,j);
	}else if (atoi(inp) == 3)
	{
		move_player_left(i,j);
	}else
	{
		move_player_up(i,j);
	}
}

/*********************************************************************
** Function: move_prompt_top
** Description: if the player is along the "top" of the cave, they will be
**				prompted for right, down, and left moves
** Parameters: int, int
** Pre-Conditions: Player is along top perimeter
** Post-Conditions: Player position will be changed
*********************************************************************/

void Game::move_prompt_top(int i, int j)
{
	char inp[20]; 
	do
	{
		cout << "Move right, down, or left? (1/right 2/down 3/left): ";
		cin.getline(inp, 19);
	}while(!(is_num(inp) && is_1_3(inp)));
	if (atoi(inp) == 1)
	{
		move_player_right(i,j);
	}else if (atoi(inp) == 2)
	{
		move_player_down(i,j);
	}else
	{
		move_player_left(i,j);
	}
}

/*********************************************************************
** Function: move_prompt_left
** Description: if the player is along the "left" of the cave, they will be
**				prompted for right, down, and up moves 
** Parameters: int, int
** Pre-Conditions: Player is along left perimeter
** Post-Conditions: Player position will be changed
*********************************************************************/

void Game::move_prompt_left(int i, int j)
{
	char inp[20]; 
	do
	{
		cout << "Move right, down, or up? (1/right 2/down 3/up): ";
		cin.getline(inp, 19);
	}while(!(is_num(inp) && is_1_3(inp)));
	if (atoi(inp) == 1)
	{
		move_player_right(i,j);
	}else if (atoi(inp) == 2)
	{
		move_player_down(i,j);
	}else
	{
		move_player_up(i,j);
	}
}

/*********************************************************************
** Function: move_prompt_bot
** Description: if the player is along the "bottom" of the cave, they will be
**				prompted for right, left, and up moves 
** Parameters: int, int
** Pre-Conditions: Player is along bottom perimeter
** Post-Conditions: Player position will be changed
*********************************************************************/

void Game::move_prompt_bot(int i, int j)
{
	char inp[20]; 
	do
	{
		cout << "Move right, left, or up? (1/right 2/left 3/up): ";
		cin.getline(inp, 19);
	}while(!(is_num(inp) && is_1_3(inp)));
	if (atoi(inp) == 1)
	{
		move_player_right(i,j);
	}else if (atoi(inp) == 2)
	{
		move_player_left(i,j);
	}else
	{
		move_player_up(i,j);
	}
}

/*********************************************************************
** Function: move_prompt_right
** Description: if the player is along the "right" of the cave, they will be
**				prompted for left, down, and up moves 
** Parameters: int, int
** Pre-Conditions: Player is along right perimeter
** Post-Conditions: Player position will be changed
*********************************************************************/

void Game::move_prompt_right(int i, int j)
{
	char inp[20]; 
	do
	{
		cout << "Move down, left, or up? (1/down 2/left 3/up): ";
		cin.getline(inp, 19);
	}while(!(is_num(inp) && is_1_3(inp)));
	if (atoi(inp) == 1)
	{
		move_player_down(i,j);
	}else if (atoi(inp) == 2)
	{
		move_player_left(i,j);
	}else
	{
		move_player_up(i,j);
	}
}

/*********************************************************************
** Function: move_prompt_top_left
** Description: if the Player is in the top left corner, they will be 
**				prompted to move down and right
** Parameters: int, int
** Pre-Conditions: Player is in the top left corner
** Post-Conditions: Player position will be changed
*********************************************************************/

void Game::move_prompt_top_left(int i, int j)
{
	char inp[20];
	do
	{
		cout << "Move right or down? (1/right  2/down): ";
		cin.getline(inp, 19);
	}while(!(is_num(inp) && is_1_2(inp)));
	if (atoi(inp) == 1)
	{
		move_player_right(i,j);
	}else if(atoi(inp) == 2)
	{
		move_player_down(i,j);
	}
}

/*********************************************************************
** Function: move_prompt_top_right
** Description: if the Player is in the top right corner, they will be 
**				prompted to move down and left
** Parameters: int, int
** Pre-Conditions: Player is in the top right corner
** Post-Conditions: Player position will be changed
*********************************************************************/

void Game::move_prompt_top_right(int i, int j)
{
	char inp[20];
	do
	{
		cout << "Move left or down? (1/left  2/down): ";
		cin.getline(inp, 19);
	}while(!(is_num(inp) && is_1_2(inp)));
	if (atoi(inp) == 1)
	{
		move_player_left(i,j);
	}else if(atoi(inp) == 2)
	{
		move_player_down(i,j);
	}
}

/*********************************************************************
** Function: move_prompt_bot_right
** Description: if the Player is in the bottom right corner, they will be 
**				prompted to move up and left
** Parameters: int, int
** Pre-Conditions: Player is in the bottom right corner
** Post-Conditions: Player position will be changed
*********************************************************************/

void Game::move_prompt_bot_right(int i, int j)
{
	char inp[20];
	do
	{
		cout << "Move left or up? (1/left  2/up): ";
		cin.getline(inp, 19);
	}while(!(is_num(inp) && is_1_2(inp)));
	if (atoi(inp) == 1)
	{
		move_player_left(i,j);
	}else if(atoi(inp) == 2)
	{
		move_player_up(i,j);
	}
}

/*********************************************************************
** Function: move_prompt_bot_left
** Description: if the Player is in the bottom left corner, they will be 
**				prompted to move up and right
** Parameters: int, int
** Pre-Conditions: Player is in the bottom left corner
** Post-Conditions: Player position will be changed
*********************************************************************/

void Game::move_prompt_bot_left(int i, int j)
{
	char inp[20];
	do
	{
		cout << "Move right or up? (1/right  2/up): ";
		cin.getline(inp, 19);
	}while(!(is_num(inp) && is_1_2(inp)));
	if (atoi(inp) == 1)
	{
		move_player_right(i,j);
	}else if(atoi(inp) == 2)
	{
		move_player_up(i,j);
	}
}

/*********************************************************************
** Function: move_player_right
** Description: moves the Player to the right by 1
** Parameters: int, int
** Pre-Conditions: Player has chosen to move
** Post-Conditions: Player position will be 1 to the right
*********************************************************************/

void Game::move_player_right(int i, int j)
{
	p.set_player_position(i, j+1);
}

/*********************************************************************
** Function: move_player_down
** Description: moves the Player to the down by 1
** Parameters: int, int
** Pre-Conditions: Player has chosen to move
** Post-Conditions: Player position will be 1 down
*********************************************************************/

void Game::move_player_down(int i, int j)
{
	p.set_player_position(i+1, j);
}

/*********************************************************************
** Function: move_player_left
** Description: moves the Player to the left by 1
** Parameters: int, int
** Pre-Conditions: Player has chosen to move
** Post-Conditions: Player position will be 1 to the left
*********************************************************************/

void Game::move_player_left(int i, int j)
{
	p.set_player_position(i, j-1);
}

/*********************************************************************
** Function: move_player_up
** Description: moves the Player up by 1
** Parameters: int, int
** Pre-Conditions: Player has chosen to move
** Post-Conditions: Player position will be 1 up
*********************************************************************/ 

void Game::move_player_up(int i, int j)
{
	p.set_player_position(i-1, j);
}


/*********************************************************************
** Function: player_shoot
** Description: prompts the player for which direction they would like
**				to shoot and calls the cooresponding function
** Parameters: none 
** Pre-Conditions: none 
** Post-Conditions: none
*********************************************************************/ 

void Game::player_shoot()
{
	char inp[20];
	do
	{
		cout << "Which direction would you like to shoot?\n";
		cout << "(1/right 2/left 3/up 4/down): \n";
		cin.getline(inp, 19);
	}while(!(is_num(inp) && is_1_4(inp)));
	p.decrement_arrow();
	if(atoi(inp) == 1)
	{
		shoot_right(); 			
	}
	else if (atoi(inp) == 2)
	{
		shoot_left();				
	}
	else if (atoi(inp) == 3)
	{
		shoot_up();
	}else
	{
		shoot_down();		
	}
}

/*********************************************************************
** Function: shoot_right
** Description: checks three spots to the right and the adjacent spots
**				to the spots checked...if the arrow hits the side of the cave,
**				if the arrow kills the Wumpus, or if the arrow wakes up 
**				the Wumpus (adjacent space)
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
*********************************************************************/ 

void Game::shoot_right()
{
	int i = p.get_row_pos();
	int j = p.get_col_pos();
	int s = 1;
	while (s < 4)
	{
		
		if (j == dimension-1)
		{
			cout << "Your arrow hit a wall...\n";
			break;		
		}
		else if((j+s) >= dimension-1 && cave[i][j+s].get_event() == NULL)		//checks if along arrow's flight path, is wall
		{
			cout << "Your arrow hit a wall...\n";
			break;
		}
		else if(cave[i][j+s].get_event() != NULL)
		{	
			if ((char)cave[i][j+s].get_event()->get_name() == 'W')
			{
				cout << "Your arrow pierced the Wumpus' heart!\n";
				p.kill_wumpus();
				cave[i][j+s].clear_event();
				break;
			}
		}
		if((i-1) >= 0 && cave[i-1][j+s].get_event() != NULL)
		{
			if((char)cave[i-1][j+s].get_event()->get_name() == 'W')
			{
				wumpus_wake(i-1,j+s);  //wake the wump, 75% rand move
			}
		}
		if((i+1) <= dimension-1 && cave[i+1][j+s].get_event() != NULL)
		{
			if((char)cave[i+1][j+s].get_event()->get_name() == 'W')
			{
				wumpus_wake(i+1,j+s);  //wake the wump, 75% rand move
			}
		}
		s++;
	}
}

/*********************************************************************
** Function: shoot_left
** Description: checks three spots to the left and the adjacent spots
**				to the spots checked...if the arrow hits the side of the cave,
**				if the arrow kills the Wumpus, or if the arrow wakes up 
**				the Wumpus (adjacent space)
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
*********************************************************************/ 

void Game::shoot_left()
{
	int i = p.get_row_pos();
	int j = p.get_col_pos();
	int s = 1;
	while (s < 4)
	{
		if (j==0)
		{
			cout << "Your arrow hit a wall...\n";
			break;
		}
		else if((j-s) <= 0 && cave[i][j-s].get_event() == NULL)		//checks if along arrow's flight path, is wall
		{
			cout << "Your arrow hit a wall...\n";
			break;
		}
		else if(cave[i][j-s].get_event() != NULL)
		{	
			if ((char)cave[i][j-s].get_event()->get_name() == 'W')
			{
				cout << "Your arrow pierced the Wumpus' heart!\n";
				p.kill_wumpus();
				cave[i][j-s].clear_event();
				break;
			}
		}
		if((i-1) >= 0 && cave[i-1][j-s].get_event() != NULL)
		{
			if((char)cave[i-1][j-s].get_event()->get_name() == 'W')
			{
				wumpus_wake(i-1,j-s);  //wake the wump, 75% rand move
			}
		}
		if((i+1) <= dimension-1 && cave[i+1][j-s].get_event() != NULL)
		{
			if((char)cave[i+1][j-s].get_event()->get_name() == 'W')
			{
				wumpus_wake(i+1,j-s);  //wake the wump, 75% rand move
			}
		}
		s++;
	}
}

/*********************************************************************
** Function: shoot_up
** Description: checks three spots upwards and the adjacent spots
**				to the spots checked...if the arrow hits the side of the cave,
**				if the arrow kills the Wumpus, or if the arrow wakes up 
**				the Wumpus (adjacent space)
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
*********************************************************************/ 

void Game::shoot_up()
{
	int i = p.get_row_pos();
	int j = p.get_col_pos();
	int s = 1;
	while (s < 4)
	{
		if (i == 0)
		{
			cout << "Your arrow hit a wall...\n";
			break;
		}		
		else if((i-s) <= 0 && cave[i-s][j].get_event() == NULL)		//checks if along arrow's flight path, is wall
		{
			cout << "Your arrow hit a wall...\n";
			break;
		}
		else if(cave[i-s][j].get_event() != NULL)
		{	
			if ((char)cave[i-s][j].get_event()->get_name() == 'W')
			{
				cout << "Your arrow pierced the Wumpus' heart!\n";
				p.kill_wumpus();
				cave[i-s][j].clear_event();
				break;
			}
		}
		if((j-1) >= 0 && cave[i-s][j-1].get_event() != NULL)
		{
			if((char)cave[i-s][j-1].get_event()->get_name() == 'W')
			{
				wumpus_wake(i-s,j-1);  //wake the wump, 75% rand move
			}
		}
		if((j+1) <= dimension-1 && cave[i-s][j+1].get_event() != NULL)
		{
			if((char)cave[i-s][j+1].get_event()->get_name() == 'W')
			{
				wumpus_wake(i-s,j+1);  //wake the wump, 75% rand move
			}
		}
		s++;
	}
}

/*********************************************************************
** Function: shoot_down
** Description: checks three spots downward and the adjacent spots
**				to the spots checked...if the arrow hits the side of the cave,
**				if the arrow kills the Wumpus, or if the arrow wakes up 
**				the Wumpus (adjacent space)
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
*********************************************************************/ 

void Game::shoot_down()
{
	int i = p.get_row_pos();
	int j = p.get_col_pos();
	int s = 1;
	while (s < 4)
	{
		
		if (i == dimension-1)
		{
			cout << "Your arrow hit a wall...\n";
			break;
		}
		else if((i+s) >= dimension-1 && cave[i+s][j].get_event() == NULL)		//checks if along arrow's flight path, is wall
		{
			cout << "Your arrow hit a wall...\n";
			break;
		}
		else if(cave[i+s][j].get_event() != NULL)
		{	
			if ((char)cave[i+s][j].get_event()->get_name() == 'W')
			{
				cout << "Your arrow pierced the Wumpus' heart!\n";
				p.kill_wumpus();
				cave[i+s][j].clear_event();
				break;
			}
		}
		if((j-1) >= 0 && cave[i+s][j-1].get_event() != NULL)
		{
			if((char)cave[i+s][j-1].get_event()->get_name() == 'W')
			{
				wumpus_wake(i+s,j-1);  //wake the wump, 75% rand move
			}
		}
		if((j+1) <= dimension-1 && cave[i+s][j+1].get_event() != NULL)
		{
			if((char)cave[i+s][j+1].get_event()->get_name() == 'W')
			{
				wumpus_wake(i+s,j+1);   //wake the wump, 75% rand move
			}
		}
		s++;
	}
}

/*********************************************************************
** Function: wumpus_wake
** Description: if an arrow travels through a room adjacent to a Wumpus
**				there is a 75% chance the Wumpus will change locations 
** Parameters: int, int
** Pre-Conditions: Arrow has flown past the Wumpus' room (Miss)
** Post-Conditions: Wumpus may move
*********************************************************************/ 

void Game::wumpus_wake(int i, int j)
{
	srand(time(NULL));
	int chance = rand()%4;
	if(chance != 0)
	{
		cave[i][j].clear_event();
		wumpus_escape();
	}	
}

/*********************************************************************
** Function: wumpus_escape
** Description: this function will move the Wumpus to a new room
** Parameters: none
** Pre-Conditions: An arrow flew by the Wumpus' room
** Post-Conditions: Wumpus position has changed
*********************************************************************/ 

void Game::wumpus_escape()
{
	srand(time(NULL));
	int i = -1;
	int j = -1;
	do
	{
		i = rand()% dimension;
		j = rand()% dimension;
	}while(cave[i][j].get_event() != NULL);
	cout << "You hear footsteps thundering throughout the cave...\n";
	cout << "You deduce that the monster moved to escape detection...\n";
	cave[i][j].set_event(new Wumpus);

}








