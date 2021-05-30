#pragma once
#include <iostream>
#include <string.h>
#include "Date.h"

using namespace std;

class Item {
private:
	char Group;
	int Subgroup;
	string Name;
	Date Timestamp;
public:
	Item();
	Item(char, int, string, Date);
	Item(const Item&);
	~Item();

	char getGroup();
	int getSubgroup();
	string getName();
	Date getTimestamp();
};

