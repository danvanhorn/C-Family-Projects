/*********************************************************************
** Program Filename: wumpus.cpp
** Author: Dan Van Horn
** Date: 05/16/2016
** Description: Wumpus class implentation, derived from Event
** Input: none 
** Output: none
*********************************************************************/

#include <iostream>
#include <cstring>
#include "./wumpus.h"
#include "./player.h"

using std::cout;
using std::endl;
 

Wumpus::Wumpus()
{
	set_percept();
	set_name();
}


Wumpus::~Wumpus()
{
	delete [] percept;
	percept = NULL;
}

Wumpus::Wumpus(const Wumpus &other)
{
	percept = new char[strlen(other.percept)+1];
	strcpy(percept, other.percept);
	name = other.name;	
}

void Wumpus::operator=(const Wumpus &other)
{
	delete [] percept;
	percept = new char[strlen(other.percept)+1];
	strcpy(percept, other.percept);
	name = other.name;	
}

/*********************************************************************
** Function: set_percept
** Description: sets the percept for the Wumpus
** Parameters: none
** Pre-Conditions: Wumpus object has been created
** Post-Conditions: none
*********************************************************************/ 

void Wumpus::set_percept()
{
	if (percept != NULL)
		delete [] percept;
	percept = new char[29];
	strcpy(percept,"You smell a terrible stench.\0");	
}

/*********************************************************************
** Function: get_percept
** Description: returns the Wumpus' percept
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
*********************************************************************/ 

char* Wumpus::get_percept()
{
	return percept;
}

/*********************************************************************
** Function: set_name
** Description: sets the Wumpus name
** Parameters: none
** Pre-Conditions: Wumpus object has been created
** Post-Conditions: none
*********************************************************************/ 

void Wumpus::set_name()
{
	name = 'W';
}

/*********************************************************************
** Function: get_name
** Description: returns the name of Wumpus ('W')
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
*********************************************************************/ 

char Wumpus::get_name()
{
	//cout << name << endl;
	return name;
}

/*********************************************************************
** Function: act_on_player
** Description: If the Player enters a Room with a Wumpus this function
**				sets the position of the player to -1, -1 (dead)
** Parameters: Player*, int
** Pre-Conditions: none
** Post-Conditions: none
*********************************************************************/ 

void Wumpus::act_on_player(Player *p, int d)
{
	cout << "A great shadow rises from is slumber...\n";
	cout << "The last thing you see is a giant clawed hand coming straight for your face...\n";
	cout << "You are dead...\n";
	p->set_player_position(-1,-1);
}