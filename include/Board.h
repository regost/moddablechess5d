#pragma once

#ifndef _BOARD_H
#define _BOARD_H 

//#include "Piece.h"
#include <iostream>
#include <string>
#include <stdint.h>
#include "usingnames.h"

using namespace std;

class Piece;
struct BorderBoard;
class Board;

class Board
{
public:
	static Board StartingPosition9x9;
	static Board StartingPosition8x8;
	static Board KnightPosition5x5;
	static Board Null;
public:
	Board();
	Board(uint8_t* toCopy);
	Board(uint8_t* toCopy, uint16_t SizeBoard);
	Board(Board CopyOnlyPieces, uint16_t SizeBoard);
	Board(size_t sizebytes);
	//~Board(); idk bc Game class clears that shit
private:
	uint8_t* boardptr;
public:
	uint8_t GetSquare(uint8_t x, uint8_t y, BorderBoard border); //get the piece
	uint8_t* GetBoard();
	Board GetDeepCopy(uint16_t size);

	void SetSquare(uint8_t piece, uint8_t x, uint8_t y, BorderBoard border);//set the piece
	void SetNull();
	void SetNullAndDelete();
	void SetBoardPointer(uint8_t* ptr);
	bool IsNull();

	//(starting position) 
	// PrintRank(0) -> "R N B Q K B N R" 
	// PrintRank(1) -> "P P P P P P P P"
	// PrintRank(2) -> "               "
	void PrintRank(uint8_t Rank, BorderBoard border);
	void PrintBoard(BorderBoard border);

	operator rawpointer();

	

};

#endif