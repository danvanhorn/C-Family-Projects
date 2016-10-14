/*********************************************************************
** Program Filename: room.h
** Author: Dan Van Horn
** Date: 05/16/2016
** Description: room class for the game "Hunt the Wumpus"
** Input: none
** Output: none
*********************************************************************/

#ifndef ROOM_H
#define ROOM_H

#include "./event.h"

class Room
{

private: 
	Event *e;
	char p[2];
public:
	Room();
	~Room();
	Room(const Room &);
	void operator=(const Room &);
	void set_event(Event *);
	void clear_event();
	Event* get_event();
	char* get_event_percept();
	char get_event_name();
	void check_current_room(Player *, int);
	
};

#endif