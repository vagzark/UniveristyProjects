//
//  main.cpp
//  ergasia
//
//  Created by apple on 27/5/22.
//

#include <ctime>
#include <cstdlib>
#include <iostream>
#include "player.hpp"

using namespace std;

int main() {
    // Uncomment the following line to make the moves random
    srand(time(NULL));

    // Initialize the game objects
    Board* board = new Board();
    Player** players = new Player*[2];
    players[0] = new ComputerPlayer(0);
    players[1] = new ComputerPlayer(1);

    int playerTurn = 0;
    do {
        cout << endl << "Board:" << endl << board->toString();
        players[playerTurn]->printAvailablePieces();

        if (players[playerTurn]->canPlaceAnyPiece(board)) {
            // Determine and play the next move
            Move* pmove = ((ComputerPlayer*)players[playerTurn])->placePiece(board);
            board->placePiece(pmove->getPiece(), pmove->getX(), pmove->getY(), pmove->getOrientation(), pmove->getFlip());
            delete pmove;
        }

        playerTurn = 1 - playerTurn;
        // Uncomment the following line to add a delay
    //for(int i = 0; i < 100000000; i++);
    } while(players[0]->canPlaceAnyPiece(board) || players[1]->canPlaceAnyPiece(board));
    cout << endl << "Board:" << endl << board->toString();
    players[0]->printAvailablePieces();
    players[1]->printAvailablePieces();

    // Print the winner and the final score of the game
    int player1points = board->computeScore(players[0]);
    int player2points = board->computeScore(players[1]);
    if (player1points > player2points)
        cout << players[0]->getName() << " has won! (Score: " << player1points << " - " << player2points << ")" << endl;
    else if (player1points < player2points)
        cout << players[1]->getName() << " has won! (Score: " << player1points << " - " << player2points << ")" << endl;
    else
        cout << "It's a draw! (Score: " << player1points << " - " << player2points << ")" << endl;

    delete board;
    for (int i = 0; i < 2; i++)
        delete players[i];
    delete[] players;

    return 0;
}

