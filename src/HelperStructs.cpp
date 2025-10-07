

#include "HelperStructs.h"
#include <map>
#include <set>
#include <iostream>

#include "Piece.h"
#include "Game.h"

using namespace std;

void MoveSet::Add(Turn& turn)
{
	vectorOfTurns.push_back(turn);
}

void MoveSet::Print()
{
	for (size_t i = 0; i < this->vectorOfTurns.size(); ++i) {
		this->vectorOfTurns[i].Print();
	}
}

bool MoveSet::isEqual(MoveSet& r_value)
{
	//TODO when i finish Move class i'll get to it
	return vectorOfTurns.size() == r_value.vectorOfTurns.size();
	//&& std::equal(vectorOfTurns.begin(), vectorOfTurns.end(), r_value.vectorOfTurns.begin(), r_value.vectorOfTurns.end());
}

bool MoveSet::operator==(MoveSet& r_value)
{
	return isEqual(r_value);
}

void XYTL::Print()
{
	cout << "x: " << int(x) << " y: " << int(y) << " t: " << t << " l: " << l << "\n";
}

bool XYTL::operator==(XYTL& r_value)
{
	return this->x == r_value.x && this->y == r_value.y &&
		this->t == r_value.t && this->l == r_value.l;
}


XY::XY(uint8_t x, uint8_t y)
{
	this->x = x;
	this->y = y;
}

bool XY::operator==(XY& r_value)
{
	return r_value.x == this->x && r_value.y == this->y;
}
