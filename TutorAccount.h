#pragma once
#ifndef TUTORACCOUNT_H
#define TUTORACCOUNT_H

#include "DBConnection.h"
#include <string>
#include <vector>
#include <chrono>
#include <ctime>
#include <sstream>
#include <iomanip>

class TutorAccount
{
public://access specifier
	std::string TutorID, SubjectID, AdminID, TutorPass, Name, Phone_Number, Subject_Experties, Available_Tutoring_Date, AccountStatus;

	// constructor method
	TutorAccount();
	TutorAccount(std::string TutorID, std::string SubjectID, std::string AdminID, std::string TutorPass, std::string Name, std::string Phone_Number, std::string Subject_Experties, std::string Available_Tutoring_Date,std::string AccountStatus);

	//Tutor function
	bool login(); // login
	void insert(); // register
	bool registeredIC();
	bool registeredPN();
	int setAge();
	void update(); // update information
	bool remove(); // remove tutor
	bool deactive(); // deactive tutor
	bool reactive(); // reactive tutor
	std::vector<TutorAccount> listTutor(); // to get list of tutor information
	std::string getName(std::string TutorID); // get the tutor name and date for corresponding subjectID
	std::string getDate(std::string TutorID); // get the tutor name and date for corresponding subjectID


	//destructor method
	~TutorAccount();


};

#endif

