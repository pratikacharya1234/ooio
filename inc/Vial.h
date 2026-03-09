#ifndef VIAL_H
#define VIAL_H

class Vial {
public:
	static const int MAX_CONTENTS = 4;

	Vial();
	Vial(char contents[], int size, int filled);
	Vial(char c1, char c2, char c3, char c4, int filled);

	bool add(char content);
	void display() const;
	bool isComplete() const;
	void setLabel(int label);
	bool transfer(Vial& destination);

	int getFilled() const;
	bool isEmpty() const;

private:
	char contents[MAX_CONTENTS];
	int filled;
	int label;
};

#endif
