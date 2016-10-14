#ifndef CARD_H
#define CARD_H

#include <string>

using namespace std;

class Card{
	private:
		int value;
		string face_val;
		string suit;
	public:
		Card();
		Card(const Card &);
		~Card();
		void operator=(const Card &);
		void set_value(int);
		void set_face_val(string);
		void set_suit(string);
		int get_value();
		string get_face_val();
		string get_suit();
};

#endif