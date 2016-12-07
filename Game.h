#ifndef GAME_H
#define GAME_H

#include "Player.h"
#include "Board.h"
#include "Tile_Structure/Block.h"
#include "Tile_Structure/TileStack.h"

class Game{

public:
	Game(std::string gameId, Player player1, Player player2, TileStack t,  Tile startingTile, std::pair<int,int> startingCoordinates);
	Game();
	~Game();

	//ignore this it was mainly for debugging
	void play();
	//function for the other player making a move
	void enemyMove(Tile tile, int i, int j, int orientation, bool goat, bool tiger, bool croc, std::pair<int,int> tigerSpot);
	//main function for our ai to make a move
	std::string makeMove(Tile, std::string);
	// meeple subsection of ai the tile placment part is in board
	std::string meepleAi(int i, int j);
	// goat subsection of ai the tile placement part is in board
	std::string goatAi(int i, int j);
	//ignore this
	void updateBoard();
	// printint the board to a text file for the gui
	void printToTextFile(Board);
	//setter
	void setID(std::string identification) { gameId = identification; }
	//getter
	std::string getID() { return gameId; }

	Board gameboard;
private:
	// get points for a place to place a tiger
	int structurePoints(Structure structure);

	int numMeeples, numGoats;
	std::string gameId;
	Player player1;
	Player player2;
	TileStack tileStack;
	Tile* currentTile;
};

#endif
