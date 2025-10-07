#pragma once


#ifndef HELLO
#define HELLO


#include <list>
#include <string>
#include <algorithm>
#include <fstream>
#include <vector>
#include <stdint.h>

#include "Piece.h"
#include "Game.h"
#include "ScrollableGame.h"


using namespace std;

class Piece;
struct Turn;
struct XYTL;
struct BorderBoard;
class Game;
//void SetTimelineAndTurn(string& strMove, Game& chess, Coordinate& data);
//void SetPiece(string& strMove, Game& chess, Coordinate& data);
void SetXY(string& strMove, XYTL& data);
void FindChar(string& parse, size_t& i, char toFind);

struct XY {
	uint8_t x;
	uint8_t y;
	XY() = default;
	XY(uint8_t x, uint8_t y);
	bool operator==(XY& r_value);
};



struct XYTL : XY
{
	XYTL() = default;
	XYTL(uint8_t x, uint8_t y, uint16_t t, uint16_t l) : XY(x, y) { this->t = t; this->l = l; }
	uint16_t t;
	//should be int and add to the Game uint16_t shift
	uint16_t l;
	void Print();
	bool operator==(XYTL& r_value);
};


struct Turn {
	XYTL begin;
	XYTL end;
	Turn(uint8_t x1, uint8_t y1, uint16_t t1, uint16_t l1, uint8_t x2, uint8_t y2, uint16_t t2, uint16_t l2);
	Turn(const std::string Parse, uint16_t primeTimeline, uint16_t NegativeTurns, uint16_t isBlackMove);
	Turn() = default;
	~Turn() = default;
	bool operator==(Turn& r_value);
	bool isEqual(Turn& r_value);
	void Print();
	void MakeMove(Game& chess);
	void UndoMove(Game& chess);
	void GetString(Game& chess, string& str);
	void SetStringTurn(Game& chess, const string& parse,uint16_t color);
};

/*
struct TurnString : Turn {
	string strMove;
	TurnString(std::string Parse, uint16_t primeTimeline, uint16_t NegativeTurns, uint16_t isBlackMove);
	TurnString() = default;
	void SetString(Game& chess);
	void Print();
};
*/

//Turn -> TurnStrin

struct MoveSet {
	MoveSet() = default;
	std::vector<Turn> vectorOfTurns;
	void Add(Turn& turn);
	void Print();
	bool isEqual(MoveSet& r_value);
	bool operator==(MoveSet& r_value);

};


template <typename T> struct ActionAndString {
	ActionAndString(std::string Parse, uint16_t primeTimeline, uint16_t NegativeTurns, uint16_t isBlackMove);
	ActionAndString() = default;
	void Print();
	void SetString(Game& toset);
	bool operator==(ActionAndString<T>& r);
	T move;
	string str;
};

template<typename T>
inline ActionAndString<T>::ActionAndString(std::string Parse, uint16_t primeTimeline, uint16_t NegativeTurns, uint16_t isBlackMove)
{
	move = Turn(Parse, primeTimeline, NegativeTurns, isBlackMove);
	str = Parse;
}

template<typename T>
inline void ActionAndString<T>::Print()
{
	cout << str;
}

template<typename T>
inline void ActionAndString<T>::SetString(Game& chess)
{
	this->move.GetString(chess, str);
}

template<typename T>
inline bool ActionAndString<T>::operator==(ActionAndString<T>& r)
{
	return (this->move == r.move);
}
#endif // !HELLO