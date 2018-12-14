//Chess Board Functions
// Rank = 1,2,3,4,5,6,7,8
// File = A,B,C,D,E,F,G,H
// (File, Rank) = (X,Y)

#include "pieces.h"
#include "board.h"
#include <iostream>

using namespace std;

void Board::playBoard()
{
  string startPos;
  string endPos;
  bool checkTest = false;
  cout << "\tWelcome to Chess!\nPlease Enter Moves in the Format: \"e2 e4\"" << endl;
  cout << "\"(Starting Positon of Piece)(space)(Ending Position of Piece)\"" << endl;
  cout << "May the Best Player Win! Good Luck!" << endl << endl;

  do {
    moveCounter++;

    printBoard();
    do {
      cout << "White to Move: ";
      cin >> startPos >> endPos;
    } while(!isValidMove(startPos, endPos));
    moveHistory.push_back(to_string(moveCounter)+". ");
    moveHistory.push_back(string(1, getPieceAt(startPos)->id) + endPos+" ");
    cout << "Moving " << getPieceAt(startPos)->id << " at " + startPos +" to "+endPos<< endl;
    movePiece(getPieceAt(startPos), getPieceAt(endPos));

    printBoard();
    do {
      cout << "Black to Move: ";
      cin >> startPos >> endPos;
    } while(!isValidMove(startPos, endPos));
    moveHistory.push_back(string(1, getPieceAt(startPos)->id) + endPos+" ");
    cout << "Moving " << getPieceAt(startPos)->id << " at " + startPos +" to "+endPos<< endl;
    movePiece(getPieceAt(startPos), getPieceAt(endPos));

  } while(!checkTest);

}

void Board::translateMove2Cords(string move, int& movY, int& movX)
{
  switch(move[0])
  {
    case 'a': movX = BOARDSIZE - 10;
              break;
    case 'b': movX = BOARDSIZE - 9;
              break;
    case 'c': movX = BOARDSIZE - 8;
              break;
    case 'd': movX = BOARDSIZE - 7;
              break;
    case 'e': movX = BOARDSIZE - 6;
              break;
    case 'f': movX = BOARDSIZE - 5;
              break;
    case 'g': movX = BOARDSIZE - 4;
              break;
    case 'h': movX = BOARDSIZE - 3;
              break;
  }

  switch(move[1])
  {
    case '1': movY = BOARDSIZE - 3;
              break;
    case '2': movY = BOARDSIZE - 4;
              break;
    case '3': movY = BOARDSIZE - 5;
              break;
    case '4': movY = BOARDSIZE - 6;
              break;
    case '5': movY = BOARDSIZE - 7;
              break;
    case '6': movY = BOARDSIZE - 8;
              break;
    case '7': movY = BOARDSIZE - 9;
              break;
    case '8': movY = BOARDSIZE - 10;
              break;
  }
}

Piece* Board::getPieceAt(string move)
{
  int yCord = 0;
  int xCord = 0;
  translateMove2Cords(move, yCord, xCord);

  return board[yCord][xCord];
}

bool Board::isValidMove(string start, string end)
{
  Piece* p1 = getPieceAt(start);
  Piece* p2 = getPieceAt(end);

  //For Pawn Captures
  if(tolower(p1->id) == 'p')
  {
    if(p1->isWhite)
    {
      if(p2->y == p1->y-1 && (p2->x == p1->x-1 || p2->x == p1->x+1))
      {
        if(!p2->isWhite && p2->isBoard && !p2->isNull) return true;
      }
    }
    else if(!p1->isWhite)
    {
      if(p2->y == p1->y+1 && (p2->x == p1->x-1 || p2->x == p1->x+1))
      {
        if(p2->isWhite && p2->isBoard && !p2->isNull) return true;
      }
    }
  }
  //For Other Moves
  if(p1->isValidMove(p2->y, p2->x))
  {
    if(p1->needsPath && !hasPath(p1, p2)) return false;

    if(!p1->isNull)
    {
      if(p1->isWhite)
      {
        if((!p2->isWhite || p2->isNull) && p2->isBoard)
        {
          return true;
        }
      }
      else if(!p1->isWhite)
      {
        if((p2->isWhite || p2->isNull) && p2->isBoard)
        {
          return true;
        }
      }
    }
  }

  return false;
}

void Board::movePiece(Piece* p1, Piece* p2)
{
  int oldY = p1->y;
  int oldX = p1->x;

  int newY = p2->y;
  int newX = p2->x;

  delete board[newY][newX];
  board[newY][newX] = board[oldY][oldX];
  board[newY][newX]->movePiece(newY, newX);

  board[oldY][oldX] = new NullPiece(oldY, oldX, true, true, '-');
}

bool Board::hasPath(Piece* p1, Piece* p2)
{
  //For Straight Up or Down Moves
  if(p1->x == p2->x && p1->y < p2->y)
  {
    for(int y = p1->y+1; y < p2->y; y++)
    {
      if(!board[y][p1->x]->isNull) return false;
    }
    return true;
  }
  else if(p1->x == p2->x && p1->y > p2->y)
  {
    for(int y = p1->y-1; y > p2->y; y--)
    {
      if(!board[y][p1->x]->isNull) return false;
    }
    return true;
  }
  //For Straight Right or Left Moves
  if(p1->y == p2->y && p1->x < p2->x)
  {
    for(int x = p1->x+1; x < p2->x; x++)
    {
      if(!board[p1->y][x]->isNull) return false;
    }
    return true;
  }
  else if(p1->y == p2->y && p1->x > p2->x)
  {
    for(int x = p1->x-1; x > p2->x; x--)
    {
      if(!board[p1->y][x]->isNull) return false;
    }
    return true;
  }
  //For Diagonal Up Left or Down Right Moves
  if(p1->y > p2->y && p1->x > p2->x)
  {
    for(int y = p1->y-1; y > p2->y; y--)
    {
      for(int x = p1->x-1; x > p2->x; x--)
      {
        if(!board[y][x]->isNull) return false;
        y--;
      }
    }
    return true;
  }
  else if(p1->y < p2->y && p1->x < p2->x)
  {
    for(int y = p1->y+1; y < p2->y; y++)
    {
      for(int x = p1->x+1; x < p2->x; x++)
      {
        if(!board[y][x]->isNull) return false;
        y++;
      }
    }
    return true;
  }
  //For Diagonal Up Right or Down Left Moves
  if(p1->y > p2->y && p1->x < p2->x)
  {
    for(int y = p1->y-1; y > p2->y; y--)
    {
      for(int x = p1->x+1; x < p2->x; x++)
      {
        if(!board[y][x]->isNull) return false;
        y--;
      }
    }
    return true;
  }
  else if(p1->y < p2->y && p1->x > p2->x)
  {
    for(int y = p1->y+1; y < p2->y; y++)
    {
      for(int x = p1->x-1; x > p2->x; x--)
      {
        if(!board[y][x]->isNull) return false;
        y++;
      }
    }
    return true;
  }


  return false;
}

void Board::initializeBoard()
{
  placeNullBorder();
  placeAlphaNumBorder();
  placeBack(2, false);
  placeFront(3, false);
  placeMidBoard();
  placeFront(8, true);
  placeBack(9, true);
}

void Board::placeBack(int y, bool isWhite)
{
  board[y][2] = new Rook(y, 2, isWhite);
  board[y][3] = new Knight(y, 3, isWhite);
  board[y][4] = new Bishop(y, 4, isWhite);
  board[y][5] = new Queen(y, 5, isWhite);
  board[y][6] = new King(y, 6, isWhite);
  board[y][7] = new Bishop(y, 7, isWhite);
  board[y][8] = new Knight(y, 8, isWhite);
  board[y][9] = new Rook(y, 9, isWhite);
}

void Board::placeFront(int y, bool isWhite)
{
  for(int x = 2; x < 10; x++) board[y][x] = new Pawn(y, x, isWhite);
}

void Board::placeNullBorder()
{
  for(int y = 0; y < BOARDSIZE; y++)
  {
    for(int x = 0; x < BOARDSIZE; x++)
    {
      if(y == 0 || y == 11) board[y][x] = new NullPiece(y, x, true, false, 'x');
      if(x == 0 || x == 11) board[y][x] = new NullPiece(y, x, true, false, 'x');
    }
  }
}
void Board::placeAlphaNumBorder()
{
  string alphas = "xABCDEFGHx";
  string nums = "x87654321x";
  for(int y = 1; y < BOARDSIZE -1; y++)
  {
    board[y][1] = new NullPiece(y, 1, true, false, nums[y-1]);
    board[y][10] = new NullPiece(y, 10, true, false, nums[y-1]);
  }
  for(int x = 1; x < BOARDSIZE -1; x++)
  {
    board[1][x] = new NullPiece(1, x, true, false, alphas[x-1]);
    board[10][x] = new NullPiece(10, x, true, false, alphas[x-1]);
  }
}

void Board::placeMidBoard()
{
  for(int y = 4; y < 8; y++)
  {
    for(int x = 2; x < 10; x++)
    {
      board[y][x] = new NullPiece(y, x, true, true, '-');
    }
  }
}

float Board::evaluateBoard()
{
  float evaluation = 0;
  for(int y = 0; y < BOARDSIZE; y++)
  {
    for(int x = 0; x < BOARDSIZE; x++)
    {
      evaluation += board[y][x]->value;
    }
  }
  return evaluation/10;
}

void Board::printBoard()
{
  cout << endl;
  for(int i = 0; i < moveHistory.size(); i ++) cout << moveHistory[i];
  cout << endl;

  cout << "Current Evaluation: " << evaluateBoard() << endl;
  for(int y = 0; y < BOARDSIZE; y++)
  {
    for(int x = 0; x < BOARDSIZE; x++)
    {
      if(board[y][x]->id == 'x') cout << "\e[0;45m" << "  " << "\e[0m";
      else if(board[y][x]->isNull && board[y][x]->id != '-')
      {
        cout << "\e[0;45m" << board[y][x]->id << " " << "\e[0m";
      }
      else cout << board[y][x]->id << " ";
    }
    cout << endl;
  }
}
