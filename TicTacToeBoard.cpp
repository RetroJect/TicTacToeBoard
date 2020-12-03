#include "TicTacToeBoard.h"
/**
 * Class for representing a 3x3 Tic-Tac-Toe game board, using the Piece enum
 * to represent the spaces on the board.
**/

//Constructor sets an empty board and specifies it is X's turn first
TicTacToeBoard::TicTacToeBoard()
{
  turn = X;
  for(int i=0; i<BOARDSIZE; i++)
    for(int j=0; j<BOARDSIZE; j++)
      board[i][j] = Blank;
}

/**
 * Switches turn member variable to represent whether it's X's or O's turn
 * and returns whose turn it is
**/
Piece TicTacToeBoard::toggleTurn()
{
  return this->turn = (this->turn == O) ? X : O;
}

/**
 * Places the piece of the current turn on the board, returns what
 * piece is placed, and toggles which Piece's turn it is. placePiece does 
 * NOT allow to place a piece in a location where there is already a piece.
 * In that case, placePiece just returns what is already at that location. 
 * Out of bounds coordinates return the Piece Invalid value. When the game
 * is over, no more pieces can be placed so attempting to place a piece
 * should neither change the board nor change whose turn it is.
**/ 
Piece TicTacToeBoard::placePiece(int row, int column)
{
  // The piece at the location
  Piece boardPiece = getPiece(row, column);

  // Location isn't invalid, and doesn't already have a piece
  if (boardPiece != Blank)
    return boardPiece;

  // If game not over, update turn and piece
  if (getWinner() == Invalid) {
    board[row][column] = this->turn;
    toggleTurn();
  }
  // Always return piece at location
  return boardPiece;
}

/**
 * Returns what piece is at the provided coordinates, or Blank if there
 * are no pieces there, or Invalid if the coordinates are out of bounds
**/
Piece TicTacToeBoard::getPiece(int row, int column)
{
  // Make sure location isn't invalid
  if (row < 0 || row > 2){
    return Invalid;
  }
  if (column < 0 || column > 2){
    return Invalid;
  }

  return board[row][column];
}

/**
 * Returns which Piece has won, if there is a winner, Invalid if the game
 * is not over, or Blank if the board is filled and no one has won.
**/
Piece TicTacToeBoard::getWinner()
{
  bool anyBlank = false;
  Piece winner = Invalid;

  // Check rows for winner
  for (int row=0; row<BOARDSIZE; row++){
    Piece left = getPiece(row, 0);
    Piece middle = getPiece(row, 1);
    Piece right = getPiece(row, 2);

    // Check it's either X or O
    bool leftValid = (left == X || left == O);
    bool middleValid = (middle == X || middle == O);
    bool rightValid = (right == X || right == O);

    // If any are blank set true
    if (left == Blank || middle == Blank || right == Blank)
      anyBlank = true;

    // If any not valid, continue
    if (!leftValid || !middleValid || !rightValid)
      continue;

    // If all equal, winner returned
    if (left == middle && middle == right)
      return left;
  }

  // Check columns for winner
  for (int column=0; column<BOARDSIZE; column++){
    Piece top = getPiece(0, column);
    Piece middle = getPiece(1, column);
    Piece bottom = getPiece(2, column);

    // Check it's either X or O
    bool topValid = (top == X || top == O);
    bool middleValid = (middle == X || middle == O);
    bool bottomValid = (bottom == X || bottom == O);

    // If any are blank set true
    if (top == Blank || middle == Blank || bottom == Blank)
      anyBlank = true;

    // If any not valid, continue
    if (!topValid || !middleValid || !bottomValid)
      continue;

    // If all equal, winner returned
    if (top == middle && middle == bottom)
      return top;
  }


  // Check diagonals for winner
  // - Left Diagonal '\'
  {
    Piece top = getPiece(0, 0);
    Piece middle = getPiece(1, 1);
    Piece bottom = getPiece(2, 2);

    // Check it's either X or O
    bool topValid = (top == X || top == O);
    bool middleValid = (middle == X || middle == O);
    bool bottomValid = (bottom == X || bottom == O);

    // If any are blank set true
    if (top == Blank || middle == Blank || bottom == Blank)
      anyBlank = true;

    // If all valid, check winner
    if (topValid && middleValid && bottomValid) {
      // If all equal, winner returned
      if (top == middle && middle == bottom)
        return top;
    }
  }

  // - Right Diagonal '/'
  {
    Piece top = getPiece(0, 2);
    Piece middle = getPiece(1, 1);
    Piece bottom = getPiece(2, 0);

    // Check it's either X or O
    bool topValid = (top == X || top == O);
    bool middleValid = (middle == X || middle == O);
    bool bottomValid = (bottom == X || bottom == O);

    // If any are blank set true
    if (top == Blank || middle == Blank || bottom == Blank)
      anyBlank = true;

    // If all valid, check winner
    if (topValid && middleValid && bottomValid) {
      // If all equal, winner returned
      if (top == middle && middle == bottom)
        return top;
    }
  }

  // No winner so far, check if any blank
  if (anyBlank)
    return Invalid; // Blank spaces, game not over
  else
    return Blank; // All spots filled, tie game
}
