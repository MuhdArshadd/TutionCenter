#include "menu.h"
#include <iostream>
#include <conio.h>
using namespace std;

menu::menu() {
	header = "";
	footer = "Select option";
	bullet = "-";
}
int menu::prompt() {
	int selected = -1;
	do
	{
		system("cls"); // clear ur console
		cout << header << endl; // display the header
		for (int i = 0; i < options.size(); i++) // depends on the how many option has been added
		{//loop through each option 
			cout << i + 1 << bullet << options[i].first; // for each option , dia akan taruk number 
			if (options[i].second != "") {
				cout << " : " << options[i].second;
			}
			cout << endl;
		}
		cout << footer << endl;

		selected = _getch() - '0';
	} while (selected < 1 || selected > options.size());
	return selected;
}
void menu::addOption(string option) {
	options.push_back({ option,"" });
}
void menu::setValue(int index, string value) {
	if (index >= 0 && index < options.size()) {
		options[index].second = value;
	}
}
menu::~menu() {
	options.clear();
}