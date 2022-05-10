//============================================================================
// Name        : knight.cpp
// Author      : Faizan Ahmed
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <iomanip>
using namespace std;

int horizontal[8], vertical[8];			//store the possible changes
int lessAccessible, moreAccessible;		//

//  return the Accessibility of given Order i.e row x col

int Accessibility(int row, int col) {
	int access[8][8];
	access[0][0] = access[0][8 - 1] = access[8 - 1][0] = access[8 - 1][8 - 1] =
			2;

	access[0][1] = access[1][0] = access[0][6] = access[6][0] = access[1][7] =
			access[7][1] = access[7][6] = access[6][7] = 3;

	access[0][2] = access[0][3] = access[0][4] = access[0][5] = access[2][0] =
			access[3][0] = access[4][0] = access[5][0] = access[7][2] =
					access[7][3] = access[7][4] = access[7][5] = access[2][7] =
							access[3][7] = access[4][7] = access[5][7] =
									access[1][1] = access[1][6] = access[6][1] =
											access[6][6] = 4;

	access[1][2] = access[1][3] = access[1][4] = access[1][5] = access[2][1] =
			access[3][1] = access[4][1] = access[5][1] = access[2][6] =
					access[6][2] = access[3][6] = access[4][6] = access[5][6] =
							access[6][3] = access[6][4] = access[6][5] = 6;

	access[2][2] = access[2][3] = access[2][4] = access[2][5] = access[3][2] =
			access[3][3] = access[3][4] = access[3][5] = access[4][2] =
					access[4][3] = access[4][4] = access[4][5] = access[5][2] =
							access[5][3] = access[5][4] = access[5][5] = 8;
	return access[row][col];
}

// move is not land off the board
// or square is visited

int validMove(int **chess, int row, int col) {
	if (col < 0 || col >= 8 || row < 0 || row >= 8)
		return false;
	else if (chess[row][col] != 0)
		return false;
	else
		return true;
}


//  all squares are visited or not


int TourCompleted(int ** chess) {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (chess[i][j] == 0)
				return false;
		}
	}
	return true;
}


// main function
// recursively find the correct path


int KnightTour(int ** chess, int row = 0, int col = 0, int Nmoves = 0) {
	int rowIncriment, colIncriment;
	lessAccessible = 9, moreAccessible = 9;
	if (TourCompleted(chess)) {
		cout << "total number of moves are :" << Nmoves << endl;
		
		bool debug[64];
		for (int i = 0; i < 64; i++) {
			debug[i] = false;
		}

		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				cout <<"\t"<< chess[i][j];
				debug[chess[i][j] - 1] = true;
			}
			cout << endl;
		}
		for (int i = 0; i < 64; i++) {
			if(debug[i] == false)
				cout << i << " is not found" << endl;
		}
		return false;
	} else {
		chess[row][col] = Nmoves;

	}
	for (int i = 0; i < 8; i++) {
		if (validMove(chess, row + vertical[i], col + horizontal[i])) {
			cout << "valid move is " << row + vertical[i] << "," << col + horizontal[i] << endl; 
			moreAccessible = Accessibility(row + vertical[i],
					col + horizontal[i]);
			if (moreAccessible < lessAccessible) {
				lessAccessible = moreAccessible;
				rowIncriment = vertical[i];
				colIncriment = horizontal[i];
			}
		}
	}

	 {
	/*	cout << "Move no " << Nmoves << endl;
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				cout << "    "<< chess[i][j];
			}
			cout << endl;
		}*/
		KnightTour(chess, row + rowIncriment, col + colIncriment, Nmoves + 1);
	}
	return false;
}

int main() {
	int **chess;

	horizontal[0] = 2;
	horizontal[1] = 1;
	horizontal[2] = -1;
	horizontal[3] = -2;
	horizontal[4] = -2;
	horizontal[5] = -1;
	horizontal[6] = 1;
	horizontal[7] = 2;

	vertical[0] = -1;
	vertical[1] = -2;
	vertical[2] = -2;
	vertical[3] = -1;
	vertical[4] = 1;
	vertical[5] = 2;
	vertical[6] = 2;
	vertical[7] = 1;

	chess = new int*[8];
	for (int i = 0; i < 8; i++) {		//initializing the chess with 0's
		chess[i] = new int[8];
		for (int j = 0; j < 8; j++) {
			chess[i][j] = 0;
		}
	}
	KnightTour(chess,0);
	return 0;
}
