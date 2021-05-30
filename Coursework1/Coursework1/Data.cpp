#pragma once
#include <iostream>
#include <string>
#include "Data.h"

Data::Data(int n) {
	n = n - 1;
	do {
		Item* usedVar = new Item();
		char indxv = usedVar->getGroup();
		char factorVarinit = usedVar->getSubgroup();

		if (DataStructure.count(indxv) > 0) {
			if ((*DataStructure[indxv]).count(factorVarinit) > 0) {
				(*DataStructure[indxv])[factorVarinit]->push_back(usedVar);
			}
			else {
				auto listt = new list< Item*>{ usedVar };
				(*DataStructure[indxv])[factorVarinit] = listt;
			}
		}
		else {
			auto listt = new list<Item*>{ usedVar };
			auto mapp = new map<int, list<Item*>*>{ {factorVarinit, listt} };
			DataStructure[indxv] = mapp;
		}
	} while (n--);
}

Data::Data() {
	DataStructure = map<char, map<int, list<Item*>*>*>{};
}

Data::~Data() {
	if (DataStructure.empty()) return;
	for (auto indxv : DataStructure) {
		for (auto factorVarinit : *indxv.second) {
			for (auto item : *factorVarinit.second)
				delete item;
			delete factorVarinit.second;
		}
		delete indxv.second;
	}
}

void Data::PrintAll() {
	for (const auto& indxv : DataStructure) {
		cout << indxv.first << ":\n";
		for (const auto& factorVarinit : *indxv.second) {
			if (factorVarinit.second->size() > 1) {
				factorVarinit.second->sort([](Item* i1, Item* i2) {
					for (int n = 0;; n++) {
						if (i1->getName()[n] < i2->getName()[n]) return true;
						else if (i1->getName()[n] == i2->getName()[n]) continue;
						else return false;
					}
					});
			}
			for (const auto& l : *factorVarinit.second)
				cout << factorVarinit.first << ": " << l->getName() << " " << l->getTimestamp().ToString() << endl;
		}
		cout << endl;
	}
}

int Data::CountItems() {
	int n = 0;
	for (const auto& indxv : DataStructure)
		for (const auto& factorVarinit : *indxv.second)
			for (const auto& listt : *factorVarinit.second)
				n++;
	return n;
}

map<int, list<Item*>*>* Data::GetGroup(char c) {
	if (DataStructure.count(c) == 0) return nullptr;
	return DataStructure[c];
}

void Data::PrintGroup(char c) {
	try {
		if (DataStructure.count(c) == 0) throw invalid_argument("Group does not exist");
		for (const auto& factorVarinit : *DataStructure[c]) {
			if (factorVarinit.second->size() > 1) {
				factorVarinit.second->sort([](Item* i1, Item* i2) {
					for (int n = 0;; n++) {
						if (i1->getName()[n] < i2->getName()[n]) return true;
						else if (i1->getName()[n] == i2->getName()[n]) continue;
						else return false;
					}
					});
			}
			for (const auto& l : *factorVarinit.second)
				cout << factorVarinit.first << ": " << l->getName() << " " << l->getTimestamp().ToString() << endl;
		}
		cout << endl;
	}
	catch (const invalid_argument& e) {
		cout << e.what() << endl;
	}
}

int Data::CountGroupItems(char c) {
	if (DataStructure.count(c) == 0) return 0;
	int n = 0;
	for (const auto& factorVarinit : *DataStructure[c])
		for (const auto& listt : *factorVarinit.second)
			n++;
	return n;
}

list<Item*>* Data::GetSubgroup(char c, int i) {
	if (DataStructure.count(c) == 0 || (*DataStructure[c]).count(i) == 0) return nullptr;
	return (*DataStructure[c])[i];
}

void Data::PrintSubgroupByNames(char c, int i) {
	try {
		if (DataStructure.count(c) == 0) throw invalid_argument("Group does not exist");
		if ((*DataStructure[c]).count(i) == 0) throw invalid_argument("Subgroup does not exist");
		if ((*DataStructure[c])[i]->size() > 1) {
			(*DataStructure[c])[i]->sort([](Item* i1, Item* i2) {
				for (int n = 0;; n++) {
					if (i1->getName()[n] < i2->getName()[n]) return true;
					else if (i1->getName()[n] == i2->getName()[n]) continue;
					else return false;
				}
				});
		}
		for (const auto& listt : *(*DataStructure[c])[i])
			cout << listt->getName() << " " << listt->getTimestamp().ToString() << endl;
	}
	catch (const invalid_argument& e) {
		cout << e.what() << endl;
	}
}

void Data::PrintSubgroupByDates(char c, int i) {
	try {
		if (DataStructure.count(c) == 0) throw invalid_argument("Group does not exist");
		if ((*DataStructure[c]).count(i) == 0) throw invalid_argument("Subgroup does not exist");
		if ((*DataStructure[c])[i]->size() > 1) {
			(*DataStructure[c])[i]->sort([](Item* i1, Item* i2) {
				return i1->getTimestamp().operator<(i2->getTimestamp());
				});
		}
		for (const auto& listt : *(*DataStructure[c])[i])
			cout << listt->getName() << " " << listt->getTimestamp().ToString() << endl;
	}
	catch (const invalid_argument& e) {
		cout << e.what() << endl;
	}
}

int Data::CountSubgroupItems(char c, int i) {
	if (DataStructure.count(c) == 0 || (*DataStructure[c]).count(i) == 0) return 0;
	int n = 0;
	for (const auto& listt : *(*DataStructure[c])[i])
		n++;
	return n;
}

Item* Data::GetItem(char c, int i, string s) {
	if (DataStructure.count(c) == 0 || (*DataStructure[c]).count(i) == 0) return nullptr;
	for (Item* item : *(*DataStructure[c])[i]) {
		if (!item->getName().compare(s)) return item;
	}
	return nullptr;
}

void Data::PrintItem(char c, int i, string s) {
	try {
		if (DataStructure.count(c) == 0 || (*DataStructure[c]).count(i) == 0) throw invalid_argument("Item does not exist");
		for (Item* item : *(*DataStructure[c])[i]) {
			if (!item->getName().compare(s)) {
				cout << item->getGroup() << " " << item->getSubgroup() << " " << item->getName() << " " << item->getTimestamp().ToString() << endl;
				return;
			}
		}
		throw invalid_argument("Item does not exist");
	}
	catch (const invalid_argument& e) {
		cout << e.what() << endl;
	}
}

Item* Data::InsertItem(char c, int i, string s, Date d) {
	if (c < 'A' || c > 'Z' || i < 0 || i > 99 || s.empty()) return nullptr;

	Item* usedVar = new Item(c, i, s, d);
	if (DataStructure.count(c) > 0) {
		if ((*DataStructure[c]).count(i) > 0) {
			for (Item* item : *(*DataStructure[c])[i]) {
				if (!item->getName().compare(s)) return nullptr;
			}
			(*DataStructure[c])[i]->push_back(usedVar);
		}
		else {
			auto listt = new list<Item*>{ usedVar };
			(*DataStructure[c])[i] = listt;
		}
	}
	else {
		auto listt = new list<Item*>{ usedVar };
		auto mapp = new map<int, list<Item*>*>{ {i, listt} };
		DataStructure[c] = mapp;
	}
	return usedVar;
}

list<Item*>* Data::InsertSubgroup(char c, int i, initializer_list<Item*> items) {
	if (c < 'A' || c > 'Z' || i < 0 || i > 99 || items.size() == 0) return nullptr;
	if (DataStructure.count(c) > 0 && (*DataStructure[c]).count(i) > 0) return nullptr;

	auto listt = new list<Item*>{ items };
	if (DataStructure.count(c) > 0)
		(*DataStructure[c])[i] = listt;
	else {
		auto mapp = new map<int, list<Item*>*>{ {i, listt} };
		DataStructure[c] = mapp;
	}
	return listt;
}

map<int, list<Item*>*>* Data::InsertGroup(char c, initializer_list<int> subgroups, initializer_list<initializer_list<Item*>> items) {
	if (c < 'A' || c > 'Z' || subgroups.size() == 0 || items.size() == 0) return nullptr;
	if (DataStructure.count(c) > 0) return nullptr;

	auto mapp = new map<int, list<Item*>*>;
	DataStructure[c] = mapp;

	initializer_list<int>::iterator i;
	initializer_list<initializer_list<Item*>>::iterator listt;
	for (i = subgroups.begin(), listt = items.begin(); i != subgroups.end() && listt != items.end(); ++i, ++listt) {
		auto listt2 = new list<Item*>{ *listt };
		(*mapp)[*i] = listt2;
	}
	return mapp;
}

bool Data::RemoveItem(char c, int i, string s) {
	Item* toRemove = GetItem(c, i, s);
	if (toRemove) {
		(*(*DataStructure[c])[i]).remove(toRemove);
		if ((*(*DataStructure[c])[i]).empty()) {
			(*DataStructure[c]).erase(i);
			if ((*DataStructure[c]).empty())
				DataStructure.erase(c);
		}
		delete toRemove;
		return true;
	}
	return false;
}

bool Data::RemoveSubgroup(char c, int i) {
	if (DataStructure.count(c) == 0 || (*DataStructure[c]).count(i) == 0) return false;
	for (auto item : *(*DataStructure[c])[i])
		delete item;
	(*DataStructure[c]).erase(i);
	if ((*DataStructure[c]).empty())
		DataStructure.erase(c);
	return true;
}

bool Data::RemoveGroup(char c) {
	if (DataStructure.count(c) == 0) return false;
	for (auto factorVarinit : *DataStructure[c])
		for (auto item : *factorVarinit.second)
			delete item;
	DataStructure.erase(c);
	return true;
}

