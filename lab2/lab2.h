#include "stdafx.h"
#include <string>

using namespace std;

//Define error values
enum errors
{
	usage_error = 1,
	argument_value_error = 2,
	num_args_error = 3
};

//Define arguments to the program
enum arguments
{
	program_name = 0,
	game_name = 1,
	num_args = 2
};

//message function that prints out a helpful message on how to use the program
int message(string pname, int error_value);
