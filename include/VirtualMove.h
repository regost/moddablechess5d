
#include "Game.h"
#include "usingnames.h"
#include "HelperStructs.h"
#include <string>
class Game;
class MoveWrapper;
struct XYTL;
struct Move;

//regular Vtable cant store variables
class Vtable{
public:
	//void(*) (Game& chess) MakeMove;
	void UndoMove(Game& chess){};
	void GetString(Game& chess, string& str){};
	void SetMoveByString(Game& chess, const string& parse,uint16_t color){};
};


class VirtualMove{
public:
	virtual void MakeMove(Game& chess){};
	virtual void UndoMove(Game& chess){};
	virtual void GetString(Game& chess, string& str){};
	virtual void SetMoveByString(Game& chess, const string& parse,uint16_t color){};
    virtual ~VirtualMove(){};
};

class VRegularMove : virtual public VirtualMove {
    Move move;
public:
    void MakeMove(Game& chess) override;
    void UndoMove(Game& chess) override;
    void GetString(Game& chess, string& str) override;
    //["name"] move if a move isnt regular 
    //"(0T1)Ng1f3"
    //"[jump] (0T1)e8" but [jump] gets cut off when passing the string in that function
    void SetMoveByString(Game& chess, const string& parse, uint16_t color) override;
};

class MoveWrapper {
    VirtualMove* move = nullptr;
public:
    void MakeMove(Game& chess);
    void UndoMove(Game& chess);
    void GetString(Game& chess, string& str);
    void SetMoveByString(Game& chess, const string& parse, uint16_t color);
    MoveWrapper() = default;
    ~MoveWrapper();
};

//8 bytes
class VCastle : virtual public VirtualMove{
    inline static string name = "castle";
    XYTL king;
    uint8_t kingendx;
    uint8_t rookendx;
    
    //we dont know where the info is stored so we have store that variable
    uint16_t location;
    void MakeMove(Game& chess) override;
    void UndoMove(Game& chess) override;
    void GetString(Game& chess, string& str) override;
    void SetMoveByString(Game& chess, const string& parse,uint16_t color) override;
};