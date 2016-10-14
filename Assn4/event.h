/*********************************************************************
** Program Filename: event.h
** Author: Dan Van Horn
** Date: 05/16/2016
** Description: event base class
** Input: none
** Output: none
*********************************************************************/

#ifndef EVENT_H
#define EVENT_H

#include <cstring>
#include "./player.h"

class Event
{

protected: 
	char *percept;
	char name;
public:
	Event();
	Event(const Event &);
	virtual ~Event();
	virtual void operator=(const Event &);
	virtual void set_percept() = 0;
	virtual char* get_percept() = 0;
	virtual void set_name() = 0;
	virtual char get_name() = 0;
	virtual void act_on_player(Player *, int) = 0;
	//virtual void generate_event() = 0;

};

#endif