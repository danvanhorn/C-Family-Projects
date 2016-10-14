#include <iostream>
#include <cstdlib>
#include <cstring>
#include "./game.h"
#include "./errorcheck.h"

using namespace std;

/*********************************************************************
** Function: validate_dimensions
** Description: this function validates the cmd line argument, taken as 
**				a c-string, for the game's "Cave". 
** Parameters: char d[]
** Pre-Conditions: c-string has been read from cmd line
** Post-Conditions: int greater than 4
*********************************************************************/ 

int validate_dimensions(char *d)
{
	while(!(is_num(d) && atoi(d)>4))
	{

		cout << "Please enter cave dimension (greater than 4): ";
		cin.getline(d, 19);
	}
	return atoi(d);
}

/*********************************************************************
** Function: get_dimensions
** Description: reads the cmd line array for a -d (dimension), the c-string  
**				following "-d" is the one we must check for cave dimensions
** Parameters: int argc, char **argv, char d[]
** Pre-Conditions: argc > 1
** Post-Conditions: potential cave dimension taken in as c-string
*********************************************************************/ 

void get_dimensions(int argc, char *argv[], char *d)
{

	for (int i = 0; i < argc; i++)
	{
		if (argv[i][0] == '-')
		{
			if(strcmp("-c", argv[i]) == 0)
			{
				strcpy(d, argv[i+1]);
			}
		}
	}
}

/*********************************************************************
** Function:
** Description:
** Parameters:
** Pre-Conditions:
** Post-Conditions:
*********************************************************************/ 

int main(int argc, char *argv[])
{
	//declare a pointer for "dimension", cave will be d x d.
	char d[20];
	int dimension = 0;
	if (argc == 3)
	{
		get_dimensions(argc, argv, d);
		dimension = validate_dimensions(d);
		Game g(dimension);
		g.play();
	}else
	{
		do{
			cout << "Enter cave dimensions (must be greater than 4):";
			cin.getline(d,19);
		}while(!(is_num(d) && atoi(d) > 4));
		dimension = atoi(d);
		Game g(dimension);
		g.play();
	}


	return 0;
}