#pragma once
#ifndef ENROLLMENT_H
#define ENROLLMENT_H

#include "DBConnection.h"
#include <string>
#include <vector>
#include <iomanip>

class Enrollment
{
public:
	std::string StudentID, SubjectID, Feedback, Status;

	// constructor method
	Enrollment();
	Enrollment(std::string StudentID, std::string SubjectID, std::string Feedback, std::string Status);

	//function header
	void insert(const std::string StudentID, const std::vector<std::string>& subjectID);
	bool doFeedback(const std::string& StudentID, const std::string& SubjectID, const std::string& Feedback);
	std::vector<Enrollment> enrollmentDetails();
	bool alreadyEnrolled(const std::string& StudentID, const std::string& SubjectID);
	std::string getFeesPeriod(const std::string& StudentID, const std::string& SubjectID);
	void getFeedback(const std::string& TutorID);
	bool unrollSubject(const std::string& StudentID, const std::string& SubjectID);
	void displayEnrolled(const std::string& StudentID);


	//destructor method
	~Enrollment();

};
#endif
