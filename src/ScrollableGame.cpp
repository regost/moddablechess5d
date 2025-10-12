

#include "ScrollableGame.h"
#include "LoadPgn.h"
#include "Game.h"
#include "Node.cpp"

// moveset(1 2 3 end) moveset(1 2 end)
//                ∧  submit() ∧ 1st move isnt played
//                |           | 

// moveset(1 2 3 end) moveset(1 2 end)
//                ∧  nextmove() ∧ 1st move is played
//                |             | 2nd move isnt played

void ScrollableGame::SetNotation(string path) {
	LoadPgn::ParsePNGfile(this->primeNode, path, this->state.PrimeTimeline, this->state.NumberOfNegativeTurns);
}


void ScrollableGame::NextMoveSet() {
	NextMoveSet(0);
}

void ScrollableGame::NextMoveSet(size_t ind) {


	if (currentMove == currentNode->data.end()) {
		if (currentNode->isLast()) { return; }

		currentNode = currentNode->vectorOfNodes[ind];
		currentMove = currentNode->data.begin();
	}
	MakeAllMovesAndSetEnd(currentNode->data, currentMove);
	Submit();

}

void ScrollableGame::PreviousMoveSet() {

	if (this->currentNode->isFirst()) { return; }
	if (currentMove == currentNode->data.end()) {
		UndoSubmit();
	}
	UndoAllMovesAndSetBegin(currentNode->data, currentMove);
	currentNode = currentNode->p_previous;
	currentMove = currentNode->data.end();

}


void ScrollableGame::NextMove() {
	cout << "isnt implemented";
}


void ScrollableGame::PreviousMove() {
	cout << "isnt implemented";
}


void ScrollableGame::UndoSubmitInNotation() {

	UndoSubmit();
	currentNode = currentNode->p_previous;
	currentMove = currentNode->data.end();

}

void ScrollableGame::SubmitInNotation()
{

	currentNode = currentNode->vectorOfNodes[0];
	currentMove = currentNode->data.begin();

}


void ScrollableGame::WriteMoveOrFollow(Node<Move>* movesetToWrite)
{
	Node<Move>* tofind = currentNode->Find(*movesetToWrite);
	if (tofind == nullptr) {
		currentNode->AddAndSetLast(movesetToWrite);
		currentNode = movesetToWrite;
		currentMove = currentNode->data.end();
		return;
	}
	currentNode = tofind;
	currentMove = currentNode->data.end();
	return;

}

void ScrollableGame::LoadFromPGN(const string& path)
{
	LoadPgn::ParsePNGfile(this->primeNode, path, this->state.PrimeTimeline, this->state.NumberOfNegativeTurns);
}

void ScrollableGame::LoadFromDatabase(string& path)
{
	this->primeNode->Load(path, *this);
}

void ScrollableGame::SaveAsDatabase(string& path)
{
	this->primeNode->Save(path);
}







ScrollableGame::ScrollableGame(XYTL border, uint16_t WhiteBorder, uint16_t BlackBorder, uint16_t thePresent)
	: Game(border, WhiteBorder, BlackBorder, thePresent) {
	currentNode = new Node<Move>();
	currentNode->p_previous = nullptr;
	primeNode = currentNode;
	currentMove = currentNode->data.end();
	//MoveSetToWrite = new Node<Turn>(nullptr);

}

void ScrollableGame::PrintNextMove()
{
	//string printing = "";
	//if (this->currentMove != currentNode->data.end()) {
	//	(*this->currentMove).move.GetString(*this, printing);
	//	cout << printing << endl;
	//}
	//else if (currentNode->isLast()) {
	//	cout << "there is no next move" << endl;
	//}
	//currentNode->vectorOfNodes[0]->data[0].str;
}

void ScrollableGame::MakeMoveAndIncrement(vector<ActionAndString<Move>>::iterator& currentMove)
{
	MakeMove(currentMove->move);
	++currentMove;
}

void ScrollableGame::UndoMoveAndDecrement(vector<ActionAndString<Move>>::iterator& currentMove)
{
	--currentMove;
	UndoMove(currentMove->move);
}

void ScrollableGame::MakeAllMovesAndSetEnd(vector<ActionAndString<Move>>& moveset, vector<ActionAndString<Move>>::iterator& currentMove)
{
	for (; currentMove != moveset.end();) {
		(*currentMove).move.MakeMove(*this);
		++currentMove;
	}
}

void ScrollableGame::UndoAllMovesAndSetBegin(vector<ActionAndString<Move>>& moveset, vector<ActionAndString<Move>>::iterator& currentMove)
{
	for (; currentMove != moveset.begin();) {
		--currentMove;
		(*currentMove).move.UndoMove(*this);
	}
}


void ScrollableGame::SetIteratorEnd(vector<ActionAndString<Move>>& moveset, vector<ActionAndString<Move>>::iterator& currentMove)
{
	currentMove = moveset.end();
}

void ScrollableGame::SetIteratorBegin(vector<ActionAndString<Move>>& moveset, vector<ActionAndString<Move>>::iterator& currentMove)
{
	currentMove = moveset.begin();
}