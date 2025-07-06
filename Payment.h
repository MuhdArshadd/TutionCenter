#pragma once
#ifndef PAYMENT_H
#define PAYMENT_H

#include "DBConnection.h"
#include <string>
#include <vector>
#include <chrono>
#include <ctime>
#include <sstream>
#include <cstdlib>
#include <iomanip>
#include <random>

class Payment
{
public:
	std::string PaymentID, StudentID, Payment_Date, AdminID;
	int Total_Subject;
	double Total_Fees;

	// constructor method
	Payment(); 
	Payment(std::string PaymentID, std::string StudentID,int Total_Subject, double Total_Fees, std::string Payment_Date, std::string AdminID);

	//Payment function
	void insert(); // insert new payment details
	void update(const std::string subjectsUnpaid); // update status of payment

	//destructor method
	~Payment();

};
#endif
