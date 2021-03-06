﻿#include "Adapter.h"
/*Adapter translates messages sent by the server into types congruent 
with our internal Game structure and vice versa*/

Adapter::Adapter() {}

Adapter::~Adapter() {}

/*Converts an tile number to the appropriate tile string
GAME->SERVER*/
std::string Adapter::tileToExpr(int i){
	std::string tiles[28] = {"JJJJ-", "JJJJX", "JJTJX", "TTTT-", "TJTJ-",
		"TJJT-" , "TJTT-", "LLLL-", "JLLL-" , "LLJJ-", "JLJL-", "LJLJ-",
		"LJJJ-", "JLLJ-", "TLJT-", "TLJTP", "JLTT-", "JLTTB", "TLTJ-" ,
		"TLTJD", "TLLL-", "TLTT-" , "TLTTP", "TLLT-" , "TLLTB" , "LJTJ-", "LJTJD", "TLLLC"};
	return tiles[i-1];
}

/*Converts a tile string to the appropriate tile number
SERVER->GAME*/
int Adapter::exprToTile(std::string &expr)
{
	transform(expr.begin(), expr.end(), expr.begin(), toupper);
	if (expr == "JJJJ-")
	{
		return 1;
	}
	if (expr == "JJJJX")
	{
		return 2;
	}
	if (expr == "JJTJX")
	{
		return 3;
	}
	if (expr == "TTTT-")
	{
		return 4;
	}
	if (expr == "TJTJ-")
	{
		return 5;
	}
	if (expr == "TJJT-")
	{
		return 6;
	}
	if (expr == "TJTT-")
	{
		return 7;
	}
	if (expr == "LLLL-")
	{
		return 8;
	}
	if (expr == "JLLL-")
	{
		return 9;
	}
	if (expr == "LLJJ-")
	{
		return 10;
	}
	if (expr == "JLJL-")
	{
		return 11;
	}
	if (expr == "LJLJ-")
	{
		return 12;
	}
	if (expr == "LJJJ-")
	{
		return 13;
	}
	if (expr == "JLLJ-")
	{
		return 14;
	}
	if (expr == "TLJT-")
	{
		return 15;
	}
	if (expr == "TLJTP")
	{
		return 16;
	}
	if (expr == "JLTT-")
	{
		return 17;
	}
	if (expr == "JLTTB")
	{
		return 18;
	}
	if (expr == "TLTJ-")
	{
		return 19;
	}
	if (expr == "TLTJD")
	{
		return 20;
	}
	if (expr == "TLLL-")
	{
		return 21;
	}
	if (expr == "TLTT-")
	{
		return 22;
	}
	if (expr == "TLTTP")
	{
		return 23;
	}
	if (expr == "TLLT-")
	{
		return 24;
	}
	if (expr == "TLLTB")
	{
		return 25;
	}
	if (expr == "LJTJ-")
	{
		return 26;
	}
	if (expr == "LJTJD")
	{
		return 27;
	}
	if (expr == "TLLLC")
	{
		return 28;
	}
	return -1;

}

/*Converts number of rotations to a degree of rotation
GAME->SERVER*/
int Adapter::numRotations(const int x) {
	int numRotations = 0;
	if (x == 90)
		return numRotations = 1;
	if (x == 180)
		return numRotations = 2;
	if (x == 270)
		return numRotations = 3;

	return numRotations;
}
/*Parses through message reccieved by the server and stores each word in a 
string vector. */
std::vector<std::string> Adapter::convertExpression(const std::string& expr) {
	// Convert to stream
	std::istringstream buf(expr);
	std::istream_iterator<std::string> begin(buf), end;

	// Store in vector and return
	std::vector<std::string> myV(begin, end);
	return myV;
}

/*Returns the appropriate value for the given prop*/
std::string Adapter::get(const std::string& prop) {
	if (prop == "pid")
		return this->playerID;
	if (prop == "rid")
		return this->roundID;
	if (prop == "score")
		return this->score;
	if (prop == "challenges")
		return this->numChallenges;
	if (prop == "rounds")
		return this->numRounds;
	if (prop == "ptime")
		return this->planTime;
	if (prop == "mtime")
		return this->moveTime;

	return "Error";
}

/*Sets the appropriate attribute(chosen by prop) to the string const*/
void Adapter::set(const std::string& prop, const std::string value) {
	if (prop == "pid")
		this->playerID = value;
	if (prop == "rid")
		this->roundID = value;
	if (prop == "score")
		this->score = value;
	if (prop == "challenges")
		this->numChallenges = value;
	if (prop == "rounds")
		this->numRounds = value;
	if (prop == "ptime")
		this->planTime = value;
	if (prop == "mtime")
		this->moveTime = value;
}

/*Returns the tile string at the given index, also contains error check*/
std::string Adapter::getTileString(const int& index) {
	// Error check
	if (index < 0 || index > this->tileList.size())
		return "Error";

	return this->tileList[index];
}

/*Converts coordinates given by the server to the system of coordinates used in 
game logic
SERVER->CLIENT*/
std::pair<int, int> Adapter::convertCoordinates(int x, int y)  
{
	int row = 72 - y;
	int col = x + 72;
	return std::pair<int, int> (row, col);
}

/*Converts coordinates given by client to those that can be understood by the 
server
CLIENT->SERVER*/
std::pair<int, int> Adapter::convertCoordinates(std::pair<int, int> location) //convert from client to server
{
	int x = location.second - 72;
	int y = 72 - location.first;
	return std::pair<int, int>(x, y);
}

/*Converts zone coordinates given by client to zone number 
used by server
CLIENT->SERVER*/
int Adapter::convertZone(std::pair<int, int> location)
{
	int i = location.first;
	int j = location.second;

	if(i == 0)
	{
		if(j == 0) return 1;
		else if(j == 1) return 2;
		else if(j == 2) return 3;
	}
	else if(i == 1)
	{
		if(j == 0) return 4;
		else if(j == 1) return 5;
		else if(j == 2) return 6;
	}
	else if(i == 2)
	{
		if(j == 0) return 7;
		else if(j == 1) return 8;
		else if(j == 2) return 9;
	}
}

/*Converts zone number given by server to coordinates used by client
SERVER->CLIENT*/
std::pair<int, int> Adapter::convertZone(int spot)
{
	if(spot == 1) return std::pair<int, int>(0,0);
	else if(spot == 2) return std::pair<int, int>(0,1);
	else if(spot == 3) return std::pair<int, int>(0,2);
	else if(spot == 4) return std::pair<int, int>(1,0);
	else if(spot == 5) return std::pair<int, int>(1,1);
	else if(spot == 6) return std::pair<int, int>(1,2);
	else if(spot == 7) return std::pair<int, int>(2,0);
	else if(spot == 8) return std::pair<int, int>(2,1);
	else if(spot == 9) return std::pair<int, int>(2,2);
}

/*Reads the first word of the message sent by server then calls the appropriate 
parsing method*/
values_t Adapter::translate(std::string message)
{
	values_t output;
	if (message.compare(0,8,"STARTING") == 0) //STARTING TILE IS <tile> AT <x> <y> <orientation>
	{
		return parseStartingTile(message);
	}
	if (message.compare(0,3,"THE") == 0) //THE REMAINING <number_tiles> TILES ARE [ <tiles> ]
	{
	  return parseTileStack(message);
	}
	if (message.compare(0,5,"MATCH") == 0) // MATCH BEGINS IN <timeplan> SECONDS
	{
	  return parseMatch(message);
	}
	if (message.compare(0,4,"MAKE") == 0) // MAKE YOUR MOVE IN GAME <gid> WITHIN <timemove> SECOND: MOVE <#> PLACE <tile>
	{
	  return parseMakeMove(message);
	}
	if (message.compare(0,4,"GAME") == 0) // INITIAL ACCESS TO A GAME MESSAGE
	{
	  return parseGameMove(message);
	}
	return output;
}

/*Parses message sent by server, returns info about starting tile
Called by adapter::translate()*/
values_t Adapter::parseStartingTile(std::string message)
{
	std::string starting_tile, substr;
	values_t out;

	starting_tile = message.substr(17, message.find(" AT")-17); //get string where tile description starts until before " AT"
	out.tile_num = exprToTile(starting_tile);
	substr = message.substr(message.find("AT ")+3,message.find(" ", message.find("AT ")+3, 1)-message.find("AT ")-3); //get first string integer
	out.i =  stoi(substr);
	substr = message.erase(0, message.find(substr) + substr.length() + 1); //get string with last two integers
	out.j = stoi(substr.substr(0,substr.find(" ")));
	substr = substr.erase(0,substr.find(" ")+1); //get string with last int
	substr = substr.substr(0,std::string::npos); //get the last integer
	out.rotation = stoi(substr);
	return out;
}

/*Parses message sent by server, returns info about tile stack
Called by adapter::translate()*/
values_t Adapter::parseTileStack(std::string message)
{
  std::string token, substr;
  std::string delimiter = " "; //delimiter between tiles
  size_t pos = 0;
  std::vector<int> tile_stack;
  int tile_num;
  values_t out;

  substr = message.substr(14,message.find(" TILE")-14); //get first string integer
  out.number_of_tiles = stoi(substr);
  substr = message.erase(0, message.find("[")+1); //get string starting with the first tile to start tokeninzing tiles
  for (int i = 0; i < out.number_of_tiles; i++)
  {
  	pos = substr.find(" ");
  	token = substr.substr(0, pos);
  	substr.erase(0, pos + 1);
  	tile_num = exprToTile(token);
  	tile_stack.push_back(tile_num);
  }
  return out;
}

/*Parses message sent by server, returns info about match
Called by adapter::translate()*/
values_t Adapter::parseMatch(std::string message)
{
  values_t out;
  return out;
}

/*Parses message sent by server, returns info about current move
Called by adapter::translate()*/
values_t Adapter::parseMakeMove(std::string message)
{
  std::istringstream buffer(message);
  std::istream_iterator<std::string> beg(buffer), end;

  std::vector<std::string> messageWords(beg,end);   //Put all the words from the message into a vector

  std::string gameId = messageWords[5];       // Get the gameId from the string
  std::string tileType = messageWords[messageWords.size()-1]; //get the tileType that we are about to place
  std::string moveNum = messageWords[messageWords.size()-3];  //get the move number

  values_t out;
  out.gameId = gameId;
  out.tile_num = exprToTile(tileType);
  out.moveNumber = moveNum;

  return out;
}

/*Parses message sent by server, returns info about game state
Called by adapter::translate()*/
values_t Adapter::parseGameMove(std::string message)
{
  values_t out;

  std::istringstream buffer(message);
  std::istream_iterator<std::string> beg(buffer), end;

  std::vector<std::string> messageWords(beg,end);   //Put all the words from the message into a vector

  std::string gameId = messageWords[1];
  out.gameId = gameId;
  std::string temp = messageWords[3];
  out.moveNumber = temp;

  if(messageWords[6] == "FORFEITED:")  //Check to see if the other player forfeited
  {
    out.forfeit = -1;
    return out;
  }
  else if(messageWords[6] == "PLACED")  //Check to see if the other player forfeited
  {
	std::string playerId = messageWords[5];
    std::string tileType = messageWords[7];
    int xCoord = stoi(messageWords[9]);
    int yCoord = stoi(messageWords[10]);
    int rotation = stoi(messageWords[11]);
    std::string animalType = messageWords[12];

	out.playerId = playerId;

	out.coordinates = convertCoordinates(xCoord, yCoord);
	out.rotation = numRotations(rotation);
	out.tile_num = exprToTile(tileType);
	if (animalType == "CROCODILE")
		out.croc = true;
	else
		out.croc = false;
	if (animalType == "TIGER")
		out.tiger = true;
	else
		out.tiger = false;


    if(messageWords.size() == 14 && animalType == "TIGER"){
      int tigerZone = stoi(messageWords[13]);
      out.tiger_spot = convertZone(tigerZone);   //Set the zone where the meeple is placed in the tile
    }

    return out;
  }
}
