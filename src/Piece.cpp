

#include "Piece.h"
#include "HelperStructs.h"
#include "Game.h"

float Piece::spriteSize = 512;

bool Piece::CanTakeThePiece(bool color_)
{
    return this->color != color_;
}

//void Piece::SetSprites()
//{
//    Texture& texture = *TextureBuffer::getTexture("pieces.png");
//
//    //texture.setSmooth(true);
//
//    const int xStep = texture.getSize().x / 6;
//    const int yStep = texture.getSize().y / 2;
//
//    for (int i = 1; i <= 18; ++i) {
//        Piece::PieceArray[i].sprite.setTexture(texture);
//    }
//    Piece::PieceArray[2].sprite.setTextureRect(IntRect(0, 0, xStep, yStep));
//    Piece::PieceArray[4].sprite.setTextureRect(IntRect(0, 0, xStep, yStep));
//    Piece::PieceArray[6].sprite.setTextureRect(IntRect(xStep * 3, 0, xStep, yStep));
//    Piece::PieceArray[8].sprite.setTextureRect(IntRect(xStep * 3, 0, xStep, yStep));
//    Piece::PieceArray[10].sprite.setTextureRect(IntRect(xStep * 1, 0, xStep, yStep));
//    Piece::PieceArray[12].sprite.setTextureRect(IntRect(xStep * 2, 0, xStep, yStep));
//    Piece::PieceArray[14].sprite.setTextureRect(IntRect(xStep * 4, 0, xStep, yStep));
//    Piece::PieceArray[16].sprite.setTextureRect(IntRect(xStep * 5, 0, xStep, yStep));
//    Piece::PieceArray[18].sprite.setTextureRect(IntRect(xStep * 5, 0, xStep, yStep));
//
//    Piece::PieceArray[1].sprite.setTextureRect(IntRect(0, yStep, xStep, yStep));
//    Piece::PieceArray[3].sprite.setTextureRect(IntRect(0, yStep, xStep, yStep));
//    Piece::PieceArray[5].sprite.setTextureRect(IntRect(xStep * 3, yStep, xStep, yStep));
//    Piece::PieceArray[7].sprite.setTextureRect(IntRect(xStep * 3, yStep, xStep, yStep));
//    Piece::PieceArray[9].sprite.setTextureRect(IntRect(xStep * 1, yStep, xStep, yStep));
//    Piece::PieceArray[11].sprite.setTextureRect(IntRect(xStep * 2, yStep, xStep, yStep));
//    Piece::PieceArray[13].sprite.setTextureRect(IntRect(xStep * 4, yStep, xStep, yStep));
//    Piece::PieceArray[15].sprite.setTextureRect(IntRect(xStep * 5, yStep, xStep, yStep));
//    Piece::PieceArray[17].sprite.setTextureRect(IntRect(xStep * 5, yStep, xStep, yStep));
//}



Piece::Piece(string FEN, string PGN, bool color_, bool isRoyal_, function<void(Game&, Turn)> makeMove_)
{
    this->FEN = FEN;
    this->PGN = PGN;
    this->color = color_;
    this->makeMove = makeMove_;

}