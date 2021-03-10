#include "MapLoader/MapLoader.h"
#include "Player.h"

int main()
{
	MapLoader* mapLoader;
	mapLoader = startGame();

	delete mapLoader;

	vector<Player*> players = Player::getPlayerList();
	for (int i = 0; i < Player::getPlayerNum(); i++)
	{
		delete players[i];
	}
	return 0;
}