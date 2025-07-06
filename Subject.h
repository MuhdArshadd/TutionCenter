#pragma once
#ifndef SUBJECT_H
#define SUBJECT_H

#include "DBConnection.h"
#include <string>
#include <vector>
#include <iomanip>

class Subject
{
public://access specifier
	std::string SubjectID, Name, AdminID, TutorID;
	int Quota, Category_Age;
	double Fees;

	// constructor method
	Subject();
	Subject(std::string SubjectID, std::string Name, double Fees, int Quota, int Category_Age, std::string AdminID, std::string TutorID);

	//Subject function
	void insert(); //register new subject
	void remove(); //remove a subject
	bool assignedSubject();
	std::vector<Subject> listSubject(); //get list of subject
	std::string getStatus(std::string StudentID,std::string SubjectID);
	std::string getTutorID(std::string SubjectID);
	std::string getSubjectID(std::string TutorID);
	bool fullSubject(std::string SubjectID);
	int getSubAge(std::string SubjectID);
	std::string getSubName(std::string SubjectID);
	void displaySubject(int age);
	//destructor method
	~Subject();
};
#endif
