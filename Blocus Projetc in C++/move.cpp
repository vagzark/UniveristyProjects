#include "move.hpp"

Move::Move(Piece* piece, int x, int y, Orientation orientation, Flip flip){
    this->piece = piece;
    this->x = x;
    this->y = y;
    this->orientation = orientation;
    this->flip = flip;
}

void Move::setPiece(Piece* piece){
    this->piece = piece;
}

Piece* Move::getPiece(){
    return piece;
}

int Move::getX(){
    return x;
}

int Move::getY(){
    return y;
}

Orientation Move::getOrientation(){
    return orientation;
}

Flip Move::getFlip(){
    return flip;
}
