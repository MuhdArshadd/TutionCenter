#include "Payment.h"

using namespace std;

Payment::Payment() {
	//initialize
	PaymentID = "";
	StudentID = "";
	Total_Subject = 0;
	Total_Fees = 0;
	Payment_Date = "";
	AdminID = "";
}
Payment::Payment(std::string PaymentID, std::string StudentID, int Total_Subject, double Total_Fees, std::string Payment_Date, std::string AdminID)
{
	this->PaymentID = PaymentID;
	this->StudentID = StudentID;
	this->Total_Subject = Total_Subject;
	this->Total_Fees = Total_Fees;
	this->Payment_Date = Payment_Date;
	this->AdminID = AdminID;
}
void Payment::insert() {

	DBConnection db;//instantiate
	db.prepareStatement("Insert into payment (StudentID, Total_Subject, Total_Fees, AdminID) VALUES (?,?,?,?)");
	//PaymentID is auto increment
	db.stmt->setString(1, StudentID); 
	db.stmt->setInt(2, Total_Subject);
	db.stmt->setDouble(3, Total_Fees);
	db.stmt->setString(4, AdminID);
	db.QueryStatement();
	db.~DBConnection();
}
void Payment::update(const std::string subjectsUnpaid) {

	DBConnection db;
	db.prepareStatement("UPDATE enrollment SET Status='PAID' WHERE StudentID=? AND SubjectID=?");
	const std::string& SubjectID = subjectsUnpaid;
	db.stmt->setString(1, StudentID);
	db.stmt->setString(2, SubjectID);
	db.QueryStatement();

	db.~DBConnection();
}
Payment::~Payment() {

}