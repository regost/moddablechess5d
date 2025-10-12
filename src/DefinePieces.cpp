
#include "Piece.h"
#include "Game.h"
#include "Timeline.h"
#include "Piece.h"
#include "Board.h"
#include "HelperStructs.h"

enum colorEnum {
    Royal = true, NotRoyal = false
};
enum ColorType {
    White = true, Black = false
};

enum PieceType {
    Void = 0,
    BMovedKing = 17,
    WMovedKing = 18,
    BMovedRook = 7,
    WMovedRook = 8
};

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

Piece wPawn("P", "", ColorType::White, NotRoyal, f_TurnIntoMovedPiece);//en passant
Piece wMovedPawn("P", "", ColorType::White, NotRoyal, f_WhitePromotionAndEnPassant);
Piece wRook("R", "R", ColorType::White, NotRoyal, f_TurnIntoMovedPiece);
Piece wMovedRook("R", "R", ColorType::White, NotRoyal, f_RegularMove);
Piece wKnight("N", "N", ColorType::White, NotRoyal, f_RegularMove);
Piece wBishop("B", "B", ColorType::White, NotRoyal, f_RegularMove);
Piece wQueen("Q", "Q", ColorType::White, NotRoyal, f_RegularMove);
Piece wKing("K", "K", ColorType::White, Royal, f_WhiteCastle);//add castle
Piece wMovedKing("K", "K", ColorType::White, Royal, f_RegularMove);

Piece bPawn("p", "", ColorType::Black, NotRoyal, f_TurnIntoMovedPiece);//en passant
Piece bMovedPawn("p", "", ColorType::Black, NotRoyal, f_BlackPromotionAndEnPassant);
Piece bRook("r", "R", ColorType::Black, NotRoyal, f_TurnIntoMovedPiece);
Piece bMovedRook("r", "R", ColorType::Black, NotRoyal, f_RegularMove);
Piece bKnight("n", "N", ColorType::Black, NotRoyal, f_RegularMove);
Piece bBishop("b", "B", ColorType::Black, NotRoyal, f_RegularMove);
Piece bQueen("q", "Q", ColorType::Black, NotRoyal, f_RegularMove);
Piece bKing("k", "K", ColorType::Black, Royal, f_BlackCastle);//add castle
Piece bMovedKing("k", "K", ColorType::Black, Royal, f_RegularMove);


Piece Piece::PieceArray[19] = { emptySquare,
    bPawn,wPawn, bMovedPawn ,wMovedPawn,bRook,wRook,
    bMovedRook,wMovedRook,bKnight,wKnight,bBishop,wBishop,bQueen,wQueen,
    bKing,wKing,bMovedKing,wMovedKing
};
