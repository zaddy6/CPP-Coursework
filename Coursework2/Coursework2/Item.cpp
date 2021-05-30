#pragma once
#include <iostream>
#include <fstream>
#include <random>
#include <string>
#include <ctime>
#include "Item.h"
#include "Date.h"

using namespace std;

Item::Item() {

	random_device rd;
	default_random_engine generator(rd());

	uniform_int_distribution<int> dRandom(0, 25);
	Group = 'A' + dRandom(generator);

	uniform_int_distribution<int> dsubRandom(0, 87);
	Subgroup = dsubRandom(generator);

	vector<string> lines;
	string line;
	ifstream file("Birds.txt");
	while (getline(file, line)) {
		if (!line.empty())
			lines.push_back(line);
	}
	int randnum = rand() % (int)lines.size() - 1;
	uniform_int_distribution<int> newNm(randnum, (int)lines.size() - 1);
	Name = lines[newNm(generator)];
	file.close();

	Timestamp = Date::CreateRandomDate(Date(6, 6, 2001), Date(6, 6, 2021));
}

Item::Item(char group, int subgroup, string name, Date timestamp) {
	Group = group;
	Subgroup = subgroup;
	Name = name;
	Timestamp = timestamp;
}

Item::Item(const Item& original) {
	Group = original.Group;
	Subgroup = original.Subgroup;
	Name = original.Name;
	Timestamp = original.Timestamp;
}

Item::~Item() {}

char Item::getGroup() {
	return Group;
}

int Item::getSubgroup() {
	return Subgroup;
}

string Item::getName() {
	return Name;
}

Date Item::getTimestamp() {
	return Timestamp;
}
