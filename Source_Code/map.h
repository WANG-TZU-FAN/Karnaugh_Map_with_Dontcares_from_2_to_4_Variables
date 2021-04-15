#define _CRT_SECURE_NO_WARNINGS

// For Project
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <cstring>
// For Testing
#include <iomanip>


using namespace std;

class Map {
private:
	// Using same matrix in Map Class
	int matrix[4][4];
public:
	// Set the Kmap by question
	void setKmap(string number, int count1, vector<string> Initialiter_m, int count2, vector<string> Initialiter_d);
	// Help Simplifier to get the map
	void getMatrix(int m[4][4]);
	// Draw the map of the output
	void drawMap(string number, ofstream& outFile);
};

