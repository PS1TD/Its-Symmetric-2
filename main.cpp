#include <fstream>
#include <iostream>
#include <iterator>
#include <math.h>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

struct cell {
	int value;
	bool colored;
};

bool isHorizontallySymmetric(vector<vector<cell>> &grid) {
	for (size_t i = 0; i < ceil(grid.size() / 2.0); i++) {
		for (size_t j = 0; j < grid.size(); j++) {
			if (grid[i][j].colored != grid[grid.size() - i - 1][j].colored) {
				return false;
			}
		}
	}
	return true;
}

bool isVerticallySymmetric(vector<vector<cell>> &grid) {
	for (size_t i = 0; i < grid.size(); i++) {
		for (size_t j = 0; j < ceil(grid.size() / 2.0); j++) {
			if (grid[i][j].colored != grid[i][grid.size() - j - 1].colored) {
				return false;
			}
		}
	}
	return true;
}

bool isTLtoBRDiagonallySymmetric(vector<vector<cell>> &grid) {

	size_t j = 0;
	for (size_t i = 0; i < grid.size(); i++) {
		for (size_t k = j; k < grid.size(); k++) {
			if (grid[i][k].colored != grid[k][i].colored) {
				return false;
			}
		}
		j++;
	}
	return true;
}

bool isBLtoTRDiagonallySymmetric(vector<vector<cell>> &grid) {

	size_t j = grid.size() - 1;
	for (size_t i = 0; i < grid.size(); i++) {
		for (int k = j; k >= 0; k--) {
			if (grid[i][k].colored !=
				grid[grid.size() - 1 - k][grid.size() - 1 - i].colored) {
				return false;
			}
		}
		j--;
	}
	return true;
}

bool isRotationallySymmetric(vector<vector<cell>> &grid) {
	for (size_t i = 0; i < ceil(grid.size() / 2.0); i++) {
		for (size_t j = 0; j < ceil(grid.size() / 2.0); j++) {
			// 90
			// 0 0 -> 0 4
			// 0 1 -> 1 4
			// 0 2 -> 2 4
			// 1 0 -> 0 3
			// 1 1 -> 1 3
			// 1 2 -> 2 3
			// 2 0 -> 0 2
			// 2 1 -> 1 2
			// 2 2 -> 2 2
			if (grid[i][j].colored != grid[j][grid.size() - i - 1].colored) {
				return false;
			}

			// 180
			// 0 0 -> 4 4
			// 0 1 -> 4 3
			// 0 2 -> 4 2
			// 1 0 -> 3 4
			// 1 1 -> 3 3
			// 1 2 -> 3 2
			// 2 0 -> 2 4
			// 2 1 -> 2 3
			// 2 2 -> 2 2
			if (grid[i][j].colored !=
				grid[grid.size() - i - 1][grid.size() - j - 1].colored) {
				return false;
			}

			// 270
			// 0 0 -> 4 0
			// 0 1 -> 3 0
			// 0 2 -> 2 0
			// 1 0 -> 4 1
			// 1 1 -> 3 1
			// 1 2 -> 2 1
			// 2 0 -> 4 2
			// 2 1 -> 3 2
			// 2 2 -> 2 2
			if (grid[i][j].colored != grid[grid.size() - j - 1][i].colored) {
				return false;
			}
		}
	}
	return true;
}

bool isSymmetric(vector<vector<cell>> &grid) {
	bool h = isHorizontallySymmetric(grid);
	cout << "Horizontally Symmetric: " << h << endl;

	bool v = isVerticallySymmetric(grid);
	cout << "Vertically Symmetric: " << v << endl;

	bool tlbr = isTLtoBRDiagonallySymmetric(grid);
	cout << "Top Left to Bottom Right Symmetric: " << tlbr << endl;

	bool bltr = isBLtoTRDiagonallySymmetric(grid);
	cout << "Bottom Left to Top Right Symmetric: " << bltr << endl;

	bool r = isRotationallySymmetric(grid);
	cout << "Rotationally Symmetric: " << r << endl;

	bool a = h || v || tlbr || bltr || r;
	cout << "Any Symmetric: " << a << endl;

	return a;
}

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

		isSymmetric(grid);

		inputfile.close();
	} else {
		cout << "Error opening file!";
	}

	return 0;
}
