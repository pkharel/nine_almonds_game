#include "stdafx.h"
#include "ninealmonds.h"
#include <sstream>


//This is the main constructor of the class. It creates empty pieces everywhere except the
//inner squares which is filled with almonds
NineAlmondsGame::NineAlmondsGame() {
	game_piece piece;
	unsigned int x,y,m_x,m_y;
	index2coord(middle_square,m_x,m_y);
	for (int i = 0; i < dim; ++i) {
		index2coord(i,x,y);
		if (((x == m_x) || (x == m_x+1) || (x == m_x-1)) && ((y == m_y) || (y == m_y+1) || (y == m_y-1)))  {
			piece.display="A";
			piece.name = "brown almond";
		} else {
			piece.display = " ";
			piece.name = "";
		}
		pieces.push_back(piece);
	}
}

//Returns true if no more valid moves can be performed
bool NineAlmondsGame::stalemate() {
	unsigned int numValid = 0;
	//iterate through all possible squares and compare each one to see
	//if a valid move can be made
	for (unsigned int i = 0; i < dim; ++i) {
		for (unsigned int j = 0; j < dim; ++j) {
			if (valid(i,j) == valid_move) {
				numValid++;
			}
		}
	}
	if (numValid == 0) {
		return true;
	} else {
		return false;
	}
}

//Checks to see if the game is complete
bool NineAlmondsGame::done() {
	//iterate through all squares
	//check if all squares are empty
	for (unsigned int i = 0; i < dim; ++i) {
		//if middle of board, check if almond, else check if blank
		if (i == middle_square) {
			if (pieces[i].name == "") {
				return false;
			}
		} else {
			if (pieces[i].name != "") {
				return false;
			}
		}
	}
	return true;
}

//Check if the move from start index to finish index is valid or not
int NineAlmondsGame::valid(unsigned int &s_idx, unsigned int &f_idx) {
	//middle coordinate index
	unsigned int m_idx = (s_idx+f_idx)/2;
	//Check if starting square has an almond
	if (pieces[s_idx].name != "") {
		//convert indexes to coordinates
		unsigned int s_x,s_y,f_x,f_y;
		index2coord(s_idx,s_x,s_y);
		index2coord(f_idx,f_x,f_y);
		//Check if final square is 2 squares away or not
		if (((f_x == s_x - 2) || (f_x == s_x + 2) || (f_x == s_x)) && ((f_y == s_y - 2) || (f_y == s_y + 2) || (f_y == s_y))) {
			//check if final square has an almond or not
			if (pieces[f_idx].name == "") {
				//Check if middle square has an almond or not
				if (pieces[m_idx].name != "") {
					//If almond in middle then valid move.
					return valid_move;
				} else {
					return no_almond_mid;
				}
			} else {
				return almond_fin;
			}
		} else {
			return not_2_squares;
		}
	} else {
		return no_almond_start;
	}
}

//Prompts the user for input
int NineAlmondsGame::prompt(unsigned int &x, unsigned int &y) {
	string cmd;
	//keep prompting until we get a value
	while (true) {
		cout << "Enter coordinate (e.g 2,3) or quit (quit): ";
		getline(cin,cmd);
		//replace "," with " "
		for (size_t i = 0; i < cmd.length(); ++i) {
			if (cmd[i] == ',') {
				cmd[i] = ' ';
			}
		}

		if (cmd == "quit") {
			return user_quit;
		}

		//wrap string with stream and store in variables
		istringstream coords(cmd);

		if ((coords >> x >> y)) {
			if ((x >= 0 && x < width) && (x >=0 && y < height)) {
				cout << "Coordinates Accepted" << endl;
				return proper_coords;
			} else {
				cout << "Coordinates outside game board" << endl;
			}
		} else {
			cout << "Couldn't parse string properly" << endl;
		}
	}
}

//Implements the turn method of the game
int NineAlmondsGame::turn() {
	unsigned int s_x,s_y,f_x,f_y;
	bool cont = false;
	int numValid = 0;
	ostringstream oss;
	int ret1;
	while ((numValid == 0) || cont) {
		//If not continuing, ask for new value
		if (cont == false) {
			ret1 = prompt(s_x,s_y);
			if (ret1 == user_quit) {
				return user_quit;
			}
		}


		int ret2 = prompt(f_x,f_y);
		if (ret2 == user_quit) {
			return user_quit;
		} else if (ret2 == proper_coords) {
			//Store index value of start coordinates
			unsigned int s_idx = coord2index(s_x,s_y);
			//final coordinate index
			unsigned int f_idx = coord2index(f_x,f_y);
			//middle coordinate index
			unsigned int m_idx = coord2index((s_x + f_x)/2,(s_y+f_y)/2);
			
			//Check if move is valid
			int validRet = valid(s_idx,f_idx);
			if (validRet == valid_move) {
				//Increment number of valid moves
				numValid++;
				//Actually move the almond from start to finish
				pieces[f_idx].name = "brown almond";
				pieces[f_idx].display = "A";
				pieces[s_idx].name = "";
				pieces[s_idx].display = " ";
				//Remove middle almond
				pieces[m_idx].name = "";
				pieces[m_idx].display = " ";
				//Print game
				cout << *this << endl;

				//Construct string that prints the moves done so far.
				if (!cont) {
					oss << s_x << "," << s_y;
				}
				oss << " to " << f_x << ',' << f_y;
				cout << oss.str() << endl;

				//Loop until user decides whether to continue turn or not.
				string usrInp;
				bool choice = false;
				cout << endl;
				while (!choice) {
					cout << "Continue this turn (YyNn)?";
					getline(cin,usrInp);	
					if ((usrInp == "Y") || (usrInp == "y")) {
						cont = true;
						s_x = f_x;
						s_y = f_y;
						choice = true;
					} else if ((usrInp == "N") || (usrInp == "n")) {
						cont = false;
						choice = true;
					} 
				}
			} else {
				if (validRet == no_almond_start) {
					cout << "Starting square does not have an Almond. ";
				} else if (validRet == not_2_squares) {
					cout << "Final square needs to be two squares from starting square. ";
				} else if (validRet == almond_fin) {
					cout << "Final square needs to be empty. Start Over ";
				} else if (validRet == no_almond_mid) {
					cout << "Middle square does not contain an Almond. Start Over ";
				}
				//User has to start with 1st pair of coordinates if not hit continue. Else just one.
				if (cont) {
						cout << "Try again." << endl;
					} else {
						cout << "Start over with starting coordinates" << endl;
				}
			}
		}
	}	
	if (numValid > 0) {
		return valid_move;
	} else {
		return no_valid_moves;
	}
}

int NineAlmondsGame::play() {
	bool cont = true;
	int numTurns = 0;
	//Keep running turn until quit, done or stalemate
	while (true) {
		cout << *this;
		if (turn() == user_quit) {
			cout << "Game quit. Number of turns played is " << numTurns << "." << endl;
			return user_quit;
		} else {
			numTurns++;
			if (done()) {
				cout << "Game completed. The game took " << numTurns << " turns to complete." << endl;
				return game_end;
			} else if (stalemate()) {
				cout << "Stalemate! No more valid moves. Number of turns palyed is " << numTurns << "." << endl;
				return stalemate_end;
			}
		}
	}
}

ostream & operator<< (ostream &o, NineAlmondsGame &game) {
	//Print out the board
	for (unsigned int i = height; i > 0; i-- ) {
		string line = "";
		o << (i-1);
		for (unsigned int j = width; j > 0; j--) {
			unsigned int idx = height * (i-1) + (j-1);
			line = " " + game.pieces[idx].display + line ;
		}
		o << line << endl;
	}
	o << "x 0 1 2 3 4" << endl;
	return o;
}

unsigned int coord2index(unsigned int x, unsigned int y) {
	int result = width*y + x;
	return result;
}

void index2coord(unsigned int idx, unsigned int &x, unsigned int &y) {
	x = idx % width;
	y = idx / width;
}
