#include "VirtualMove.h"

void VRegularMove::MakeMove(Game &chess){this->move.MakeMove(chess);}
void VRegularMove::UndoMove(Game &chess){this->move.UndoMove(chess);}
void VRegularMove::GetString(Game &chess, string &str){this->move.GetString(chess,str);}
void VRegularMove::SetMoveByString(Game &chess, const string &parse, uint16_t color)
{this->move.SetMoveByString(chess,parse,color);}


void MoveWrapper::MakeMove(Game &chess){this->move->MakeMove(chess);}
void MoveWrapper::UndoMove(Game &chess){this->move->UndoMove(chess);}
void MoveWrapper::GetString(Game &chess, string &str){this->move->GetString(chess,str);}
void MoveWrapper::SetMoveByString(Game &chess, const string &parse, uint16_t color)
{this->move->SetMoveByString(chess,parse,color);}
MoveWrapper::~MoveWrapper(){delete this->move;}
