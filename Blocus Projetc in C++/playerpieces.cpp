#include <iomanip>
#include <cstdlib>
#include <iostream>

#include "player.hpp"

void Player::createPieces() {
    char o = (id == 0 ? '#' : 'O'), i = '-';

    char allspieces[21][5][5] = {{
                                {o, i, i, i, i}, // Piece 1
                                {i, i, i, i, i},
                                {i, i, i, i, i},
                                {i, i, i, i, i},
                                {i, i, i, i, i}
                                }, {
                                {o, i, i, i, i}, // Piece 2
                                {o, i, i, i, i},
                                {i, i, i, i, i},
                                {i, i, i, i, i},
                                {i, i, i, i, i}
                                }, {
                                {o, i, i, i, i}, // Piece 3
                                {o, i, i, i, i},
                                {o, i, i, i, i},
                                {i, i, i, i, i},
                                {i, i, i, i, i}
                                }, {
                                {o, i, i, i, i}, // Piece 4
                                {o, o, i, i, i},
                                {i, i, i, i, i},
                                {i, i, i, i, i},
                                {i, i, i, i, i}
                                }, {
                                {o, i, i, i, i}, // Piece 5
                                {o, i, i, i, i},
                                {o, i, i, i, i},
                                {o, i, i, i, i},
                                {i, i, i, i, i}
                                }, {
                                {i, o, i, i, i}, // Piece 6
                                {i, o, i, i, i},
                                {o, o, i, i, i},
                                {i, i, i, i, i},
                                {i, i, i, i, i}
                                }, {
                                {o, i, i, i, i}, // Piece 7
                                {o, o, i, i, i},
                                {o, i, i, i, i},
                                {i, i, i, i, i},
                                {i, i, i, i, i}
                                }, {
                                {o, o, i, i, i}, // Piece 8
                                {o, o, i, i, i},
                                {i, i, i, i, i},
                                {i, i, i, i, i},
                                {i, i, i, i, i}
                                }, {
                                {o, o, i, i, i}, // Piece 9
                                {i, o, o, i, i},
                                {i, i, i, i, i},
                                {i, i, i, i, i},
                                {i, i, i, i, i}
                                }, {
                                {o, i, i, i, i}, // Piece 10
                                {o, i, i, i, i},
                                {o, i, i, i, i},
                                {o, i, i, i, i},
                                {o, i, i, i, i}
                                }, {
                                {i, o, i, i, i}, // Piece 11
                                {i, o, i, i, i},
                                {i, o, i, i, i},
                                {o, o, i, i, i},
                                {i, i, i, i, i}
                                }, {
                                {i, o, i, i, i}, // Piece 12
                                {i, o, i, i, i},
                                {o, o, i, i, i},
                                {o, i, i, i, i},
                                {i, i, i, i, i}
                                }, {
                                {i, o, i, i, i}, // Piece 13
                                {o, o, i, i, i},
                                {o, o, i, i, i},
                                {i, i, i, i, i},
                                {i, i, i, i, i}
                                }, {
                                {o, o, i, i, i}, // Piece 14
                                {i, o, i, i, i},
                                {o, o, i, i, i},
                                {i, i, i, i, i},
                                {i, i, i, i, i}
                                }, {
                                {o, i, i, i, i}, // Piece 15
                                {o, o, i, i, i},
                                {o, i, i, i, i},
                                {o, i, i, i, i},
                                {i, i, i, i, i}
                                }, {
                                {i, o, i, i, i}, // Piece 16
                                {i, o, i, i, i},
                                {o, o, o, i, i},
                                {i, i, i, i, i},
                                {i, i, i, i, i}
                                }, {
                                {o, i, i, i, i}, // Piece 17
                                {o, i, i, i, i},
                                {o, o, o, i, i},
                                {i, i, i, i, i},
                                {i, i, i, i, i}
                                }, {
                                {o, o, i, i, i}, // Piece 18
                                {i, o, o, i, i},
                                {i, i, o, i, i},
                                {i, i, i, i, i},
                                {i, i, i, i, i}
                                }, {
                                {o, i, i, i, i}, // Piece 19
                                {o, o, o, i, i},
                                {i, i, o, i, i},
                                {i, i, i, i, i},
                                {i, i, i, i, i}
                                }, {
                                {o, i, i, i, i}, // Piece 20
                                {o, o, o, i, i},
                                {i, o, i, i, i},
                                {i, i, i, i, i},
                                {i, i, i, i, i}
                                }, {
                                {i, o, i, i, i}, // Piece 21
                                {o, o, o, i, i},
                                {i, o, i, i, i},
                                {i, i, i, i, i},
                                {i, i, i, i, i}
                            }};
    for (int i = 0; i < 21; i++){
        // Compute the size of each piece
        int sizeX = 0;
        int sizeY = 0;
        for(int x = 0; x < 5; x++){
            for(int y = 0; y < 5; y++) {
                if (allspieces[i][x][y] != '-'){
                    sizeX = (x + 1 > sizeX) ? (x + 1) : sizeX;
                    sizeY = (y + 1 > sizeY) ? (y + 1) : sizeY;
                }
            }
        }
        // Create the squares of each piece
        Square*** squares = new Square**[sizeX];
        for(int x = 0; x < sizeX; x++) {
            squares[x] = new Square*[sizeY];
            for(int y = 0; y < sizeY; y++) {
                squares[x][y] = new Square(x, y, allspieces[i][x][y]);
            }
        }
        // Create the piece
        pieces[i] = new Piece(i + 1, id == 0 ? '#' : 'O', squares, sizeX, sizeY);
    }
};

void Player::printPiecesSideBySide(Piece** pieces, int pstart, int pend){
    // Compute the number of pieces to be print
    int numPieces = pend - pstart;

    // Print the ids of the pieces and concatenate the pieces using a stream
    stringstream ss[numPieces];
    cout << "   ";
    for (int i = pstart; i < pend; i++){
        cout << (pieces[i]->getId() > 9 ? "" : " ") << pieces[i]->getId() << "          ";
        ss[i - pstart] << pieces[i]->toString();
    }
    cout << endl;

    // Print the pieces line by line
    string to[numPieces];
    for (int j = 0; j < 5; j++){
        for (int i = pstart; i < pend; i++){
            getline(ss[i - pstart], to[i - pstart], '\n');
            cout << to[i - pstart] << "   ";
        }
        cout << endl;
    }
}

void Player::printAvailablePieces(){
    // Create an array with the available pieces of the player
    int numAvailablePieces = getNumberOfAvailablePieces();
    Piece** availablePieces = new Piece*[numAvailablePieces];
    int j = 0;
    for (int i = 0; i < numPieces; i++){
        if (!pieces[i]->isPlaced())
            availablePieces[j++] = pieces[i];
    }

    // Print the name of the player, the number of available pieces, and the available pieces
    cout << "\n\nPlayer " << (id + 1) << " has " << numAvailablePieces << " available pieces:" << endl;
    if (numAvailablePieces > 7){
        printPiecesSideBySide(availablePieces, 0, 7);
        if (numAvailablePieces > 14){
            printPiecesSideBySide(availablePieces, 7, 14);
            printPiecesSideBySide(availablePieces, 14, numAvailablePieces);
        }
        else
            printPiecesSideBySide(availablePieces, 7, numAvailablePieces);
    }
    else
        printPiecesSideBySide(availablePieces, 0, numAvailablePieces);
    delete[] availablePieces;
}

bool Player::canPlacePiece(Board* board, Piece* piece) {
    Orientation orientations[] = {UP, RIGHT, DOWN, LEFT};
    Flip flips[] = {NO, YES};
    if (!piece->isPlaced()) {
        for (int x = 0; x < board->getSizeX(); x++) {
            for (int y = 0; y < board->getSizeY(); y++) {
                for (int o = 0; o < 4; o++) {
                    for (int f = 0; f < 2; f++) {
                        if (board->pieceCanBePlaced(piece, x, y, orientations[o], flips[f]))
                            return true;
                    }
                }
            }
        }
    }
    return false;
}

bool Player::canPlaceAnyPiece(Board* board) {
    for (int i = 0; i < numPieces; i++) {
        if (canPlacePiece(board, pieces[i]))
            return true;
    }
    return false;
}

Move* HumanPlayer::placePiece(Board* board) {
    int pieceId, x, y;
    int orientation, flip;
    cout << "Select piece (1-21), orientation (0 for UP, 1 for RIGHT, 2 for DOWN, 3 for LEFT), " <<
            "flip (0 for NO, 1 for YES), position (x, y), (e.g. 3 0 0 3 4): " << endl;
    if (getNumberOfPlacedPieces() == 0)
        cout << "First piece must touch square " << (getId() == 0 ? "4, 4" : "9, 9") << endl;
    cin >> pieceId >> orientation >> flip >> x >> y;
    return new Move(pieces[pieceId-1], x, y, (Orientation)orientation, (Flip)flip);
}

Move* ComputerPlayer::placePiece(Board* board) {
    int pieceId, x, y;
    Orientation orientation;
    Flip flip;
    Piece* piece;
    do {
        pieceId = getRandomPieceId();
        piece = pieces[pieceId-1];
        x = rand() % board->getSizeX();
        y = rand() % board->getSizeY();
        orientation = getRandomOrientation();
        flip = getRandomFlip();
    } while(piece->isPlaced() || !board->pieceCanBePlaced(piece, x, y, orientation, flip));
    return new Move(piece, x, y, orientation, flip);
}

