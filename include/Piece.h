#pragma once


#ifndef _PIECE_H_
#define _PIECE_H_


#include <bitset>
#include <string>
#include <functional>
#include <stdint.h>
#include "Enum.h"

using namespace std;

class Game;
struct Move;
class Color;

class Piece
{
public:
	static float spriteSize;
	static Piece PieceArray[19];
	//static void SetSprites();

	string FEN;
	string PGN;
	//Sprite sprite;

	function<void(Game&, Move)> makeMove;
	Piece(string FEN, string PGN, Color color_, bool isRoyal_, function<void(Game&, Move)> Movement);
	Piece(string FEN, string PGN, uint8_t bitinfo);
	bool CanTakeThePiece(bool color);
	uint8_t bitinfo;
	Color color;
	bool isRoyal : 1;
};

enum Info {
	isVoid = 1 << 0,//empty square
	hasColor = 1 << 1,//duck, wall, void - dont have
	isBlack = 1 << 2,//
	isRoyal = 1 << 3,//king, royal queen
	isPawnType = 1 << 4,//pawn, useful for atomic chess
	isCapturable = 1 << 5,//bedrock wall,duck arent
};
#endif