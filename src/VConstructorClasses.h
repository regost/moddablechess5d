#pragma once

#ifndef __VConstructor_H__
#define __VConstructor_H__

#include "VConstructor.h"
#include <stdint.h>

class Game;
class VConstructor;
class Board;

class ConstructCopy : public virtual VConstructor {
public:
	void Construct(rawpointer newobj, rawpointer oldobj, std::variant<Timeline*, Board> extra, Game* chess) override;
	ConstructCopy() = default;
};

class ConstructZeros : public virtual VConstructor {
public:
	void Construct(rawpointer newobj, rawpointer oldobj, std::variant<Timeline*, Board> extra, Game* chess) override;
	ConstructZeros() = default;
};
//
//
class ConstructOnes : public virtual VConstructor {
public:
	void Construct(rawpointer newobj, rawpointer oldobj, std::variant<Timeline*, Board> extra, Game* chess) override;
	ConstructOnes() = default;
};
//
//
class ByDefaultOnes : public virtual VConstructor {
public:
	void ConstructByDefault(rawpointer newobject) override;
	ByDefaultOnes() = default;
};
//
//
class ByDefaultZeros : public virtual VConstructor {
public:
	void ConstructByDefault(rawpointer newobject) override;
	ByDefaultZeros() = default;
};


////has name "squares"
class ConstructSquares : virtual public ConstructCopy, ByDefaultZeros {
public:
	inline static const std::string name = "squares";

	size_t squares = 0;
	uint8_t piecesizeinbytes = 0;
	uint8_t x = 0; uint8_t y = 0;
	ConstructSquares(uint8_t x, uint8_t y, uint8_t piecesizeinbytes);
	void Set(Game* obj, SetupGame& setuper) override;
};

template<typename... Types>
class VConstructorTemplate : virtual public Types... {
public:
	VConstructorTemplate() = default;
	VConstructorTemplate(size_t sizebytes) : VConstructor(sizebytes) {};
	VConstructorTemplate(size_t sizebytes, uint8_t flags) : VConstructor(sizebytes, flags) {}
};
#endif