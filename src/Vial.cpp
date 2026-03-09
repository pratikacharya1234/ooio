#include "Vial.h"

#include <iostream>

Vial::Vial() : filled(0), label(0) {
	for (int i = 0; i < MAX_CONTENTS; ++i) {
		contents[i] = ' ';
	}
}

Vial::Vial(char initialContents[], int size, int initialFilled) : filled(0), label(0) {
	for (int i = 0; i < MAX_CONTENTS; ++i) {
		contents[i] = ' ';
	}

	if (size > MAX_CONTENTS) {
		size = MAX_CONTENTS;
	}

	for (int i = 0; i < size; ++i) {
		contents[i] = initialContents[i];
	}

	if (initialFilled < 0) {
		initialFilled = 0;
	}
	if (initialFilled > MAX_CONTENTS) {
		initialFilled = MAX_CONTENTS;
	}
	filled = initialFilled;
}

Vial::Vial(char c1, char c2, char c3, char c4, int initialFilled) : filled(0), label(0) {
	contents[0] = c1;
	contents[1] = c2;
	contents[2] = c3;
	contents[3] = c4;

	if (initialFilled < 0) {
		initialFilled = 0;
	}
	if (initialFilled > MAX_CONTENTS) {
		initialFilled = MAX_CONTENTS;
	}
	filled = initialFilled;

	for (int i = filled; i < MAX_CONTENTS; ++i) {
		contents[i] = ' ';
	}
}

bool Vial::add(char content) {
	if (filled >= MAX_CONTENTS) {
		return false;
	}
	contents[filled] = content;
	filled++;
	return true;
}

void Vial::display() const {
	std::cout << "Vial " << label << "\n";
	std::cout << "+---+\n";
	for (int i = MAX_CONTENTS - 1; i >= 0; --i) {
		std::cout << "| " << contents[i] << " |\n";
	}
	std::cout << "+---+\n";
}

bool Vial::isComplete() const {
	if (filled != MAX_CONTENTS) {
		return false;
	}
	for (int i = 1; i < MAX_CONTENTS; ++i) {
		if (contents[i] != contents[0]) {
			return false;
		}
	}
	return true;
}

void Vial::setLabel(int newLabel) { label = newLabel; }

bool Vial::transfer(Vial& destination) {
	if (filled == 0) {
		std::cout << "Source vial is empty.\n";
		return false;
	}

	if (destination.filled >= MAX_CONTENTS) {
		std::cout << "Destination vial is full.\n";
		return false;
	}

	const char sourceTop = contents[filled - 1];
	if (destination.filled > 0) {
		const char destinationTop = destination.contents[destination.filled - 1];
		if (sourceTop != destinationTop) {
			std::cout << "Contents do not match.\n";
			return false;
		}
	}

	destination.contents[destination.filled] = sourceTop;
	destination.filled++;

	contents[filled - 1] = ' ';
	filled--;

	return true;
}

int Vial::getFilled() const { return filled; }

bool Vial::isEmpty() const { return filled == 0; }
