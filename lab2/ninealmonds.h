#include "stdafx.h"
#include <vector>
#include <string>
#include <iostream>

using namespace std;

//Define game piece
struct game_piece {
	string name;
	string display;
};

//Define the NineAlmondsGame class
class NineAlmondsGame {
	public:
		//Constructor for the game
		NineAlmondsGame();
		//Waits for input and parses user input to find coordinates
		int prompt(unsigned int &x, unsigned int &y);
		//Implements one turn of the game
		int turn();
		//Main game method
		int play();
		//returns true if the game was completed successfully
		bool done();
		//returns true if there are no more valid moves left
		bool stalemate();
		//determines if the move is valid or not
		int NineAlmondsGame::valid(unsigned int &s_idx, unsigned int &f_idx);
		//operator overload to print game board
		friend ostream& operator<< (ostream &o, NineAlmondsGame &game);
	private:
		//main vector that stores the game pieces
		vector<game_piece> pieces;
};

//Simple function that converts coordinates (x,y) into index value
unsigned int coord2index(unsigned int x, unsigned int y);

//Simple function that converts index into coordinates
void index2coord(unsigned int idx, unsigned int &x, unsigned int &y);



//Various game constants
enum game_nums
{
	height = 5,
	width = 5,
	dim = height*width,
	middle_square = (dim-1)/2
};

//Return values for various functions
enum ret_vals
{
	//prompt
	proper_coords = 0,
	non_coords = 2,
	invalid_coords = 3,

	//turn
	valid_move = 0,
	user_quit = 1,
	no_almond_start = 2,
	not_2_squares = 3,
	almond_fin = 4,
	no_almond_mid = 5, 
	no_valid_moves = 6,

	//play
	game_end = 0,
	stalemate_end = 1,
};

