Lab: 2
Name: Pradosh Kharel

Errors encountered:
1>\\warehouse2.seasad.wustl.edu\home\pradosh.kharel\my documents\visual studio 2012\projects\lab2\lab2\lab2.cpp(5): warning C4627: '#include "lab2.h"': skipped when looking for precompiled header use
1>          Add directive to 'stdafx.h' or rebuild precompiled header

fixed by adding "#include "stdafx.h"


ninealmonds.cpp:
	This file contains all the method and functions required for the game

ninealmonds.h:
	This file contains class definition for the nine almonds game and also
	all of the function declarations. It also contains a struct that defines a game piece as
	well as other userful simple functions. Descriptions of the functions are included in the file.
	Return values and special game variables or constants are also defined here.
	
lab2.cpp:
	This file contains the main function which actually creates the game object and runs it.
	Also contains function for printing out program usage
	
lab2.h:
	contains error values related to the initialization of the game and also the command line
	arguments.
	
Running the game:
	use lab2.exe NineAlmonds
	
	When running turn(), the program asks the user for 2 inputs. If it is not a valid move (due to 
	a problem with either the first square or the second square), the user has to input BOTH values again. If
	it is an out of bounds error, no need to repeate older coordinate.
	
	If this is a continued turn (user already has one valid move), then only put in the second coordinate when
	prompted for coordinates. The starting is assumed to be the same almond you moved.
	
	If you choose to continue but find out that there are no valid moves you can make, you have to quit the game.
	Please plan ahead and only choose to continue when you can clearly see a valid move.
	
	"Coordinates Accepted" simply means that coordinates where properly read.
	"Coordinates outside game board" means exactly that and the user gets to input string again.
	"Couldn't parse string properly" means exactly that and the user gets to input string again.
	
	
Testing the game:
	command: lab2.exe
	output: usage: lab2.exe NineAlmonds
	
	command: lab2.exe game
	output: usage: lab2.exe NineAlmonds
	
	Both cases were handled properly.
	
	Prompt was tested with multiple variations of input strings like
	2,2
	2    2
	2,,,,,,,,6
	    3,, 2
	In all cases, the string was parsed correctly. Any combination of commas and spaces are handled properly.
	If more than 2 numbers are given, only the first 2 are considered. If less than 2 numbers then user is
	asked to input coordinates again.
	
	The game was played multiple times and seems to run properly, given that instructions are followed
	properly.
	
	Game runs properly and detects stalemate and completion properly.
	
	
	
	
