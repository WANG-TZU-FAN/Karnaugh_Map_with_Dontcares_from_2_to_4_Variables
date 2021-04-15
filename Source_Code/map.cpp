#include "map.h"

// Set the Kmap by question
/* Parameters : 1. how many variables  2. number of minterms  3. input minterms  4. number of don't cares  5. input don't cares */
void Map::setKmap(string number, int count1, vector<string> Initialiter_m, int count2, vector<string> Initialiter_d) {

	// Initialize the matrix with 0
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			matrix[i][j] = 0;
		}
	}

	// Set Kmap for 2 variables
	if (number == "2") {
		for (int i = 0; i < count1; i++)
		{
			if (Initialiter_m[i] == "0") {
				matrix[0][0] = 1;
			}
			if (Initialiter_m[i] == "1") {
				matrix[1][0] = 1;
			}
			if (Initialiter_m[i] == "2") {
				matrix[0][1] = 1;
			}
			if (Initialiter_m[i] == "3") {
				matrix[1][1] = 1;
			}
		}
		for (int i = 0; i < count2; i++)
		{
			if (Initialiter_d[i] == "0") {
				matrix[0][0] = -1;
			}
			if (Initialiter_d[i] == "1") {
				matrix[1][0] = -1;
			}
			if (Initialiter_d[i] == "2") {
				matrix[0][1] = -1;
			}
			if (Initialiter_d[i] == "3") {
				matrix[1][1] = -1;
			}
		}
	}
	// Set Kmap for 3 variables
	else if (number == "3") {
		for (int i = 0; i < count1; i++)
		{
			if (Initialiter_m[i] == "0") {
				matrix[0][0] = 1;
			}
			if (Initialiter_m[i] == "1") {
				matrix[1][0] = 1;
			}
			if (Initialiter_m[i] == "2") {
				matrix[0][1] = 1;
			}
			if (Initialiter_m[i] == "3") {
				matrix[1][1] = 1;
			}
			if (Initialiter_m[i] == "4") {
				matrix[0][3] = 1;
			}
			if (Initialiter_m[i] == "5") {
				matrix[1][3] = 1;
			}
			if (Initialiter_m[i] == "6") {
				matrix[0][2] = 1;
			}
			if (Initialiter_m[i] == "7") {
				matrix[1][2] = 1;
			}
		}
		for (int i = 0; i < count2; i++)
		{
			if (Initialiter_d[i] == "0") {
				matrix[0][0] = -1;
			}
			if (Initialiter_d[i] == "1") {
				matrix[1][0] = -1;
			}
			if (Initialiter_d[i] == "2") {
				matrix[0][1] = -1;
			}
			if (Initialiter_d[i] == "3") {
				matrix[1][1] = -1;
			}
			if (Initialiter_d[i] == "4") {
				matrix[0][3] = -1;
			}
			if (Initialiter_d[i] == "5") {
				matrix[1][3] = -1;
			}
			if (Initialiter_d[i] == "6") {
				matrix[0][2] = -1;
			}
			if (Initialiter_d[i] == "7") {
				matrix[1][2] = -1;
			}
		}
	}
	// Set Kmap for 4 variables
	else if (number == "4") {
		for (int i = 0; i < count1; i++)
		{
			if (Initialiter_m[i] == "0") {
				matrix[0][0] = 1;
			}
			if (Initialiter_m[i] == "1") {
				matrix[1][0] = 1;
			}
			if (Initialiter_m[i] == "2") {
				matrix[3][0] = 1;
			}
			if (Initialiter_m[i] == "3") {
				matrix[2][0] = 1;
			}
			if (Initialiter_m[i] == "4") {
				matrix[0][1] = 1;
			}
			if (Initialiter_m[i] == "5") {
				matrix[1][1] = 1;
			}
			if (Initialiter_m[i] == "6") {
				matrix[3][1] = 1;
			}
			if (Initialiter_m[i] == "7") {
				matrix[2][1] = 1;
			}
			if (Initialiter_m[i] == "8") {
				matrix[0][3] = 1;
			}
			if (Initialiter_m[i] == "9") {
				matrix[1][3] = 1;
			}
			if (Initialiter_m[i] == "10") {
				matrix[3][3] = 1;
			}
			if (Initialiter_m[i] == "11") {
				matrix[2][3] = 1;
			}
			if (Initialiter_m[i] == "12") {
				matrix[0][2] = 1;
			}
			if (Initialiter_m[i] == "13") {
				matrix[1][2] = 1;
			}
			if (Initialiter_m[i] == "14") {
				matrix[3][2] = 1;
			}
			if (Initialiter_m[i] == "15") {
				matrix[2][2] = 1;
			}
		}
		for (int i = 0; i < count2; i++)
		{
			if (Initialiter_d[i] == "0") {
				matrix[0][0] = -1;
			}
			if (Initialiter_d[i] == "1") {
				matrix[1][0] = -1;
			}
			if (Initialiter_d[i] == "2") {
				matrix[3][0] = -1;
			}
			if (Initialiter_d[i] == "3") {
				matrix[2][0] = -1;
			}
			if (Initialiter_d[i] == "4") {
				matrix[0][1] = -1;
			}
			if (Initialiter_d[i] == "5") {
				matrix[1][1] = -1;
			}
			if (Initialiter_d[i] == "6") {
				matrix[3][1] = -1;
			}
			if (Initialiter_d[i] == "7") {
				matrix[2][1] = -1;
			}
			if (Initialiter_d[i] == "8") {
				matrix[0][3] = -1;
			}
			if (Initialiter_d[i] == "9") {
				matrix[1][3] = -1;
			}
			if (Initialiter_d[i] == "10") {
				matrix[3][3] = -1;
			}
			if (Initialiter_d[i] == "11") {
				matrix[2][3] = -1;
			}
			if (Initialiter_d[i] == "12") {
				matrix[0][2] = -1;
			}
			if (Initialiter_d[i] == "13") {
				matrix[1][2] = -1;
			}
			if (Initialiter_d[i] == "14") {
				matrix[3][2] = -1;
			}
			if (Initialiter_d[i] == "15") {
				matrix[2][2] = -1;
			}
		}
	}
}

// Help Simplifier to get the map
/* Parameters : 1. matrix */
void Map::getMatrix(int m[4][4]) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			m[i][j] = matrix[i][j];
		}
	}
}

// Draw the map of the output
/* Parameters : 1. how many variables  2. Output file for data write in */
void Map::drawMap(string number, ofstream& outFile) {
	//Draw Kmap for 2 variables
	if (number == "2") {
		cout << "=====Kmap=====" << endl;
		cout << "  \\ A|       |" << endl;
		cout << " B \\ | 0   1 |" << endl;
		cout << "-----+---+---+ " << endl;
		cout << " 0   |";
		outFile << "=====Kmap=====" << endl;
		outFile << "  \\ A|       |" << endl;
		outFile << " B \\ | 0   1 |" << endl;
		outFile << "-----+---+---+ " << endl;
		outFile << " 0   |";
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 2; j++) {
				if (matrix[i][j] == 1) {
					cout << " 1 |";
					outFile << " 1 |";
				}
				else if (matrix[i][j] == -1) {
					cout << " X |";
					outFile << " X |";
				}
				else {
					cout << " 0 |";
					outFile << " 0 |";
				}
			}
			cout << endl << "-----+---+---+" << endl;
			outFile << endl << "-----+---+---+" << endl;
			if (i == 0) { 
				cout << " 1   |"; 
				outFile << " 1   |";
			}
		}
	}
	//Draw Kmap for 3 variables
	else if (number == "3") {
		cout << "=========Kmap=========" << endl;
		cout << "  \\AB|               |" << endl;
		cout << " C \\ | 00  01  11  10|" << endl;
		cout << "-----+---+---+---+---+ " << endl;
		cout << "  0  |";
		outFile << "=========Kmap=========" << endl;
		outFile << "  \\AB|               |" << endl;
		outFile << " C \\ | 00  01  11  10|" << endl;
		outFile << "-----+---+---+---+---+ " << endl;
		outFile << "  0  |";
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 4; j++) {
				if (matrix[i][j] == 1) {
					cout << " 1 |";
					outFile << " 1 |";
				}
				else if (matrix[i][j] == -1) {
					cout << " X |";
					outFile << " X |";
				}
				else {
					cout << " 0 |";
					outFile << " 0 |";
				}
			}
			cout << endl << "-----+---+---+---+---+" << endl;
			outFile << endl << "-----+---+---+---+---+" << endl;
			if (i == 0) {
				cout << "  1  |"; 
				outFile << "  1  |";
			}
		}
	}
	//Draw Kmap for 4 variables
	else if (number == "4") {
		cout << "=========Kmap=========" << endl;
		cout << "  \\AB|               |" << endl;
		cout << "CD \\ | 00  01  11  10|" << endl;
		cout << "-----+---+---+---+---+ " << endl;
		cout << "  00 |";
		outFile << "=========Kmap=========" << endl;
		outFile << "  \\AB|               |" << endl;
		outFile << "CD \\ | 00  01  11  10|" << endl;
		outFile << "-----+---+---+---+---+ " << endl;
		outFile << "  00 |";
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				if (matrix[i][j] == 1) {
					cout << " 1 |";
					outFile << " 1 |";
				}
				else if (matrix[i][j] == -1) {
					cout << " X |";
					outFile << " X |";
				}
				else {
					cout << " 0 |";
					outFile << " 0 |";
				}
			}
			cout << endl << "-----+---+---+---+---+" << endl;
			outFile << endl << "-----+---+---+---+---+" << endl;
			if (i == 0) { 
				cout << "  01 |"; 
				outFile << "  01 |";
			}
			else if (i == 1) { 
				cout << "  11 |"; 
				outFile << "  11 |";
			}
			else if (i == 2) { 
				cout << "  10 |"; 
				outFile << "  10 |";
			}
		}
	}
}

