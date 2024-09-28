//
//  player.hpp
//  ergasia
//
//  Created by apple on 27/5/22.
//

#ifndef player_hpp
#define player_hpp

#include <string>
#include "move.hpp"
#include "piece.hpp"
#include "board.hpp"

/**
 * Class that implements a player of the game.
 */
class Player {
private:
    int id;
    char symbol;
protected:
    string name;
    int numPieces; // the number of pieces of the player (initialized to 21)
    Piece** pieces; // the pieces of the player

public:
    /**
     * Initializes a player setting the index and the name. The numPieces is set to 21 and the numPlacedPieces is set to zero.
     * Finally, the createPieces method must be called to create all the pieces of the player.
     *
     * @param id the id of the player.
     */
    Player(int id);

    /**
     * Deletes this player by deleting the array of pieces.
     */
    ~Player();

    /**
     * Returns the id of the player.
     *
     * @return the id of the player.
     */
    int getId();

    /**
     * Returns the symbol of the player (# for the first player, O for the second).
     *
     * @return the symbol of the player as a char '#' or 'O'.
     */
    char getSymbol();


    /**
     * Returns the name of the player.
     *
     * @return the name of the player.
     */
    string getName();

    /**
     * Returns a piece of the player given its index.
     *
     * @param index the index of the piece to be returned.
     * @return a piece of the player given its index.
     */
    Piece* getPiece(int index);

    /**
     * Returns the number of the placed pieces of the player, i.e. the number
     * of pieces that have been placed on the board.
     *
     * @return the number of the placed pieces of the player.
     */
    int getNumberOfPlacedPieces();

    /**
     * Returns the number of the available pieces of the player, i.e. the number
     * of pieces that have not been placed yet.
     *
     * @return the number of the available pieces of the player.
     */
    int getNumberOfAvailablePieces();

    /// THE METHODS OF PLAYER BELOW THIS POINT ARE IMPLEMENTED IN FILE playerpieces.cpp
    /**
     * Checks if the player can place the given piece in any square of the board, any orientation and any flip.
     *
     * @param board the board to check if any piece can be placed.
     * @param piece the piece to check if it can be placed.
     * @return true if the piece can be placed on the board, or false otherwise.
     */
    bool canPlacePiece(Board* board, Piece* piece);

    /**
     * Checks if the player can place any piece in any square of the board, any orientation and any flip.
     * This method is used to determine whether the player can make any move in order to end the game.
     *
     * @param board the board to check if any piece can be placed.
     * @return true if the piece can be placed on the board, or false otherwise.
     */
    bool canPlaceAnyPiece(Board* board);

    /**
     * Prints the available pieces of the player, This method calls the printPiecesSideBySide method to
     * print the pieces side by side.
     */
    void printAvailablePieces();

private:
    /**
     * Creates the pieces of the player by calling the different constructors.
     */
    void createPieces();

    /**
     * Prints the given pieces from pstart to pend side by side.
     *
     * @param pieces the pieces to be printed.
     * @param pstart the start index of the array of pieces to be printed.
     * @param pend the end index of the array of pieces to be printed.
     */
    void printPiecesSideBySide(Piece** pieces, int pstart, int pend);
};

/**
 * Class that implements (υλοποιει) a human player that plays according to the input given by the console.
 */
class HumanPlayer : public Player {
public:
    /**
     * Initializes a human player calling the constructor of the player.
     *
     * @param id the id of the player.
     */
    HumanPlayer(int id);

    /**
     * Initializes a human player calling the constructor of the player and setting (overriding)
     * also the name of the player.
     *
     * @param id the id of the player.
     * @param name the name of the player.
     */
    HumanPlayer(int id, string name);

    /// THE METHODS OF HUMANPLAYER BELOW THIS POINT ARE IMPLEMENTED IN FILE playerpieces.cpp
    /**
     * Receives the current state of the board and returns a move. A move contains the piece
     * to be placed on the board, its position (x, y), its orientation, and its flip.
     * The information of the move is read by the console.
     *
     * @return an object of type Move containing a piece, its position, its orientation, and its flip..
     */
    Move* placePiece(Board* board);
};

/**
 * Class that implements a computer player that plays randomly.
 */
class ComputerPlayer : public Player {
public:
    /**
     * Returns a random id for a piece of the player. Pieces have ids from 1 to 21, so this method
     * returns an integer from 1 to 21 (including 1 and including 21).
     *
     * @return a random id for a piece of the player between 1 and 21.
     */
    int getRandomPieceId();

    /**
     * Returns a random orientation value for a piece of the player. Orientation values can be
     * UP, RIGHT, DOWN, LEFT so this method returns an orientation among these four.
     *
     * @return a random orientation value among UP, RIGHT, DOWN, and LEFT.
     */
    Orientation getRandomOrientation();

    /**
     * Returns a random flip value for a piece of the player. Flip values can be NO, YES
     * so this method returns a flip between these two values.
     *
     * @return a random flip value between NO and YES.
     */
    Flip getRandomFlip();

    /**
     * Initializes a computer player calling the constructor of the player.
     *
     * @param id the id of the player.
     */
    ComputerPlayer(int id);

    /// THE METHODS OF COMPUTERPLAYER BELOW THIS POINT ARE IMPLEMENTED IN FILE playerpieces.cpp
    /**
     * Receives the current state of the board and returns a random move. A move contains the piece
     * to be placed on the board, its position (x, y), its orientation, and its flip.
     *
     * @return an object of type Move containing a piece, its position, its orientation, and its flip..
     */
    Move* placePiece(Board* board);
};


#endif /* player_hpp */
