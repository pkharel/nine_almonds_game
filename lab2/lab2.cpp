// lab1.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include "ninealmonds.h"
#include "lab2.h"

using namespace std;

int main(int argc, char* argv[]) {
	if (argc != num_args) {
		return(message(argv[program_name],num_args_error));
	}
	if (string(argv[game_name]) != "NineAlmonds") {
		return(message(argv[program_name],argument_value_error));
	}
	NineAlmondsGame game;
	int mainRet = game.play();
	return mainRet;
	//cout << "x: " << x << "y: " << y << endl;
}

int message(string pname, int error_value) 
{
	cout << "usage: " << pname << " NineAlmonds" << endl;
	if (error_value == num_args) {
		return usage_error;
	} else if (error_value == argument_value_error) {
		return argument_value_error;
	} else {
		return error_value;
	}
}
