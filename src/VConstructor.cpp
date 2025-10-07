#include "VConstructor.h"
#include "Game.h"
#include "Board.h"

void VConstructor::Set(Game* obj, SetupGame& setuper){}
void VConstructor::Construct(rawpointer newobject, rawpointer old, std::variant<Timeline*, Board> extra, Game* chess){}
void VConstructor::ConstructByDefault(rawpointer newobject){}
VConstructor::~VConstructor(){}
VConstructor::VConstructor(){}

/////////////////VConstructor///////////////////////////////
VConstructor::VConstructor(size_t sizebytes)
{
    this->sizebytes = sizebytes;
}

VConstructor::VConstructor(size_t sizebytes, uint8_t flags)
{
    this->sizebytes = sizebytes;
    this->flags = flags;
}

bool VConstructor::ready()
{
	return sizebytes != 0;
}


void VConstructor::setposition(size_t pos)
{
    this->bitposition = pos;
}

size_t VConstructor::getposition()
{
    return this->bitposition;
}

rawpointer VConstructor::get(const rawpointer pointer)
{
    return pointer + this->bitposition;
}


template<class T>
rawpointer VConstructor::get(const rawpointer pointer)
{
    return reinterpret_cast<T>(get(pointer));
}

////////////////////////////////////////////////////////////

