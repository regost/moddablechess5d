

#include "HelperStructs.h"
#include "Timeline.h"

#include <map>
#include <set>

//replace that with uint8_t + 'a'
const map<char, uint8_t> transformChar = {
	{'a',0} ,{'b',1} ,{'c',2} ,{'d',3},
	{'e',4} ,{'f',5} ,{'g',6} ,{'h',7},
	{'i',8}
};

string letters = "abcdefghi";

//use a better way char - '0' < 10
const set<char> numberChars = { '0','1','2','3','4','5','6','7','8','9' };

void SetTimelineAndTurn(string& strMove, Game& chess, XYTL& data) {
	strMove += "(";
	strMove += std::to_string(int(chess.state.PrimeTimeline) - int(data.l));
	strMove += "T";
	strMove += std::to_string(int((data.t >> 1) - chess.state.NumberOfNegativeTurns));
	strMove += ")";
}

void SetPiece(string& strMove, Game& chess, XYTL& data) {
	strMove += Piece::PieceArray[chess.GetPiece(data)].PGN;
}

void SetXY(string& strMove, XYTL& data) {
	strMove += letters[data.x];
	strMove += to_string(data.y + 1);
}


void FindChar(const string& parse, size_t& i, char toFind) {
	for (; i < parse.size(); ++i) {
		if (parse[i] == toFind) {
			return;
		}
	}
	throw "error in finding a char " + toFind;
}


void GetL(XYTL& turn, const string& parse, uint16_t primeTimeline, size_t& i) {
	size_t Result = 0;
	if (parse[i] == '(') { ++i; }
	if (parse[i] == '+') { --Result; ++i; }
	int firstElement = i;
	FindChar(parse, i, 'T');
	Result += int(primeTimeline) - stoi(parse.substr(firstElement, i - firstElement));


	turn.l = uint16_t(Result);
	++i;
}


void GetT(XYTL& turn, const string& parse, uint16_t NumberOfNegativeTurns, uint16_t color, size_t& i) {
	size_t number = i;
	FindChar(parse, i, ')');
	turn.t = ((stoi(parse.substr(number, i - number)) + NumberOfNegativeTurns) << 1) + color;
	//turn.t -= 1;

	++i;
}


void GetX(XYTL& turn,const string& parse, size_t& i) {
	auto it = transformChar.find(parse[i]);
	if (it == transformChar.cend()) {
		++i;
		it = transformChar.find(parse[i]);
	}
	turn.x = it->second;
	++i;
}


void GetY(XYTL& turn,const string& parse, size_t& i) {
	size_t findNumber = i;
	while (size_t(i) <= parse.size() && (numberChars.find(parse[i]) != numberChars.cend())) {
		++i;
	}
	turn.y = stoi(parse.substr(findNumber, i - findNumber + 1)) - 1;
}


//todo use string_view
Move::Move(const std::string& parse, uint16_t primeTimeline, uint16_t NegativeTurns, uint16_t color)
{
	size_t i = 0;//each Get function increases i   
	//prime timeline is -0 or 0 , '+' increments the timeline var -2,-1,-0,+0,+1,+2 => -2,-1,0,1,2,3
	GetL(this->begin, parse, primeTimeline, i);
	GetT(this->begin, parse, NegativeTurns, color, i);
	GetX(this->begin, parse, i);
	GetY(this->begin, parse, i);
	if (parse[i] == '>') {
		while (parse[i] != '(') { ++i; }
		GetL(this->end, parse, primeTimeline, i);
		GetT(this->end, parse, NegativeTurns, color, i);
	}
	else {
		this->end.t = this->begin.t;
		this->end.l = this->begin.l;
	}
	GetX(this->end, parse, i);
	GetY(this->end, parse, i);
}




Move::Move(uint8_t x1, uint8_t y1, uint16_t t1, uint16_t l1, uint8_t x2, uint8_t y2, uint16_t t2, uint16_t l2)
{
	begin.x = x1; begin.y = y1; begin.t = t1; begin.l = l1;
	end.x = x2; end.y = y2; end.t = t2; end.l = l2;
}


void Move::Print()
{
	const string between = " ";
	cout << "(" << int(begin.x) << between << int(begin.y) << between << begin.t << between << begin.l << between;
	cout << int(end.x) << between << int(end.y) << between << end.t << between << end.l << ")";

}

void Move::MakeMove(Game& chess) { chess.MakeMove(*this); }
void Move::UndoMove(Game& chess) { chess.UndoMove(*this); }

void Move::GetString(Game& chess, string& str)
{
	SetTimelineAndTurn(str, chess, this->begin);
	SetPiece(str, chess, this->begin);
	SetXY(str, this->begin);
	bool isTravel, isBetweenTimelines;
	isTravel = chess.GetTimeline(end.l).GetCurrentTurn() != this->end.t;
	isBetweenTimelines = this->begin.l != this->end.l;

	if (isTravel || isBetweenTimelines) {
		if (isTravel) {
			str += ">>";
		}
		else {
			str += ">";
		}
		SetTimelineAndTurn(str, chess, this->end);
	}
	SetXY(str, this->end);
}

void Move::SetStringTurn(Game& chess,const string& parse, uint16_t color)
{
	//(0T2)Nf3>>(0T1)f5
	size_t i = 0;//each Get function increases i   
	//prime timeline is -0 or 0, '+' increments the timeline var -2,-1,-0,+0,+1,+2 => -2,-1,0,1,2,3
	//(0T2)
	GetL(this->begin, parse, chess.state.PrimeTimeline, i);
	GetT(this->begin, parse, chess.state.NumberOfNegativeTurns, color, i);
	//f3
	GetX(this->begin, parse, i);
	GetY(this->begin, parse, i);
	if (parse[i] == '>') {
		while (parse[i] != '(') { ++i; }
		GetL(this->end, parse, chess.state.PrimeTimeline, i);
		GetT(this->end, parse, chess.state.NumberOfNegativeTurns, color, i);
	}
	else {
		//(0T1)
		this->end.t = this->begin.t;
		this->end.l = this->begin.l;
	}
	//f5
	GetX(this->end, parse, i);
	GetY(this->end, parse, i);

}

bool Move::operator==(Move& r_value)
{
	return (this->begin == r_value.begin) && (this->end == r_value.end);
}

bool Move::isEqual(Move& r_value) {
	return *this == r_value;
}
