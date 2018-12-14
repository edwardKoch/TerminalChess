//Chess Board Class
// Rank = 1,2,3,4,5,6,7,8
// File = A,B,C,D,E,F,G,H
// (File, Rank) = (X,Y)

#ifndef BOARD_H
#define BOARD_H

#include "pieces.h"
#include <vector>
#include <iostream>
using namespace std;

const int BOARDSIZE = 12;

class Board{
  public:
    Piece* board[BOARDSIZE][BOARDSIZE];
    int moveCounter;
    vector<string> moveHistory;

    Board(){
      moveCounter = 0;
      moveHistory.clear();
      initializeBoard();
    }

    void playBoard();

    void translateMove2Cords(string move, int& movY, int& movX);
    Piece* getPieceAt(string move);
    bool canMakeMove(string start, string end);
    bool isValidMove(Piece* p1, Piece* p2);
    void movePiece(Piece* p1, Piece* p2);
    bool hasPath(Piece* p1, Piece* p2);
    bool isCheck(bool colorIsW);

    void initializeBoard();
    void placeNullBorder();
    void placeAlphaNumBorder();
    void placeMidBoard();
    void placeBack(int y, bool isWhite);
    void placeFront(int y, bool isWhite);

    float evaluateBoard();
    void printBoard();
};


#endif
