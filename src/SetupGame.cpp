#include "SetupGame.h"
#include "Game.h"
#include "VConstructor.h"

void SetupGame::SetupConstructor(Game& game)
{
	for (auto& it : this->mapconstructor) {
		const std::pair<VConstructor*, Location> temp = it.second;
		const size_t place = size_t(temp.second);
		temp.first->setposition(game.sizebytes[place] * 8);
		if (temp.first == nullptr) {
			throw "error nullptr";
		}
		game.constructor[place].push_back(temp.first);
		game.sizebytes[place] += temp.first->sizebytes;
	}
}

SetupGame::SetupGame(std::map<std::string, std::pair<VConstructor*, Location>> mapconstructor)
{
	this->mapconstructor = mapconstructor;
}



void SetupGame::Setup(Game& game)
{
	this->SetupConstructor(game);
}

