#include "Vial.h"

#include <algorithm>
#include <iostream>
#include <random>
#include <vector>

static void displayAllVials(const std::vector<Vial>& vials) {
	std::cout << "\n================================\n";
	for (const Vial& vial : vials) {
		vial.display();
	}
	std::cout << "================================\n";
}

static bool puzzleSolved(const std::vector<Vial>& vials) {
	for (const auto& vial : vials) {
		if (vial.getFilled() == 0) {
			continue;
		}
		if (!vial.isComplete()) {
			return false;
		}
	}
	return true;
}

int main() {
	const int colorCount = 4;
	const int extraEmptyVials = 2;
	const char colors[colorCount] = {'a', 'b', 'c', 'd'};
	const int totalVials = colorCount + extraEmptyVials;

	std::vector<Vial> vials(totalVials);
	for (int i = 0; i < totalVials; ++i) {
		vials[i].setLabel(i + 1);
	}

	std::vector<char> bag;
	for (int i = 0; i < colorCount; ++i) {
		for (int j = 0; j < Vial::MAX_CONTENTS; ++j) {
			bag.push_back(colors[i]);
		}
	}

	std::random_device rd;
	std::mt19937 gen(rd());
	std::shuffle(bag.begin(), bag.end(), gen);

	int bagIndex = 0;
	for (int vialIndex = 0; vialIndex < colorCount; ++vialIndex) {
		for (int slot = 0; slot < Vial::MAX_CONTENTS; ++slot) {
			vials[vialIndex].add(bag[bagIndex]);
			bagIndex++;
		}
	}

	std::cout << "Simple Sort Puzzle\n";
	std::cout << "Goal: each non-empty vial should contain a single repeated character.\n";
	std::cout << "Pick source and destination labels (enter 0 to quit).\n";

	while (true) {
		displayAllVials(vials);

		if (puzzleSolved(vials)) {
			std::cout << "\nPuzzle solved. Nice work!\n";
			break;
		}

		int source = 0;
		int destination = 0;

		std::cout << "\nSource vial label: ";
		std::cin >> source;

		if (!std::cin) {
			std::cout << "Invalid input. Exiting.\n";
			break;
		}

		if (source == 0) {
			std::cout << "Goodbye.\n";
			break;
		}

		std::cout << "Destination vial label: ";
		std::cin >> destination;

		if (!std::cin) {
			std::cout << "Invalid input. Exiting.\n";
			break;
		}

		if (source < 1 || source > totalVials || destination < 1 || destination > totalVials) {
			std::cout << "Invalid vial numbers. Try again.\n";
			continue;
		}

		if (source == destination) {
			std::cout << "Source and destination cannot be the same.\n";
			continue;
		}

		const bool moved = vials[source - 1].transfer(vials[destination - 1]);
		if (moved) {
			std::cout << "Transfer successful.\n";
		}
	}

	return 0;
}
