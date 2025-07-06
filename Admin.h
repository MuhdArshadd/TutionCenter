#pragma once
#ifndef ADMIN_H
#define ADMIN_H

#include "DBConnection.h"
#include <string>

class Admin
{
public:
	std::string AdminID, AdminPass;

	//constructor
	Admin();
	Admin(std::string AdminID, std::string AdminPass);

	//admin function
	bool login(); // admin login

	//destructor
	~Admin();
};

#endif
