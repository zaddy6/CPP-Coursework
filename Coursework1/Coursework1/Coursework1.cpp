#include <iostream>
#include <list>
#include <string>
#include "Date.h"
#include "Item.h"
#include "Data.h"

using namespace std;

int main() {
	int intValue;
	char charValue;
	string strValue;
	int indx;

	Data createdItems(300);
	Data firData(30);
	Data secData(100);
	initializer_list<Item*> i1{ new Item(), new Item(), new Item() };
	initializer_list<Item*> i2{ new Item(), new Item(), new Item() };
	initializer_list<Item*> i3{ new Item(), new Item(), new Item() };
	initializer_list<Item*> i6{ new Item(), new Item(), new Item() };
	initializer_list<Item*> i7{ new Item(), new Item(), new Item() };
	initializer_list<Item*> i4{ new Item(), new Item(), new Item() };
	initializer_list<Item*> i5{ new Item(), new Item(), new Item() };
	initializer_list<initializer_list<Item*>> nesti1{ i4, i5 };
	initializer_list<int> subgroups1{ 16, 32 };
	initializer_list<initializer_list<Item*>> nesti2{ i4, i5 };
	initializer_list<int> subgroups2{ 16, 32 };
reinit:
	cout << "Enter testcase number\n1:Print all Items\n2:Number of items\n3:Select group\n4:Select subgroup\n5:Select subgroup and Print by dates\n6:select subgroup,print and count\n7:Print existing and non-existing item\n8:Create 30 items\n9:Insert subgroups and check results\n10:Insert groups\n11:Create 100 items\n12:Remove items and check result\n13:Remove subgroups and check results\n14:Remove groups and check results\n";
	cin >> indx;
	switch (indx) {
	case 1:
	cout << "Printing items\n";
	createdItems.PrintAll();
	break;
	case 2:
     cout << "Number of items: " << createdItems.CountItems() << endl;
	 break;
	case 3:

		cout << "Select group, print and count items\n";
		cout << "Select group (A-Z): ";
		cin >> charValue;
		createdItems.PrintGroup(charValue);
		cout << "Number of items in group " << createdItems.CountGroupItems(charValue) << endl;

		break;
	case 4:
		cout << "Select subgroup and print it by names, by dates and then count items\n";
		cout << "Select subgroup with 2+ items\n";
		cout << "Select group (A-Z): ";
		cin >> charValue;
		cout << "Select subgroup (0-99): ";
		cin >> intValue;
		cout << "\nBy names\n";
		createdItems.PrintSubgroupByNames(charValue, intValue);
		cout << "\nBy dates\n";
		createdItems.PrintSubgroupByDates(charValue, intValue);
		cout << "Number of items in group " << createdItems.CountSubgroupItems(charValue, intValue) << endl;

		break;
	case 5:
		cout << "Select subgroup and print it by names, by dates and then count items\n";
		cout << "Select subgroup with 1 item\n";
		cout << "Select group (A-Z): ";
		cin >> charValue;
		cout << "Select subgroup (0-99): ";
		cin >> intValue;
		cout << "\nBy names\n";
		createdItems.PrintSubgroupByNames(charValue, intValue);
		cout << "\nBy dates\n";
		createdItems.PrintSubgroupByDates(charValue, intValue);
		cout << "Number of items in group " << createdItems.CountSubgroupItems(charValue, intValue) << endl;

		break;
	case 6:

		cout << "Select subgroup and print it by names, by dates and then count items\n";
		cout << "Select non-existing subgroup\n";
		cout << "Select group (A-Z): ";
		cin >> charValue;
		cout << "Select subgroup (0-99): ";
		cin >> intValue;
		cout << "\nBy names\n";
		createdItems.PrintSubgroupByNames(charValue, intValue);
		cout << "\nBy dates\n";
		createdItems.PrintSubgroupByDates(charValue, intValue);
		cout << "Number of items in group " << createdItems.CountSubgroupItems(charValue, intValue) << endl;
		goto reinit;
		break;
	case 7:
		cout << "Print existing and non-existing item\n";
		cout << "Select existing item\n";
		cout << "Select group (A-Z): ";
		cin >> charValue;
		cout << "Select subgroup (0-99): ";
		cin >> intValue;
		cin.ignore();
		cout << "Select name: ";
		getline(cin, strValue);
		createdItems.PrintItem(charValue, intValue, strValue);
		cout << "Select non-existing item\n";
		cout << "Select group (A-Z): ";
		cin >> charValue;
		cout << "Select subgroup (0-99): ";
		cin >> intValue;
		cin.ignore();
		cout << "Select name: ";
		getline(cin, strValue);
		createdItems.PrintItem(charValue, intValue, strValue);
		goto reinit;
		break;
	case 8:
		cout << "Create 30 items and print\n";
		
		firData.PrintAll();
		//requires 7 init
		cout << "8- Print and count non-existing group items\n";
		cout << "Select non-existing group (A-Z): ";
		cin >> charValue;
		firData.PrintGroup(charValue);
		firData.CountGroupItems(charValue);
		//requires 7 init;
		cout << "9- Insert items and check the results\n";
		cout << "9a-Select existing group and subgroup\n";
		cout << "Select group (A-Z): ";
		cin >> charValue;
		cout << "Select subgroup (0-99): ";
		cin >> intValue;
		cin.ignore();
		cout << "Select name: ";
		getline(cin, strValue);
		firData.InsertItem(charValue, intValue, strValue, Date::CreateRandomDate(Date(6, 6, 2001), Date(6, 6, 2021)));
		cout << "Select existing group and non-existing subgroup\n";
		cout << "Select group (A-Z): ";
		cin >> charValue;
		cout << "Select subgroup (0-99): ";
		cin >> intValue;
		cin.ignore();
		cout << "Select name: ";
		getline(cin, strValue);
		firData.InsertItem(charValue, intValue, strValue, Date::CreateRandomDate(Date(6, 6, 2001), Date(6, 6, 2021)));
		cout << "Select non-existing group\n";
		cout << "Select group (A-Z): ";
		cin >> charValue;
		cout << "Select subgroup (0-99): ";
		cin >> intValue;
		cin.ignore();
		cout << "Select name: ";
		getline(cin, strValue);
		firData.InsertItem(charValue, intValue, strValue, Date::CreateRandomDate(Date(6, 6, 2001), Date(6, 6, 2021)));
		cout << "Select existing item\n";
		cout << "Select group (A-Z): ";
		cin >> charValue;
		cout << "Select subgroup (0-99): ";
		cin >> intValue;
		cin.ignore();
		cout << "Select name: ";
		getline(cin, strValue);
		firData.InsertItem(charValue, intValue, strValue, Date::CreateRandomDate(Date(6, 6, 2001), Date(6, 6, 2021)));
		cout << "9e- Check results\n";
		firData.PrintAll();
		break;
	case 9:
		cout << "Insert subgroups and check results\n";
		cout << "Select existing group\n";
		cout << "Select group (A-Z): ";
		cin >> charValue;
		cout << "Select subgroup (0-99): ";
		cin >> intValue;
		
		firData.InsertSubgroup(charValue, intValue, i1);
		cout << "Select non-existing group\n";
		cout << "Select group (A-Z): ";
		cin >> charValue;
		cout << "Select subgroup (0-99): ";
		cin >> intValue;
		
		firData.InsertSubgroup(charValue, intValue, i2);
		cout << "Select existing subgroup\n";
		cout << "Select group (A-Z): ";
		cin >> charValue;
		cout << "Select subgroup (0-99): ";
		cin >> intValue;
		
		firData.InsertSubgroup(charValue, intValue, i3);
		cout << "Check results\n";
		firData.PrintAll();
		break;
	case 10:
		cout << "Insert groups\n";
		cout << "Select non-existing group\n";
		cout << "Select group (A-Z): ";
		cin >> charValue;
	
		firData.InsertGroup(charValue, subgroups1, nesti1);
		cout << "Select existing group\n";
		cout << "Select group (A-Z): ";
		cin >> charValue;
		
		firData.InsertGroup(charValue, subgroups2, nesti2);
		cout << "11c- Check Results\n";
		firData.PrintAll();
		break;
	case 11:
		cout << "Create 100 items and print\n";
		
		secData.PrintAll();
		break;
		break;
	case 12:
		cout << "Remove Items and check results\n";
		cout << "Select subgroup with 2 items\n";
		cout << "Select group (A-Z): ";
		cin >> charValue;
		cout << "Select subgroup (0-99): ";
		cin >> intValue;
		cin.ignore();
		cout << "Select name: ";
		getline(cin, strValue);
		secData.RemoveItem(charValue, intValue, strValue);
		cout << "13b- Select group with multiple subgroups and subgroup with 1 item\n";
		cout << "Select group (A-Z): ";
		cin >> charValue;
		cout << "Select subgroup (0-99): ";
		cin >> intValue;
		cin.ignore();
		cout << "Select name: ";
		getline(cin, strValue);
		secData.RemoveItem(charValue, intValue, strValue);
		cout << "13c- Select group with 1 subgroup and item\n";
		cout << "Select group (A-Z): ";
		cin >> charValue;
		cout << "Select subgroup (0-99): ";
		cin >> intValue;
		cin.ignore();
		cout << "Select name: ";
		getline(cin, strValue);
		secData.RemoveItem(charValue, intValue, strValue);
		cout << "Select non-existing item\n";
		cout << "Select group (A-Z): ";
		cin >> charValue;
		cout << "Select subgroup (0-99): ";
		cin >> intValue;
		cin.ignore();
		cout << "Select name: ";
		getline(cin, strValue);
		secData.RemoveItem(charValue, intValue, strValue);
		cout << "Check results\n";
		secData.PrintAll();
		break;
	case 13:
		cout << "Remove subgroups and check results\n";
		cout << "Select group with several subgroups\n";
		cout << "Select group (A-Z): ";
		cin >> charValue;
		cout << "Select subgroup (0-99): ";
		cin >> intValue;
		secData.RemoveSubgroup(charValue, intValue);
		cout << "Select group with 1 subgroup\n";
		cout << "Select group (A-Z): ";
		cin >> charValue;
		cout << "Select subgroup (0-99): ";
		cin >> intValue;
		secData.RemoveSubgroup(charValue, intValue);
		cout << "Select non-existing subgroup\n";
		cout << "Select group (A-Z): ";
		cin >> charValue;
		cout << "Select subgroup (0-99): ";
		cin >> intValue;
		secData.RemoveSubgroup(charValue, intValue);
		cout << "Check results\n";
		secData.PrintAll();
		break;
	case 14:
		cout << "Remove groups and check results\n";
		cout << "Select existing group\n";
		cout << "Select group (A-Z): ";
		cin >> charValue;
		secData.RemoveGroup(charValue);
		cout << "Select non-existing group\n";
		cout << "Select group (A-Z): ";
		cin >> charValue;
		secData.RemoveGroup(charValue);
		cout << "Check Results\n";
		secData.PrintAll();

		break;

	}
	goto reinit;
	return 0;
}
