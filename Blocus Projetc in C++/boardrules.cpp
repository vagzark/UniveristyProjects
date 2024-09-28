#include "board.hpp"
#include "player.hpp"
#include <iostream>
#include <cstdlib>

bool Board::pieceCanBePlaced(Piece* piece, int x, int y)
{
    if(playerHasPlacedNoPieces(piece->getPlayer()))//case where the piece is the first one to be placed by the player
        {
            if(piece->getPlayer()=='#')
            {
                int i,j;

                if(x>4 || y>4)
                    return false;

                for(i=0;i<piece->getSizeX();i++)
                    for(j=0;j<piece->getSizeY();j++)
                    {
                        if((x+i)==4 && (y+j)==4)
                        {
                            if(piece->squareHasPiece(i,j)==true)
                            {
                                return true;
                            }
                        }
                    }
            }
            else if(piece->getPlayer()=='O')
            {
                int i,j;

                if(x>9 || y>9)
                {
                    return false;
                }
                for(i=0;i<piece->getSizeX();i++)
                    for(j=0;j<piece->getSizeY();j++)
                        if((x+i)==9 && (y+j)==9)
                        {
                            if(piece->squareHasPiece(i,j)==true)
                                return true;
                        }
            }

            return false;
        }//case where the piece is not the first one to be place by the player
     else if(!playerHasPlacedNoPieces(piece->getPlayer()))
    {
        int check=0;
        for(int i=0;i<piece->getSizeX();i++)//checking if at least one square of the piece is touching the edge of another piece previously placed by the same player
            for(int j=0;j<piece->getSizeY();j++)
        {
            if(piece->squareHasPiece(i,j)==true)
            {
                if(x+i>13 || y+j>13)
                    return false;

                if(x+i==0 && y+j>0 && y+j<13)
                {
                    if(squareBelongsToPlayer(x+i+1,y+j-1,piece->getPlayer())==true)
                        check=1;
                    else if(squareBelongsToPlayer(x+i+1,y+j+1,piece->getPlayer())==true)
                        check=1;
                }
                else if(y+j==0 && x+i>0 && x+i<13)
                {
                    if(squareBelongsToPlayer(x+i-1,y+j+1,piece->getPlayer())==true)
                        check=1;
                    else if(squareBelongsToPlayer(x+i+1,y+j+1,piece->getPlayer())==true)
                        check=1;
                }
                else if(x+i==0 && y+j==0)
                {
                    if(squareBelongsToPlayer(x+i+1,y+j+1,piece->getPlayer())==true)
                        check=1;
                }
                else if(x+i>0 && x+i<13 && y+j>0 && y+j<13)
                {
                    if (squareBelongsToPlayer(x+i-1,y+j-1,piece->getPlayer())==true)
                        check=1;
                    else if(squareBelongsToPlayer(x+i+1,y+j-1,piece->getPlayer())==true)
                        check=1;
                    else if(squareBelongsToPlayer(x+i-1,y+j+1,piece->getPlayer())==true)
                        check=1;
                    else if(squareBelongsToPlayer(x+i+1,y+j+1,piece->getPlayer())==true)
                        check=1;
                }
                else if(x+i==0 && y+j==13)
                {
                    if (squareBelongsToPlayer(x+i+1,y+j-1,piece->getPlayer())==true)
                        check=1;
                }
                else if(y+j==0 && x+i==13)
                {
                    if (squareBelongsToPlayer(x+i-1,y+j+1,piece->getPlayer())==true)
                        check=1;
                }
                else if(x+i>0 && x+i<13 && y+j==13)
                {
                    if (squareBelongsToPlayer(x+i-1,y+j-1,piece->getPlayer())==true)
                        check=1;
                    else if (squareBelongsToPlayer(x+i+1,y+j-1,piece->getPlayer())==true)
                        check=1;
                }
                else if(y+j>0 && y+j<13 && x+i==0)
                {
                    if (squareBelongsToPlayer(x+i+1,y+j-1,piece->getPlayer())==true)
                        check=1;
                    else if (squareBelongsToPlayer(x+i+1,y+j+1,piece->getPlayer())==true)
                        check=1;
                }
                else if(x+i==13 && y+j==13)
                {
                    if (squareBelongsToPlayer(x+i-1,y+j-1,piece->getPlayer())==true)
                        check=1;
                }

            }
        }

        if(check!=1)
            return false;

        else if(check==1)
        {
          if(x<0 || x>13 || y<0 || y>13)/////////////////////////////////////////////////////////////
            return false;

          if(x>=10 && y<10)
            for(int i=piece->getSizeX()-1;(x+i)>13;i--)
                for(int j=0;j<piece->getSizeY();j++)
                    if(piece->squareHasPiece(i,j)==1)
                        return false;

          if(y>=10 && x<10)
            for(int i=piece->getSizeY()-1;(y+i)>13;y--)
                for(int j=0;j<piece->getSizeX();j++)
                    if(piece->squareHasPiece(j,i)==1)
                        return false;

          if(x>=10&& y>10)
            for(int i=piece->getSizeX()-1;i>=0;i--)
                for(int j=piece->getSizeY()-1;j>=0;j--)
                    if(piece->squareHasPiece(i,j)==1)
                        return false;
          check=2;
        }

        if(check!=2)
            return false;
        else if(check==2)
        {
            for(int i=0;i<piece->getSizeX();i++)
                for(int j=0;j<piece->getSizeY();j++)
                {
                    if(!(x+i>13 || y+j>13))
                        if(squares[x+i][y+j]->hasPiece()==1)
                            if(piece->squareHasPiece(i,j)==1)
                                return false;
                }
            check=3;
        }

        if(check!=3)
            return false;
        else if(check==3)
        {
            for(int i=0;i<piece->getSizeX();i++)
                for(int j=0;j<piece->getSizeY();j++)
            {

                if(piece->squareHasPiece(i,j)==1)
                {
                    if(x+i>0 && x+i<13 && y+j>0 && y+j<13)
                    {
                        if(squares[x+i-1][y+j]->hasPiece(piece->getPlayer())==1)
                            return false;
                        else if(squares[x+i+1][y+j]->hasPiece(piece->getPlayer())==1)
                            return false;
                        else if(squares[x+i][y+j-1]->hasPiece(piece->getPlayer())==1)
                            return false;
                        else if(squares[x+i][y+j+1]->hasPiece(piece->getPlayer())==1)
                            return false;
                    }
                    else if(x+i==0 && y+j==0)
                    {
                        if(squares[x+i+1][y+j]->hasPiece(piece->getPlayer())==1)
                            return false;
                        else if(squares[x+i][y+j+1]->hasPiece(piece->getPlayer())==1)
                            return false;
                    }
                    else if(x+i==0 && y+j>0 && y+j<13)
                    {
                        if(squares[x+i][y+j-1]->hasPiece(piece->getPlayer())==1)
                            return false;
                        else if(squares[x+i+1][y+j]->hasPiece(piece->getPlayer())==1)
                            return false;
                        else if(squares[x+i][y+j+1]->hasPiece(piece->getPlayer())==1)
                            return false;
                    }
                    else if(y+j==0 && x+i>0 && x+i<13)
                    {
                        if(squares[x+i-1][y+j]->hasPiece(piece->getPlayer())==1)
                            return false;
                        else if(squares[x+i][y+j+1]->hasPiece(piece->getPlayer())==1)
                            return false;
                        else if(squares[x+i+1][y+j]->hasPiece(piece->getPlayer())==1)
                            return false;
                    }
                    else if(x+i==0 && y+j==13)
                    {
                        if(squares[x+i+1][y+j]->hasPiece(piece->getPlayer())==1)
                            return false;
                        else if(squares[x+i][y+j-1]->hasPiece(piece->getPlayer())==1)
                            return false;
                    }
                    else if(y+j==0 && x+i==13)
                    {
                        if(squares[x+i-1][y+j]->hasPiece(piece->getPlayer())==1)
                            return false;
                        else if(squares[x+i][y+j+1]->hasPiece(piece->getPlayer())==1)
                            return false;
                    }
                    else if(x+i==13 && y+j>0 && y+j<13)
                    {
                        if(squares[x+i-1][y+j]->hasPiece(piece->getPlayer())==1)
                            return false;
                        else if(squares[x+i][y+j-1]->hasPiece(piece->getPlayer())==1)
                            return false;
                        else if(squares[x+i][y+j+1]->hasPiece(piece->getPlayer())==1)
                            return false;
                    }
                    else if(y+j==13 && x+i>0 && x+i<13)
                    {
                        if(squares[x+i-1][y+j]->hasPiece(piece->getPlayer())==1)
                            return false;
                        else if(squares[x+i][y+j-1]->hasPiece(piece->getPlayer())==1)
                            return false;
                        else if(squares[x+i+1][y+j]->hasPiece(piece->getPlayer())==1)
                            return false;
                    }
                    else if(x+i==13 && y+j==13)
                    {
                        if(squares[x+i-1][y+j]->hasPiece(piece->getPlayer())==1)
                            return false;
                        else if(squares[x+i][y+j-1]->hasPiece(piece->getPlayer())==1)
                            return false;
                    }
                }
            }
            check=4;
        }

    }
        return true;
}


int Board::computeScore(Player* player)
{
    int score=0;

    for(int i=0; i<boardSizeX; i++)
        for(int j=0; j<boardSizeY; j++)
        {
            if(squareBelongsToPlayer(i,j, player->getSymbol()))
                score++;

            if(player->getNumberOfAvailablePieces()==0)
            {
                score+=15;
                if(getLastPiecePlayedByPlayer(player)==player->getPiece(0))
                    score+=5;
            }
        }
    return score;
}
