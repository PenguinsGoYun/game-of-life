// Author: Yeon Kim
// Conway's Game of Life

#include <iostream>
#include <fstream>
using namespace std;

#include "lifeboard.h"

Lifeboard option_a(Lifeboard);
Lifeboard option_r(Lifeboard);
Lifeboard option_n(Lifeboard);
void option_p(Lifeboard);

int main(int argc, char *argv[]) {
	if (argc == 1) {	// if user just types the exec
		
		system("clear");

		// INTERACTIVE MODE
		char userChoice = ' ';
		bool runMenu = true;
		Lifeboard world;
		
		while (runMenu) {
			
			cout << "MENU----------------------------------------------" << endl;
			cout << " a: add a new live cell" << endl;
			cout << " r: remove a cell" << endl;
			cout << " n: advance simulation to the next step" << endl;
			cout << " q: quit the program" << endl;
			cout << " p: play the game continuously (exit by CTRL-c)" << endl;
			cout << "--------------------------------------------------" << endl;
			cout << "Enter your option: ";
			
			cin >> userChoice;
			
			switch(userChoice) {
				case 'a': case 'A':
					world = option_a(world);
					break;
				case 'r': case 'R':
					world = option_r(world);
					break;
				case 'n': case 'N':
					world = option_n(world);
					break;
				case 'q': case 'Q':
					runMenu = false;
					break;
				case 'p': case 'P':
					option_p(world);
					break;
			}
		}
	} else if (argc == 2) {
		// BATCH MODE
		Lifeboard world;

		ifstream ifs;

		ifs.open(argv[1]);
		if(!ifs) {
			cout << "Error opening file: " << argv[1] << endl;
			return 1;
		}

		int x, y;
		char option;

		ifs >> option;
		while (option != 'p') {
			ifs >> x >> y;
			if (option == 'a') {
				world.genLife(x, y);
			} else if (option == 'r') {
				world.remLife(x, y);
			}
			ifs >> option;
		}
		
		world.playBoard();
	} else {
		cout << "ERROR: Too many arguments!" << endl;
		return 2;
	}

	cout << endl << "Hope you enjoyed. Good bye!" << endl;
	return 0;
}

Lifeboard option_a(Lifeboard world) {
	int x=0, y=0;
	cout << endl << "ADDING CELLS" << endl;
	
	// Check if coordinates are in range
	bool inRange = false;
	while (!inRange) {
		cout << "Enter your coordinates x and y: ";
		cin >> x >> y;
		if ( ((x>=0)&&(x<40)) && ((y>=0)&&(y<40)) ) {
			inRange = true;
		} else {
			cout << "Please enter values within the range 0-39." << endl;
		}
	}

	// Checks whether cell is already occupied
	if (world.checkAlive(x, y)) {
		system("clear");
		cout << "There is already a cell at x = " << x << " and y = " << y << "!" << endl << endl;
	} else {
		// Adds the cell via coordinate and display new board
		world.genLife(x, y);

		system("clear");
		world.displayLifeboard();
	
		cout << "Cell successfully added at point x = " << x << " and y = " << y << "." << endl << endl;
	}
	return world;
}

Lifeboard option_r(Lifeboard world) {
	int x=0, y=0;
	cout << endl << "REMOVING CELLS" << endl;
	
	// Check if coordinates are in range
	bool inRange = false;
	while (!inRange) {
		cout << "Enter your coordinates x and y: ";
		cin >> x >> y;
		if ( ((x>=0)&&(x<40)) && ((y>=0)&&(y<40)) ) {
			inRange = true;
		} else {
			cout << "Please enter values within the range 0-39." << endl;
		}
	}

	// Checks if there is any cell to remove
	if (world.checkEmpty(x, y)) {
		system("clear");
		cout << "There is no cell to remove at x = " << x << " and y = " << y << "!" << endl << endl;
	} else {
		// Removes the cell from coordinate and display new board
		world.remLife(x, y);

		system("clear");
		world.displayLifeboard();
		
		cout << "Cell successfully removed at point x = " << x << " and y = " << y << "." << endl << endl;
	}
	return world;
}

Lifeboard option_n(Lifeboard world) {
	world.nextBoard();
	
	system("clear");
	world.displayLifeboard();

	return world;
}
void option_p(Lifeboard world) {
	world.playBoard();
}
