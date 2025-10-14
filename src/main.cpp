#include <iostream>
#include <map>
#include <stdint.h>
#include <string>

#include "Board.h"
#include "HelperStructs.h"
#include "ScrollableGame.h"
#include "SetupGame.h"
#include "VConstructor.h"
#include "VConstructorClasses.h"
#include "Timeline.h"

using namespace std;

enum {
    a = 0, b = 1, c = 2, d = 3, e = 4, f = 5, g = 6, h = 7,
    _1 = 0, _2 = 1, _3 = 2, _4 = 3, _5 = 4, _6 = 5, _7 = 6, _8 = 7,
    l0 = 64, l1 = 63, l2 = 62, lminus1 = 65, lminus2 = 66
};

class Timeline;

int main()
{
    std::map<std::string, std::pair<VConstructor*, Location>> temp;

    temp[ConstructSquares::name] = { new ConstructSquares(8, 8, 1), Location::BOARD };
    temp["en passant"] = {new VConstructorTemplate<ByDefaultZeros, ConstructCopy>(2), Location::BOARD};
    SetupGame setup(temp);
  
    BorderBoard g;
    g.x = 8;
    g.y = 8;

    ScrollableGame a(XYTL(8, 8, 512, 129), l0, l0, 2);

    setup.Setup(a);
    a.SetTimeline(l0, Timeline::CreateTimelinePointer(500, 64, 1, Board::StartingPosition8x8));
    
    a.GetTimeline(l0).CreateNextTurnSamePointer();
    Move move;
    move.SetMoveByString(a,"(0T1)d2d4",0);
    Move move2;
    move2.SetMoveByString(a,"(0T1)Ng8>>(0T0)g6",1);
    Move move3;
    move3.SetMoveByString(a,"(-1T1)Ng1f3",0);
    a.MakeMove(move);
    a.MakeMove(move2);
    a.MakeMove(move3);

    const string test = "game.txt";

   
    a.Print(); 
}
