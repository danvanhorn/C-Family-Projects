/*********************************************************************
** Program Filename: gold.h
** Author: Dan Van Horn
** Date: 05/16/2016
** Description: Gold class, derived from Event class
** Input: none
** Output: none
*********************************************************************/

#ifndef GOLD_H
#define GOLD_H

#include "./event.h"
#include "./player.h"

class Gold : public Event
{
public:
	Gold();
	~Gold();
	Gold(const Gold &);
	void operator=(const Gold &);
	char* get_percept();
	void set_percept();
	void set_name();
	char get_name();
	void act_on_player(Player *, int);
};

#endif