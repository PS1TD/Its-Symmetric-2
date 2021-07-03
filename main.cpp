#include <fstream>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

struct cell {
	int value;
	bool colored;
};

size_t getLargestCellSize(vector<vector<cell>> &grid) {
	size_t maxSize = 0;

	for (size_t i = 0; i < grid.size(); i++) {
		for (size_t j = 0; j < grid.size(); j++) {
			if (to_string(grid[i][j].value).length() > maxSize) {
				maxSize = to_string(grid[i][j].value).length();
			}
		}
	}

	return maxSize;
}

void printGrid(vector<vector<cell>> &grid) {
	const string RESET	 = "\033[0m";
	const string MAGENTA = "\033[35m";
	const string WHITE	 = "\033[37m";
	const string YELLOW	 = "\033[33m";

	const string HBORDER = "-";
	const string VBORDER = "|";

	size_t cellSize = getLargestCellSize(grid);

	cout << MAGENTA << HBORDER;
	for (size_t i = 0; i < grid[0].size(); i++) {
		cout << HBORDER;
		for (size_t j = 0; j < cellSize; j++) {
			cout << HBORDER;
		}
		cout << HBORDER << HBORDER;
	}
	cout << RESET << endl;

	for (size_t i = 0; i < grid.size(); i++) {
		cout << MAGENTA << VBORDER << RESET;
		for (size_t j = 0; j < grid.size(); j++) {
			cout << " ";

			if (to_string(grid[i][j].value).length() == cellSize) {

				if (grid[i][j].colored) {
					cout << YELLOW;
				} else {
					cout << WHITE;
				}

				cout << grid[i][j].value << RESET;
			} else {

				if (grid[i][j].colored) {
					cout << YELLOW;
				} else {
					cout << WHITE;
				}
				cout << grid[i][j].value << RESET;
				size_t sizeDiff =
					cellSize - to_string(grid[i][j].value).length();
				for (int k = 0; k < sizeDiff; k++) {
					cout << " ";
				}
			}
			cout << " " << MAGENTA << VBORDER;
		}
		cout << RESET << endl;

		cout << MAGENTA << HBORDER;
		for (size_t i = 0; i < grid[0].size(); i++) {
			cout << HBORDER;
			for (size_t j = 0; j < cellSize; j++) {
				cout << HBORDER;
			}
			cout << HBORDER << HBORDER;
		}
		cout << RESET << endl;
	}
}

int main() {

	vector<vector<cell>> grid;

	ifstream inputfile;

	inputfile.open("example.txt");
	if (inputfile.is_open()) {

		string line;

		while (getline(inputfile, line)) {

			istringstream lineStream(line);

			string element;

			vector<cell> lineVector;

			while (getline(lineStream, element, ' ')) {
				if (stoi(element) == 0) {
					struct cell c = {stoi(element), false};
					lineVector.push_back(c);
				} else if (stoi(element)) {
					struct cell c = {stoi(element), true};
					lineVector.push_back(c);
				} else {
					cout << "Cell is not a number!" << endl;
				}
			}

			grid.push_back(lineVector);
		}

		printGrid(grid);

		inputfile.close();
	} else {
		cout << "Error opening file!";
	}

	return 0;
}
