#pragma once

#ifndef __CONSTRUCTOR_H__
#define __CONSTRUCTOR_H__

#include <map>
#include <bitset>
#include <variant>
#include <string>
#include <vector>
#include <utility>
#include <stdint.h>

#include "usingnames.h"

class Timeline;
class Board;
class Game;
class VConstructor;
class SetupGame;

class VConstructor {
	friend SetupGame;
	friend Game;
	protected:
	//public:
		size_t bitposition = 0;
		size_t sizebytes;

		//we should not create boards without a reason
		//1) affects checkmate detection
		//2) affects legal move detection
		//3) affects stalemate detection

		uint8_t flags = 1 + 2 + 4;
		//vector<std::pair<string, void*>> TODO{};
	public:
		//TODO make it a pointer
		virtual void Set(Game* obj, SetupGame& setuper);
		//if you wanna create 1) the board extra should be a timeline, obj is a Board 
		//		   2) the timeline extra should be a board, obj is a Timeline
		virtual void Construct(rawpointer newobject, rawpointer old, std::variant<Timeline*, Board> extra, Game* chess);
		virtual void ConstructByDefault(rawpointer newobject) ;
		virtual ~VConstructor();

		VConstructor();
		VConstructor(size_t sizebytes);
		VConstructor(size_t sizebytes, uint8_t flags);
		bool ready();

		rawpointer get(rawpointer pointer);
		template <class T> rawpointer get(rawpointer pointer);

		void setposition(size_t pos);
		size_t getposition();
};

//it works dont touch actually touch but later
#include "VConstructorClasses.h"

#endif // !__DATA_H__

