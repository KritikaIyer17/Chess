#include "stdafx.h"
#include <iostream>
#include <cstdio>
#include <conio.h>
#include<cstdlib>

using namespace std;

int checkcheck = 0;
int KWCnt = 0, KBCnt = 0, RWaCnt = 0, RWhCnt = 0, RBaCnt = 0, RBhCnt = 0;

class Piece
{
	virtual int AreSquaresLegal(int SRow, int SCol, int DestRow, int DestCol, Piece* PBoard[8][8]) = 0; //Pure Virtual Function
	char Colour1;
public:
	Piece(char Colour2) : Colour1(Colour2) {}
	~Piece() {}
	virtual char GetPiece() = 0;//Pure Virtual Function
	char GetColour()
	{
		return Colour1;
	}
	virtual int IsLegalMove(int SRow, int SCol, int DestRow, int DestCol, Piece* PBoard[8][8])
	{
		//Checks if square is empty or occupied by opposite colour
		Piece* Dest = PBoard[DestRow][DestCol];
		if ((Dest == 0) || (Colour1 != Dest->GetColour()))
		{
			return AreSquaresLegal(SRow, SCol, DestRow, DestCol, PBoard);
		}
		return 0;
	}
};

class Pawn : public Piece
{
	char GetPiece()
	{
		return 'P';
	}
	int AreSquaresLegal(int SRow, int SCol, int DestRow, int DestCol, Piece* PBoard[8][8])
	{
		Piece* Dest = PBoard[DestRow][DestCol];
		if (Dest == 0)
		{
			// Destination square is unoccupied
			if (SCol == DestCol)
			{
				if (GetColour() == 'W')
				{
					if (SRow == 1)
					{
						if (DestRow == SRow + 2 || DestRow == SRow + 1)
						{
							return 1;
						}
					}
					else
					{
						if (DestRow == SRow + 1)
						{
							return 1;
						}
					}
				}
				else
				{
					if (SRow == 6)
					{
						if (DestRow == SRow - 2 || DestRow == SRow - 1)
						{
							return 1;
						}
					}
					else
					{
						if (DestRow == SRow - 1)
						{
							return 1;
						}
					}
				}
			}
		}
		else
		{
			// Destination holds piece of opposite color
			if ((SCol == DestCol + 1) || (SCol == DestCol - 1))
			{
				if (GetColour() == 'W')
				{
					if (DestRow == SRow + 1)
					{
						return 1;
					}
				}
				else
				{
					if (DestRow == SRow - 1)
					{
						return 1;
					}
				}
			}
		}
		return 0;
	}

public:
	Pawn(char Colour2) : Piece(Colour2) {}
	~Pawn() {}
};

class Knight : public Piece
{
	char GetPiece()
	{
		return 'N';
	}
	int AreSquaresLegal(int SRow, int SCol, int DestRow, int DestCol, Piece* PBoard[8][8])
	{
		// Destination square is unoccupied or occupied by opposite color
		if ((SCol == DestCol + 1) || (SCol == DestCol - 1))
		{
			if ((SRow == DestRow + 2) || (SRow == DestRow - 2))
			{
				return 1;
			}
		}
		if ((SCol == DestCol + 2) || (SCol == DestCol - 2))
		{
			if ((SRow == DestRow + 1) || (SRow == DestRow - 1))
			{
				return 1;
			}
		}
		return 0;
	}

public:
	Knight(char Colour2) : Piece(Colour2) {}
	~Knight() {}
};

class Bishop : public Piece
{
	char GetPiece()
	{
		return 'B';
	}
	int AreSquaresLegal(int SRow, int SCol, int DestRow, int DestCol, Piece* PBoard[8][8])
	{
		if ((DestCol - SCol == DestRow - SRow) || (DestCol - SCol == SRow - DestRow))
		{
			// Make sure that all intervening squares are empty
			int RowOffset = (DestRow - SRow > 0) ? 1 : -1;
			int ColOffset = (DestCol - SCol > 0) ? 1 : -1;
			int CheckRow;
			int CheckCol;
			for (CheckRow = SRow + RowOffset, CheckCol = SCol + ColOffset; CheckRow != DestRow; CheckRow = CheckRow + RowOffset, CheckCol = CheckCol + ColOffset)
			{
				if (PBoard[CheckRow][CheckCol] != 0)
				{
					return 0;
				}
			}
			return 1;
		}
		return 0;
	}

public:
	Bishop(char Colour2) : Piece(Colour2) {}
	~Bishop() {}
};

class Rook : public Piece
{
	char GetPiece()
	{
		return 'R';
	}
	int AreSquaresLegal(int SRow, int SCol, int DestRow, int DestCol, Piece* PBoard[8][8])
	{
		if (SRow == DestRow)
		{
			// Make sure that all intervening squares are empty
			int ColOffset = (DestCol - SCol > 0) ? 1 : -1;
			for (int CheckCol = SCol + ColOffset; CheckCol != DestCol; CheckCol = CheckCol + ColOffset)
			{
				if (PBoard[SRow][CheckCol] != 0)
				{
					return 0;
				}
				if (Game.Turn == 'W')
				{
					if ((SCol == 7) && (SRow == 0))
						RWhCnt = 1;
					else if ((SCol == 0) && (SRow == 0))
						RWaCnt = 1;
					else
						;
				}
				else
				{
					if ((SCol == 7) && (SRow == 7))
						RWhCnt = 1;
					else if ((SCol == 0) && (SRow == 7))
						RWaCnt = 1;
					else
						;
				}

			}
			return 1;
		}
		else if (DestCol == SCol)
		{
			// Make sure that all intervening squares are empty
			int RowlOffset = (DestRow - SRow > 0) ? 1 : -1;
			for (int CheckRow = SRow + RowlOffset; CheckRow != DestRow; CheckRow = CheckRow + RowlOffset)
			{
				if (PBoard[CheckRow][SCol] != 0)
				{
					return 0;
				}
			}
			return 1;
		}
		return 0;
	}

public:
	Rook(char Colour2) : Piece(Colour2) {}
	~Rook() {}
};

class Queen : public Piece
{
	char GetPiece()
	{
		return 'Q';
	}
	int AreSquaresLegal(int SRow, int SCol, int DestRow, int DestCol, Piece* PBoard[8][8])
	{
		if (SRow == DestRow)
		{
			// Make sure that all intervening squares are empty
			int ColOffset = (DestCol - SCol > 0) ? 1 : -1;
			for (int CheckCol = SCol + ColOffset; CheckCol != DestCol; CheckCol = CheckCol + ColOffset)
			{
				if (PBoard[SRow][CheckCol] != 0)
				{
					return 0;
				}
			}
			return 1;
		}
		else if (DestCol == SCol)
		{
			// Make sure that all intervening squares are empty
			int RowlOffset = (DestRow - SRow > 0) ? 1 : -1;
			for (int CheckRow = SRow + RowlOffset; CheckRow != DestRow; CheckRow = CheckRow + RowlOffset)
			{
				if (PBoard[CheckRow][SCol] != 0)
				{
					return 0;
				}
			}
			return 1;
		}
		else if ((DestCol - SCol == DestRow - SRow) || (DestCol - SCol == SRow - DestRow))
		{
			// Make sure that all intervening squares are empty
			int RowlOffset = (DestRow - SRow > 0) ? 1 : -1;
			int ColOffset = (DestCol - SCol > 0) ? 1 : -1;
			int CheckRow;
			int CheckCol;
			for (CheckRow = SRow + RowlOffset, CheckCol = SCol + ColOffset; CheckRow != DestRow; CheckRow = CheckRow + RowlOffset, CheckCol = CheckCol + ColOffset)
			{
				if (PBoard[CheckRow][CheckCol] != 0)
				{
					return 0;
				}
			}
			return 1;
		}
		return 0;
	}

public:
	Queen(char Colour2) : Piece(Colour2) {}
	~Queen() {}
};

class King : public Piece
{
	char GetPiece()
	{
		return 'K';
	}
	int AreSquaresLegal(int SRow, int SCol, int DestRow, int DestCol, Piece* PBoard[8][8])
	{
		int RowDelta = DestRow - SRow;
		int ColDelta = DestCol - SCol;
		if (((RowDelta >= -1) && (RowDelta <= 1)) && ((ColDelta >= -1) && (ColDelta <= 1)))
		{
			if (Game.Turn == 'W')
				KWCnt = 1;
			else
				KBCnt = 1;
			return 1;
		}
		if ((ColDelta == 2 || ColDelta == -2) && (RowDelta == 0))
		{
			int flag;
			flag = Castle(int ColDelta, int Srow, Piece* PBoard[8][8]);
			if (flag == 0)
				return 0;
			else
				return 1;
		}
		else
		{
			return 0;
		}
	}
public:
	King(char Colour2) : Piece(Colour2) {}
	~King() {}
};

class Board
{
	public:
	Piece * Boardptr[8][8];
	Board()
	{
		int Row, Col;
		for (Row = 0; Row < 8; ++Row)
		{
			for (Col = 0; Col < 8; ++Col)
			{
				Boardptr[Row][Col] = 0;
			}
		}
		// Allocate and place black pieces
		for (Col = 0; Col < 8; ++Col)
		{
			Boardptr[6][Col] = new Pawn('B');
		}
		Boardptr[7][0] = new Rook('B');
		Boardptr[7][1] = new Knight('B');
		Boardptr[7][2] = new Bishop('B');
		Boardptr[7][3] = new Queen('B');
		Boardptr[7][4] = new King('B');
		Boardptr[7][5] = new Bishop('B');
		Boardptr[7][6] = new Knight('B');
		Boardptr[7][7] = new Rook('B');
		// Allocate and place white pieces
		for (Col = 0; Col < 8; ++Col)
		{
			Boardptr[1][Col] = new Pawn('W');
		}
		Boardptr[0][0] = new Rook('W');
		Boardptr[0][1] = new Knight('W');
		Boardptr[0][2] = new Bishop('W');
		Boardptr[0][3] = new Queen('W');
		Boardptr[0][4] = new King('W');
		Boardptr[0][5] = new Bishop('W');
		Boardptr[0][6] = new Knight('W');
		Boardptr[0][7] = new Rook('W');
	}
	~Board()
	{
		int Row, Col;
		for (Row = 0; Row < 8; ++Row)
		{
			for (Col = 0; Col < 8; ++Col)
			{
				delete Boardptr[Row][Col];
				Boardptr[Row][Col] = 0;
			}
		}
	}

	void Print()
	{
		const int Width = 4;
		const int Height = 3;
		int Row, Col;
		for (Row = 0; Row < 8 * Height; ++Row)
		{
			int SquareRow = Row / Height;
			// Print side border with numbering
			if (Row % 3 == 1)
			{
				cout << '-' << (char)('1' + 7 - SquareRow) << '-';
			}
			else
			{
				cout << "---";
			}
			// Print the chess board
			for (Col = 0; Col < 8 * Width; ++Col)
			{
				int SquareCol = Col / Width;
				if (((Row % 3) == 1) && ((Col % 4) == 1 || (Col % 4) == 2) && Boardptr[7 - SquareRow][SquareCol] != 0)
				{
					if ((Col % 4) == 1)
					{
						cout << Boardptr[7 - SquareRow][SquareCol]->GetColour();
					}
					else
					{
						cout << Boardptr[7 - SquareRow][SquareCol]->GetPiece();
					}
				}
				else
				{
					if ((SquareRow + SquareCol) % 2 == 1)
					{
						cout << ' ';
					}
					else
					{
						cout << '|';
					}
				}
			}
			cout << endl;
		}
		// Print the bottom border with numbers
		for (Row = 0; Row < Height; ++Row)
		{
			if (Row % 3 == 1)
			{
				cout << "---";
				for (Col = 0; Col < 8 * Width; ++Col)
				{
					int SquareCol = Col / Width;
					if ((Col % 4) == 1)
					{
						cout << char(96 + (SquareCol + 1));
					}
					else
					{
						cout << '-';
					}
				}
				cout << endl;
			}
			else
			{
				for (Col = 1; Col < 9 * Width; ++Col)
				{
					cout << '-';
				}
				cout << endl;
			}
		}
	}

	int IsInCheck(char Colour2)
	{
		// Find the king
		int Row, Col;
		int KingRow;
		int KingCol;
		for (Row = 0; Row < 8; ++Row)
		{
			for (Col = 0; Col < 8; ++Col)
			{
				if (Boardptr[Row][Col] != 0)
				{
					if (Boardptr[Row][Col]->GetColour() == Colour2)
					{
						if (Boardptr[Row][Col]->GetPiece() == 'K')
						{
							KingRow = Row;
							KingCol = Col;
						}
					}
				}
			}
		}
		// Run through the opponent's pieces and see if any can take the king
		for (Row = 0; Row < 8; ++Row)
		{
			for (Col = 0; Col < 8; ++Col)
			{
				if (Boardptr[Row][Col] != 0)
				{
					if (Boardptr[Row][Col]->GetColour() != Colour2)
					{
						if (Boardptr[Row][Col]->IsLegalMove(Row, Col, KingRow, KingCol, Boardptr))
						{
							checkcheck = 1;
							return 1;
						}
					}
				}
			}
		}
		checkcheck = 0;
		return 0;
	}
	int Castle(int ColDelta, int SCol, Piece* PBoard[8][8])
	{
		if (!checkcheck)
		{
			if (ColDelta == 2)
			{
				if ((SCol + 1 == 0) && (SCol + 2 == 0))
				{

					if (Game.Turn == 'W')
					{
						if ((KWCnt == 0) && (RWhCnt == 0))
						{
							PBoard[6][0] = PBoard[4][0];
							PBoard[4][0] = 0;
							PBoard[5][0] = PBoard[7][0];
							PBoard[7][0] = 0;
							return 1;
						}
						else
						{
							return 0;
						}
					}
					else
					{
						if ((KBCnt == 0) && (RBhCnt == 0))
						{
							PBoard[6][7] = PBoard[4][7];
							PBoard[4][7] = 0;
							PBoard[5][7] = PBoard[7][7];
							PBoard[7][7] = 0;
							return 1;
						}
						else
						{
							return 0;
						}
					}
				}
				else if ((SCol - 1 == 0) && (SCol - 2 == 0) && (SCol - 3 == 0))
				{
					if (Game.Turn == 'W')
					{
						if ((KWCnt == 0) && (RWaCnt == 0))
						{
							PBoard[2][0] = PBoard[4][0];
							PBoard[4][0] = 0;
							PBoard[3][0] = PBoard[0][0];
							PBoard[0][0] = 0;
							return 1;
						}
						else
						{
							return 0;
						}
					}
					else
					{
						if ((KBCnt == 0) && (RBaCnt == 0))
						{
							PBoard[2][7] = PBoard[4][7];
							PBoard[4][7] = 0;
							PBoard[3][7] = PBoard[0][7];
							PBoard[0][7] = 0;
							return 1;
						}
						else
						{
							return 0;
						}
					}
				}
				else
				{
					return 0;
				}
			}
			else()
			{
				return 0;
			}
		}
		else
		{
			return 0;
		}
	}
	int CanMove(char Colour2)
	{
		// Run through all pieces
		for (int Row = 0; Row < 8; ++Row)
		{
			for (int Col = 0; Col < 8; ++Col)
			{
				if (Boardptr[Row][Col] != 0)
				{
					// If it is a piece of the current player, see if it has a legal move
					if (Boardptr[Row][Col]->GetColour() == Colour2)
					{
						for (int MoveRow = 0; MoveRow < 8; ++MoveRow)
						{
							for (int MoveCol = 0; MoveCol < 8; ++MoveCol)
							{
								if (Boardptr[Row][Col]->IsLegalMove(Row, Col, MoveRow, MoveCol, Boardptr))
								{
									// Make move and check whether king is in check
									Piece* Temp = Boardptr[MoveRow][MoveCol];
									Boardptr[MoveRow][MoveCol] = Boardptr[Row][Col];
									Boardptr[Row][Col] = 0;
									int Move = !IsInCheck(Colour2);
									// Undo the move
									Boardptr[Row][Col] = Boardptr[MoveRow][MoveCol];
									Boardptr[MoveRow][MoveCol] = Temp;
									if (Move)
									{
										return 1;
									}
								}
							}
						}
					}
				}
			}
		}
		return 0;
	}
};

class Chess
{
	Board BoardObj;
	public:
	char Turn;
	Chess() : Turn('W') {}//mem-initialisation
	~Chess() {}
	void Start()
	{
		do
		{
			GetNextMove(BoardObj.Boardptr);
			AlternateTurn();
		} 
		while (!IsGameOver());
		BoardObj.Print();
	}

	void GetNextMove(Piece* PBoard[8][8])
	{
		int ValidMove = 0;
		do
		{
			BoardObj.Print();
			// Get input and convert to coordinates
			cout << "\n" << Turn << "'s Move: " << endl << "\nEnter position of piece to move:";
			char StartMove[10];
			cin.getline(StartMove, 3);
			int StartRow = int(StartMove[1]) - 48 - 1;
			int StartCol = (int(StartMove[0])) - 96 - 1;
			cout << "\nTo: ";
			char EndMove[10];
			cin.getline(EndMove, 3);
			int EndRow = int(EndMove[1]) - 48 - 1;
			int EndCol = (int(EndMove[0])) - 96 - 1;
			// Check that the indices are in range and that the source and destination are different
			if ((StartRow >= 0 && StartRow <= 7) && (StartCol >= 0 && StartCol <= 7) && (EndRow >= 0 && EndRow <= 7) && (EndCol >= 0 && EndCol <= 7))
			{
				Piece* CurrPiece = PBoard[StartRow][StartCol];
				// Check that the piece is the correct color
				if ((CurrPiece != 0) && (CurrPiece->GetColour() == Turn))
				{
					// Check that the destination is a valid destination
					if (CurrPiece->IsLegalMove(StartRow, StartCol, EndRow, EndCol, PBoard))
					{
						// Make the move
						Piece* Temp = PBoard[EndRow][EndCol];
						PBoard[EndRow][EndCol] = PBoard[StartRow][StartCol];
						PBoard[StartRow][StartCol] = 0;
						// Make sure that the current player is not in check
						if (!BoardObj.IsInCheck(Turn))
						{
							delete Temp;
							ValidMove = 1;
						}
						else
						{
							// Undo the last move
							PBoard[StartRow][StartCol] = PBoard[EndRow][EndCol];
							PBoard[EndRow][EndCol] = Temp;
						}
					}
				}
			}
			if (!ValidMove)
			{
				cout << "\nInvalid Move!" << endl;
			}
		} while (!ValidMove);
	}
	void AlternateTurn()
	{
		if (BoardObj.IsInCheck(Turn))
		{
			cout << "\n\a" << Turn << "is in check!!!" << endl;
			checkcheck = 1;
		}
		else
			checkcheck = 0;
		Turn = (Turn == 'W') ? 'B' : 'W';
	}
	int IsGameOver()
	{
		// Check if the current player can move
		int Move = 0;
		Move = BoardObj.CanMove(Turn);
		if (!Move)
		{
			if (BoardObj.IsInCheck(Turn))
			{
				AlternateTurn();
				cout << "\nCHECKMATE!\t" << Turn << " WINS!" << endl;
			}
			else
			{
				cout << "\nStalemate!" << endl;
			}
		}
		return !Move;
	}
}Game;

int main()
{
	char ch;
	do
	{
		//clrscr();
		Game.Start();
		cout << "Again(y/n)?" << endl;
		cin >> ch;
	} while (ch == 'y' || ch == 'Y');
	_getch();
	return 0;
}
