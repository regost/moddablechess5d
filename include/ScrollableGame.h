#pragma once

#ifndef _A_
#define _A_

#include "Game.h"
#include <stdint.h>

struct Turn;
class Game;
struct MoveSet;
struct XYTL;
class LoadPgn;

template<typename Turn> struct ActionAndString;
template <typename T> class Node;


class ScrollableGame : public Game
{
public:
	Node<Turn>* primeNode;
	Node<Turn>* currentNode;

	vector<ActionAndString<Turn>>::iterator currentMove;
	size_t NextMoveIndex = 0;

	void SetNotation(string path);
	void NextMoveSet();
	void NextMoveSet(size_t ind);
	void PreviousMoveSet();
	void NextMove();
	void PreviousMove();
	void UndoSubmitInNotation();//undo submit in a tree rename
	void SubmitInNotation();//submit in a tree rename
	void WriteMoveOrFollow(Node<Turn>* movesetToWrite);
	void LoadFromPGN(const string& path);
	void LoadFromDatabase(string& path);
	void SaveAsDatabase(string& path);

	ScrollableGame(XYTL border, uint16_t WhiteBorder, uint16_t BlackBorder, uint16_t thePresent);

	void PrintNextMove();
private:
	void MakeMoveAndIncrement(vector<ActionAndString<Turn>>::iterator& currentMove);
	void UndoMoveAndDecrement(vector<ActionAndString<Turn>>::iterator& currentMove);
	void MakeAllMovesAndSetEnd(vector<ActionAndString<Turn>>& moveset, vector<ActionAndString<Turn>>::iterator& currentMove);
	void UndoAllMovesAndSetBegin(vector<ActionAndString<Turn>>& moveset, vector<ActionAndString<Turn>>::iterator& currentMove);
	static void SetIteratorEnd(vector<ActionAndString<Turn>>& moveset, vector<ActionAndString<Turn>>::iterator& currentMove);
	static void SetIteratorBegin(vector<ActionAndString<Turn>>& moveset, vector<ActionAndString<Turn>>::iterator& currentMove);



	//[1[2[3],4[5,6]],7[8,9[10]]]


};

#endif