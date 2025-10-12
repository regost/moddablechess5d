#pragma once

#ifndef _LOAD_H_
#define _LOAD_H_

#include <iostream>
#include <string>
#include <list>
#include <string_view>
#include <stdint.h>

#include "ScrollableGame.h"
#include "HelperStructs.h"

using namespace std;

class Game;
struct MoveSet;
struct TurnString;
//template<typename Turn> class Node;

class LoadPgn
{
public:
	static void ParsePNGfile(Node<Move>* listOfMoves, const string& path, uint16_t primeTimeline, uint16_t negativeTurns);
	static void SetPosition(list<MoveSet>& listOfMoves, Game& game);
};

#endif