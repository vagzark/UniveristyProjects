#include <iostream>
#include <cstdlib>
#include "player.hpp"

Player::Player(int id)
{
    this->id=id;
    numPieces = 21;

    pieces = new Piece*[21];

    if(id == 0){
        this->name = "Player 1";
        symbol='#';
    }
    else
    {
        this->name = "Player 2";
        symbol='O';
    }

    createPieces();
}

Player::~Player()
{
    for(int i=0; i<numPieces; i++)
        delete pieces[i];
    delete [] pieces;
}

int Player::getId()
{
    return id;
}

char Player::getSymbol()
{
    return symbol;
}

string Player::getName()
{
    return name;
}

Piece* Player::getPiece(int index)
{
    return pieces[index];
}

int Player::getNumberOfPlacedPieces()
{
    int counter=0;//counter of placed pieces

    for(int i=0; i<numPieces; i++)
        if(pieces[i]->isPlaced()==true)
            counter++;

    return counter;
}

int Player::getNumberOfAvailablePieces()
{
    int counter=0;////counter of available pieces

    for(int i=0; i<numPieces; i++)
        if(pieces[i]->isPlaced()==false)
            counter++;

    return counter;
}



HumanPlayer :: HumanPlayer(int id): Player(id){}

HumanPlayer::HumanPlayer(int id, string name):Player(id)
{
    this->name = name;
}


int ComputerPlayer::getRandomPieceId()
{
    return 1 + rand()% 21;
}


Orientation ComputerPlayer::getRandomOrientation()
{
    int x;
    x = rand() % 4;
    return (Orientation)x;
}

Flip ComputerPlayer::getRandomFlip()
{
    int x;
    x = rand() % 2;
    return (Flip)x;
}

ComputerPlayer :: ComputerPlayer(int id): Player(id){}
