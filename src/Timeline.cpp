#include "Board.h"
#include "HelperStructs.h"
#include "usingnames.h"
#include "DataGame.h"
#include "Timeline.h"

Timeline* Timeline::CreateTimelinePointer(uint16_t SizeOfTimeLine, uint16_t SizeBoard, uint16_t indexFirstBoard, Board toSet)
{
	Timeline* toreturn = new Timeline(SizeOfTimeLine, SizeBoard, toSet, indexFirstBoard);
	return toreturn;
}

void Timeline::AllocateMemory()
{

	try { timeline = new Board[size]; }
	catch (std::bad_alloc& e) { cout << e.what(); }

	for (uint16_t i = 0; i < this->size; ++i){
		timeline[i].SetNull();
	}
	//TODO replace a loop (instead of indexing, use iterator)
}

void Timeline::AllocateMemory(uint16_t size)
{
	this->size = size;
	AllocateMemory();
}

Timeline::Timeline(uint16_t SizeOfTimeLine_, uint16_t BoardSize, Board FirstBoard, uint16_t indexFirstBoard_) {
	SetSizeOfTimeline(SizeOfTimeLine_);
	SetIndexFirstBoard(indexFirstBoard_);
	SetCurrentTurn(indexFirstBoard_);
	AllocateMemory();
	timeline[indexFirstBoard_] = FirstBoard;
}

Timeline::Timeline(uint16_t SizeOfTimeLine_)
{
	SetSizeOfTimeline(SizeOfTimeLine_);
	AllocateMemory();
}

//use std::move
//it is not a copy constructor
Timeline::Timeline(Timeline &&move)
{
	this->extradata = extradata;
	this->currentTurn = currentTurn;
	this->firstBoard = firstBoard;
	this->size = size;
	this->timeline = timeline;
}

Timeline::~Timeline() {
	//did not implement ~Board yet
}



void Timeline::CreateNextTurn(uint16_t Size,Game& chess)
{
	//TODO replace array with a vector
	if (currentTurn == size) { 
		throw "timeline overflow";
		return;
	} 

	Board CurrentBoard = timeline[currentTurn];
	IncrementCurrentTurn();

	try {
		#if NEWBOARDCONSTRUCTOR
			Board NextTurn = chess.CreateBoard(CurrentBoard,this);
		#else 
			Board NextTurn = CurrentBoard.GetDeepCopy(Size);//deep copy
		#endif 
		timeline[currentTurn] = NextTurn;
	}
	catch (std::bad_alloc& e) { 
		cout << e.what(); 
	}
}


void Timeline::CreateNextTurnSamePointer() {
	// has IncrementCurrentTurn();
	if (currentTurn + 5 == size) { cout << "Stack Overflow";  return; } //todo throw or create a new array
	Board temp = timeline[currentTurn];
	IncrementCurrentTurn();
	SetBoard(currentTurn, temp); //todo
}

bool Timeline::ThereIsOneBoard() {
	return currentTurn == firstBoard;
}

void Timeline::UndoTurn() {// has DecrementCurrentTurn();
	timeline[this->currentTurn].SetNullAndDelete();
	DecrementCurrentTurn();
}






uint16_t Timeline::GetCurrentTurn() { return this->currentTurn; }

Board Timeline::GetCurrentTurnBoard() { 
	if (this == nullptr) {
		throw "nullptr";
	}
	return timeline[currentTurn]; 
}
Board* Timeline::GetTimeline() { return this->timeline; }
uint16_t Timeline::GetFirstBoardIndex() { return this->firstBoard; }
Board Timeline::GetBoard(uint16_t index) { return this->timeline[index]; }
uint16_t Timeline::GetSize() { return this->size; }


void Timeline::SetCurrentTurn(uint16_t toSet) { currentTurn = toSet; }
void Timeline::SetIndexFirstBoard(uint16_t toSet) { this->firstBoard = toSet; }
void Timeline::SetSizeOfTimeline(uint16_t toSet) { this->size = toSet; }
void Timeline::SetBoard(uint16_t index, Board toSet) { this->timeline[index].SetBoardPointer(toSet.GetBoard()); }


void Timeline::SetJustCreatedTimeline(uint16_t index, Board board)
{
	this->SetCurrentTurn(index);
	this->SetIndexFirstBoard(index);
	this->SetBoard(index, board);
}


void Timeline::IncrementCurrentTurn() { ++this->currentTurn; }
void Timeline::DecrementCurrentTurn() { --this->currentTurn; }


void Timeline::PrintTimeline(BorderBoard border)
{
	
	cout << border.x;
	cout << " ";
	cout << border.y << endl;

	static const int RangeOfConsole = 13;
	for (int i = border.y - 1; i >= 0; --i) {
		uint16_t j = 0; int printedBoards = 0;
		while (j <= currentTurn && printedBoards < RangeOfConsole) {
			cout << "|";
			if (GetBoard(j).IsNull()) {
				++j; ++printedBoards;
				for (uint16_t i = 0; i < (border.x << 1) - 1; ++i) {
					cout << " ";
				}
				cout << "| ";
				continue;
			}
			GetBoard(j).PrintRank(uint8_t(i), border);
			cout << "|";
			if (j % 2 == 0 && j != currentTurn) { cout << "*"; }
			else { cout << " "; }
			++j; ++printedBoards;
		}
		cout << endl;
	}
}