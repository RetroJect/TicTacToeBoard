/**
 * Unit Tests for TicTacToeBoard
**/

#include <gtest/gtest.h>
#include "TicTacToeBoard.h"

class TicTacToeBoardTest : public ::testing::Test
{
protected:
  TicTacToeBoardTest() {}          //constructor runs before each test
  virtual ~TicTacToeBoardTest() {} //destructor cleans up after tests
  virtual void SetUp() {}          //sets up before each test (after constructor)
  virtual void TearDown() {}       //clean up after each test, (before destructor)
};

TEST(TicTacToeBoardTest, placePieceValid) {
  // Place a piece in every valid cell
  for(int row=0; row<BOARDSIZE; row++) {
    for(int column=0; column<BOARDSIZE; column++) {
      TicTacToeBoard board;
      ASSERT_TRUE(board.placePiece(row, column) == X);
    }
  }
}

TEST(TicTacToeBoardTest, placePieceNegative) {
  TicTacToeBoard board;

  // Negative Row
  ASSERT_TRUE(board.placePiece(-1,0) == Invalid);
  // Negative Column
  ASSERT_TRUE(board.placePiece(0,-1) == Invalid);
  // Negative Row and Column
  ASSERT_TRUE(board.placePiece(-1,-1) == Invalid);
}

TEST(TicTacToeBoardTest, placePieceBigPositive) {
  TicTacToeBoard board;

  // Large Row
  ASSERT_TRUE(board.placePiece(3,0) == Invalid);
  // Large Column
  ASSERT_TRUE(board.placePiece(0,3) == Invalid);
  // Large Row and Column
  ASSERT_TRUE(board.placePiece(3,3) == Invalid);
}

TEST(TicTacToeBoardTest, placePieceOverAnother) {
  TicTacToeBoard board;

  // Place X piece
  board.placePiece(0,0);

  // Try to overwrite it with O
  ASSERT_TRUE(board.placePiece(0,0) == X);
}

TEST(TicTacToeBoardTest, placePieceOverSame) {
  TicTacToeBoard board;
  // Place X piece
  board.placePiece(0,0);
  // Place O Piece
  board.placePiece(0,1);
  // Try to overwrite X, returns X
  ASSERT_TRUE(board.placePiece(0,0) == X);
  // Should still be X's turn
  ASSERT_TRUE(board.placePiece(1,0) == X);
}

TEST(TicTacToeBoardTest, getPieceBlank) {
  TicTacToeBoard board;

  // All should be blank
  for(int row=0; row<BOARDSIZE; row++) {
    for(int column=0; column<BOARDSIZE; column++) {
      ASSERT_TRUE(board.getPiece(row, column) == Blank);
    }
  }
}

TEST(TicTacToeBoardTest, getPieceNegative) {
  TicTacToeBoard board;

  // Negative Row
  ASSERT_TRUE(board.getPiece(-1,0) == Invalid);
  // Negative Column
  ASSERT_TRUE(board.getPiece(0,-1) == Invalid);
  // Negative Row and Column
  ASSERT_TRUE(board.getPiece(-1,-1) == Invalid);
}

TEST(TicTacToeBoardTest, getPieceBigPositive) {
  TicTacToeBoard board;

  // Big Row
  ASSERT_TRUE(board.getPiece(3,0) == Invalid);
  // Big Column
  ASSERT_TRUE(board.getPiece(0,3) == Invalid);
  // Big Row and Column
  ASSERT_TRUE(board.getPiece(3,3) == Invalid);
}

TEST(TicTacToeBoard, getWinnerInvalid) {
  TicTacToeBoard board;

  // Blank board
  ASSERT_TRUE(board.getWinner() == Invalid);

  // Do some moves
  board.placePiece(0,0);
  board.placePiece(0,1);
  board.placePiece(0,2);

  // No winner and board not full
  ASSERT_TRUE(board.getWinner() == Invalid);
}

TEST(TicTacToeBoard, getWinnerBlank) {
  TicTacToeBoard board;

  // Fill the board but no winner
  /*
  oxo
  xxo
  xox
  */
  board.placePiece(0,1); // x
  board.placePiece(0,0); // o
  board.placePiece(1,0); // x
  board.placePiece(0,2); // o
  board.placePiece(1,1); // x
  board.placePiece(1,2); // o
  board.placePiece(2,0); // x
  board.placePiece(2,1); // o
  board.placePiece(2,2); // x

  ASSERT_TRUE(board.getWinner() == Blank);
}