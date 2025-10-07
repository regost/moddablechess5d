
#include <cstring>
#include "VConstructorClasses.h"
#include "Game.h"
#include "Board.h"

//64 squares = 64 bits = 8 bytes
//class SetMaskSize : virtual public VConstructor {
//	void Set(Game* obj) override {
//		auto it = obj->mapconstructor.find(ConstructSquares::name);
//		if (it == obj->mapconstructor.end()) {
//			throw "there are no squares";
//		}
//		ConstructSquares* temp = reinterpret_cast<ConstructSquares*>((*it).second.first);
//		this->copysizebytes = (temp->squares + 7) / 8;
//	}
//};

ConstructSquares::ConstructSquares(uint8_t x, uint8_t y, uint8_t piecesizeinbytes)
{
	this->x = x; this->y = y;
	this->squares = size_t(x) * size_t(y);
	this->piecesizeinbytes = piecesizeinbytes;
	this->sizebytes = squares * piecesizeinbytes;
}

void ConstructSquares::Set(Game* obj, SetupGame& setuper)
{
	obj->GetState().border.x = x;
	obj->GetState().border.y = y;
	obj->GetState().SizeBoard = squares;
}

void ConstructCopy::Construct(rawpointer newobj, rawpointer oldobj, std::variant<Timeline*, Board> extra, Game* chess)
{
	std::memcpy(newobj + bitposition, oldobj + bitposition, sizebytes);
}

void ConstructZeros::Construct(rawpointer newobj, rawpointer oldobj, std::variant<Timeline*, Board> extra, Game* chess)
{
	std::memset(newobj, 0, this->sizebytes);
}

void ConstructOnes::Construct(rawpointer newobj, rawpointer oldobj, std::variant<Timeline*, Board> extra, Game* chess)
{
	std::memset(newobj, 1, this->sizebytes);
}

void ByDefaultOnes::ConstructByDefault(rawpointer newobject)
{
	std::memset(newobject, 1, this->sizebytes);
}

void ByDefaultZeros::ConstructByDefault(rawpointer newobject)
{
	std::memset(newobject, 0, this->sizebytes);
}
