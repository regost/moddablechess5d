#include "Game.h"
#include "DataGame.h"
#include "HelperStructs.h"
#include "Timeline.h"
#include "Piece.h"
#include "Enum.h"
#include "VConstructor.h"
#include "Board.h"

Timeline*& Game::GetTimelines() {
	return *this->multiverse;
}

uint8_t Game::GetPiece(XYTL& click)
{
	return multiverse[click.l]->GetBoard(click.t).GetSquare(click.x, click.y, this->state.border);
}

Piece& Game::GetPieceAddress(uint8_t piece)
{
	return Piece::PieceArray[piece];
}

Piece& Game::GetPieceAddress(XYTL& click)
{
	return GetPieceAddress(GetPiece(click));
}


Board Game::CreateBoard(Board old, std::variant<Timeline*, Board> extra)
{
	if (GetBoardSize() == 0) {
		throw "board size is 0";
	}

	Board newboard(GetBoardSize());
	
	for (auto it : this->constructor[Game::BOARD]) {
		it->Construct(newboard, old, extra,this);
	}

	//this->constructor[Game::BOARD][0]->Construct(newboard, old, extra, this);

	return newboard;
}

Timeline* Game::CreateTimeline(Timeline* old, std::variant<Timeline*, Board> extra)
{

	//const rawpointer newtimelineptr = reinterpret_cast<rawpointer>(newtimeline);
	const size_t size = this->sizebytes[this->sizebytes[MULTIVERSE]];
	rawpointer newtimelineptr = new char[size];
	const rawpointer oldtimelineptr = reinterpret_cast<rawpointer>(old);

	for (auto it : this->constructor[Game::TIMELINE]) {
		it->Construct(newtimelineptr, oldtimelineptr, extra,this);
	}

	return reinterpret_cast<Timeline*>(newtimelineptr);
}


////////////////////////////////////////////////////////////////////////////////////////////

//void Game::PrintComponents()
//{
//	static string place[3] = { "multiverse", "timeline", "board" };
//	for (auto i = this->components.begin(); i != this->components.end(); ++i) {
//		cout << "name: " << i->first << endl;
//		cout << "size: " << i->second.sizebits << " bit" << (i->second.sizebits != 1 ? "s" : "") << endl;
//		cout << "where: " << place[i->second.placetype] << endl;
//		cout << endl;
//	}
//}

size_t Game::GetBoardSize()
{
	return this->sizebytes[Game::BOARD];
}

GameState& Game::GetState() {
	return this->state;
}



uint16_t Game::GetNumberOfTimelines() {
	return 1 + state.BlackTimelinesBorder.InactiveTimelines - state.WhiteTimelinesBorder.InactiveTimelines;
}

void Game::MakeRegularMove(Turn& toMove) {//non-castle , non-en passant move , non-special move
	MakeRegularMove(toMove, multiverse[toMove.begin.l]->GetCurrentTurnBoard().GetSquare(toMove.begin.x, toMove.begin.y, state.border));
}


void Game::NotTimeTravelMove(uint8_t setPieceAfterMove, Turn& toMove)
{
	multiverse[toMove.begin.l]->CreateNextTurn(this->state.SizeBoard,*this);
	if (toMove.begin.l != toMove.end.l) {
		multiverse[toMove.end.l]->CreateNextTurn(this->state.SizeBoard,*this);
	}
	multiverse[toMove.begin.l]->GetCurrentTurnBoard().SetSquare(0, toMove.begin.x, toMove.begin.y, state.border);
	multiverse[toMove.end.l]->GetCurrentTurnBoard().SetSquare(setPieceAfterMove, toMove.end.x, toMove.end.y, state.border);
}

Board Game::MakeTravelAndGetBoard(const Turn& turn, const bool color)
{
	const uint16_t toSetTurn = turn.end.t + 1;

	#if NEWBOARDCONSTRUCTOR
		Board board = CreateBoard(multiverse[turn.end.l]->GetBoard(turn.end.t), multiverse[turn.end.l]);
	#else
		Board board = multiverse[turn.end.l]->GetBoard(turn.end.t).GetDeepCopy(this->state.SizeBoard);
	#endif

	if (color == ColorType::Black) {//Black
		OnBlackCreatesTimeline(turn.end.t);
		if (multiverse[state.BlackTimelinesBorder.InactiveTimelines] == nullptr) { 

		#if not NEWTIMELINECONSTRUCTOR
			Timeline* temp = new Timeline(this->state.border.t);//edited

		#else 
			Timeline* temp = this->CreateTimeline(multiverse[turn.begin.l], board);
			temp->AllocateMemory(TIMELINESIZEINBOARDS);
		#endif

			multiverse[state.BlackTimelinesBorder.InactiveTimelines] = temp;
		}

		multiverse[state.BlackTimelinesBorder.InactiveTimelines]->SetCurrentTurn(toSetTurn);
		multiverse[state.BlackTimelinesBorder.InactiveTimelines]->SetIndexFirstBoard(toSetTurn);
		multiverse[state.BlackTimelinesBorder.InactiveTimelines]->SetBoard(toSetTurn, board);
		return board;
	}

	OnWhiteCreatesTimeline(turn.end.t);
	if (multiverse[state.WhiteTimelinesBorder.InactiveTimelines] == nullptr) { multiverse[state.WhiteTimelinesBorder.InactiveTimelines] = new Timeline(this->state.border.t); }

	multiverse[state.WhiteTimelinesBorder.InactiveTimelines]->SetIndexFirstBoard(toSetTurn);
	multiverse[state.WhiteTimelinesBorder.InactiveTimelines]->SetCurrentTurn(toSetTurn);
	multiverse[state.WhiteTimelinesBorder.InactiveTimelines]->SetBoard(toSetTurn, board);

	return board;
}

//void Game::ResetSize()
//{
//	this->size[0] = 0;
//	this->size[1] = TIMELINESIZEBYTES;
//	this->size[2] = 0;
//};



void Game::MakeMove(Turn& toMove)
{
	Piece::PieceArray[multiverse[toMove.begin.l]->GetCurrentTurnBoard().GetSquare(toMove.begin.x, toMove.begin.y, state.border)].makeMove(*this, toMove);
}


void Game::MakeMoveSet(vector<Turn>& toMove, vector<Turn>::iterator& currentMove) {

	for (; currentMove != toMove.end(); ++currentMove) {
		MakeMove(*currentMove);
	}
}


void Game::MakeMoveSet(vector<Turn>& toMove) {

	for (auto it = toMove.begin(); it != toMove.end(); ++it) {
		MakeMove(*it);
	}
}


void Game::UndoMove(Turn& toMove) {
	if (state.Move == ColorType::Black) {
		UndoMove(toMove, Game::_fBlackUndoTravel);
		return;
	}
	UndoMove(toMove, Game::_fWhiteUndoTravel);
}


void Game::UndoMoveSet(vector<Turn>& toMove, vector<Turn>::iterator& currentMove, function<void(Game& multiverse, Turn& toMove)> undoTravel) {
	while (currentMove != toMove.begin()) {
		--currentMove;
		this->UndoMove(*currentMove, undoTravel);
	}
}

//void Game::AddSpace(uint8_t where, string& name, size_t bites, constructor::VConstructor* construct)
//{
//	AllocatedType temp;
//	temp.copyingtype = -1;
//	temp.placetype = where;
//	temp.sizebits = bites;
//	this->components[name] = temp;
//	this->creator.constructor[where].push_back(construct);
//}

//Board Game::CreateBoard(Board prev, const Turn& tomove)
//{
//	
//}

void Game::UndoMove(Turn& move, function<void(Game& multiverse, Turn& toMove)> undoTravel)
{
	this->multiverse[move.begin.l]->UndoTurn();

	if (move.begin.l != move.end.l) {
		Timeline& endmovetimeline = *this->multiverse[move.end.l];
		if (move.end.t != endmovetimeline.GetCurrentTurn() && endmovetimeline.GetBoard(move.end.t + 1).GetSquare(move.end.x, move.end.y, this->state.border) == 0) {

			//temporal solution 
			//todo add to the class turn with a bool variable which indicates was it a travel move
			//and on move change that variable if move creates a timeline then in a makemove func 
			//this bool variable is changed
			//because if 2 moves are the same it doesnt mean that its possible to distinguish

			undoTravel(*this, move);
		}
		else {
			this->multiverse[move.end.l]->UndoTurn();
		}
	}
	else if (move.end.t != this->multiverse[move.end.l]->GetCurrentTurn()) {
		undoTravel(*this, move);
	}

}

void Game::UndoMoveSet(vector<Turn>& moveset, function<void(Game& multiverse, Turn& toMove)> undoTravel) {
	vector<Turn>::iterator it = moveset.end();
	UndoMoveSet(moveset, it, undoTravel);
}

void Game::UndoMoveSet(vector<Turn>& toMove)
{

	if ((this->state.Move == ColorType::White)) {
		UndoMoveSet(toMove, Game::_fWhiteUndoTravel);
		return;
	}
	UndoMoveSet(toMove, Game::_fBlackUndoTravel);
}


void Game::UndoMoveSet(vector<Turn>& toMove, vector<Turn>::iterator& currentMove)
{
	if ((this->state.Move == ColorType::White)) {
		UndoMoveSet(toMove, currentMove, Game::_fWhiteUndoTravel);
		return;
	}
	UndoMoveSet(toMove, currentMove, Game::_fBlackUndoTravel);
}

void WhiteUndoTravel(Game& multiverse, Turn& toMove) {
	multiverse.multiverse[multiverse.state.WhiteTimelinesBorder.InactiveTimelines]->UndoTurn();
	if (!(multiverse.state.TimelineBalance > multiverse.state.MaxActiveTimelineDifference)) {
		++multiverse.state.WhiteTimelinesBorder.ActiveTimelines;
	}
	if (multiverse.state.TimelineBalance <= -multiverse.state.MaxActiveTimelineDifference) {
		--multiverse.state.BlackTimelinesBorder.ActiveTimelines;
	}
	--multiverse.state.TimelineBalance;
	++multiverse.state.WhiteTimelinesBorder.InactiveTimelines;

	multiverse.state.ThePresent = multiverse.CalculateThePresent() | 1;//add 1 if even
	++multiverse.state.ThePresent;
}

void BlackUndoTravel(Game& multiverse, Turn& toMove) {
	multiverse.multiverse[multiverse.state.BlackTimelinesBorder.InactiveTimelines]->UndoTurn();
	if (!(multiverse.state.TimelineBalance < -multiverse.state.MaxActiveTimelineDifference)) {
		--multiverse.state.BlackTimelinesBorder.ActiveTimelines;
	}
	if (multiverse.state.TimelineBalance >= multiverse.state.MaxActiveTimelineDifference) {
		++multiverse.state.WhiteTimelinesBorder.ActiveTimelines;
	}
	++multiverse.state.TimelineBalance;
	--multiverse.state.BlackTimelinesBorder.InactiveTimelines;

	multiverse.state.ThePresent = multiverse.CalculateThePresent();
	multiverse.state.ThePresent += multiverse.state.ThePresent & 1; // add one if odd
	++multiverse.state.ThePresent;

}

function<void(Game& multiverse, Turn& toMove)> Game::_fWhiteUndoTravel = WhiteUndoTravel;
function<void(Game& multiverse, Turn& toMove)> Game::_fBlackUndoTravel = BlackUndoTravel;


namespace canclick {
	bool CanDefaultClick(Game& multiverse, XYTL click) {
		const uint8_t piece = multiverse.multiverse[click.l]->GetBoard(click.t).GetSquare(click.x, click.y, multiverse.state.border);
		return piece != PieceType::Void
			&& Piece::PieceArray[piece].color == multiverse.state.Move
			&& (click.t & 1) == multiverse.GetState().Move
			&& multiverse.multiverse[click.l]->GetCurrentTurn() == click.t;
	}
	bool CanDefaultMove(Game& multiverse, XYTL click) {
		const uint8_t piece = multiverse.multiverse[click.l]->GetBoard(click.t).GetSquare(click.x, click.y, multiverse.state.border);
		return (piece == PieceType::Void || Piece::PieceArray[piece].color != multiverse.GetState().Move)
			&& (click.t & 1) == multiverse.GetState().Move;
	}
}
namespace cansubmit {
	bool CanDefaultSubmit(Game& chess) {
		for (uint16_t l = chess.state.WhiteTimelinesBorder.ActiveTimelines; l <= chess.state.BlackTimelinesBorder.ActiveTimelines; ++l) {
			if (chess.multiverse[l]->GetCurrentTurn() < chess.state.ThePresent) { return false; }
		}
		return true;
	}
}


Game::Game(XYTL border, uint16_t WhiteBorder, uint16_t BlackBorder, uint16_t thePresent) {

	this->state.border.l = border.l;
	this->state.border.t = border.t;
	this->state.WhiteTimelinesBorder.InactiveTimelines = WhiteBorder;
	this->state.BlackTimelinesBorder.InactiveTimelines = BlackBorder;
	this->state.WhiteTimelinesBorder.ActiveTimelines = WhiteBorder;
	this->state.BlackTimelinesBorder.ActiveTimelines = BlackBorder;
	this->state.ThePresent = thePresent;
	this->state.MaxActiveTimelineDifference = 1;

	//cout << int(border.x);
	this->state.border.x = border.x;
	//cout << int(this->state.border.x);
	this->state.border.y = border.y;
	this->state.SizeBoard = uint16_t(border.x) * uint16_t(border.y);

	const size_t piecesize = 8;

	//this->mapconstructor[ConstructSquares::name] = {new ConstructSquares(8,8,1),Game::BOARD};
	

	//this->extradatasize.board.AddBits(size_t(this->parameters.SizeBoard * piecesize));//piece size 
	this->GetState().Move = false;

	this->multiverse = new Timeline*[border.t];

	for (uint16_t i = 0; i < border.t; ++i) { multiverse[i] = nullptr; }

	uint16_t sum = this->state.WhiteTimelinesBorder.ActiveTimelines + this->state.BlackTimelinesBorder.ActiveTimelines;

	if ((sum & 1) == false) { this->state.PrimeTimeline = sum >> 1; } //if even
	else { this->state.PrimeTimeline = (sum >> 1) + 1; }//if odd

	v_CanClick.push_back({ canclick::CanDefaultClick,canclick::CanDefaultMove });
	this->v_CanSubmit = { cansubmit::CanDefaultSubmit };
}


void Game::Submit()
{
	state.Move = !state.Move;
	++state.ThePresent;
}

void Game::UndoSubmit()
{
	state.Move = !state.Move;
	--state.ThePresent;
}


bool Game::CanSubmit()
{
	for (auto func : v_CanSubmit) {
		if (func(*this) == false) {
			return false;
		}
	}
	return true;
}



void Game::MakeRegularMove(Turn& toMove, uint8_t piece)//non-castle , non-en passant moves but you can turn the piece in moved piece (e2e4, 0-0)
{
	if (multiverse[toMove.end.l]->GetCurrentTurn() == toMove.end.t) {
		NotTimeTravelMove(piece, toMove);
		return;
	}
	const bool isBlack = (toMove.begin.t & 1);//create multiverse.isBlack();
	Board createdBoard = MakeTravelAndGetBoard(toMove, isBlack);
	createdBoard.SetSquare(piece, toMove.end.x, toMove.end.y, state.border);
	multiverse[toMove.begin.l]->CreateNextTurn(this->state.SizeBoard,*this);
	multiverse[toMove.begin.l]->GetCurrentTurnBoard().SetSquare(0, toMove.begin.x, toMove.begin.y, state.border);
}





void Game::SetTimeline(uint16_t t, Timeline* toSet)
{
	multiverse[t] = toSet;
}


uint16_t Game::CalculateThePresent()
{
	uint16_t min = -1;
	for (uint16_t i = state.WhiteTimelinesBorder.ActiveTimelines; i <= state.BlackTimelinesBorder.ActiveTimelines; ++i) {
		if (multiverse[i]->GetCurrentTurn() < min) {
			min = multiverse[i]->GetCurrentTurn();
		}
	}
	return min;
}

void Game::OnWhiteCreatesTimeline(const uint16_t endT)
{

	if (state.TimelineBalance < this->state.MaxActiveTimelineDifference) {
		--this->state.WhiteTimelinesBorder.ActiveTimelines;

		if (endT < this->state.ThePresent) {
			this->state.ThePresent = endT;
			this->state.ThePresent |= 1; // add one since endT is even
		}
		if (state.TimelineBalance < -state.MaxActiveTimelineDifference) {
			++state.BlackTimelinesBorder.ActiveTimelines;
			if (this->multiverse[state.WhiteTimelinesBorder.ActiveTimelines]->GetCurrentTurn() < this->state.ThePresent) {
				this->state.ThePresent = this->multiverse[state.BlackTimelinesBorder.ActiveTimelines]->GetCurrentTurn();
				this->state.ThePresent |= 1; // add one if even
			}

		}
	}

	--state.WhiteTimelinesBorder.InactiveTimelines;
	++state.TimelineBalance;
}

void Game::OnBlackCreatesTimeline(const uint16_t endT)
{
	if (state.TimelineBalance > -this->state.MaxActiveTimelineDifference) {
		++state.BlackTimelinesBorder.ActiveTimelines;

		if (endT < this->state.ThePresent) {
			this->state.ThePresent = endT;//always odd
			++this->state.ThePresent;
			//add one if present is wrong delete this line and uncomment a line below
			//this->state.ThePresent += this->state.ThePresent & 1; //add one if odd
		}

		if (state.TimelineBalance > state.MaxActiveTimelineDifference) {
			--state.WhiteTimelinesBorder.ActiveTimelines;

			if (this->multiverse[state.BlackTimelinesBorder.ActiveTimelines]->GetCurrentTurn() < this->state.ThePresent) {
				this->state.ThePresent = this->multiverse[state.WhiteTimelinesBorder.ActiveTimelines]->GetCurrentTurn();
				this->state.ThePresent += this->state.ThePresent & 1;//add one if odd
			}
		}
	}

	++state.BlackTimelinesBorder.InactiveTimelines;
	--state.TimelineBalance;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//void Game::AddExtraBoardData(size_t amountofbits, string& name)
//{
//	this->extradatasize.board.AddBits(amountofbits);
//	void* ptr = new size_t(this->extradatasize.board.bits);
//	this->ptrsystem.AddElement(name, ptr);
//}
//
//void Game::AddExtraTimelineData(size_t amountofbits, string& name)
//{
//	this->extradatasize.timeline.AddBits(amountofbits);
//	void* ptr = new size_t(this->extradatasize.timeline.bits);
//	this->ptrsystem.AddElement(name, ptr);
//}



void Game::PrintState()
{
	this->state.print();

}

void Game::PrintPart(uint16_t max, uint16_t min)
{
	for (uint16_t i = max; i > min; --i) {
		if (multiverse[i] == nullptr) {
			cout << "Null\n";
			continue;
		}
		multiverse[i]->PrintTimeline(this->state.border);
		if ((i - 1 > min) && (i <= max)) { cout << endl; }
	}
}

void Game::PrintLineBetweenTimelines(uint16_t t)
{
	uint16_t size = (multiverse[t]->GetCurrentTurn() + 1) * (this->state.border.x * 2 + 2) - 1;
	for (uint16_t i = 0; i < size; ++i) {
		cout << '-';
	}
	cout << " "; //by some unknown reason the last symbol doesnt show up and i gotta print that
}


void Game::Print()
{
	PrintPart(state.BlackTimelinesBorder.InactiveTimelines, state.BlackTimelinesBorder.ActiveTimelines); // black's inactive timelines
	PrintLineBetweenTimelines(state.BlackTimelinesBorder.ActiveTimelines);
	PrintPart(state.BlackTimelinesBorder.ActiveTimelines, state.WhiteTimelinesBorder.ActiveTimelines - 1);// active timelines
	PrintLineBetweenTimelines(state.WhiteTimelinesBorder.ActiveTimelines);
	PrintPart(state.WhiteTimelinesBorder.ActiveTimelines - 1, state.WhiteTimelinesBorder.InactiveTimelines - 1); // white's inactive timelines
	cout << endl;
}

void Game::PrintSize()
{
	//cout << "Board: " << this->extradatasize.board.bits << " bits" << "\n";
	//cout << "Timeline: " << this->extradatasize.timeline.bits << " bits" << "\n";
}

Game::~Game()
{
	delete[] multiverse;
}

