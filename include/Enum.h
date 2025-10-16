#pragma once

#ifndef _ENUM_H_
#define _ENUM_H_

class Color {
public:
    enum : bool {
        WHITE = 0,
        BLACK = 1
    };

    bool value;

    Color(bool v = WHITE) : value(v) {}

    operator bool() const {
        return value == BLACK;
    }

    bool operator==(bool other) const {
        return value == other;
    }
};

namespace PieceType {
	enum pieceEnum {
		BPawn = 1, BMovedPawn = 3, BRook = 5, BMovedRook = 7, BKnight = 9, BBishop = 11, BQueen = 13, BPrincess = 19,
		BKing = 15, BMovedKing = 17, BCommonKing = 21, BRoyalQueen = 23, BDragon = 25, BUnicorn = 27, BBrawn = 29, BMovedBrawn = 31,
		WPawn = 2, WMovedPawn = 4, WRook = 6, WMovedRook = 8, WKnight = 10, WBishop = 12, WQueen = 14, WPrincess = 20, WKing = 16,
		WMovedKing = 18, WCommonKing = 22, WRoyalQueen = 24, WDragon = 26, WUnicorn = 28, WBrawn = 30, WMovedBrawn = 32,
		Void = 0
	};
}

#endif

