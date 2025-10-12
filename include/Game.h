#pragma once

#ifndef _MULTIVERSE_H_
#define _MULTIVERSE_H_

#include <functional>
#include <vector>
#include <map>
#include <utility>
#include <variant>
#include <stdint.h>
#include "usingnames.h"
#include "DataGame.h"

//TODO move over these to cpp 

using namespace std;

class Timeline;
struct GameState;
struct Move;
struct MoveSet;
struct BorderBoard;
class Board;
class Piece;
struct XYTL;
class Game;
class VConstructor;
struct AlloctedType;
class ConstructCopy;
class ConstructSquares;
class SetupGame;

struct CanClick {
	function<bool(Game& game, XYTL click)> OnFirstClick;
	function<bool(Game& game, XYTL click)> OnSecondClick;
};

enum class Location {
	MULTIVERSE = 0,
	TIMELINE = 1,
	BOARD = 2
};

//std::pair<VConstructor*, uint8_t> _squares(new ConstructSquares(8, 8, 1), 2);



class Game
{
	friend SetupGame;
	friend VConstructor;
public:
	static const size_t MULTIVERSE = 0;
	static const size_t TIMELINE = 1;
	static const size_t BOARD = 2;


	static function<void(Game& game, Move& toMove)> _fBlackUndoTravel;
	static function<void(Game& game, Move& toMove)> _fWhiteUndoTravel;
	//static function<void(Game& game, Turn& toMove)> _fUndotravel[2];

public:
	Game(XYTL border, uint16_t WhiteBorder, uint16_t BlackBorder, uint16_t thePresent);
private:
	//timelines use state to be on range
	Timeline** multiverse;
public:
	//vector of pieces
	vector<Piece> pieces;//todo
	
/////////////////////////////////////////////////////////////////////////////////////
private:
	size_t sizebytes[3]{0,TIMELINESIZEBYTES,0};
	std::vector<VConstructor*> constructor[3];
	
	//void AddComponent(std::string name, VConstructor* obj, Location where);
public:
	rawpointer allocateddata;
/////////////////////////////////////////////////////////////////////////////////////
public:
	//does not contain timelines
	GameState state;
	//////////////////////////////////////////////////////////////////////////
	Board CreateBoard(Board old, std::variant<Timeline*, Board> extra);
	Timeline* CreateTimeline(Timeline* old, std::variant<Timeline*, Board> extra);

	void CreateTimeline(Timeline& created, Timeline* old, Board extra);
public:
	size_t GetBoardSize();
	GameState& GetState();

	Timeline& GetTimeline(uint16_t l);
	void SetTimeline(uint16_t l, Timeline* toSet);

	uint8_t GetPiece(XYTL& coordinates);

	Piece& GetPieceAddress(uint8_t piece);
	Piece& GetPieceAddress(XYTL& click);

	//void SetBoard(uint16_t l, uint16_t t, Board toSet);
	//void SetPiece(XYTL coordinates, uint8_t toSetPiece);

	//uint8_t IsGameEnded();
	bool CanSubmit();
	//bool IsExist(XYTL click);

	void Print();
	void PrintSize();
	void PrintState();
	
	uint16_t GetNumberOfTimelines();
	uint16_t CalculateThePresent();

	void Submit();
	void UndoSubmit();

	void MakeRegularMove(Move& toMove, uint8_t PieceToPlace); //makes a regular move but pawn rook becomes a moved rook
	void MakeRegularMove(Move& toMove);//makes a regular move
	void MakeMove(Move& toMove);//call a fuction from class piece
	void MakeMoveSet(vector<Move>& toMove);
	void MakeMoveSet(vector<Move>& toMove, vector<Move>::iterator& currentMove);

	void UndoMove(Move& toMove);
	void UndoMove(Move& toMove, function<void(Game& multiverse, Move& toMove)> undoTravel);
	void UndoMoveSet(vector<Move>& toMove, function<void(Game& multiverse, Move& toMove)> undoTravel);
	void UndoMoveSet(vector<Move>& toMove);
	void UndoMoveSet(vector<Move>& toMove, vector<Move>::iterator& currentMoveSet);
	void UndoMoveSet(vector<Move>& toMove, vector<Move>::iterator& currentMoveSet, function<void(Game& multiverse, Move& toMove)> undoTravel);

	//void Delete(Board board);
	//void Delete(Timeline* board);

	vector<void(*)(Board b, Move move)> onboardcreation;

	vector<CanClick> v_CanClick;
	vector<function<bool(Game& multiverse)>> v_CanSubmit;
	vector<function<bool(Game& multiverse)>> v_OnSubmit;

protected:



private:
	void PrintPart(uint16_t max, uint16_t min);
	void PrintLineBetweenTimelines(uint16_t t);
	void NotTimeTravelMove(uint8_t setPieceAfterMove, Move& turn);
	void OnWhiteCreatesTimeline(const uint16_t endT);
	void OnBlackCreatesTimeline(const uint16_t endT);
	Board MakeTravelAndGetBoard(const Move& turn, bool color);
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//vector<function<bool(Game& multiverse, Turn& onTurn)>> v_onTurnEnded;
	//function<uint8_t(Game& multiverse)> f_isGameEnded;

public:
	~Game();
};

#endif