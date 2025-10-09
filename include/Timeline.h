#pragma once

#ifndef _TIMELINE_H_
#define _TIMELINE_H_

using namespace std;

#include <stdint.h>

class Board;
class Game;
struct BorderBoard;

//Timelines is a pointer itself and thats not good
//divide that into three parts
//Board* timeline

/*
uint16_t size; //example: 512  -> 256 moves
uint16_t currentTurn;//the present of current timeline
uint16_t firstBoard;
*/

//its already divided
//std::pair<Timeline,char* data>
class Timeline
{
public:
	//TODO Timeline should not be a pointer ~= (rearange other shit)
	//Timeline* is not efficient 
	static Timeline* CreateTimelinePointer(uint16_t SizeOfTimeLine, uint16_t SizeBoard, uint16_t indexFirstBoard, Board toSet);
private:
	//TODO make it a vector
	Board* timeline = nullptr; //array of pointers Board;
	uint16_t size; //example: 512  [white, black] * 256
	uint16_t currentTurn;//the present of current timeline
	uint16_t firstBoard;

public:
	//TODO this is gonna be used for modding
	rawpointer extradata;
private:
	void AllocateMemory();
	void SetSizeOfTimeline(uint16_t toSet);
public:
	Timeline() = default;
	Timeline(uint16_t SizeOfTimeLine_, uint16_t BoardSize, Board FirstBoard, uint16_t indexFirstBoard_);
	Timeline(uint16_t SizeOfTimeLine_);
	Timeline(Timeline&& move);
	~Timeline();// will be deleted, Game class clears that shit
	//true if timeline is allocated
	//false is it's not allocated
	operator bool() const;
	//DO make private
	void AllocateMemory(uint16_t size);

	void CreateNextTurn(uint16_t size, Game& game); 

	//not recommended maybe used to create a T-inf
	void CreateNextTurnSamePointer();

	void UndoTurn();//uses decrement
	bool ThereIsOneBoard(); //if(ThereIsOneBoard()) { //good when undoing moves }

	////////////////////////////////////////////////////////////
	Board GetBoard(uint16_t index);
	Board GetCurrentTurnBoard();
	Board* GetTimeline();
	uint16_t GetFirstBoardIndex();
	uint16_t GetSize();
	uint16_t GetCurrentTurn();

	////////////////////////////////////////////////////////////
	void SetCurrentTurn(uint16_t toSet);
	void SetIndexFirstBoard(uint16_t toSet);
	void SetBoard(uint16_t index, Board toSet);
	void SetJustCreatedTimeline(uint16_t index, Board toSet);
	////////////////////////////////////////////////////////////
	void IncrementCurrentTurn();
	void DecrementCurrentTurn();
	////////////////////////////////////////////////////////////
	//void Move(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2);

public:
	void PrintTimeline(BorderBoard border);
};
#endif // !_TIMELINE_H_