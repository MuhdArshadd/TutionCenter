#pragma once
#ifndef STUDACCOUNT_H
#define STUDACCOUNT_H

#include "DBConnection.h"
#include <string>
#include <vector>
#include <chrono>
#include <ctime>
#include <sstream>
#include <iomanip>

class StudAccount
{
public://access specifier
	std::string StudentID, StudentPass, Phone_Number, Name, AdminID, SubjectID, AccountStatus;
	int Age;

	// constructor method
	StudAccount();
	StudAccount(std::string StudentID, std::string StudentPass, std::string Name, int Age, std::string Phone_Number, std::string AdminID, std::string SubjectID,std::string AccountStatus);

	//Student function
	bool login(); // login student account
	void insert(); // register new student account
	void update(); // update student information
	bool remove(); // remove user
	bool deactive(); // deactive user
	bool reactive(); //reactive user
	int setAge();
	bool registeredIC();
	bool registeredPN();
	std::vector<StudAccount> listStudent(); // to get the details of student
	std::vector<StudAccount> listSubjectEnrolled(); // to get the details of subject enrolled
	void timeTable();
	std::vector<StudAccount> listSubjectUnpaid();

	//destructor method
	~StudAccount();
};
#endif

