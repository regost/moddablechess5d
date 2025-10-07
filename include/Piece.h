#pragma once


#ifndef _PIECE_H_
#define _PIECE_H_


#include <bitset>
#include <string>
#include <functional>
#include <stdint.h>

using namespace std;

class Game;
struct Turn;


class Piece
{
public:
	static float spriteSize;
	static Piece PieceArray[19];
	//static void SetSprites();

	string FEN;
	string PGN;
	//Sprite sprite;

	function<void(Game&, Turn)> makeMove;
	Piece(string FEN, string PGN, bool color_, bool isRoyal_, function<void(Game&, Turn)> Movement);
	Piece(string FEN, string PGN, uint8_t bitinfo);
	bool CanTakeThePiece(bool color);
	uint8_t bitinfo;
	bool color : 1;
	bool isRoyal : 1;
};

enum Info {
	isVoid = 1 << 0,//empty square
	hasColor = 1 << 1,//duck, wall, void - dont have
	isBlack = 1 << 2,//
	isRoyal = 1 << 3,//king, royal queen
	isPawnType = 1 << 4,//pawn, useful for atomic chess
	isCapturable = 1 << 5,//bedrock wall,duck arent
	changesOnMove = 1 << 6,//pawn,rook,king -> moved pawn,moved rook,moved king 
	hasRayMove = 1 << 7, //bishops, rooks, queens, and double step pawn's move counts as well
};
#endif