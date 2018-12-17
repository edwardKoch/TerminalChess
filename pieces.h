//Chess Piece Classes
// Rank = 1,2,3,4,5,6,7,8
// File = A,B,C,D,E,F,G,H
// (File, Rank) = (X,Y)

#ifndef PIECE_H
#define PIECE_H

#include <vector>
#include <iostream>
using namespace std;

class Piece{
  public:
    int x;
    int y;
    float value;
    char id;
    bool moved;
    bool captured;
    bool isWhite;
    bool isNull;
    bool isBoard;
    bool needsPath;

    Piece(int ypos, int xpos, bool color)
    {
      x = xpos;
      y = ypos;
      captured = false;
      isNull =  false;
      isBoard = true;
      if(color) isWhite = true;
      id = 'v';
    }
    virtual bool isValidMove(int newy, int newx) {return false;}
    void movePiece(int newY, int newX)
    {
      x = newX;
      y = newY;
      moved = true;
    }
};

class Pawn : public Piece{
  public:

    Pawn(int ypos, int xpos, bool color) : Piece(ypos, xpos, color)
    {
      if(color)
      {
        value = 10;
        id = 'P';
      }
      else
      {
        value = -10;
        id = 'p';
      }

      moved = false;
      needsPath = false;
    }
    bool isValidMove(int newy, int newx)
    {
      int diff = 1;
      if(!isWhite) diff = -1;

      if(moved)
      {
        if(newx == x && newy == y - diff) return true;
      }
      else
      {
        if(newx == x && (newy == y - (diff*2) || newy == y - diff)) return true;
      }

      return false;
    }
};

class Knight : public Piece{
  public:

    Knight(int ypos, int xpos, bool color) : Piece(ypos, xpos, color)
    {
      if(color)
      {
        value = 30;
        id = 'N';
      }
      else
      {
        value = -30;
        id = 'n';
      }
      needsPath = false;
    }

    bool isValidMove(int newy, int newx)
    {
      if((newx == x+1 && (newy == y+2 || newy == y-2)) ||
         (newx == x-1 && (newy == y+2 || newy == y-2)) ||
         (newy == y+1 && (newx == x+2 || newx == x-2)) ||
         (newy == y-1 && (newx == x+2 || newx == x-2))) return true;

      return false;
    }
};

class Bishop : public Piece{
  public:

    Bishop(int ypos, int xpos, bool color) : Piece(ypos, xpos, color)
    {
      if(color)
      {
        value = 35;
        id = 'B';
      }
      else
      {
        value = -35;
        id = 'b';
      }
      needsPath = true;
    }

    bool isValidMove(int newy, int newx)
    {
      if(abs(newx - x) == abs(newy - y)) return true;
      return false;
    }

};

class Rook : public Piece{
  public:

    Rook(int ypos, int xpos, bool color) : Piece(ypos, xpos, color)
    {
      if(color)
      {
        value = 50;
        id = 'R';
      }
      else
      {
        value = -50;
        id = 'r';
      }
      needsPath = true;
    }

    bool isValidMove(int newy, int newx)
    {
      if(newx == x || newy == y) return true;

      return false;
    }
};

class Queen : public Piece{
  public:

    Queen(int ypos, int xpos, bool color) : Piece(ypos, xpos, color)
    {
      if(color)
      {
        value = 90;
        id = 'Q';
      }
      else
      {
        value = -90;
        id = 'q';
      }
      needsPath = true;
    }

    bool isValidMove(int newy, int newx)
    {
      if((newx == x || newy == y) ||
         (abs(newx - x) == abs(newy - y))) return true;

      return false;
    }
};

class King : public Piece{
  public:

    King(int ypos, int xpos, bool color) : Piece(ypos, xpos, color)
    {
      if(color)
      {
        value = 900;
        id = 'K';
      }
      else
      {
        value = -900;
        id = 'k';
      }
      needsPath = true;
    }

    bool isValidMove(int newy, int newx)
    {
      if((newx == x+1 && (newy == y+1 || newy == y || newy == y-1)) ||
         (newx == x-1 && (newy == y+1 || newy == y || newy == y-1)) ||
         (newx == x && (newy == y+1 || newy == y-1))) return true;

      return false;
    }
};

class NullPiece : public Piece{
  public:
    NullPiece(int ypos, int xpos, bool color, bool isOnBoard, char myid) : Piece(ypos, xpos, color)
    {
      value = 0;
      id = myid;
      isNull = true;
      isBoard = isOnBoard;
    }
};


#endif
