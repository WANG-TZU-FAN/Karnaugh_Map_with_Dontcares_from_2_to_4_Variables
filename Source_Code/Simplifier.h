#include "map.h"

/* Class of Simplifier to simplify the funtion */
class Simplifier
{
private:
	int matrix[4][4];
	Map* map;

public:
	// Constructor of the simplifier
	Simplifier(Map *map);
	// Group the map with don't cares
	vector<vector<int>> pushImplicants(vector<vector<int>> &groups_final, string number);
	// Get the final prime implicant without don't cares
	vector<vector<int>> getPrimeImplicants(vector<vector<int>> &groups_final, vector<string> Initialiter_d, int count2);
	// Get essential prime implicant
	vector<vector<int>> getEssentialPrimeImplicants(vector<vector<int>> &groups_final, vector<string> Initialiter_d, int count2);
	// Get Final Output
	vector<vector<int>> getFinalOutput(vector<vector<int>> &prime_implicant, vector<vector<int>> &essential_prime_implicant);
};
