

#include <cstring>
#include <iostream>
#include "Board.h"
#include "Piece.h"
#include "HelperStructs.h"
#include "DataGame.h"
#include "usingnames.h"

const uint8_t MINUS1 = 255;

//string Board::stringPieces[33] = { " ","p*","P*","p","P","r","R","r*","R*","n","N","b","B","q","Q","k*","K*","k","K","s","S","c","C","y","Y","d","D","u","U","w*","W*","w","W"};



Board::Board() = default;

Board::Board(uint8_t* toCopy, uint16_t SizeBoard) {
	this->boardptr = new uint8_t[SizeBoard];

	if (!toCopy) {
		throw "error Board::Board";
	}

	std::memcpy(this->boardptr, toCopy, SizeBoard);//copy
}

Board::Board(Board toCopy, uint16_t SizeBoard) {
	this->boardptr = new uint8_t[SizeBoard];
	std::memcpy(this->boardptr, toCopy.boardptr, SizeBoard);//copy
}
Board::Board(size_t sizebytes)
{
	this->boardptr = new uint8_t[sizebytes];
}

Board::Board(uint8_t* toCopy) {
	this->boardptr = toCopy;
}

uint8_t Board::GetSquare(uint8_t x, uint8_t y, BorderBoard border) {

	//cout << "x: " << int(x) << " y:" << int(y) << endl;
	return boardptr[y * border.y + x];
}

Board Board::GetDeepCopy(uint16_t size)//only board
{
	Board toReturn(this->boardptr, size);
	return toReturn;
}

void Board::SetBoardPointer(uint8_t* ptr)
{
	this->boardptr = ptr;
}


void Board::SetSquare(uint8_t piece, uint8_t x, uint8_t y, BorderBoard border) { boardptr[(y * border.y) + x] = piece; }

void Board::PrintRank(uint8_t Rank, BorderBoard border)
{
	for (uint8_t i = 0; i < border.x - 1; ++i) {
		uint8_t piece = GetSquare(i, Rank, border);
		cout << (Piece::PieceArray[piece]).FEN[0] << " ";
	}
	cout << (Piece::PieceArray[GetSquare(border.x - 1, Rank, border)]).FEN[0];
}

void Board::PrintBoard(BorderBoard border)
{
	for (uint8_t i = border.y - 1; i != MINUS1; --i) {
		PrintRank(i, border);
		cout << endl;
	}
}

Board::operator rawpointer()
{
	return reinterpret_cast<rawpointer>(this);
}

//Board::operator rawpointer()
//{
//	//return static_cast<char*>(this);
//}

void Board::SetNull() { this->boardptr = nullptr; }
bool Board::IsNull() { return this->boardptr == nullptr; }
void Board::SetNullAndDelete() { delete this->boardptr; this->boardptr = nullptr; }
uint8_t* Board::GetBoard() { return boardptr; }

//void Board::Draw(RenderWindow& window, BorderBoard border, float step, float x, float y) {
//	for (uint8_t i = 0; i < border.MaxX; ++i) {
//		for (uint8_t j = 0; j < border.MaxY; ++j) {
//			if (GetSquare(j, i, border) == 0) { continue; }
//			Piece::PieceArray[GetSquare(j, i, border)].sprite.setPosition(Vector2f(x + float(j) * step, y + float(i) * step));
//			window.draw(Piece::PieceArray[GetSquare(j, i, border)].sprite);
//		}
//	}
//}



uint8_t* p_StartingPosition8x8 = new uint8_t[64]
{
	6,10,12,14,16,12,10,6,
	2,2,2 ,2 ,2 ,2 ,2,2,
	0,0,0 ,0 ,0 ,0 ,0,0,
	0,0,0 ,0 ,0 ,0 ,0,0,
	0,0,0 ,0 ,0 ,0 ,0,0,
	0,0,0 ,0 ,0 ,0 ,0,0,
	1,1,1 ,1 ,1 ,1 ,1,1,
	5,9,11,13,15,11,9,5
};

uint8_t* p_StartingPosition9x9 = new uint8_t[81]
{
	6,10,12,16,14,16,10,12,6,
	2,2,2 ,2 ,2 ,2 ,2,2,2,
	0,0,0 ,0 ,0 ,0 ,0,0,0,
	0,0,0 ,0 ,0 ,0 ,0,0,0,
	0,0,0 ,0 ,0 ,0 ,0,0,0,
	0,0,0 ,0 ,0 ,0 ,0,0,0,
	0,0,0 ,0 ,0 ,0 ,0,0,0,
	1,1,1 ,1 ,1 ,1 ,1,1,1,
	5,11,9,15,13,15,11,9,5
};

uint8_t* p_KnightPosition5x5 = new uint8_t[25]
{
	6,10,16,10,6,
	2, 2, 2,2, 2,
	0,0,0 ,0 ,0 ,
	1,1,1 ,1 ,1,
	5,9,15,9,5
};

Board Board::StartingPosition9x9(p_StartingPosition9x9);
Board Board::StartingPosition8x8(p_StartingPosition8x8);
Board Board::KnightPosition5x5(p_KnightPosition5x5);
Board Board::Null(nullptr);