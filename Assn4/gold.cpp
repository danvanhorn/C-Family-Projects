/*********************************************************************
** Program Filename: gold.cpp
** Author: Dan Van Horn
** Date: 05/16/2016
** Description: Gold class implementation 
** Input: none
** Output: none
*********************************************************************/

#include <iostream>
#include <cstring>
#include "./gold.h"
#include "./player.h"

using std::cout;
using std::endl;

// constructor

Gold::Gold()
{
	set_percept();
	set_name();
}

// destructor

Gold::~Gold()
{
	delete [] percept;
	percept = NULL;
}

// copy constructor

Gold::Gold(const Gold &other)
{
	percept = new char[strlen(other.percept)+1];
	strcpy(percept, other.percept);
	name = other.name;
}

// assignment operator overload

void Gold::operator=(const Gold &other)
{
	delete [] percept;
	percept = new char[strlen(other.percept)+1];
	strcpy(percept, other.percept);
	name = other.name;
}

/*********************************************************************
** Function: set_percept
** Description: sets the percept for Gold
** Parameters: none
** Pre-Conditions: Gold object has been created
** Post-Conditions: none
*********************************************************************/ 

void Gold::set_percept()
{
	if (percept != NULL)
		delete [] percept;
	percept = new char[26];
	strcpy(percept,"You see a glimmer nearby.\0");	
}

/*********************************************************************
** Function: get_percept
** Description: returns the percept for Gold
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
*********************************************************************/ 


char* Gold::get_percept()
{
	return percept;
}

/*********************************************************************
** Function: set_name
** Description: sets the name for Gold ('G')
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
*********************************************************************/ 

void Gold::set_name()
{
	name = 'G';
}

/*********************************************************************
** Function: set_name
** Description: returns the name of Gold ('G')
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
*********************************************************************/ 

char Gold::get_name()
{
	//cout << name << endl;
	return name;
}

/*********************************************************************
** Function: act_on_player
** Description: if the Player is in the same Room with Gold then call
**				the Player::get_gold() function
** Parameters: Player*, int
** Pre-Conditions: none
** Post-Conditions: none
*********************************************************************/ 

void Gold::act_on_player(Player *p, int d)
{
	cout << "What's this? .....a gold ring? It feels heavy....\n";
	cout << "You place it in your waistcoat pocket...\n";
	p->get_gold();
}