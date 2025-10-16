
#include "Piece.h"
#include "Game.h"
#include "Timeline.h"
#include "Piece.h"
#include "Board.h"
#include "HelperStructs.h"
#include "Enum.h"

enum Royalty {
    Royal = true, NotRoyal = false
};
enum ColorType {
    White = true, Black = false
};

// Removed duplicate enum PieceType, using the one from Enum.h

void f_VoidCanNotMove(Game& chess, Move turn) {
    cout << "void can not move, you must fix that error\n";
    cout << "begin(" << "l: " << turn.begin.l << " " << "t: " << turn.begin.t << " " << "x: " << int(turn.begin.x) << " y: " << int(turn.begin.y) << ")\n";
    cout << "end(" << "l: " <<turn.end.l << " " << "t: " << turn.end.t << " " << "x: " << int(turn.end.x) << " " << "y: " << int(turn.end.y) << ")\n";
    string a;
    turn.GetString(chess, a);
    cout << a << endl;
}

void f_RegularMove(Game& multiverse, Move turn) {
    multiverse.MakeRegularMove(turn);
}
void f_TurnIntoMovedPiece(Game& multiverse, Move turn) { // pawn -> moved pawn
    
    uint8_t piece = multiverse.GetTimeline(turn.begin.l).GetBoard(turn.begin.t).GetSquare(turn.begin.x, turn.begin.y, multiverse.state.border);
    multiverse.MakeRegularMove(turn, piece + 2);
}
void f_BlackCastle(Game& multiverse, Move turn) { //todo
    uint8_t piece = multiverse.GetTimeline(turn.begin.l).GetBoard(turn.begin.t).GetSquare(turn.begin.x, turn.begin.y, multiverse.state.border);
    multiverse.MakeRegularMove(turn, PieceType::BMovedKing);

    if (turn.end.x == 6) {
        multiverse.GetTimeline(turn.end.l).GetCurrentTurnBoard().SetSquare(PieceType::Void, multiverse.state.border.x - 1, multiverse.state.border.y - 1, multiverse.state.border);
        multiverse.GetTimeline(turn.end.l).GetCurrentTurnBoard().SetSquare(PieceType::BMovedRook, multiverse.state.border.x - 3, multiverse.state.border.y - 1, multiverse.state.border);
    }
    if (turn.end.x == 2) {
        multiverse.GetTimeline(turn.end.l).GetCurrentTurnBoard().SetSquare(PieceType::Void, 0, multiverse.state.border.y - 1, multiverse.state.border);
        multiverse.GetTimeline(turn.end.l).GetCurrentTurnBoard().SetSquare(PieceType::BMovedRook, 3, multiverse.state.border.y - 1, multiverse.state.border);
    }
}
void f_WhiteCastle(Game& multiverse, Move turn) { //todo

    uint8_t piece = multiverse.GetTimeline(turn.begin.l).GetBoard(turn.begin.t).GetSquare(turn.begin.x, turn.begin.y, multiverse.state.border);
    multiverse.MakeRegularMove(turn, PieceType::WMovedKing);
    if (turn.end.x == 6) {
        multiverse.GetTimeline(turn.end.l).GetCurrentTurnBoard().SetSquare(PieceType::Void, multiverse.state.border.x - 1, 0, multiverse.state.border);
        multiverse.GetTimeline(turn.end.l).GetCurrentTurnBoard().SetSquare(PieceType::WMovedRook, multiverse.state.border.x - 3, 0, multiverse.state.border);
    }
    if (turn.end.x == 2) {
        multiverse.GetTimeline(turn.end.l).GetCurrentTurnBoard().SetSquare(PieceType::Void, 0, 0, multiverse.state.border);
        multiverse.GetTimeline(turn.end.l).GetCurrentTurnBoard().SetSquare(PieceType::WMovedRook, 3, 0, multiverse.state.border);
    }
}

void f_WhitePromotionAndEnPassant(Game& multiverse, Move turn) { //todo
    uint8_t piece = multiverse.GetTimeline(turn.begin.l).GetBoard(turn.begin.t).GetSquare(turn.begin.x, turn.begin.y, multiverse.state.border);
    multiverse.MakeRegularMove(turn, piece);
}

void f_BlackPromotionAndEnPassant(Game& multiverse, Move turn) { //todo
    uint8_t piece = multiverse.GetTimeline(turn.begin.l).GetBoard(turn.begin.t).GetSquare(turn.begin.x, turn.begin.y, multiverse.state.border);
    multiverse.MakeRegularMove(turn, piece);
}


Piece emptySquare(" ", " ", PieceType::Void, NotRoyal, f_VoidCanNotMove);

Piece wPawn("P", "", Color::WHITE, NotRoyal, f_TurnIntoMovedPiece);//en passant
Piece wMovedPawn("P", "", Color::WHITE, NotRoyal, f_WhitePromotionAndEnPassant);
Piece wRook("R", "R", Color::WHITE, NotRoyal, f_TurnIntoMovedPiece);
Piece wMovedRook("R", "R", Color::WHITE, NotRoyal, f_RegularMove);
Piece wKnight("N", "N", Color::WHITE, NotRoyal, f_RegularMove);
Piece wBishop("B", "B", Color::WHITE, NotRoyal, f_RegularMove);
Piece wQueen("Q", "Q", Color::WHITE, NotRoyal, f_RegularMove);
Piece wKing("K", "K", Color::WHITE, Royal, f_WhiteCastle);//add castle
Piece wMovedKing("K", "K", Color::WHITE, Royal, f_RegularMove);

Piece bPawn("p", "", Color::BLACK, NotRoyal, f_TurnIntoMovedPiece);//en passant
Piece bMovedPawn("p", "", Color::BLACK, NotRoyal, f_BlackPromotionAndEnPassant);
Piece bRook("r", "R", Color::BLACK, NotRoyal, f_TurnIntoMovedPiece);
Piece bMovedRook("r", "R", Color::BLACK, NotRoyal, f_RegularMove);
Piece bKnight("n", "N", Color::BLACK, NotRoyal, f_RegularMove);
Piece bBishop("b", "B", Color::BLACK, NotRoyal, f_RegularMove);
Piece bQueen("q", "Q", Color::BLACK, NotRoyal, f_RegularMove);
Piece bKing("k", "K", Color::BLACK, Royal, f_BlackCastle);//add castle
Piece bMovedKing("k", "K", Color::BLACK, Royal, f_RegularMove);


Piece Piece::PieceArray[19] = { emptySquare,
    bPawn,wPawn, bMovedPawn ,wMovedPawn,bRook,wRook,
    bMovedRook,wMovedRook,bKnight,wKnight,bBishop,wBishop,bQueen,wQueen,
    bKing,wKing,bMovedKing,wMovedKing
};
