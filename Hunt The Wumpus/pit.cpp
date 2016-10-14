/*********************************************************************
** Program Filename: pit.cpp
** Author: Dan Van Horn
** Date: 05/16/2016
** Description: Pit class implentation
** Input: none
** Output: none
*********************************************************************/

#include <iostream>
#include <cstring>
#include "./pit.h"
#include "./player.h"

using std::cout;
using std::endl;

// constructor

Pit::Pit()
{
	set_percept();
	set_name();
}

//destructor

Pit::~Pit()
{
	delete [] percept;
	percept = NULL;
}

// copy constructor

Pit::Pit(const Pit &other)
{
	percept = new char[strlen(other.percept)+1];
	strcpy(percept, other.percept);
	name = other.name;
}

// assignment operator overload

void Pit::operator=(const Pit &other)
{
	delete [] percept;
	percept = new char[strlen(other.percept)+1];
	strcpy(percept, other.percept);
	name = other.name;
}

/*********************************************************************
** Function: set_percept
** Description: sets the c-string percept of a Pit
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
*********************************************************************/ 

void Pit::set_percept()
{
	if (percept != NULL)
		delete [] percept;
	percept = new char[19];
	strcpy(percept,"You feel a breeze.\0");	
}

/*********************************************************************
** Function: get_percept
** Description: returns the percept for a pit
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
*********************************************************************/ 

char* Pit::get_percept()
{
	return percept;
}

/*********************************************************************
** Function: set_name
** Description: sets the name of a Pit ('P')
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
*********************************************************************/ 

void Pit::set_name()
{
	name = 'P';
}

/*********************************************************************
** Function: get_name
** Description: returns the name of a Pit ('P')
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
*********************************************************************/ 

char Pit::get_name()
{
	//cout << name << endl;
	return name;
}

/*********************************************************************
** Function: act_on_player
** Description: If the Player enters the same Room as a Pit, the Player's
**				position will be set to -1, -1
** Parameters: Player*, int
** Pre-Conditions: none
** Post-Conditions: none
*********************************************************************/ 

void Pit::act_on_player(Player *p, int d)
{
	cout << "Taking a few steps into this new room, you realize there is no floor...\n";
	cout << "You meet your demise at the bottom of a deadly pit...\n";
	p->set_player_position(-1,-1);

}