#include "Simplifier.h"

/* At the first step of grouping, store index values as Pairs */
class Pair {
public:
	int x;
	int y;
	Pair() { x = 0, y = 0; }
	Pair(int n1, int n2) { x = n1; y = n2; }
};

/* Covert the position of Kmap items to decimal terms */
int number_of_minterms(int number, int i, int j) {
	if (number == 2) {
		if (i == 0 && j == 0) {
			return 0;
		}
		if (i == 1 && j == 0) {
			return 1;
		}
		if (i == 0 && j == 1) {
			return 2;
		}
		if (i == 1 && j == 1) {
			return 3;
		}
	}
	if (number == 3) {
		if (i == 0 && j == 0) {
			return 0;
		}
		if (i == 1 && j == 0) {
			return 1;
		}
		if (i == 0 && j == 1) {
			return 2;
		}
		if (i == 1 && j == 1) {
			return 3;
		}
		if (i == 0 && j == 3) {
			return 4;
		}
		if (i == 1 && j == 3) {
			return 5;
		}
		if (i == 0 && j == 2) {
			return 6;
		}
		if (i == 1 && j == 2) {
			return 7;
		}
	}
	if (number == 4) {
		if (i == 0 && j == 0) {
			return 0;
		}
		if (i == 1 && j == 0) {
			return 1;
		}
		if (i == 3 && j == 0) {
			return 2;
		}
		if (i == 2 && j == 0) {
			return 3;
		}
		if (i == 0 && j == 1) {
			return 4;
		}
		if (i == 1 && j == 1) {
			return 5;
		}
		if (i == 3 && j == 1) {
			return 6;
		}
		if (i == 2 && j == 1) {
			return 7;
		}
		if (i == 0 && j == 3) {
			return 8;
		}
		if (i == 1 && j == 3) {
			return 9;
		}
		if (i == 3 && j == 3) {
			return 10;
		}
		if (i == 2 && j == 3) {
			return 11;
		}
		if (i == 0 && j == 2) {
			return 12;
		}
		if (i == 1 && j == 2) {
			return 13;
		}
		if (i == 3 && j == 2) {
			return 14;
		}
		if (i == 2 && j == 2) {
			return 15;
		}
	}
}

// Constructor of the simplifier
Simplifier::Simplifier(Map *map) :
	map(map)
{
}

// Group the map with don't cares
vector<vector<int>> Simplifier::pushImplicants(vector<vector<int>> &groups_final, string number) {

	map->getMatrix(matrix);

	vector <Pair> group;
	vector <int> group_for_2D;

	vector <int> minterm;
	vector <vector <Pair>> groups;
	int count = 0;
	int count_min_is_Implicant = 0;

	int temp_1;
	int temp_2;

	// Set don't cares to 1 when grouping
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (matrix[i][j] == 1 || matrix[i][j] == -1)
			{
				matrix[i][j] = 1;
			}
			else
			{
				matrix[i][j] = 0;
			}
		}
	}

	if (number == "2") {
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 2; j++) {
				groups.push_back(group);
				// ( Up & Down ) Find Pairs
				if (matrix[i][j] == 1 && matrix[(i + 1) % 2][j] != 0) {
					groups[count].push_back(Pair(number_of_minterms(2, i, j), number_of_minterms(2, (i + 1) % 2, j)));
					// ( Right ) Find Squares
					if (matrix[i][(j + 1) % 4] != 0 && matrix[(i + 1) % 2][(j + 1) % 4] == matrix[i][(j + 1) % 4]) {
						groups[count].push_back(Pair(number_of_minterms(3, i, (j + 1) % 4), number_of_minterms(3, (i + 1) % 2, (j + 1) % 4)));
						matrix[i][j] ++;
						matrix[(i + 1) % 2][j] ++;
						matrix[i][(j + 1) % 2] ++;
						matrix[(i + 1) % 2][(j + 1) % 2] ++;
						count++;
					}
					// No Squares
					else {
						matrix[i][j] = matrix[i][j] + 1;
						matrix[(i + 1) % 2][j] = matrix[(i + 1) % 2][j] + 1;
						count++;
					}
				}
				// ( Left & Right ) Find Pairs
				else if (matrix[i][j] == 1 && matrix[i][(j + 1) % 2] != 0) {
					groups[count].push_back(Pair(number_of_minterms(2, i, j), number_of_minterms(2, i, (j + 1) % 2)));
					matrix[i][j]++;
					matrix[i][(j + 1) % 2]++;
					count++;
				}
			}
		}

		//Check if correct output
		/*
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 2; j++) {
				cout << matrix[i][j];
			}
			cout << endl;
		}
		*/

		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 2; j++) {
				if (matrix[i][j] == 1) {
					minterm.push_back(number_of_minterms(2, i, j));
					matrix[i][j] ++;
					count_min_is_Implicant++;
				}
			}
		}
		/* Check if correct prime implicant with don't cares*/
		/*
		cout << endl << "There have " << count + count_min_is_Implicant << " prime implicants with don't cares." << endl;

		cout << endl << "Prime implicants with don't cares: " << endl;

		for (int i = 0; i < count_min_is_Implicant; i++) {
			cout << minterm[i] << endl;
		}

		for (int i = 0; i < count; i++) {
			for (int j = 0; j < groups[i].size(); j++) {
				cout << " " << groups[i][j].x << " " << groups[i][j].y;
			}
			cout << endl;
		}
		*/
	}

	if (number == "3") {
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 4; j++) {
				groups.push_back(group);
				// ( Down & Up ) Find Pairs
				if (matrix[i][j] == 1 && matrix[(i + 1) % 2][j] != 0) {
					// ( Right ) Find Squares
					groups[count].push_back(Pair(number_of_minterms(3, i, j), number_of_minterms(3, (i + 1) % 2, j)));
					if (matrix[i][(j + 1) % 4] != 0 && matrix[(i + 1) % 2][(j + 1) % 4] == matrix[i][(j + 1) % 4]) {
						groups[count].push_back(Pair(number_of_minterms(3, i, (j + 1) % 4), number_of_minterms(3, (i + 1) % 2, (j + 1) % 4)));
						matrix[i][j] ++;
						matrix[(i + 1) % 4][j] ++;
						matrix[i][(j + 1) % 4] ++;
						matrix[(i + 1) % 2][(j + 1) % 4] ++;
						count++;
					}
					// ( Left ) Find Squares
					else if (matrix[i][(j - 1 + 4) % 4] != 0 && matrix[(i + 1) % 2][(j - 1 + 4) % 4] == matrix[i][(j - 1 + 4) % 4]) {
						groups[count].push_back(Pair(number_of_minterms(3, i, (j - 1 + 4) % 4), number_of_minterms(3, (i + 1) % 2, (j - 1 + 4) % 4)));
						matrix[i][j] ++;
						matrix[(i + 1) % 4][j] ++;
						matrix[i][(j - 1 + 4) % 4] ++;
						matrix[(i + 1) % 2][(j - 1 + 4) % 4] ++;
						count++;
					}
					// No Squares
					else {
						matrix[i][j] ++;
						matrix[(i + 1) % 2][j] ++;
						count++;
					}
				}
				// ( Left ) Find Pairs
				if (matrix[i][j] == 1 && matrix[i][(j - 1 + 4) % 4] != 0) {
					groups[count].push_back(Pair(number_of_minterms(3, i, j), number_of_minterms(3, i, (j - 1 + 4) % 4)));
					// ( Left ) Find Bars
					if (matrix[i][(j - 2 + 4) % 4] != 0 && matrix[i][(j - 2 + 4) % 4] == matrix[i][(j - 3 + 4) % 4]) {
						groups[count].push_back(Pair(number_of_minterms(3, i, (j - 2 + 4) % 4), number_of_minterms(3, i, (j - 3 + 4) % 4)));
						matrix[i][j]++;
						matrix[i][(j - 1 + 4) % 4]++;
						matrix[i][(j - 2 + 4) % 4]++;
						matrix[i][(j - 3 + 4) % 4]++;
						count++;
					}
					// No Bars
					else {
						matrix[i][j]++;
						matrix[i][(j - 1 + 4) % 4]++;
						count++;
					}
				}
				// ( Right ) Find Pairs
				if (matrix[i][j] == 1 && matrix[i][(j + 1) % 4] != 0) {
					groups[count].push_back(Pair(number_of_minterms(3, i, j), number_of_minterms(3, i, (j + 1) % 4)));
					// ( Right ) Find Bars
					if (matrix[i][(j + 2) % 4] != 0 && matrix[i][(j + 2) % 4] == matrix[i][(j + 3) % 4]) {
						groups[count].push_back(Pair(number_of_minterms(3, i, (j + 2) % 4), number_of_minterms(3, i, (j + 3) % 4)));
						matrix[i][j]++;
						matrix[i][(j + 1) % 4]++;
						matrix[i][(j + 2) % 4]++;
						matrix[i][(j + 3) % 4]++;
						count++;
					}
					// No Bars
					else {
						matrix[i][j]++;
						matrix[i][(j + 1) % 4]++;
						count++;
					}
				}
			}
		}

		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 4; j++) {
				if (matrix[i][j] == 1) {
					minterm.push_back(number_of_minterms(3, i, j));
					matrix[i][j] ++;
					count_min_is_Implicant++;
				}
			}
		}

		//Check if correct output
		/*
		for (int i = 0; i <= 2; i++) {
			for (int j = 0; j < 4; j++) {
				cout << matrix[i][j];
			}
			cout << endl;
		}
		*/
		/* Check if correct prime implicant with don't cares*/
		/*
		cout << endl << "There have " << count << " prime implicants with don't cares." << endl;

		cout << endl << "Prime implicants with don't cares: " << endl;

		for (int i = 0; i < count_min_is_Implicant; i++) {
			cout << " " << minterm[i] << endl;
		}

		for (int i = 0; i < groups.size(); i++) {
			for (int j = 0; j < groups[i].size(); j++) {
				cout << " " << groups[i][j].x << " " << groups[i][j].y;
			}
			cout << endl;
		}
		*/
	}
	if (number == "4") {
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				groups.push_back(group);

				// ( Left ) Find Pairs
				if (matrix[i][j] == 1 && matrix[i][(j - 1 + 4) % 4] != 0) {
					groups[count].push_back(Pair(number_of_minterms(4, i, j), number_of_minterms(4, i, (j - 1 + 4) % 4)));
					// ( Down ) Find Squares
					if (matrix[(i + 1 + 4) % 4][(j - 0 + 4) % 4] != 0 && matrix[(i + 1 + 4) % 4][(j - 1 + 4) % 4] != 0) {
						groups[count].push_back(Pair(number_of_minterms(4, (i + 1 + 4) % 4, (j - 0 + 4) % 4), number_of_minterms(4, (i + 1 + 4) % 4, (j - 1 + 4) % 4)));
						// ( Right ) Find Octants
						if (matrix[(i + 0 + 4) % 4][(j - 2 + 4) % 4] != 0 && matrix[(i + 0 + 4) % 4][(j - 3 + 4) % 4] != 0 && matrix[(i + 1 + 4) % 4][(j - 2 + 4) % 4] != 0 && matrix[(i + 1 + 4) % 4][(j - 3 + 4) % 4] != 0) {
							groups[count].push_back(Pair(number_of_minterms(4, (i + 0 + 4) % 4, (j - 2 + 4) % 4), number_of_minterms(4, (i + 0 + 4) % 4, (j - 3 + 4) % 4)));
							groups[count].push_back(Pair(number_of_minterms(4, (i + 1 + 4) % 4, (j - 2 + 4) % 4), number_of_minterms(4, (i + 1 + 4) % 4, (j - 3 + 4) % 4)));
							matrix[(i + 0 + 4) % 4][(j - 0 + 4) % 4] ++;
							matrix[(i + 0 + 4) % 4][(j - 1 + 4) % 4] ++;
							matrix[(i + 0 + 4) % 4][(j - 2 + 4) % 4] ++;
							matrix[(i + 0 + 4) % 4][(j - 3 + 4) % 4] ++;
							matrix[(i + 1 + 4) % 4][(j - 0 + 4) % 4] ++;
							matrix[(i + 1 + 4) % 4][(j - 1 + 4) % 4] ++;
							matrix[(i + 1 + 4) % 4][(j - 2 + 4) % 4] ++;
							matrix[(i + 1 + 4) % 4][(j - 3 + 4) % 4] ++;
							count++;
						}
						// ( Down ) Find Octants
						else if (matrix[(i + 2 + 4) % 4][(j - 0 + 4) % 4] != 0 && matrix[(i + 3 + 4) % 4][(j - 0 + 4) % 4] != 0 && matrix[(i + 2 + 4) % 4][(j - 1 + 4) % 4] != 0 && matrix[(i + 3 + 4) % 4][(j - 1 + 4) % 4] != 0) {
							groups[count].push_back(Pair(number_of_minterms(4, (i + 2 + 4) % 4, (j - 0 + 4) % 4), number_of_minterms(4, (i + 2 + 4) % 4, (j - 1 + 4) % 4)));
							groups[count].push_back(Pair(number_of_minterms(4, (i + 3 + 4) % 4, (j - 0 + 4) % 4), number_of_minterms(4, (i + 3 + 4) % 4, (j - 1 + 4) % 4)));
							matrix[(i + 0 + 4) % 4][(j - 0 + 4) % 4] ++;
							matrix[(i + 1 + 4) % 4][(j - 0 + 4) % 4] ++;
							matrix[(i + 2 + 4) % 4][(j - 0 + 4) % 4] ++;
							matrix[(i + 3 + 4) % 4][(j - 0 + 4) % 4] ++;
							matrix[(i + 0 + 4) % 4][(j - 1 + 4) % 4] ++;
							matrix[(i + 1 + 4) % 4][(j - 1 + 4) % 4] ++;
							matrix[(i + 2 + 4) % 4][(j - 1 + 4) % 4] ++;
							matrix[(i + 3 + 4) % 4][(j - 1 + 4) % 4] ++;
							count++;
						}
						// no octants
						else {
							matrix[(i + 0 + 4) % 4][(j - 0 + 4) % 4] ++;
							matrix[(i + 0 + 4) % 4][(j - 1 + 4) % 4] ++;
							matrix[(i + 1 + 4) % 4][(j - 0 + 4) % 4] ++;
							matrix[(i + 1 + 4) % 4][(j - 1 + 4) % 4] ++;
							count++;
						}
					}
					// ( Up ) Find Squares
					else if (matrix[(i - 1 + 4) % 4][(j - 0 + 4) % 4] != 0 && matrix[(i - 1 + 4) % 4][(j - 1 + 4) % 4] != 0) {
						groups[count].push_back(Pair(number_of_minterms(4, (i - 1 + 4) % 4, (j - 0 + 4) % 4), number_of_minterms(4, (i - 1 + 4) % 4, (j - 1 + 4) % 4)));
						// ( Right ) Find Octants
						if (matrix[(i - 0 + 4) % 4][(j - 2 + 4) % 4] != 0 && matrix[(i - 0 + 4) % 4][(j - 3 + 4) % 4] != 0 && matrix[(i - 1 + 4) % 4][(j - 2 + 4) % 4] != 0 && matrix[(i - 1 + 4) % 4][(j - 3 + 4) % 4] != 0) {
							groups[count].push_back(Pair(number_of_minterms(4, (i - 0 + 4) % 4, (j - 2 + 4) % 4), number_of_minterms(4, (i - 0 + 4) % 4, (j - 3 + 4) % 4)));
							groups[count].push_back(Pair(number_of_minterms(4, (i - 1 + 4) % 4, (j - 2 + 4) % 4), number_of_minterms(4, (i - 1 + 4) % 4, (j - 3 + 4) % 4)));
							matrix[(i - 0 + 4) % 4][(j - 0 + 4) % 4] ++;
							matrix[(i - 0 + 4) % 4][(j - 1 + 4) % 4] ++;
							matrix[(i - 0 + 4) % 4][(j - 2 + 4) % 4] ++;
							matrix[(i - 0 + 4) % 4][(j - 3 + 4) % 4] ++;
							matrix[(i - 1 + 4) % 4][(j - 0 + 4) % 4] ++;
							matrix[(i - 1 + 4) % 4][(j - 1 + 4) % 4] ++;
							matrix[(i - 1 + 4) % 4][(j - 2 + 4) % 4] ++;
							matrix[(i - 1 + 4) % 4][(j - 3 + 4) % 4] ++;
							count++;
						}
						// no octants
						else {
							matrix[(i - 0 + 4) % 4][(j - 0 + 4) % 4] ++;
							matrix[(i - 0 + 4) % 4][(j - 1 + 4) % 4] ++;
							matrix[(i - 1 + 4) % 4][(j - 0 + 4) % 4] ++;
							matrix[(i - 1 + 4) % 4][(j - 1 + 4) % 4] ++;
							count++;
						}
					}

					// ( Right ) Find Bars
					else if (matrix[i][(j - 2 + 4) % 4] != 0 && matrix[i][(j - 3 + 4) % 4] != 0) {
						groups[count].push_back(Pair(number_of_minterms(4, i, (j - 2 + 4) % 4), number_of_minterms(4, i, (j - 3 + 4) % 4)));
						// ( Down ) Find Octants
						if (matrix[(i + 1 + 4) % 4][(j - 0 + 4) % 4] != 0 && matrix[(i + 1 + 4) % 4][(j - 1 + 4) % 4] != 0 && matrix[(i + 1 + 4) % 4][(j - 2 + 4) % 4] != 0 && matrix[(i + 1 + 4) % 4][(j - 3 + 4) % 4] != 0) {
							groups[count].push_back(Pair(number_of_minterms(4, (i + 1 + 4) % 4, (j - 0 + 4) % 4), number_of_minterms(4, (i + 1 + 4) % 4, (j - 1 + 4) % 4)));
							groups[count].push_back(Pair(number_of_minterms(4, (i + 1 + 4) % 4, (j - 2 + 4) % 4), number_of_minterms(4, (i + 1 + 4) % 4, (j - 3 + 4) % 4)));
							matrix[i][(j - 0 + 4) % 4] ++;
							matrix[i][(j - 1 + 4) % 4] ++;
							matrix[i][(j - 2 + 4) % 4] ++;
							matrix[i][(j - 3 + 4) % 4] ++;
							matrix[(i + 1 + 4) % 4][(j - 0 + 4) % 4] ++;
							matrix[(i + 1 + 4) % 4][(j - 1 + 4) % 4] ++;
							matrix[(i + 1 + 4) % 4][(j - 2 + 4) % 4] ++;
							matrix[(i + 1 + 4) % 4][(j - 3 + 4) % 4] ++;
							count++;
						}
						// ( Up ) Find Octants
						else if (matrix[(i - 1 + 4) % 4][(j - 0 + 4) % 4] != 0 && matrix[(i - 1 + 4) % 4][(j - 1 + 4) % 4] != 0 && matrix[(i - 1 + 4) % 4][(j - 2 + 4) % 4] != 0 && matrix[(i - 1 + 4) % 4][(j - 3 + 4) % 4 % 4] != 0) {
							groups[count].push_back(Pair(number_of_minterms(4, (i - 1 + 4) % 4, (j - 0 + 4) % 4), number_of_minterms(4, (i - 1 + 4) % 4, (j - 1 + 4) % 4)));
							groups[count].push_back(Pair(number_of_minterms(4, (i - 1 + 4) % 4, (j - 2 + 4) % 4), number_of_minterms(4, (i - 1 + 4) % 4, (j - 3 + 4) % 4)));
							matrix[i][(j - 0 + 4) % 4] ++;
							matrix[i][(j - 1 + 4) % 4] ++;
							matrix[i][(j - 2 + 4) % 4] ++;
							matrix[i][(j - 3 + 4) % 4] ++;
							matrix[(i - 1 + 4) % 4][(j - 0 + 4) % 4] ++;
							matrix[(i - 1 + 4) % 4][(j - 1 + 4) % 4] ++;
							matrix[(i - 1 + 4) % 4][(j - 2 + 4) % 4] ++;
							matrix[(i - 1 + 4) % 4][(j - 3 + 4) % 4] ++;
							count++;
						}
						// no octants
						else {
							matrix[i][(j - 0 + 4) % 4] ++;
							matrix[i][(j - 1 + 4) % 4] ++;
							matrix[i][(j - 2 + 4) % 4] ++;
							matrix[i][(j - 3 + 4) % 4] ++;
							count++;
						}
					}
					// no bars
					else {
						matrix[i][(j - 0 + 4) % 4] ++;
						matrix[i][(j - 1 + 4) % 4] ++;
						count++;
					}
				}

				// ( Up ) Find Pairs
				else if (matrix[i][j] == 1 && matrix[(i - 1 + 4) % 4][(j + 0 + 4) % 4] != 0) {
					groups[count].push_back(Pair(number_of_minterms(4, i, j), number_of_minterms(4, (i - 1 + 4) % 4, (j + 0 + 4) % 4 % 4)));
					// ( Right ) Find Squares
					if (matrix[(i - 0 + 4) % 4][(j + 1 + 4) % 4] != 0 && matrix[(i - 1 + 4) % 4][(j + 1 + 4) % 4] != 0) {
						groups[count].push_back(Pair(number_of_minterms(4, (i - 0 + 4) % 4, (j + 1 + 4) % 4), number_of_minterms(4, (i - 1 + 4) % 4, (j + 1 + 4) % 4)));
						// ( Up ) Find Octants
						if (matrix[(i - 2 + 4) % 4][(j + 0 + 4) % 4] != 0 && matrix[(i - 3 + 4) % 4][(j + 0 + 4) % 4] != 0 && matrix[(i - 2 + 4) % 4][(j + 1 + 4) % 4] != 0 && matrix[(i - 3 + 4) % 4][(j + 1 + 4) % 4] != 0) {
							groups[count].push_back(Pair(number_of_minterms(4, (i - 2 + 4) % 4, (j + 0 + 4) % 4), number_of_minterms(4, (i - 3 + 4) % 4, (j + 0 + 4) % 4)));
							groups[count].push_back(Pair(number_of_minterms(4, (i - 2 + 4) % 4, (j + 1 + 4) % 4), number_of_minterms(4, (i - 3 + 4) % 4, (j + 1 + 4) % 4)));
							matrix[(i - 0 + 4) % 4][(j + 0 + 4) % 4] ++;
							matrix[(i - 1 + 4) % 4][(j + 0 + 4) % 4] ++;
							matrix[(i - 2 + 4) % 4][(j + 0 + 4) % 4] ++;
							matrix[(i - 3 + 4) % 4][(j + 0 + 4) % 4] ++;
							matrix[(i - 0 + 4) % 4][(j + 1 + 4) % 4] ++;
							matrix[(i - 1 + 4) % 4][(j + 1 + 4) % 4] ++;
							matrix[(i - 2 + 4) % 4][(j + 1 + 4) % 4] ++;
							matrix[(i - 3 + 4) % 4][(j + 1 + 4) % 4] ++;
							count++;
						}
						// ( Right ) Find Octants
						else if (matrix[(i - 0 + 4) % 4][(j + 2 + 4) % 4] != 0 && matrix[(i - 0 + 4) % 4][(j + 3 + 4) % 4] != 0 && matrix[(i - 1 + 4) % 4][(j + 2 + 4) % 4] != 0 && matrix[(i - 1 + 4) % 4][(j + 3 + 4) % 4] != 0) {
							groups[count].push_back(Pair(number_of_minterms(4, (i - 0 + 4) % 4, (j + 2 + 4) % 4), number_of_minterms(4, (i - 0 + 4) % 4, (j + 3 + 4) % 4)));
							groups[count].push_back(Pair(number_of_minterms(4, (i - 1 + 4) % 4, (j + 2 + 4) % 4), number_of_minterms(4, (i - 1 + 4) % 4, (j + 3 + 4) % 4)));
							matrix[(i - 0 + 4) % 4][(j + 0 + 4) % 4] ++;
							matrix[(i - 0 + 4) % 4][(j + 1 + 4) % 4] ++;
							matrix[(i - 0 + 4) % 4][(j + 2 + 4) % 4] ++;
							matrix[(i - 0 + 4) % 4][(j + 3 + 4) % 4] ++;
							matrix[(i - 1 + 4) % 4][(j + 0 + 4) % 4] ++;
							matrix[(i - 1 + 4) % 4][(j + 1 + 4) % 4] ++;
							matrix[(i - 1 + 4) % 4][(j + 2 + 4) % 4] ++;
							matrix[(i - 1 + 4) % 4][(j + 3 + 4) % 4] ++;
							count++;
						}
						// no octants
						else {
							matrix[(i - 0 + 4) % 4][(j + 0 + 4) % 4] ++;
							matrix[(i - 1 + 4) % 4][(j + 0 + 4) % 4] ++;
							matrix[(i - 0 + 4) % 4][(j + 1 + 4) % 4] ++;
							matrix[(i - 1 + 4) % 4][(j + 1 + 4) % 4] ++;
							count++;
						}
					}
					// ( Left ) Find Squares
					else if (matrix[(i - 0 + 4) % 4][(j - 1 + 4) % 4] != 0 && matrix[(i - 1 + 4) % 4][(j - 1 + 4) % 4] != 0) {
						groups[count].push_back(Pair(number_of_minterms(4, (i - 0 + 4) % 4, (j - 1 + 4) % 4), number_of_minterms(4, (i - 1 + 4) % 4, (j - 1 + 4) % 4)));
						// ( Left ) Find Octants
						if (matrix[(i - 2 + 4) % 4][(j - 0 + 4) % 4] != 0 && matrix[(i - 3 + 4) % 4][(j - 0 + 4) % 4] != 0 && matrix[(i - 2 + 4) % 4][(j - 1 + 4) % 4] != 0 && matrix[(i - 3 + 4) % 4][(j - 1 + 4) % 4] != 0) {
							groups[count].push_back(Pair(number_of_minterms(4, (i - 2 + 4) % 4, (j - 0 + 4) % 4), number_of_minterms(4, (i - 3 + 4) % 4, (j - 0 + 4) % 4)));
							groups[count].push_back(Pair(number_of_minterms(4, (i - 2 + 4) % 4, (j - 1 + 4) % 4), number_of_minterms(4, (i - 3 + 4) % 4, (j - 1 + 4) % 4)));
							matrix[(i - 0 + 4) % 4][(j - 0 + 4) % 4] ++;
							matrix[(i - 1 + 4) % 4][(j - 0 + 4) % 4] ++;
							matrix[(i - 2 + 4) % 4][(j - 0 + 4) % 4] ++;
							matrix[(i - 3 + 4) % 4][(j - 0 + 4) % 4] ++;
							matrix[(i - 0 + 4) % 4][(j - 1 + 4) % 4] ++;
							matrix[(i - 1 + 4) % 4][(j - 1 + 4) % 4] ++;
							matrix[(i - 2 + 4) % 4][(j - 1 + 4) % 4] ++;
							matrix[(i - 3 + 4) % 4][(j - 1 + 4) % 4] ++;
							count++;
						}
						// no octants
						else {
							matrix[(i - 0 + 4) % 4][(j - 0 + 4) % 4] ++;
							matrix[(i - 1 + 4) % 4][(j - 0 + 4) % 4] ++;
							matrix[(i - 0 + 4) % 4][(j - 1 + 4) % 4] ++;
							matrix[(i - 1 + 4) % 4][(j - 1 + 4) % 4] ++;
							count++;
						}
					}

					// ( Up ) Find Bars
					else if (matrix[(i - 2 + 4) % 4][j] != 0 && matrix[(i - 3 + 4) % 4][j] != 0) {
						groups[count].push_back(Pair(number_of_minterms(4, (i - 2 + 4), j), number_of_minterms(4, (i - 3 + 4), j)));
						// ( Right ) Find Octants
						if (matrix[(i - 0 + 4) % 4][(j + 1 + 4) % 4] != 0 && matrix[(i - 1 + 4) % 4][(j + 1 + 4) % 4] != 0 && matrix[(i - 2 + 4) % 4][(j + 1 + 4) % 4] != 0 && matrix[(i - 3 + 4) % 4][(j + 1 + 4) % 4] != 0) {
							groups[count].push_back(Pair(number_of_minterms(4, (i - 0 + 4) % 4, (j + 1 + 4) % 4), number_of_minterms(4, (i - 1 + 4) % 4, (j + 1 + 4) % 4)));
							groups[count].push_back(Pair(number_of_minterms(4, (i - 2 + 4) % 4, (j + 1 + 4) % 4), number_of_minterms(4, (i - 3 + 4) % 4, (j + 1 + 4) % 4)));
							matrix[(i - 0 + 4) % 4][(j + 0 + 4) % 4] ++;
							matrix[(i - 1 + 4) % 4][(j + 0 + 4) % 4] ++;
							matrix[(i - 2 + 4) % 4][(j + 0 + 4) % 4] ++;
							matrix[(i - 3 + 4) % 4][(j + 0 + 4) % 4] ++;
							matrix[(i - 0 + 4) % 4][(j + 1 + 4) % 4] ++;
							matrix[(i - 1 + 4) % 4][(j + 1 + 4) % 4] ++;
							matrix[(i - 2 + 4) % 4][(j + 1 + 4) % 4] ++;
							matrix[(i - 3 + 4) % 4][(j + 1 + 4) % 4] ++;
							count++;
						}
						// ( Left ) Find Octants
						else if (matrix[(i - 0 + 4) % 4][(j - 1 + 4) % 4] != 0 && matrix[(i - 1 + 4) % 4][(j - 1 + 4) % 4] != 0 && matrix[(i - 2 + 4) % 4][(j - 1 + 4) % 4] != 0 && matrix[(i - 3 + 4) % 4][(j - 1 + 4) % 4 % 4] != 0) {
							groups[count].push_back(Pair(number_of_minterms(4, (i - 0 + 4) % 4, (j - 1 + 4) % 4), number_of_minterms(4, (i - 1 + 4) % 4, (j - 1 + 4) % 4)));
							groups[count].push_back(Pair(number_of_minterms(4, (i - 2 + 4) % 4, (j - 1 + 4) % 4), number_of_minterms(4, (i - 3 + 4) % 4, (j - 1 + 4) % 4)));
							matrix[(i - 0 + 4) % 4][(j - 0 + 4) % 4] ++;
							matrix[(i - 1 + 4) % 4][(j - 0 + 4) % 4] ++;
							matrix[(i - 2 + 4) % 4][(j - 0 + 4) % 4] ++;
							matrix[(i - 3 + 4) % 4][(j - 0 + 4) % 4] ++;
							matrix[(i - 0 + 4) % 4][(j - 1 + 4) % 4] ++;
							matrix[(i - 1 + 4) % 4][(j - 1 + 4) % 4] ++;
							matrix[(i - 2 + 4) % 4][(j - 1 + 4) % 4] ++;
							matrix[(i - 3 + 4) % 4][(j - 1 + 4) % 4] ++;
							count++;
						}
						// no octants
						else {
							matrix[(i - 0 + 4) % 4][(j - 0 + 4) % 4] ++;
							matrix[(i - 1 + 4) % 4][(j - 0 + 4) % 4] ++;
							matrix[(i - 2 + 4) % 4][(j - 0 + 4) % 4] ++;
							matrix[(i - 3 + 4) % 4][(j - 0 + 4) % 4] ++;
							count++;
						}
					}
					// no bars
					else {
						matrix[(i - 0 + 4) % 4][(j - 0 + 4) % 4] ++;
						matrix[(i - 1 + 4) % 4][(j - 0 + 4) % 4] ++;
						count++;
					}
				}

				// ( Right ) Find Pairs
				else if (matrix[i][j] == 1 && matrix[i][(j + 1 + 4) % 4] != 0) {
					groups[count].push_back(Pair(number_of_minterms(4, i, j), number_of_minterms(4, i, (j + 1 + 4) % 4)));
					// ( Down ) Find Squares
					if (matrix[(i + 1 + 4) % 4][(j + 0 + 4) % 4] != 0 && matrix[(i + 1 + 4) % 4][(j + 1 + 4) % 4] != 0) {
						groups[count].push_back(Pair(number_of_minterms(4, (i + 1 + 4) % 4, (j + 0 + 4) % 4), number_of_minterms(4, (i + 1 + 4) % 4, (j + 1 + 4) % 4)));
						// ( Right ) Find Octants
						if (matrix[(i + 0 + 4) % 4][(j + 2 + 4) % 4] != 0 && matrix[(i + 0 + 4) % 4][(j + 3 + 4) % 4] != 0 && matrix[(i + 1 + 4) % 4][(j + 2 + 4) % 4] != 0 && matrix[(i + 1 + 4) % 4][(j + 3 + 4) % 4] != 0) {
							groups[count].push_back(Pair(number_of_minterms(4, (i + 0 + 4) % 4, (j + 2 + 4) % 4), number_of_minterms(4, (i + 0 + 4) % 4, (j + 3 + 4) % 4)));
							groups[count].push_back(Pair(number_of_minterms(4, (i + 1 + 4) % 4, (j + 2 + 4) % 4), number_of_minterms(4, (i + 1 + 4) % 4, (j + 3 + 4) % 4)));
							matrix[(i + 0 + 4) % 4][(j + 0 + 4) % 4] ++;
							matrix[(i + 0 + 4) % 4][(j + 1 + 4) % 4] ++;
							matrix[(i + 0 + 4) % 4][(j + 2 + 4) % 4] ++;
							matrix[(i + 0 + 4) % 4][(j + 3 + 4) % 4] ++;
							matrix[(i + 1 + 4) % 4][(j + 0 + 4) % 4] ++;
							matrix[(i + 1 + 4) % 4][(j + 1 + 4) % 4] ++;
							matrix[(i + 1 + 4) % 4][(j + 2 + 4) % 4] ++;
							matrix[(i + 1 + 4) % 4][(j + 3 + 4) % 4] ++;
							count++;
						}
						// ( Down ) Find Octants
						else if (matrix[(i + 2 + 4) % 4][(j + 0 + 4) % 4] != 0 && matrix[(i + 3 + 4) % 4][(j + 0 + 4) % 4] != 0 && matrix[(i + 2 + 4) % 4][(j + 1 + 4) % 4] != 0 && matrix[(i + 3 + 4) % 4][(j + 1 + 4) % 4] != 0) {
							groups[count].push_back(Pair(number_of_minterms(4, (i + 2 + 4) % 4, (j + 0 + 4) % 4), number_of_minterms(4, (i + 3 + 4) % 4, (j + 0 + 4) % 4)));
							groups[count].push_back(Pair(number_of_minterms(4, (i + 2 + 4) % 4, (j + 1 + 4) % 4), number_of_minterms(4, (i + 3 + 4) % 4, (j + 1 + 4) % 4)));
							matrix[(i + 0 + 4) % 4][(j + 0 + 4) % 4] ++;
							matrix[(i + 1 + 4) % 4][(j + 0 + 4) % 4] ++;
							matrix[(i + 2 + 4) % 4][(j + 0 + 4) % 4] ++;
							matrix[(i + 3 + 4) % 4][(j + 0 + 4) % 4] ++;
							matrix[(i + 0 + 4) % 4][(j + 1 + 4) % 4] ++;
							matrix[(i + 1 + 4) % 4][(j + 1 + 4) % 4] ++;
							matrix[(i + 2 + 4) % 4][(j + 1 + 4) % 4] ++;
							matrix[(i + 3 + 4) % 4][(j + 1 + 4) % 4] ++;
							count++;
						}
						// no octants
						else {
							matrix[(i + 0 + 4) % 4][(j + 0 + 4) % 4] ++;
							matrix[(i + 0 + 4) % 4][(j + 1 + 4) % 4] ++;
							matrix[(i + 1 + 4) % 4][(j + 0 + 4) % 4] ++;
							matrix[(i + 1 + 4) % 4][(j + 1 + 4) % 4] ++;
							count++;
						}
					}
					// ( Up ) Find Squares
					else if (matrix[(i - 1 + 4) % 4][(j + 0 + 4) % 4] != 0 && matrix[(i - 1 + 4) % 4][(j + 1 + 4) % 4] != 0) {
						groups[count].push_back(Pair(number_of_minterms(4, (i - 1 + 4) % 4, (j + 0 + 4) % 4), number_of_minterms(4, (i - 1 + 4) % 4, (j + 1 + 4) % 4)));
						// ( Right ) Find Octants
						if (matrix[(i - 0 + 4) % 4][(j + 2 + 4) % 4] != 0 && matrix[(i - 0 + 4) % 4][(j + 3 + 4) % 4] != 0 && matrix[(i - 1 + 4) % 4][(j + 2 + 4) % 4] != 0 && matrix[(i - 1 + 4) % 4][(j + 3 + 4) % 4] != 0) {
							groups[count].push_back(Pair(number_of_minterms(4, (i - 0 + 4) % 4, (j + 2 + 4) % 4), number_of_minterms(4, (i - 0 + 4) % 4, (j + 3 + 4) % 4)));
							groups[count].push_back(Pair(number_of_minterms(4, (i - 1 + 4) % 4, (j + 2 + 4) % 4), number_of_minterms(4, (i - 1 + 4) % 4, (j + 3 + 4) % 4)));
							matrix[(i + 0 + 4) % 4][(j + 0 + 4) % 4] ++;
							matrix[(i + 0 + 4) % 4][(j + 1 + 4) % 4] ++;
							matrix[(i + 0 + 4) % 4][(j + 2 + 4) % 4] ++;
							matrix[(i + 0 + 4) % 4][(j + 3 + 4) % 4] ++;
							matrix[(i - 1 + 4) % 4][(j + 0 + 4) % 4] ++;
							matrix[(i - 1 + 4) % 4][(j + 1 + 4) % 4] ++;
							matrix[(i - 1 + 4) % 4][(j + 2 + 4) % 4] ++;
							matrix[(i - 1 + 4) % 4][(j + 3 + 4) % 4] ++;
							count++;
						}
						// no octants
						else {
							matrix[(i - 0 + 4) % 4][(j + 0 + 4) % 4] ++;
							matrix[(i - 0 + 4) % 4][(j + 1 + 4) % 4] ++;
							matrix[(i - 1 + 4) % 4][(j + 0 + 4) % 4] ++;
							matrix[(i - 1 + 4) % 4][(j + 1 + 4) % 4] ++;
							count++;
						}
					}
					// ( Right ) Find Bars
					else if (matrix[i][(j + 2) % 4] != 0 && matrix[i][(j + 3) % 4] != 0) {
						groups[count].push_back(Pair(number_of_minterms(4, i, (j + 2 + 4) % 4), number_of_minterms(4, i, (j + 3 + 4) % 4)));
						// ( Down ) Find Octants
						if (matrix[(i + 1 + 4) % 4][(j + 0 + 4) % 4] != 0 && matrix[(i + 1 + 4) % 4][(j + 1 + 4) % 4] != 0 && matrix[(i + 1 + 4) % 4][(j + 2 + 4) % 4] != 0 && matrix[(i + 1 + 4) % 4][(j + 3 + 4) % 4] != 0) {
							groups[count].push_back(Pair(number_of_minterms(4, (i + 1 + 4) % 4, (j + 0 + 4) % 4), number_of_minterms(4, (i + 1 + 4) % 4, (j + 1 + 4) % 4)));
							groups[count].push_back(Pair(number_of_minterms(4, (i + 1 + 4) % 4, (j + 2 + 4) % 4), number_of_minterms(4, (i + 1 + 4) % 4, (j + 3 + 4) % 4)));
							matrix[i][(j + 0 + 4) % 4] ++;
							matrix[i][(j + 1 + 4) % 4] ++;
							matrix[i][(j + 2 + 4) % 4] ++;
							matrix[i][(j + 3 + 4) % 4] ++;
							matrix[(i + 1 + 4) % 4][(j + 0 + 4) % 4] ++;
							matrix[(i + 1 + 4) % 4][(j + 1 + 4) % 4] ++;
							matrix[(i + 1 + 4) % 4][(j + 2 + 4) % 4] ++;
							matrix[(i + 1 + 4) % 4][(j + 3 + 4) % 4] ++;
							count++;
						}
						// ( Up ) Find Octants
						if (matrix[(i - 1 + 4) % 4][(j + 0 + 4) % 4] != 0 && matrix[(i - 1 + 4) % 4][(j + 1 + 4) % 4] != 0 && matrix[(i - 1 + 4) % 4][(j + 2 + 4) % 4] != 0 && matrix[(i - 1 + 4) % 4][(j + 3 + 4) % 4 % 4] != 0) {
							groups[count].push_back(Pair(number_of_minterms(4, (i - 1 + 4) % 4, (j + 0 + 4) % 4), number_of_minterms(4, (i - 1 + 4) % 4, (j + 1 + 4) % 4)));
							groups[count].push_back(Pair(number_of_minterms(4, (i - 1 + 4) % 4, (j + 2 + 4) % 4), number_of_minterms(4, (i - 1 + 4) % 4, (j + 3 + 4) % 4)));
							matrix[i][(j + 0 + 4) % 4] ++;
							matrix[i][(j + 1 + 4) % 4] ++;
							matrix[i][(j + 2 + 4) % 4] ++;
							matrix[i][(j + 3 + 4) % 4] ++;
							matrix[(i - 1 + 4) % 4][(j + 0 + 4) % 4] ++;
							matrix[(i - 1 + 4) % 4][(j + 1 + 4) % 4] ++;
							matrix[(i - 1 + 4) % 4][(j + 2 + 4) % 4] ++;
							matrix[(i - 1 + 4) % 4][(j + 3 + 4) % 4] ++;
							count++;
						}
						// no octants
						else {
							matrix[i][(j + 0 + 4) % 4] ++;
							matrix[i][(j + 1 + 4) % 4] ++;
							matrix[i][(j + 2 + 4) % 4] ++;
							matrix[i][(j + 3 + 4) % 4] ++;
							count++;
						}
					}
					// no bars & squares
					else {
						matrix[i][(j + 0 + 4) % 4] ++;
						matrix[i][(j + 1 + 4) % 4] ++;
						count++;
					}
				}

				// ( Down ) Find Pairs
				else if (matrix[i][j] == 1 && matrix[(i + 1 + 4) % 4][(j + 0 + 4) % 4] != 0) {
					groups[count].push_back(Pair(number_of_minterms(4, i, j), number_of_minterms(4, (i + 1 + 4) % 4, (j + 0 + 4) % 4 % 4)));
					// ( Right ) Find Squares
					if (matrix[(i + 0 + 4) % 4][(j + 1 + 4) % 4] != 0 && matrix[(i + 1 + 4) % 4][(j + 1 + 4) % 4] != 0) {
						groups[count].push_back(Pair(number_of_minterms(4, (i + 0 + 4) % 4, (j + 1 + 4) % 4), number_of_minterms(4, (i + 1 + 4) % 4, (j + 1 + 4) % 4)));
						// ( Down ) Find Octants
						if (matrix[(i + 2 + 4) % 4][(j + 0 + 4) % 4] != 0 && matrix[(i + 3 + 4) % 4][(j + 0 + 4) % 4] != 0 && matrix[(i + 2 + 4) % 4][(j + 1 + 4) % 4] != 0 && matrix[(i + 3 + 4) % 4][(j + 1 + 4) % 4] != 0) {
							groups[count].push_back(Pair(number_of_minterms(4, (i + 2 + 4) % 4, (j + 0 + 4) % 4), number_of_minterms(4, (i + 3 + 4) % 4, (j + 0 + 4) % 4)));
							groups[count].push_back(Pair(number_of_minterms(4, (i + 2 + 4) % 4, (j + 1 + 4) % 4), number_of_minterms(4, (i + 3 + 4) % 4, (j + 1 + 4) % 4)));
							matrix[(i + 0 + 4) % 4][(j + 0 + 4) % 4] ++;
							matrix[(i + 1 + 4) % 4][(j + 0 + 4) % 4] ++;
							matrix[(i + 2 + 4) % 4][(j + 0 + 4) % 4] ++;
							matrix[(i + 3 + 4) % 4][(j + 0 + 4) % 4] ++;
							matrix[(i + 0 + 4) % 4][(j + 1 + 4) % 4] ++;
							matrix[(i + 1 + 4) % 4][(j + 1 + 4) % 4] ++;
							matrix[(i + 2 + 4) % 4][(j + 1 + 4) % 4] ++;
							matrix[(i + 3 + 4) % 4][(j + 1 + 4) % 4] ++;
							count++;
						}
						// ( Right ) Find Octants
						else if (matrix[(i + 0 + 4) % 4][(j + 2 + 4) % 4] != 0 && matrix[(i + 0 + 4) % 4][(j + 3 + 4) % 4] != 0 && matrix[(i + 1 + 4) % 4][(j + 2 + 4) % 4] != 0 && matrix[(i + 1 + 4) % 4][(j + 3 + 4) % 4] != 0) {
							groups[count].push_back(Pair(number_of_minterms(4, (i + 0 + 4) % 4, (j + 2 + 4) % 4), number_of_minterms(4, (i + 0 + 4) % 4, (j + 3 + 4) % 4)));
							groups[count].push_back(Pair(number_of_minterms(4, (i + 1 + 4) % 4, (j + 2 + 4) % 4), number_of_minterms(4, (i + 1 + 4) % 4, (j + 3 + 4) % 4)));
							matrix[(i + 0 + 4) % 4][(j + 0 + 4) % 4] ++;
							matrix[(i + 0 + 4) % 4][(j + 1 + 4) % 4] ++;
							matrix[(i + 0 + 4) % 4][(j + 2 + 4) % 4] ++;
							matrix[(i + 0 + 4) % 4][(j + 3 + 4) % 4] ++;
							matrix[(i + 1 + 4) % 4][(j + 0 + 4) % 4] ++;
							matrix[(i + 1 + 4) % 4][(j + 1 + 4) % 4] ++;
							matrix[(i + 1 + 4) % 4][(j + 2 + 4) % 4] ++;
							matrix[(i + 1 + 4) % 4][(j + 3 + 4) % 4] ++;
							count++;
						}
						// no octants
						else {
							matrix[(i + 0 + 4) % 4][(j + 0 + 4) % 4] ++;
							matrix[(i + 1 + 4) % 4][(j + 0 + 4) % 4] ++;
							matrix[(i + 0 + 4) % 4][(j + 1 + 4) % 4] ++;
							matrix[(i + 1 + 4) % 4][(j + 1 + 4) % 4] ++;
							count++;
						}
					}
					// ( Left ) Find Squares
					else if (matrix[(i + 0 + 4) % 4][(j - 1 + 4) % 4] != 0 && matrix[(i + 1 + 4) % 4][(j - 1 + 4) % 4] != 0) {
						groups[count].push_back(Pair(number_of_minterms(4, (i + 0 + 4) % 4, (j - 1 + 4) % 4), number_of_minterms(4, (i + 1 + 4) % 4, (j - 1 + 4) % 4)));
						// ( Left ) Find Octants
						if (matrix[(i + 2 + 4) % 4][(j - 0 + 4) % 4] != 0 && matrix[(i + 3 + 4) % 4][(j - 0 + 4) % 4] != 0 && matrix[(i + 2 + 4) % 4][(j - 1 + 4) % 4] != 0 && matrix[(i + 3 + 4) % 4][(j - 1 + 4) % 4] != 0) {
							groups[count].push_back(Pair(number_of_minterms(4, (i + 2 + 4) % 4, (j - 0 + 4) % 4), number_of_minterms(4, (i + 3 + 4) % 4, (j - 0 + 4) % 4)));
							groups[count].push_back(Pair(number_of_minterms(4, (i + 2 + 4) % 4, (j - 1 + 4) % 4), number_of_minterms(4, (i + 3 + 4) % 4, (j - 1 + 4) % 4)));
							matrix[(i + 0 + 4) % 4][(j - 0 + 4) % 4] ++;
							matrix[(i + 1 + 4) % 4][(j - 0 + 4) % 4] ++;
							matrix[(i + 2 + 4) % 4][(j - 0 + 4) % 4] ++;
							matrix[(i + 3 + 4) % 4][(j - 0 + 4) % 4] ++;
							matrix[(i + 0 + 4) % 4][(j - 1 + 4) % 4] ++;
							matrix[(i + 1 + 4) % 4][(j - 1 + 4) % 4] ++;
							matrix[(i + 2 + 4) % 4][(j - 1 + 4) % 4] ++;
							matrix[(i + 3 + 4) % 4][(j - 1 + 4) % 4] ++;
							count++;
						}
						// no octants
						else {
							matrix[(i + 0 + 4) % 4][(j - 0 + 4) % 4] ++;
							matrix[(i + 1 + 4) % 4][(j - 0 + 4) % 4] ++;
							matrix[(i + 0 + 4) % 4][(j - 1 + 4) % 4] ++;
							matrix[(i + 1 + 4) % 4][(j - 1 + 4) % 4] ++;
							count++;
						}
					}

					// ( Down ) Find Bars
					else if (matrix[(i + 2 + 4) % 4][j] != 0 && matrix[(i + 3 + 4) % 4][j] != 0) {
						groups[count].push_back(Pair(number_of_minterms(4, (i + 2 + 4), j), number_of_minterms(4, (i + 3 + 4), j)));
						// ( Right ) Find Octants
						if (matrix[(i + 0 + 4) % 4][(j + 1 + 4) % 4] != 0 && matrix[(i + 1 + 4) % 4][(j + 1 + 4) % 4] != 0 && matrix[(i + 2 + 4) % 4][(j + 1 + 4) % 4] != 0 && matrix[(i + 3 + 4) % 4][(j + 1 + 4) % 4] != 0) {
							groups[count].push_back(Pair(number_of_minterms(4, (i + 0 + 4) % 4, (j + 1 + 4) % 4), number_of_minterms(4, (i + 1 + 4) % 4, (j + 1 + 4) % 4)));
							groups[count].push_back(Pair(number_of_minterms(4, (i + 2 + 4) % 4, (j + 1 + 4) % 4), number_of_minterms(4, (i + 3 + 4) % 4, (j + 1 + 4) % 4)));
							matrix[(i + 0 + 4) % 4][(j + 0 + 4) % 4] ++;
							matrix[(i + 1 + 4) % 4][(j + 0 + 4) % 4] ++;
							matrix[(i + 2 + 4) % 4][(j + 0 + 4) % 4] ++;
							matrix[(i + 3 + 4) % 4][(j + 0 + 4) % 4] ++;
							matrix[(i + 0 + 4) % 4][(j + 1 + 4) % 4] ++;
							matrix[(i + 1 + 4) % 4][(j + 1 + 4) % 4] ++;
							matrix[(i + 2 + 4) % 4][(j + 1 + 4) % 4] ++;
							matrix[(i + 3 + 4) % 4][(j + 1 + 4) % 4] ++;
							count++;
						}
						// ( Left ) Find Octants
						else if (matrix[(i + 0 + 4) % 4][(j - 1 + 4) % 4] != 0 && matrix[(i + 1 + 4) % 4][(j - 1 + 4) % 4] != 0 && matrix[(i + 2 + 4) % 4][(j - 1 + 4) % 4] != 0 && matrix[(i + 3 + 4) % 4][(j - 1 + 4) % 4 % 4] != 0) {
							groups[count].push_back(Pair(number_of_minterms(4, (i + 0 + 4) % 4, (j - 1 + 4) % 4), number_of_minterms(4, (i + 1 + 4) % 4, (j - 1 + 4) % 4)));
							groups[count].push_back(Pair(number_of_minterms(4, (i + 2 + 4) % 4, (j - 1 + 4) % 4), number_of_minterms(4, (i + 3 + 4) % 4, (j - 1 + 4) % 4)));
							matrix[(i + 0 + 4) % 4][(j - 0 + 4) % 4] ++;
							matrix[(i + 1 + 4) % 4][(j - 0 + 4) % 4] ++;
							matrix[(i + 2 + 4) % 4][(j - 0 + 4) % 4] ++;
							matrix[(i + 3 + 4) % 4][(j - 0 + 4) % 4] ++;
							matrix[(i + 0 + 4) % 4][(j - 1 + 4) % 4] ++;
							matrix[(i + 1 + 4) % 4][(j - 1 + 4) % 4] ++;
							matrix[(i + 2 + 4) % 4][(j - 1 + 4) % 4] ++;
							matrix[(i + 3 + 4) % 4][(j - 1 + 4) % 4] ++;
							count++;
						}
						// no octants
						else {
							matrix[(i + 0 + 4) % 4][(j - 0 + 4) % 4] ++;
							matrix[(i + 1 + 4) % 4][(j - 0 + 4) % 4] ++;
							matrix[(i + 2 + 4) % 4][(j - 0 + 4) % 4] ++;
							matrix[(i + 3 + 4) % 4][(j - 0 + 4) % 4] ++;
							count++;
						}
					}
					// no bars
					else {
						matrix[(i + 0 + 4) % 4][(j - 0 + 4) % 4] ++;
						matrix[(i + 1 + 4) % 4][(j - 0 + 4) % 4] ++;
						count++;
					}
				}
			}
		}

		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				if (matrix[i][j] == 1) {
					minterm.push_back(number_of_minterms(4, i, j));
					matrix[i][j] ++;
					count_min_is_Implicant++;
				}
			}
		}

		//Check if correct output
		/*
		for (int i = 0; i <= 4; i++) {
			for (int j = 0; j < 4; j++) {
				cout << matrix[i][j];
			}
			cout << endl;
		}
		*/

		/* Check if correct prime implicant with don't cares*/
		/*
		cout << endl << "There have " << count + count_min_is_Implicant << " prime implicants with don't cares." << endl;

		cout << endl << "Prime implicants with don't cares: " << endl;

		for (int i = 0; i < count_min_is_Implicant; i++) {
			cout << " " << minterm[i] << endl;
		}
		for (int i = 0; i < groups.size(); i++) {
			for (int j = 0; j < groups[i].size(); j++) {
				cout << " " << groups[i][j].x << " " << groups[i][j].y;
			}
			cout << endl;
		}
		*/
	}

	// return the final prime implicants that is minterm itself
	for (int i = 0; i < count_min_is_Implicant; i++) {
		groups_final.push_back(group_for_2D);
		groups_final[i].push_back(minterm[i]);
	}
	// return the final prime implicants that is grouped
	for (int i = count_min_is_Implicant; i < count_min_is_Implicant + groups.size(); i++) {
		groups_final.push_back(group_for_2D);
		for (int j = 0; j < groups[i - count_min_is_Implicant].size(); j++) {
			groups_final[i].push_back(groups[i - count_min_is_Implicant][j].x);
			groups_final[i].push_back(groups[i - count_min_is_Implicant][j].y);
		}
	}
	return groups_final;
}

// Get the final prime implicant without don't cares
vector<vector<int>> Simplifier::getPrimeImplicants(vector<vector<int>> &groups_final, vector<string> Initialiter_d, int count2) {

	// Determine which Prime implicant should be left
	int PrimeImplicantChart[20][16] = { 0 };
	int count_PrimeImplicantChart[20][16] = { 0 };

	// Store the Prime Implicants
	vector<vector<int>> PrimeImplicants;
	vector<int> groups_of_without_d;

	vector<int> group;

	// save the data of groups_of_essential
	int temp = 0;

	for (int i = 0; i < groups_final.size(); i++) {
		for (int j = 0; j < groups_final[i].size(); j++) {
			for (int count_minterms = 0; count_minterms < 16; count_minterms++) {
				if (groups_final[i][j] == count_minterms) {
					PrimeImplicantChart[i][count_minterms] ++;
					PrimeImplicantChart[19][count_minterms]++;
				}
			}
		}
	}

	// If it is don't care, then take off and don't compare with others
	for (int i = 0; i < count2; i++) {
		if (Initialiter_d[i] == "0") {
			for (int i = 0; i < 20; i++) {
				PrimeImplicantChart[i][0] = 0;
			}
		}
		if (Initialiter_d[i] == "1") {
			for (int i = 0; i < 20; i++) {
				PrimeImplicantChart[i][1] = 0;
			}
		}
		if (Initialiter_d[i] == "2") {
			for (int i = 0; i < 20; i++) {
				PrimeImplicantChart[i][2] = 0;
			}
		}
		if (Initialiter_d[i] == "3") {
			for (int i = 0; i < 20; i++) {
				PrimeImplicantChart[i][3] = 0;
			}
		}
		if (Initialiter_d[i] == "4") {
			for (int i = 0; i < 20; i++) {
				PrimeImplicantChart[i][4] = 0;
			}
		}
		if (Initialiter_d[i] == "5") {
			for (int i = 0; i < 20; i++) {
				PrimeImplicantChart[i][5] = 0;
			}
		}
		if (Initialiter_d[i] == "6") {
			for (int i = 0; i < 20; i++) {
				PrimeImplicantChart[i][6] = 0;
			}
		}
		if (Initialiter_d[i] == "7") {
			for (int i = 0; i < 20; i++) {
				PrimeImplicantChart[i][7] = 0;
			}
		}
		if (Initialiter_d[i] == "8") {
			for (int i = 0; i < 20; i++) {
				PrimeImplicantChart[i][8] = 0;
			}
		}
		if (Initialiter_d[i] == "9") {
			for (int i = 0; i < 20; i++) {
				PrimeImplicantChart[i][9] = 0;
			}
		}
		if (Initialiter_d[i] == "10") {
			for (int i = 0; i < 20; i++) {
				PrimeImplicantChart[i][10] = 0;
			}
		}
		if (Initialiter_d[i] == "11") {
			for (int i = 0; i < 20; i++) {
				PrimeImplicantChart[i][11] = 0;
			}
		}
		if (Initialiter_d[i] == "12") {
			for (int i = 0; i < 20; i++) {
				PrimeImplicantChart[i][12] = 0;
			}
		}
		if (Initialiter_d[i] == "13") {
			for (int i = 0; i < 20; i++) {
				PrimeImplicantChart[i][13] = 0;
			}
		}
		if (Initialiter_d[i] == "14") {
			for (int i = 0; i < 20; i++) {
				PrimeImplicantChart[i][14] = 0;
			}
		}
		if (Initialiter_d[i] == "15") {
			for (int i = 0; i < 20; i++) {
				PrimeImplicantChart[i][15] = 0;
			}
		}
	}

	/* Check the Prime Implicant Chart */
	/**
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 16; j++) {
			cout << setw(3) << PrimeImplicantChart[i][j];
		}
		cout << endl;
	}
	*/

	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 16; j++) {
			count_PrimeImplicantChart[i][j] = PrimeImplicantChart[i][j];
		}
	}

	// Accumulate number of each minterms
	int x;

	for (int i = 0; i < 19; i++) {
		for (int j = 0; j < 16; j++) {
			x = i - 1;
			if (i != 0 && count_PrimeImplicantChart[i][j] == 1) {
				while (x != -1) {
					count_PrimeImplicantChart[i][j] = count_PrimeImplicantChart[i][j] + PrimeImplicantChart[x][j];
					--x;
				}
			}
		}
	}

	/* Check the count_Prime Implicant Chart */
	/*
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 16; j++) {
			cout << setw(3) << count_PrimeImplicantChart[i][j];
		}
		cout << endl;
	}
	*/

	for (int i = 0; i < 19; i++) {
		for (int j = 0; j < 16; j++) {
			// Condition : remove the prime implicant circles don't cares and others that has been circled
			if (PrimeImplicantChart[i][j] == 1 && count_PrimeImplicantChart[i][j] == 1) {
				groups_of_without_d.push_back(i);
				break;
			}
		}
	}
	/* Check which group of prime implicants chart are prime implicants */
	/*
	for (int i = 0; i < groups_of_without_d.size(); i++) {
		cout << groups_of_without_d[i] << endl;
	}
	*/
	for (int x = 0; x < groups_of_without_d.size(); x++) {
		PrimeImplicants.push_back(group);
		// Groups in the prime implicant
		temp = groups_of_without_d[x];
		for (int j = 0; j < groups_final[temp].size(); j++) {
				PrimeImplicants[x].push_back(groups_final[temp][j]);
		}
	}

	/* Check if correct prime implicants without don't cares*/
	/*
	cout << endl << "There have " << PrimeImplicants.size() << " prime implicants." << endl;

	cout << endl << "Prime implicants: " << endl;

	for (int i = 0; i < PrimeImplicants.size(); i++) {
		for (int j = 0; j < PrimeImplicants[i].size(); j++) {
			cout << " " << PrimeImplicants[i][j];
		}
		cout << endl;
	}
	*/
	return PrimeImplicants;
}

// Get essential prime implicant
vector<vector<int>> Simplifier::getEssentialPrimeImplicants(vector<vector<int>> &PrimeImplicants, vector<string> Initialiter_d, int count2) {

	int PrimeImplicantChart[20][16] = { 0 };

	vector<vector<int>> EssentialPrimeImplicants;
	vector<int> group;
	vector<int> groups_of_essential;

	// save the data of groups_of_essential
	int temp = 0;

	for (int i = 0; i < PrimeImplicants.size(); i++) {
		for (int j = 0; j < PrimeImplicants[i].size(); j++) {
			for (int count_minterms = 0; count_minterms < 16; count_minterms++) {
				if (PrimeImplicants[i][j] == count_minterms) {
					PrimeImplicantChart[i][count_minterms] ++;
					PrimeImplicantChart[19][count_minterms]++;
				}
			}
		}
	}

	for (int i = 0; i < count2; i++) {
		if (Initialiter_d[i] == "0") {
			for (int i = 0; i < 20; i++) {
				PrimeImplicantChart[i][0] = 0;
			}
		}
		if (Initialiter_d[i] == "1") {
			for (int i = 0; i < 20; i++) {
				PrimeImplicantChart[i][1] = 0;
			}
		}
		if (Initialiter_d[i] == "2") {
			for (int i = 0; i < 20; i++) {
				PrimeImplicantChart[i][2] = 0;
			}
		}
		if (Initialiter_d[i] == "3") {
			for (int i = 0; i < 20; i++) {
				PrimeImplicantChart[i][3] = 0;
			}
		}
		if (Initialiter_d[i] == "4") {
			for (int i = 0; i < 20; i++) {
				PrimeImplicantChart[i][4] = 0;
			}
		}
		if (Initialiter_d[i] == "5") {
			for (int i = 0; i < 20; i++) {
				PrimeImplicantChart[i][5] = 0;
			}
		}
		if (Initialiter_d[i] == "6") {
			for (int i = 0; i < 20; i++) {
				PrimeImplicantChart[i][6] = 0;
			}
		}
		if (Initialiter_d[i] == "7") {
			for (int i = 0; i < 20; i++) {
				PrimeImplicantChart[i][7] = 0;
			}
		}
		if (Initialiter_d[i] == "8") {
			for (int i = 0; i < 20; i++) {
				PrimeImplicantChart[i][8] = 0;
			}
		}
		if (Initialiter_d[i] == "9") {
			for (int i = 0; i < 20; i++) {
				PrimeImplicantChart[i][9] = 0;
			}
		}
		if (Initialiter_d[i] == "10") {
			for (int i = 0; i < 20; i++) {
				PrimeImplicantChart[i][10] = 0;
			}
		}
		if (Initialiter_d[i] == "11") {
			for (int i = 0; i < 20; i++) {
				PrimeImplicantChart[i][11] = 0;
			}
		}
		if (Initialiter_d[i] == "12") {
			for (int i = 0; i < 20; i++) {
				PrimeImplicantChart[i][12] = 0;
			}
		}
		if (Initialiter_d[i] == "13") {
			for (int i = 0; i < 20; i++) {
				PrimeImplicantChart[i][13] = 0;
			}
		}
		if (Initialiter_d[i] == "14") {
			for (int i = 0; i < 20; i++) {
				PrimeImplicantChart[i][14] = 0;
			}
		}
		if (Initialiter_d[i] == "15") {
			for (int i = 0; i < 20; i++) {
				PrimeImplicantChart[i][15] = 0;
			}
		}
	}

	/* Check the Prime Implicant Chart */
	/*
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 16; j++) {
			cout << setw(3) << PrimeImplicantChart[i][j];
		}
		cout << endl;
	}
	*/


	for (int i = 0; i < 19; i++) {
		for (int j = 0; j < 16; j++) {
			if (PrimeImplicantChart[i][j] == 1 && PrimeImplicantChart[19][j] == 1) {
				groups_of_essential.push_back(i);
				break;
			}
		}
	}

	for (int x = 0; x < groups_of_essential.size(); x++) {
		EssentialPrimeImplicants.push_back(group);
		// Groups in the prime implicant
		temp = groups_of_essential[x];
		for (int j = 0; j < PrimeImplicants[temp].size(); j++) {
			EssentialPrimeImplicants[x].push_back(PrimeImplicants[temp][j]);
		}
	}

	return EssentialPrimeImplicants;
}

// Get Final Output
vector<vector<int>> Simplifier::getFinalOutput(vector<vector<int>> &prime_implicant, vector<vector<int>> &essential_prime_implicant) {
	int PrimeImplicantChart[20][17] = { 0 };

	vector<int> left_terms_count;
	vector<vector<int>> left_terms;

	vector<vector<int>> Final_Output;
	vector<int> group;

	// save the data of groups_of_essential
	int temp = 0;

	int count = 0;


	for (int i = 0; i < essential_prime_implicant.size(); i++) {
		for (int j = 0; j < essential_prime_implicant[i].size(); j++) {
			for (int count_minterms = 0; count_minterms < 16; count_minterms++) {
				if (essential_prime_implicant[i][j] == count_minterms) {
					PrimeImplicantChart[i][count_minterms] ++;
					PrimeImplicantChart[19][count_minterms]++;
				}
			}
		}
	}

	for (int i = essential_prime_implicant.size(); i < essential_prime_implicant.size() + prime_implicant.size(); i++) {
		for (int j = 0; j < prime_implicant[i - essential_prime_implicant.size()].size(); j++) {
			for (int count_minterms = 0; count_minterms < 16; count_minterms++) {
				if (prime_implicant[i - essential_prime_implicant.size()][j] == count_minterms) {
					PrimeImplicantChart[i][count_minterms] ++;
					PrimeImplicantChart[19][count_minterms]++;
				}
			}
		}
	}



	for (int i = 0; i < essential_prime_implicant.size(); i++) {
		for (int j = 0; j < 16; j++) {
			if (PrimeImplicantChart[i][j] == 1) {
				for (int k = 0; k < 20; k++) {
					PrimeImplicantChart[k][j] = 0;
				}
			}
		}
	}


	/* Accumulate the number of minterms of left Prime Implicant */
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 16; j++) {
			if (PrimeImplicantChart[i][j] == 1) {
				PrimeImplicantChart[i][16] ++;
			}
		}
	}


	// 選涵最多 Imp 的，並把該 P_Imp 所包含的項削掉

	for (int x = 8; x > 1; x--) {
		for (int i = 0; i < 20; i++) {
			if (PrimeImplicantChart[i][16] == x) {
				left_terms_count.push_back(i);
				for (int j = 0; j < 16; j++) {
					if (PrimeImplicantChart[i][j] == 1){
						for (int k = 0; k < 20; k++) {
							if (PrimeImplicantChart[k][j] == PrimeImplicantChart[i][j]) {
								PrimeImplicantChart[k][16] --;
							}
						}
					}
				}
			}
		}
	}

	for (int i = 0; i < left_terms_count.size(); i++) {
		left_terms.push_back(group);
		for (int j = 0; j < 16; j++) {
			if (PrimeImplicantChart[left_terms_count[i]][j] == 1) {
				left_terms[i].push_back(j);
			}
		}
	}

	/* Check if correct left terms */
	/*
	for (int i = 0; i < left_terms.size(); i++) {
		for (int j = 0; j < left_terms[i].size(); j++) {
			cout << left_terms[i][j];
		}
	}
	*/


	/* Check if correct PrimeImplicant Chart*/
	/*
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 17; j++) {
			cout << setw(3) << PrimeImplicantChart[i][j];
		}
		cout << endl;
	}
	*/
	return left_terms;
}

