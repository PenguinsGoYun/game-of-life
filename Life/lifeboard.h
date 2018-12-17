// lifeboard.h

const int x = 40, y = 40;

class Lifeboard {
  public:
	// Constructors, Destructor
 	Lifeboard();
	~Lifeboard();
	// Setup functions
	void remLife(int, int);
	void genLife(int, int);
	// Check functions
	bool checkAlive(int, int);
	bool checkEmpty(int, int);
	bool checkTempAlive(int, int);
	bool checkTempEmpty(int, int);
	// Game rules
	void gen_repro(int, int);
	void rem_notSurvive(int, int);
	int findNeighbors(int, int);
	// Utility functions
	void resetBoard();
	void displayLifeboard();
	// Play functions
	void nextBoard();
	void playBoard();
  private:
	char board[x][y];
	char tempBoard[x][y];
};
