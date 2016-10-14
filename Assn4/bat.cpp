/*********************************************************************
** Program Filename: bat.cpp
** Author: Dan Van Horn
** Date: 05/17/2016
** Description: Bat class implentation for the game "Hunt the Wumpus"
** Input: none
** Output: none
*********************************************************************/



#include <iostream>
#include <cstdlib>
#include <time.h>
#include <cstring>
#include "./bat.h"
#include "./player.h"

using std::cout;
using std::endl;



Bat::Bat()
{
	set_percept();
	set_name();
}

Bat::~Bat()
{
	delete [] percept;
	percept = NULL;
}

Bat::Bat(const Bat &other)
{
	percept = new char[strlen(other.percept)+1];
	strcpy(percept, other.percept);
	name = other.name;

}

void Bat::operator=(const Bat &other)
{
	delete [] percept;
	percept = new char[strlen(other.percept)+1];
	strcpy(percept, other.percept);
	name = other.name;
}

/*********************************************************************
** Function: set_percept
** Description: sets the percept for the Bat
** Parameters: none
** Pre-Conditions: Bat object has been created
** Post-Conditions: none
*********************************************************************/

void Bat::set_percept()
{
	if (percept != NULL)
		delete [] percept;
	percept = new char[25];
	strcpy(percept,"You hear wings flapping.\0");	
}

/*********************************************************************
** Function: get_percept
** Description: returns the percept for a Bat
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
*********************************************************************/

char* Bat::get_percept()
{
	return percept;
}

/*********************************************************************
** Function: set_name
** Description: sets the name of a Bat ('B')
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
*********************************************************************/

void Bat::set_name()
{
	name = 'B';
}

/*********************************************************************
** Function: get_name
** Description: returns the name of a Bat ('B')
** Parameters: none
** Pre-Conditions: none 
** Post-Conditions: none
*********************************************************************/

char Bat::get_name()
{
	//cout << name << endl;
	return name;
}

/*********************************************************************
** Function: act_on_player
** Description: if the Player enters the same Room as a Bat, the Bat will
**				move the player to a random, potentially dangerous Room
** Parameters: Player*, int
** Pre-Conditions: Player is in the same room as Bat
** Post-Conditions: Player will be in a random room
*********************************************************************/

void Bat::act_on_player(Player *p, int d)
{
	int r1 = 0, r2 = 0;
	srand(time(NULL));
	r1 = rand() % d;
	r2 = rand() % d;
	cout << "A huge bat swoops down out of the darkness and snatches you!\n";
	cout << ".....You to find yourself in a different part of the cave.\n";
	p->set_player_position(r1, r2);

}


