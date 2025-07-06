#pragma once
#ifndef MENU_H
#define MENU_H

#include <string>
#include <vector>
#include <utility>

class menu
{
public:
	std::string header, footer, bullet;

	//constructor
	menu();
	
	//function menu
	void addOption(std::string option);
	void setValue(int index, std::string value);
	int prompt();

	//destructor
	~menu();

private:
	std::vector<std::pair<std::string, std::string>> options;
};
#endif