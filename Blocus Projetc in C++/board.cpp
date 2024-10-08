#include <iostream>
#include <cstdlib>
#include "board.hpp"
#include "player.hpp"

using namespace std;

Board::Board() {
    boardSizeX = 14;
    boardSizeY = 14;
    squares = new Square**[boardSizeX];
    for (int i = 0; i < boardSizeX; i++) {
        squares[i] = new Square*[boardSizeY];
        for (int j = 0; j < boardSizeY; j++)
            squares[i][j] = new Square(i, j);
    }
}

Board::~Board() {
    for (int i = 0; i < boardSizeX; i++) {
        for(int j = 0; j < boardSizeY; j++)
            delete squares[i][j];
        delete[] squares[i];
    }
    delete[] squares;
}

int Board::getSizeX() {
    return boardSizeX;
}

int Board::getSizeY() {
    return boardSizeY;
}

bool Board::hasPiece(int x, int y) {
    return squares[x][y]->hasPiece();
}

bool Board::squareBelongsToPlayer(int x, int y, char player) {
    return squares[x][y]->getPlayer() == player;
}

bool Board::squareBelongsToPlayer(int x, int y, Player* player) {
    return squareBelongsToPlayer(x, y, player->getSymbol());
}

bool Board::playerHasPlacedNoPieces(char player) {
    for (int i = 0; i < boardSizeX; i++) {
        for (int j = 0; j < boardSizeY; j++) {
            if (squares[i][j]->getPlayer() == player)
                return false;
        }
    }
    return true;
}

Piece* Board::getLastPiecePlayedByPlayer(Player* player){
    return player->getSymbol() == '#' ? lastPiecePlayedByFirstPlayer : lastPiecePlayedBySecondPlayer;
}

bool Board::pieceCanBePlaced(Piece* piece, int x, int y, Orientation orientation, Flip flip){
    // Make a copy of the piece to rotate and flip it virtually
    Piece* cpiece = piece->deepCopy();

    // Rotate and flip piece
    cpiece->rotatePiece(orientation);
    if (flip == YES)
        cpiece->flipPiece();

    // Check if piece can be placed on the board
    bool canBePlaced = pieceCanBePlaced(cpiece, x, y);

    // Delete the copy of piece that was created
    delete cpiece;

    // Return whether the piece can be placed
    return canBePlaced;
}

void Board::placePiece(Piece* piece, int x, int y) {
    // Play the move by setting the board squares
    for(int i = 0; i < piece->getSizeX(); i++) {
        for(int j = 0; j < piece->getSizeY(); j++) {
            if (piece->squareHasPiece(i, j))
                squares[x + i][y + j]->addPiece(piece->getPlayer());
        }
    }

    // Set the piece as placed
    piece->setPlaced();
    if (piece->getPlayer() == '#')
        lastPiecePlayedByFirstPlayer = piece;
    else
        lastPiecePlayedBySecondPlayer = piece;
}

void Board::placePiece(Piece* piece, int x, int y, Orientation orientation, Flip flip) {
    // Rotate and flip piece
    piece->rotatePiece(orientation);
    if (flip == YES)
        piece->flipPiece();

    placePiece(piece, x, y);
}

string Board::toString() {
    stringstream sstm;
    sstm << "     ________________________________________________ \n"
         << "    |                                                |\n"
         << "    |      0  1  2  3  4  5  6  7  8  9 10 11 12 13  |\n";
    for(int i = 0; i < boardSizeX; i++) {
        sstm << "    |  " << i << " ";
        if (i < 10) sstm << " ";
        for(int j = 0; j < boardSizeY; j++)
            sstm << " " << (hasPiece(i, j) ? squares[i][j]->getPlayer() : '-') << " ";
        sstm << " |\n";
    }
    sstm << "    |________________________________________________|\n";
    return sstm.str();
};

Board* Board::deepCopy() {
    Board* board = new Board();
    for (int i = 0; i < boardSizeX; i++) {
        for (int j = 0; j < boardSizeY; j++) {
            board->squares[i][j]->addPiece(squares[i][j]->getPlayer());
        }
    }
    return board;
}
