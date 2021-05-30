#pragma once
#include <list>
#include <map>
#include "Item.h"

using namespace std;

class Data {
private:
	map<char, map<int, list<Item*>*>*> DataStructure;

public:
	Data(int n);
	Data();
	~Data();
	void PrintAll();
	int CountItems();
	map<int, list<Item*>*>* GetGroup(char c);
	void PrintGroup(char c);
	int CountGroupItems(char c);
	list<Item*>* GetSubgroup(char c, int i);
	void PrintSubgroupByNames(char c, int i);
	void PrintSubgroupByDates(char c, int i);
	int CountSubgroupItems(char c, int i);
	Item* GetItem(char c, int i, string s);
	void PrintItem(char c, int i, string s);
	Item* InsertItem(char c, int i, string s, Date d);
	list<Item*>* InsertSubgroup(char c, int i, initializer_list<Item*> items);
	map<int, list<Item*>*>* InsertGroup(char c, initializer_list<int> subgroups, initializer_list<initializer_list<Item*>> items);
	bool RemoveItem(char c, int i, string s);
	bool RemoveSubgroup(char c, int i);
	bool RemoveGroup(char c);
};
