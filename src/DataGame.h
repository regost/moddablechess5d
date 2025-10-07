#pragma once

#ifndef _DATAGAME_H
#define _DATAGAME_H


#include <iostream>
#include <stdint.h>

using namespace std;

struct XY;

struct BorderGame {
	uint16_t InactiveTimelines;
	uint16_t ActiveTimelines;
	void print() {
		cout << "InactiveTimeline: " << int(InactiveTimelines) << endl;
		cout << "ActiveTimeline: " << int(ActiveTimelines) << endl;
	};
};

struct BorderBoard {
	uint8_t x = uint8_t(8);
	uint8_t y = uint8_t(8);
	uint16_t t = 0;
	uint16_t l = 0;
	BorderBoard() {
		x = 8;
		y = 8;
		t = 0;
		l = 0;
	};
	void print() {
		cout << "x: " << int(x) << endl;
		cout << "y: " << int(y) << endl;
		cout << "t: " << int(t) << endl;
		cout << "l: " << int(l) << endl;
	}
};


struct GameState;
struct XYTL;

struct GameState { //kinda state of the game
	BorderGame WhiteTimelinesBorder;
	BorderGame BlackTimelinesBorder;

	size_t SizeBoard = 64;
	BorderBoard border;
	uint16_t ThePresent = 2;//one move after the line of the present
	int TimelineBalance = 0;
	////////////////////////////////////////////////////////////////////////////////////
	int MaxActiveTimelineDifference = 1;
	uint16_t NumberOfNegativeTurns = 0;//to parse the png
	uint16_t PrimeTimeline;//if there are +0 and -0 then -0 is a prime timeline
	uint8_t IsGameEnded = 0;
	bool Move = false; // false - white's turn , true - black's turn
	bool Submit = false;
	GameState() = default;
	void print() {
		WhiteTimelinesBorder.print();
		BlackTimelinesBorder.print();
		border.print();
		cout << "present: " << ThePresent << endl;
		cout << "timeline balance: " << TimelineBalance << endl;
		cout << "prime timeline: " << PrimeTimeline << endl;
	};
};

#endif 