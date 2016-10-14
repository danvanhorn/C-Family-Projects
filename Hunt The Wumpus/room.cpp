/*********************************************************************
** Program Filename: room.cpp
** Author: Dan Van Horn
** Date: 05/16/2016
** Description: Room class implentation
** Input: none
** Output: none
*********************************************************************/
#include <iostream>
#include <time.h>
#include "./room.h"
#include "./event.h"


Room::Room()
{
	e = NULL;
	p[0] = ' ';
	p[1] = '\0';
}


Room::~Room()
{
	if (e != NULL)
	{
		delete e;
		e = NULL;
	}
}

Room::Room(const Room &other)
{
	if(other.e != NULL)
	{
		e = other.e;
	}
	strcpy(p,other.p);
}

void Room::operator=(const Room &other)
{
	if(e != NULL)
		delete e;
	if(other.e != NULL)
	{
		e = other.e;
	}
	strcpy(p,other.p);
}

/*********************************************************************
** Function: set_event
** Description: sets the event ptr in the room to whatever child class 
**				we sent in
** Parameters: Event *
** Pre-Conditions: none
** Post-Conditions: Event ptr points to a new event
*********************************************************************/ 

void Room::set_event(Event *ev)
{

	e = ev;
}

/*********************************************************************
** Function: clear_event
** Description: set the event ptr back to NULL
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: room event is NULL
*********************************************************************/

void Room::clear_event()
{
		delete e;
		e = NULL;
} 

/*********************************************************************
** Function: get_event
** Description: returns the event ptr in the room
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
*********************************************************************/ 

Event* Room::get_event()
{
	return e;
}

/*********************************************************************
** Function: get_event_percept
** Description: returns the percept as a char*
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
*********************************************************************/ 

char* Room::get_event_percept()
{
	if(e != NULL)
		return e->get_percept();
	else 
		return p;
	
}

/*********************************************************************
** Function: get_event_name
** Description: Returns the correct "name" of the event 'W'-Wumpus|'G'-Gold
**				|'P'-Pit|'B'-Bat
** Parameters: none
** Pre-Conditions: Event is not NULL
** Post-Conditions: none
*********************************************************************/ 

char Room::get_event_name()
{
	if (e != NULL)
	{
		if(e->get_name() == 'W')
		{
			return 'W';
		}
		else if (e->get_name() == 'G')
		{
			return 'G';
		}
		else if (e->get_name() == 'P')
		{
			return 'P';
		}
		else if(e->get_name() == 'B')
		{
			return 'B';
		}
	}	
	else
		return ' ';
}

/*********************************************************************
** Function: check_current_room
** Description: checks the room that the player is currently in and calls 
**				Event function to act on the player. Bat teleport, etc...
** Parameters: Player*, int
** Pre-Conditions: Player is in a Room w/an Event
** Post-Conditions: the Player will be acted upon by event
*********************************************************************/ 

void Room::check_current_room(Player *p, int dimension)
{
	if ((char)e->get_name() == 'B')
	{
		e->act_on_player(p, dimension);
	}
	else if ((char)e->get_name() == 'G')
	{
		e->act_on_player(p, dimension);
		delete e;
		e = NULL;
	}
	else if ((char)e->get_name() == 'P')
	{
		e->act_on_player(p, dimension);
	}
	else if ((char)e->get_name() == 'W')
	{
		e->act_on_player(p, dimension);
	}
}
