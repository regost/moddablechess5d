#include "VirtualMove.h"



//functions only
void VtableMove::inherittable(const VtableMove &table)
{
    if(table.makemove != nullptr){
        this->makemove = table.makemove;
    }
    if(table.undomove != nullptr){
        this->undomove = table.undomove;
    }
    if(table.setmovebyparsing != nullptr){
        this->setmovebyparsing = table.setmovebyparsing;
    }
    if(table.getstringnotation != nullptr){
        this->getstringnotation = table.getstringnotation;
    }
}

void VtableMove::SetFunctions(
void (*makemove)(Game &chess, DataMove *data, VtableMove *table), 
void (*undomove)(Game &chess, DataMove *data, VtableMove *table), 
void (*getstringnotation)(Game &chess, string &str, DataMove *data, VtableMove *table), 
void (*setmovebyparsing)(Game &chess, const string &parse, uint16_t color, DataMove *data, VtableMove *table)
)
{
    this->makemove = makemove;
    this->undomove = undomove;
    this->getstringnotation = getstringnotation;
    this->setmovebyparsing = setmovebyparsing;

}

void DataMove::MakeMove(Game &chess)
{
    this->table->makemove(chess,this,this->table);
}

void DataMove::UndoMove(Game &chess)
{
    this->table->undomove(chess,this,this->table);
}

void DataMove::GetString(Game &chess, string &str)
{
    this->table->getstringnotation(chess,str,this,this->table);
}

void DataMove::SetMove(Game &chess, const string &parse, uint16_t color)
{
    this->table->setmovebyparsing(chess,parse,color,this,this->table);
}

template <typename T>
inline T& DataMove::get()
{
    const void* ptr = this;
    const T& ref = *(T*)(ptr);
    return ref;
}