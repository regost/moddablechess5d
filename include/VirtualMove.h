
#include "Game.h"
#include "usingnames.h"
#include "HelperStructs.h"
#include <string>

class Game;
struct XYTL;
struct Move;
class VtableMove;

class DataMove {
    VtableMove* table = nullptr;
public:
    DataMove() = default;
    DataMove(initializer_list<VtableMove>& list);
    void MakeMove(Game& chess);
    void UndoMove(Game& chess);
    void GetString(Game& chess,string& str);
    void SetMove(Game& chess, const string& parse, uint16_t color);
    template <typename T> T& get();
};

//regular Vtable cant store variables
class VtableMove{
public:
    void(*makemove) (Game& chess, DataMove* data,VtableMove* table) = nullptr;
	void(*undomove) (Game& chess, DataMove* data,VtableMove* table) = nullptr;
    void(*getstringnotation) (Game& chess, string& str, DataMove* data,VtableMove* table) = nullptr;
	void(*setmovebyparsing)(Game& chess, const string& parse, uint16_t color ,DataMove* data,VtableMove* table) = nullptr;
    void inherittable(const VtableMove& table);
    VtableMove() = default;
    void SetFunctions(
        void(*makemove) (Game& chess, DataMove* data,VtableMove* table),
        void(*undomove) (Game& chess, DataMove* data,VtableMove* table),
        void(*getstringnotation) (Game& chess, string& str, DataMove* data,VtableMove* table),
        void(*setmovebyparsing)(Game& chess, const string& parse, uint16_t color ,DataMove* data,VtableMove* table)
    );
};

class DataRegularMove : public DataMove{
    Move move;
    DataRegularMove() = default;
};


