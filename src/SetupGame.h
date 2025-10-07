#include <map>
#include <utility>
#include <string>
#include "usingnames.h"

#ifndef _SetupGame_H_
#define _SetupGame_H_


class Game;
class VConstructor;
enum class Location;

class SetupGame {
	std::map<std::string, std::pair<VConstructor*, Location>> mapconstructor;
public:
	void Setup(Game& game);
	size_t GetSize(Location location);
private:
	void SetupConstructor(Game& game);

public:
	SetupGame(std::map<std::string, std::pair<VConstructor*, Location>> mapconstructor);
};

#endif // !_SetupGame_H_