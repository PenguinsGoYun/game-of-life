// Author: Yeon Kim
// lifeboard.cpp
// Conway's Game of Life example

#include <iostream>
using namespace std;

#include <unistd.h>
#include <cstdlib>

#include "lifeboard.h"

// Constructors, Destructor
Lifeboard::Lifeboard() {
	resetBoard();
}
Lifeboard::~Lifeboard() {}

// Methods
// REMOVE AND ADD CELLS
void Lifeboard::remLife(int a, int b) {
	board[a][b] = ' ';
}
void Lifeboard::genLife(int a, int b) {
	board[a][b] = 'X';
}

// RESET BOARD
void Lifeboard::resetBoard() {
	for (int i = 0; i < x; i++) {
		for (int j = 0; j < y; j++) {
			remLife(i, j);
		}
	}
}

// CHECK CELL
// TREAT ALL EDGES AS DEAD
bool Lifeboard::checkAlive(int a, int b) {
	if ( (a<0 || a>=x) || (b<0 || b>=y) ) {
		return false;
	}

	if (board[a][b] == 'X') {
		return true;
	} else {
		return false;
	}
}
bool Lifeboard::checkEmpty(int a, int b) {
	if ( (a<0 || a>=x) || (b<0 || b>=y) ) {
		return true;
	}

	if (board[a][b] == ' ') {
		return true;
	} else {
		return false;
	}
}
bool Lifeboard::checkTempAlive(int a, int b) {
	if ( (a<0 || a>=x) || (b<0 || b>=y) ) {
		return false;
	}

	if (tempBoard[a][b] == 'X') {
		return true;
	} else {
		return false;
	}
}
bool Lifeboard::checkTempEmpty(int a, int b) {
	if ( (a<0 || a>=x) || (b<0 || b>=y) ) {
		return true;
	}

	if (tempBoard[a][b] == ' ') {
		return true;
	} else {
		return false;
	}
}


// GAME RULES
// If empty cell has exactly 3 neighbors then new life in that cell (reproduction)
void Lifeboard::gen_repro(int a, int b) {
	if (checkTempEmpty(a, b)) {
		int nb = findNeighbors(a, b);
		if (nb == 3) {
			genLife(a, b);
		}
	}
}
// If filled cell has 1 or no neighbor then remove life (death by underpopulation)
// If filled cell has 4 or more neighbors then remove life (death by overpopulation)
void Lifeboard::rem_notSurvive(int a, int b) {
	if (checkTempAlive(a, b)) {
		int nb = findNeighbors(a, b);
		if ( (nb <= 1) || (nb >= 4) ) {
			remLife(a, b);
		}
	}
}
// Finds the number of neighbors per cell
int Lifeboard::findNeighbors(int a, int b) {
	int ul=0, u=0, ur=0, l=0, r=0, dl=0, d=0, dr=0;
	if (checkTempAlive((a-1), (b-1))) { ul=1; }
	if (checkTempAlive((a-1), b)) { u=1; }
	if (checkTempAlive((a-1), (b+1))) { ur=1; }
		
	if (checkTempAlive(a, (b-1))) { l=1; }
	if (checkTempAlive(a, (b+1))) { r=1; }

	if (checkTempAlive((a+1), (b-1))) { dl=1; }
	if (checkTempAlive((a+1), b)) { d=1; }
	if (checkTempAlive((a+1), (b+1))) { dr=1; }
		
	int neighbors = ul + u + ur + l + r + dl + d + dr;

	return neighbors;
}

// DISPLAY BOARD
void Lifeboard::displayLifeboard() {
	cout << "+";
	for (int i = 0; i < (x); i++) {
		cout << "-";
	}
	cout << "+";
	cout << endl;

	for (int i = 0; i < x; i++) {
		cout << "|";
		for (int j = 0; j < y; j++) {
			cout << board[i][j];
		}
		cout << "|" << endl;
	}

	cout << "+";
	for (int i = 0; i < (x); i++) {
		cout << "-";
	}
	cout << "+";
	cout << endl;
}

// Advance to next instance of board by applying game rules
void Lifeboard::nextBoard() {
	for (int i = 0; i < x; i++) {
		for (int j = 0; j < y; j++) {
			tempBoard[i][j] = board[i][j];
		}
	}
	for (int i = 0; i < x; i++) {
		for (int j = 0; j < y; j++) {
			gen_repro(i, j);
			rem_notSurvive(i, j);
		}
	}
}
// Infinitely play and display the board until the user force quits
void Lifeboard::playBoard() {
	while (true) {
		system("clear");
		nextBoard();
		displayLifeboard();
		usleep(200000);
	}
}
