#include "Simplifier.h"

/* Split the string */
vector<string> split(const string& strs, const string& delim) {
	// Store the Data in that line
	vector<string> res;
	if (strs == "") return res;
	char* str = new char[strs.size() + 1];
	strcpy(str, strs.c_str());
	char* d = new char[delim.size() + 1];
	strcpy(d, delim.c_str());
	char* p = strtok(str, d);
	while (p) {
		string temp = p;
		res.push_back(temp);
		p = strtok(NULL, d);
	}
	delete[]str;
	delete[]d;
	return res;
}

/* Count string members number */
int count_members(vector<string>& res) {
	int count = 0;
	for (auto it : res) {
		count++;
	}
	return count;
}

/* Transform the number term into character term */
/* Parameters : 1. how many variables  2. Implicants in numerical terms  3. Output file for data write in */
vector<vector<string>> Transformer(string number, vector<vector<int>> &PrimeImplicants, ofstream& outFile) {
	
	/* store the returning data */
	vector<vector<string>> PrimeImplicants_to_characters;
	/* For 2D vector */
	vector<string> group;

	/* Initialize the count of A, B, C, D */
	int count_A = 0;
	int count_B = 0;
	int count_C = 0;
	int count_D = 0;

	// Transformer for 2 variables
	if (number == "2") {
		for (int i = 0; i < PrimeImplicants.size(); i++) {
			PrimeImplicants_to_characters.push_back(group);
			// Initialize counters
			count_A = 0;
			count_B = 0;
			// Plus corresponding Caracters
			for (int j = 0; j < PrimeImplicants[i].size(); j++) {
				if (PrimeImplicants[i][j] == 0) {

				}
				if (PrimeImplicants[i][j] == 1) {
					count_B++;
				}
				if (PrimeImplicants[i][j] == 2) {
					count_A++;
				}
				if (PrimeImplicants[i][j] == 3) {
					count_A++;
					count_B++;
				}
				
			}
			// If all prime implicants have 0 on that term, then store negative value
			// If all prime implicants have 1 on that term, then store positive value
			// If tthe count is neither 0 nor the number of minterms in that prime implicant, the sum of that term is from 1 to [ number of minterms - 1 ]
			if (count_A == 0) {
				PrimeImplicants_to_characters[i].push_back("a'");
			}
			
			else if (count_A == PrimeImplicants[i].size()) {
				PrimeImplicants_to_characters[i].push_back("a");
			}
			if (count_B == 0) {
				PrimeImplicants_to_characters[i].push_back("b'");
			}
			else if (count_B == PrimeImplicants[i].size()) {
				PrimeImplicants_to_characters[i].push_back("b");
			}
		}
	}

	// Transformer for 3 variables
	if (number == "3") {
		for (int i = 0; i < PrimeImplicants.size(); i++) {
			PrimeImplicants_to_characters.push_back(group);
			// Initialize counters
			count_A = 0;
			count_B = 0;
			count_C = 0;
			// Plus corresponding Caracters
			for (int j = 0; j < PrimeImplicants[i].size(); j++) {
				if (PrimeImplicants[i][j] == 0) {

				}
				if (PrimeImplicants[i][j] == 1) {
					count_C++;
				}
				if (PrimeImplicants[i][j] == 2) {
					count_B++;
				}
				if (PrimeImplicants[i][j] == 3) {
					count_B++;
					count_C++;
				}
				if (PrimeImplicants[i][j] == 4) {
					count_A++;
				}
				if (PrimeImplicants[i][j] == 5) {
					count_A++;
					count_C++;
				}
				if (PrimeImplicants[i][j] == 6) {
					count_A++;
					count_B++;
				}
				if (PrimeImplicants[i][j] == 7) {
					count_A++;
					count_B++;
					count_C++;
				}
			}
			// If all prime implicants have 0 on that term, then store negative value
			// If all prime implicants have 1 on that term, then store positive value
			// If tthe count is neither 0 nor the number of minterms in that prime implicant, the sum of that term is from 1 to [ number of minterms - 1 ]
			if (count_A == 0) {
				PrimeImplicants_to_characters[i].push_back("a'");
			}
			else if (count_A == PrimeImplicants[i].size()) {
				PrimeImplicants_to_characters[i].push_back("a");
			}
			if (count_B == 0) {
				PrimeImplicants_to_characters[i].push_back("b'");
			}
			else if (count_B == PrimeImplicants[i].size()) {
				PrimeImplicants_to_characters[i].push_back("b");
			}
			if (count_C == 0) {
				PrimeImplicants_to_characters[i].push_back("c'");
			}
			else if (count_C == PrimeImplicants[i].size()) {
				PrimeImplicants_to_characters[i].push_back("c");
			}
		}
	}

	// Transformer for 4 variables
	if (number == "4") {
		for (int i = 0; i < PrimeImplicants.size(); i++) {
			PrimeImplicants_to_characters.push_back(group);
			// Initialize counters
			count_A = 0;
			count_B = 0;
			count_C = 0;
			count_D = 0;
			// Plus corresponding Caracters
			for (int j = 0; j < PrimeImplicants[i].size(); j++) {
				if (PrimeImplicants[i][j] == 0) {

				}
				if (PrimeImplicants[i][j] == 1) {
					count_D ++;
				}
				if (PrimeImplicants[i][j] == 2) {
					count_C++;
				}
				if (PrimeImplicants[i][j] == 3) {
					count_C++;
					count_D++;
				}
				if (PrimeImplicants[i][j] == 4) {
					count_B++;
				}
				if (PrimeImplicants[i][j] == 5) {
					count_B++;
					count_D++;
				}
				if (PrimeImplicants[i][j] == 6) {
					count_B++;
					count_C++;
				}
				if (PrimeImplicants[i][j] == 7) {
					count_B++;
					count_C++;
					count_D++;
				}
				if (PrimeImplicants[i][j] == 8) {
					count_A++;
				}
				if (PrimeImplicants[i][j] == 9) {
					count_A++;
					count_D++;
				}
				if (PrimeImplicants[i][j] == 10) {
					count_A++;
					count_C++;
				}
				if (PrimeImplicants[i][j] == 11) {
					count_A++;
					count_C++;
					count_D++;
				}
				if (PrimeImplicants[i][j] == 12) {
					count_A++;
					count_B++;
				}
				if (PrimeImplicants[i][j] == 13) {
					count_A++;
					count_B++;
					count_D++;
				}
				if (PrimeImplicants[i][j] == 14) {
					count_A++;
					count_B++;
					count_C++;
				}
				if (PrimeImplicants[i][j] == 15) {
					count_A++;
					count_B++;
					count_C++;
					count_D++;
				}
			}
			// If all prime implicants have 0 on that term, then store negative value
			// If all prime implicants have 1 on that term, then store positive value
			// If tthe count is neither 0 nor the number of minterms in that prime implicant, the sum of that term is from 1 to [ number of minterms - 1 ]
			if (count_A == 0) {
				PrimeImplicants_to_characters[i].push_back("a'");
			}
			// All A is 1
			else if (count_A == PrimeImplicants[i].size()) {
				PrimeImplicants_to_characters[i].push_back("a");
			}
			if (count_B == 0) {
				PrimeImplicants_to_characters[i].push_back("b'");
			}
			else if (count_B == PrimeImplicants[i].size()) {
				PrimeImplicants_to_characters[i].push_back("b");
			}
			if (count_C == 0) {
				PrimeImplicants_to_characters[i].push_back("c'");
			}
			else if (count_C == PrimeImplicants[i].size()) {
				PrimeImplicants_to_characters[i].push_back("c");
			}
			if (count_D == 0) {
				PrimeImplicants_to_characters[i].push_back("d'");
			}
			else if (count_D == PrimeImplicants[i].size()) {
				PrimeImplicants_to_characters[i].push_back("d");
			}
		}
	}
	
	/* output characters */
	for (int i = 0; i < PrimeImplicants_to_characters.size(); i++) {
		for (int j = 0; j < PrimeImplicants_to_characters[i].size(); j++) {
			cout << PrimeImplicants_to_characters[i][j];
			outFile << PrimeImplicants_to_characters[i][j];
		}
		// Final don't have to output comma
		if (i != PrimeImplicants_to_characters.size() - 1) {
			cout << " , ";
			outFile << " , ";
		}
	}
	return PrimeImplicants_to_characters;
}

/* Transform the final output into chacter terms*/
/* Parameters : 1. how many variables  2. Essential prime implicants in numerical terms  3. Left terms to fullfil the question  4. Output file for data write in */
vector<vector<string>> Transformer_to_Final(string number, vector<vector<int>> &EssentialPrimeImplicants, vector<vector<int>> &LeftTerms, ofstream& outFile) {
	
	/* store the returning data */
	vector<vector<string>> PrimeImplicants_to_characters;
	/* For 2D vector */
	vector<string> group;

	/* Store the data of Essential Prime Implicants and Left Terms */
	vector<vector<int>> PrimeImplicants;
	vector<int> group_for_final;
	for (int i = 0; i < EssentialPrimeImplicants.size(); i++) {
		PrimeImplicants.push_back(group_for_final);
		for(int j = 0; j < EssentialPrimeImplicants[i].size(); j++){
			PrimeImplicants[i].push_back(EssentialPrimeImplicants[i][j]);
		}
	}
	for (int i = EssentialPrimeImplicants.size(); i < LeftTerms.size() + EssentialPrimeImplicants.size(); i++) {
		PrimeImplicants.push_back(group_for_final);
		for (int j = 0; j < LeftTerms[i- EssentialPrimeImplicants.size()].size(); j++) {
			PrimeImplicants[i].push_back(LeftTerms[i - EssentialPrimeImplicants.size()][j]);
		}
	}

	/* Initialize the count of A, B, C, D */
	int count_A = 0;
	int count_B = 0;
	int count_C = 0;
	int count_D = 0;

	// Transformer for 2 variables
	if (number == "2") {
		for (int i = 0; i < PrimeImplicants.size(); i++) {
			PrimeImplicants_to_characters.push_back(group);
			// Initialize counters
			count_C = 0;
			count_D = 0;
			for (int j = 0; j < PrimeImplicants[i].size(); j++) {
				if (PrimeImplicants[i][j] == 0) {

				}
				if (PrimeImplicants[i][j] == 1) {
					count_D++;
				}
				if (PrimeImplicants[i][j] == 2) {
					count_C++;
				}
				if (PrimeImplicants[i][j] == 3) {
					count_C++;
					count_D++;
				}

			}
			if (count_C == 0) {
				PrimeImplicants_to_characters[i].push_back("a'");
			}
			else if (count_C == PrimeImplicants[i].size()) {
				PrimeImplicants_to_characters[i].push_back("a");
			}
			if (count_D == 0) {
				PrimeImplicants_to_characters[i].push_back("b'");
			}
			else if (count_D == PrimeImplicants[i].size()) {
				PrimeImplicants_to_characters[i].push_back("b");
			}
		}
	}

	// Transformer for 3 variables
	if (number == "3") {
		for (int i = 0; i < PrimeImplicants.size(); i++) {
			PrimeImplicants_to_characters.push_back(group);
			// Initialize counters
			count_A = 0;
			count_B = 0;
			count_C = 0;
			count_D = 0;
			for (int j = 0; j < PrimeImplicants[i].size(); j++) {
				if (PrimeImplicants[i][j] == 0) {

				}
				if (PrimeImplicants[i][j] == 1) {
					count_D++;
				}
				if (PrimeImplicants[i][j] == 2) {
					count_C++;
				}
				if (PrimeImplicants[i][j] == 3) {
					count_C++;
					count_D++;
				}
				if (PrimeImplicants[i][j] == 4) {
					count_B++;
				}
				if (PrimeImplicants[i][j] == 5) {
					count_B++;
					count_D++;
				}
				if (PrimeImplicants[i][j] == 6) {
					count_B++;
					count_C++;
				}
				if (PrimeImplicants[i][j] == 7) {
					count_B++;
					count_C++;
					count_D++;
				}
			}
			if (count_B == 0) {
				PrimeImplicants_to_characters[i].push_back("a'");
			}
			else if (count_B == PrimeImplicants[i].size()) {
				PrimeImplicants_to_characters[i].push_back("a");
			}
			if (count_C == 0) {
				PrimeImplicants_to_characters[i].push_back("b'");
			}
			else if (count_C == PrimeImplicants[i].size()) {
				PrimeImplicants_to_characters[i].push_back("b");
			}
			if (count_D == 0) {
				PrimeImplicants_to_characters[i].push_back("c'");
			}
			else if (count_D == PrimeImplicants[i].size()) {
				PrimeImplicants_to_characters[i].push_back("c");
			}
		}
	}

	// Transformer for 4 variables
	if (number == "4") {
		for (int i = 0; i < PrimeImplicants.size(); i++) {
			PrimeImplicants_to_characters.push_back(group);
			// Initialize counters
			count_A = 0;
			count_B = 0;
			count_C = 0;
			count_D = 0;
			for (int j = 0; j < PrimeImplicants[i].size(); j++) {
				if (PrimeImplicants[i][j] == 0) {

				}
				if (PrimeImplicants[i][j] == 1) {
					count_D++;
				}
				if (PrimeImplicants[i][j] == 2) {
					count_C++;
				}
				if (PrimeImplicants[i][j] == 3) {
					count_C++;
					count_D++;
				}
				if (PrimeImplicants[i][j] == 4) {
					count_B++;
				}
				if (PrimeImplicants[i][j] == 5) {
					count_B++;
					count_D++;
				}
				if (PrimeImplicants[i][j] == 6) {
					count_B++;
					count_C++;
				}
				if (PrimeImplicants[i][j] == 7) {
					count_B++;
					count_C++;
					count_D++;
				}
				if (PrimeImplicants[i][j] == 8) {
					count_A++;
				}
				if (PrimeImplicants[i][j] == 9) {
					count_A++;
					count_D++;
				}
				if (PrimeImplicants[i][j] == 10) {
					count_A++;
					count_C++;
				}
				if (PrimeImplicants[i][j] == 11) {
					count_A++;
					count_C++;
					count_D++;
				}
				if (PrimeImplicants[i][j] == 12) {
					count_A++;
					count_B++;
				}
				if (PrimeImplicants[i][j] == 13) {
					count_A++;
					count_B++;
					count_D++;
				}
				if (PrimeImplicants[i][j] == 14) {
					count_A++;
					count_B++;
					count_C++;
				}
				if (PrimeImplicants[i][j] == 15) {
					count_A++;
					count_B++;
					count_C++;
					count_D++;
				}
			}
			if (count_A == 0) {
				PrimeImplicants_to_characters[i].push_back("a'");
			}
			// All A is 1
			else if (count_A == PrimeImplicants[i].size()) {
				PrimeImplicants_to_characters[i].push_back("a");
			}
			if (count_B == 0) {
				PrimeImplicants_to_characters[i].push_back("b'");
			}
			else if (count_B == PrimeImplicants[i].size()) {
				PrimeImplicants_to_characters[i].push_back("b");
			}
			if (count_C == 0) {
				PrimeImplicants_to_characters[i].push_back("c'");
			}
			else if (count_C == PrimeImplicants[i].size()) {
				PrimeImplicants_to_characters[i].push_back("c");
			}
			if (count_D == 0) {
				PrimeImplicants_to_characters[i].push_back("d'");
			}
			else if (count_D == PrimeImplicants[i].size()) {
				PrimeImplicants_to_characters[i].push_back("d");
			}
		}
	}

	/* output PrimeImplicants */
	for (int i = 0; i < PrimeImplicants_to_characters.size(); i++) {
		for (int j = 0; j < PrimeImplicants_to_characters[i].size(); j++) {
			cout << PrimeImplicants_to_characters[i][j];
			outFile << PrimeImplicants_to_characters[i][j];
		}
		// Final don't have to output comma
		if (i != PrimeImplicants_to_characters.size() - 1) {
			cout << " + ";
			outFile << " + ";
		}
	}

	return PrimeImplicants_to_characters;
}

// Main Function
int main() {

	// Set The Map
	Map map;

	// Input The Map and Simplify it
	Simplifier simplifier(&map);

	// Save Prime Implicants With Don't Cares
	vector<vector<int>> groups_final;

	// Save Prime Implicants, Essential Prime Implicants, Left Terms
	vector<vector<int>> prime_implicant;
	vector<vector<int>> essential_prime_implicant;
	vector<vector<int>> left_terms;

	// Save The Output
	vector<vector<string>> final_prime_implicant;
	vector<vector<string>> final_essential_prime_implicant;
	vector<vector<string>> final_output;

	// Determine the Input is v ,m or d
	string vmd;

	// Save the data of v, m or d
	string vstr, mstr, dstr, D_str;

	// Let the user to key in number for different input file
	int file_number = 0;
	string filename;
	string filename_out;

	cout << "1) your own question ( Key in filein.txt for example )" << endl;
	cout << "2) 2 variable test" << endl;
	cout << "3) 3 variable test" << endl;
	cout << "4) 4 variable test" << endl << endl;
	
	cout << "Which one do you want to execute : ";
	
	cin >> file_number;
	
	if(file_number == 1){
		cout << "Please enter your own file name " << endl;
		cin >> filename;
		filename_out = "Your_Kmap.txt";
	}
	if(file_number == 2){
		filename = "2_variable_test.txt";
		filename_out = "2_variable_Kmap.txt";
	}
	if(file_number == 3){
		filename = "3_variable_test.txt";
		filename_out = "3_variable_Kmap.txt";
	}
	if(file_number == 4){
		filename = "4_variable_test.txt";
		filename_out = "4_variable_Kmap.txt";
	}
	
	
	// Read the File
	ifstream myfile(filename, ios::in);
	if (!myfile) {
		cerr << "Failed Opening" << endl;
		exit(1);
	}

	// Write the File
	ofstream outFile(filename_out, ios::out);
	if (!outFile) { 
		cerr << "Failed opening" << endl; 
		exit(1); 
	}

	/* Arranging Inputs */
	while (myfile >> vmd >> D_str) {
		if (vmd == "-v") {
			vstr = D_str;
		}
		else if (vmd == "-m") {
			mstr = D_str;
		}
		else if (vmd == "-d") {
			dstr = D_str;
		}
		else {
			cout << "Sorry that we cannot find those characters" << endl;
			outFile << "Sorry that we cannot find those characters" << endl;
		}
	}

	vector<string> reg_m = split(mstr, ",");
	int count1 = count_members(reg_m);

	vector<string> reg_d = split(dstr, ",");
	int count2 = count_members(reg_d);

	cout << endl;
	outFile << endl;

	// Generate the Karnaugh's Map
	map.setKmap(vstr, count1, reg_m, count2, reg_d);

	// Draw the map on screen
	map.drawMap(vstr, outFile);

	groups_final = simplifier.pushImplicants(groups_final, vstr);

	prime_implicant = simplifier.getPrimeImplicants(groups_final, reg_d, count2);

	essential_prime_implicant = simplifier.getEssentialPrimeImplicants(groups_final, reg_d, count2);

	left_terms = simplifier.getFinalOutput(prime_implicant, essential_prime_implicant);

	cout << endl << endl << "Prime implicants: ";
	outFile << endl << endl << "Prime implicants: ";

	final_prime_implicant = Transformer(vstr, prime_implicant, outFile);
	
	cout << endl << endl << "Essential Prime implicants: ";
	outFile << endl << endl << "Essential Prime implicants: ";

	final_essential_prime_implicant = Transformer(vstr, essential_prime_implicant, outFile);

	if (vstr == "2") {
		cout << endl << endl << "F (A, B) = ";
		outFile << endl << endl << "F (A, B) = ";
	}
	if (vstr == "3") {
		cout << endl << endl << "F (A, B, C) = ";
		outFile << endl << endl << "F (A, B, C) = ";
	}
	if (vstr == "4") {
		cout << endl << endl << "F (A, B, C, D) = ";
		outFile << endl << endl << "F (A, B, C, D) = ";
	}

	final_output = Transformer_to_Final(vstr, essential_prime_implicant, left_terms, outFile);

	cout << endl << endl;
	
	myfile.close();
	outFile.close();
	
	return 0;
}
