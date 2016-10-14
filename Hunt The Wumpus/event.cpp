/*********************************************************************
** Program Filename: event.cpp
** Author: Dan Van Horn
** Date: 05/16/2016
** Description: event class implentation
** Input: none
** Output: none
*********************************************************************/

#include "./event.h"

// constructor

Event::Event()
{
	percept = NULL;
	name = ' ';
}

// destructor

Event::~Event()
{
	if (percept != NULL)
	{
		delete [] percept;
	}
}

// copy constructor

Event::Event(const Event &other)
{
	if (other.percept != NULL)
	{
		percept = new char[strlen(other.percept)+1];
		strcpy(percept, other.percept);
		name = other.name;
	}else
	{
		percept = NULL;

	}
	
}

// assignment operator overload

void Event::operator=(const Event &other)
{
	if (other.percept != NULL)
	{
		delete [] percept;
		percept = new char[strlen(other.percept)+1];
		strcpy(percept, other.percept);
		name = other.name;
	}
	else
	{
		percept = NULL;
		name = other.name;
	}	
}

