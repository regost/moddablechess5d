#pragma once

#ifndef _A_
#define _A_

#include "Game.h"
#include <stdint.h>

struct Move;
class Game;
struct MoveSet;
struct XYTL;
class LoadPgn;

template<typename Move> struct ActionAndString;
template <typename T> class Node;


class ScrollableGame : public Game
{
public:
	Node<Move>* primeNode;
	Node<Move>* currentNode;

	vector<ActionAndString<Move>>::iterator currentMove;
	size_t NextMoveIndex = 0;

	void SetNotation(string path);
	void NextMoveSet();
	void NextMoveSet(size_t ind);
	void PreviousMoveSet();
	void NextMove();
	void PreviousMove();
	void UndoSubmitInNotation();//undo submit in a tree rename
	void SubmitInNotation();//submit in a tree rename
	void WriteMoveOrFollow(Node<Move>* movesetToWrite);
	void LoadFromPGN(const string& path);
	void LoadFromDatabase(const string& path);
	void SaveAsDatabase(const string& path);

	ScrollableGame(XYTL border, uint16_t WhiteBorder, uint16_t BlackBorder, uint16_t thePresent);

	void PrintNextMove();
private:
	void MakeMoveAndIncrement(vector<ActionAndString<Move>>::iterator& currentMove);
	void UndoMoveAndDecrement(vector<ActionAndString<Move>>::iterator& currentMove);
	void MakeAllMovesAndSetEnd(vector<ActionAndString<Move>>& moveset, vector<ActionAndString<Move>>::iterator& currentMove);
	void UndoAllMovesAndSetBegin(vector<ActionAndString<Move>>& moveset, vector<ActionAndString<Move>>::iterator& currentMove);
	static void SetIteratorEnd(vector<ActionAndString<Move>>& moveset, vector<ActionAndString<Move>>::iterator& currentMove);
	static void SetIteratorBegin(vector<ActionAndString<Move>>& moveset, vector<ActionAndString<Move>>::iterator& currentMove);



	//[1[2[3],4[5,6]],7[8,9[10]]]


};

#endif