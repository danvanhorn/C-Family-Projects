#include <iostream>
#include <cstdlib>
#include <string>
#include "./deck.h"
#include "./hand.h"
#include "./card.h"
#include "./dealer.h"
#include "./player.h"
#include "./game.h"

using namespace std;

bool again();

int main(){
	cout << "Welcome to Blackjack:" << endl;
	do
	{

		Game blackjack;
		blackjack.play_game();
	}
	while(again());

	return 0;
}

/*********************************************************************
** Function: again
** Description: prompts to play game again or quit
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
*********************************************************************/

bool again()
{
	string input;
	do
	{
		cout << "Play again? (1) yes ; (2) no" << endl;
		cin >> input;
	}
	while(!(input == "1" || input == "2"));
	if (input == "1")
	{
		return true;
		system ("clear");
	}
	else
	{
		return false;
	}

}



	

	