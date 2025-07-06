#include "TutorAccount.h"

using namespace std;

TutorAccount::TutorAccount() {
	//initialize
	TutorID = "";
	SubjectID = "";
	AdminID = "";
	TutorPass = "";
	Name = "";
	Phone_Number = "";
	Subject_Experties = "";
	Available_Tutoring_Date = "";
	AccountStatus = "";
}
TutorAccount::TutorAccount(std::string TutorID, std::string SubjectID, std::string AdminID, std::string TutorPass, std::string Name, std::string Phone_Number, std::string Subject_Experties, std::string Available_Tutoring_Date, std::string AccountStatus)
{
	this->TutorID = TutorID;
	this->SubjectID = SubjectID;
	this->AdminID = AdminID;
	this->TutorPass = TutorPass;
	this->Name = Name;
	this->Phone_Number = Phone_Number;
	this->Subject_Experties = Subject_Experties;
	this->Available_Tutoring_Date = Available_Tutoring_Date;
	this->AccountStatus = AccountStatus;
}
bool TutorAccount::login() {

	DBConnection db;
	db.prepareStatement("SELECT * FROM tutor WHERE TutorID=? AND TutorPass=? AND AccountStatus='ACTIVE'");
	db.stmt->setString(1, TutorID);
	db.stmt->setString(2, TutorPass);
	db.QueryResult();
	if (db.res->rowsCount() == 1) {
		while (db.res->next()) {
			TutorID = db.res->getString("TutorID");
			TutorPass = db.res->getString("TutorPass");
			Name = db.res->getString("Name");
			Phone_Number = db.res->getString("Phone_Number");
			Subject_Experties = db.res->getString("Subject_Experties");
			Available_Tutoring_Date = db.res->getString("Available_Tutoring_Date");
		}
		db.~DBConnection();
		return true;
	}
	else {
		db.~DBConnection();
		return false;
	}
}
void TutorAccount::insert() {

	DBConnection db, db2;
	//register information of new tutor
	db.prepareStatement("Insert into tutor (TutorID, AdminID, TutorPass, Name, Phone_Number, Subject_Experties, Available_Tutoring_Date ) VALUES (?,?,?,?,?,?,?)");
	db.stmt->setString(1, TutorID);
	db.stmt->setString(2, AdminID);
	db.stmt->setString(3, TutorPass);
	db.stmt->setString(4, Name);
	db.stmt->setString(5, Phone_Number);
	db.stmt->setString(6, Subject_Experties);
	db.stmt->setString(7, Available_Tutoring_Date);
	db.QueryStatement();
	db.~DBConnection();

	//register new tutor to his/her chosen subject
	db2.prepareStatement("UPDATE subject SET TutorID=? WHERE Name=?");
	db2.stmt->setString(1, TutorID);
	db2.stmt->setString(2, Subject_Experties);
	db2.QueryStatement();
	db2.~DBConnection();
}
bool TutorAccount::registeredIC() {

	DBConnection db;
	db.prepareStatement("SELECT TutorID FROM tutor WHERE TutorID=?");
	db.stmt->setString(1, TutorID);
	db.QueryResult();
	if (db.res->rowsCount() == 1) {
		return true; // exits
	}
	else
	{
		return false;
	}
	db.~DBConnection();

}
bool TutorAccount::registeredPN() {

	DBConnection db;
	db.prepareStatement("SELECT Phone_Number FROM tutor WHERE Phone_Number=?");
	db.stmt->setString(1, Phone_Number);
	db.QueryResult();
	if (db.res->rowsCount() == 1) {
		return true; // exits
	}
	else
	{
		return false;
	}
	db.~DBConnection();


}
int TutorAccount::setAge() {
	std::string YOB;
	int YOBdigit, Year, age = 0;

	YOB = TutorID.substr(0, 2);//031220140753 to string , Extract the YOB (03)
	YOBdigit = stoi(YOB); // YOB in integer

	time_t now = time(0);// Get the current time as a time_t object
	tm localTime;// Convert the time_t object to a tm struct using localtime_s
	localtime_s(&localTime, &now);  // Use localtime_s for thread safety
	std::stringstream ss;// Format the date using std::put_time
	ss << std::put_time(&localTime, "%Y-%m-%d"); // YYYY-MM-DD format
	std::string todaysDate = ss.str();
	std::string year = todaysDate.substr(2, 2); // extract the YEAR (24)
	Year = stoi(year); // convert 24 of string to digit

	if (YOBdigit >= 64 ) // age maximum is 60 based on 2024
	{
		age = YOBdigit - Year;
		return age;
	}
	if (YOBdigit <= 04) // age minimum is 20 based on 2024
	{
		age = Year - YOBdigit;
		return age;
	}
}
void TutorAccount::update() {

	DBConnection db;
	db.prepareStatement("UPDATE tutor SET Name=?, Phone_Number=?, Subject_Experties=?, Available_Tutoring_Date=?  WHERE TutorID=?");
	db.stmt->setString(1, Name);
	db.stmt->setString(2, Phone_Number);
	db.stmt->setString(3, Subject_Experties);
	db.stmt->setString(4, Available_Tutoring_Date);
	db.stmt->setString(5, TutorID);
	db.QueryStatement();
	db.~DBConnection();
}
bool TutorAccount::remove() {

	bool exists;
	DBConnection db,db2;
	db.prepareStatement("SELECT * FROM tutor WHERE TutorID=?");
	db.stmt->setString(1, TutorID);
	db.QueryResult();

	// Check if the result set has at least one row
	exists = (db.res->rowsCount() > 0);
	if (exists == true)
	{

		db2.prepareStatement("UPDATE subject SET TutorID=NULL WHERE TutorID=?");
		db2.stmt->setString(1, TutorID);
		db2.QueryStatement();
		db2.~DBConnection();

		db.prepareStatement("DELETE FROM tutor WHERE TutorID=?");
		db.stmt->setString(1, TutorID);
		db.QueryStatement();
		db.~DBConnection();

		return true;
	}
	else
	{
		db.~DBConnection();
		return false;
	}
}
bool TutorAccount::deactive() {

	bool exists;
	DBConnection db;
	db.prepareStatement("SELECT * FROM tutor WHERE TutorID=?");
	db.stmt->setString(1, TutorID);
	db.QueryResult();

	// Check if the result set has at least one row
	exists = (db.res->rowsCount() > 0);
	if (exists == true)
	{
		db.prepareStatement("UPDATE tutor SET AccountStatus='DEACTIVATED' WHERE TutorID=?");
		db.stmt->setString(1, TutorID);
		db.QueryStatement();
		db.~DBConnection();
		return true;
	}
	else
	{
		db.~DBConnection();
		return false;
	}
}
bool TutorAccount::reactive() {

	bool exists;
	DBConnection db;
	db.prepareStatement("SELECT * FROM tutor WHERE TutorID=?");
	db.stmt->setString(1, TutorID);
	db.QueryResult();

	// Check if the result set has at least one row
	exists = (db.res->rowsCount() > 0);
	if (exists == true)
	{
		db.prepareStatement("UPDATE tutor SET AccountStatus='ACTIVE' WHERE TutorID=?");
		db.stmt->setString(1, TutorID);
		db.QueryStatement();
		db.~DBConnection();
		return true;
	}
	else
	{
		db.~DBConnection();
		return false;
	}
}
std::vector<TutorAccount> TutorAccount::listTutor() {

	vector<TutorAccount> tutors;
	TutorAccount tutor;
	DBConnection db;
	db.prepareStatement("SELECT * FROM tutor ");
	db.QueryResult();
	while (db.res->next()) {
		tutor.TutorID = db.res->getString("TutorID");
		tutor.Name = db.res->getString("Name");
		tutor.Subject_Experties = db.res->getString("Subject_Experties");
		tutor.Phone_Number = db.res->getString("Phone_Number");
		tutor.Available_Tutoring_Date = db.res->getString("Available_Tutoring_Date");
		tutor.AccountStatus = db.res->getString("AccountStatus");

		tutors.push_back(tutor);
	}
	db.~DBConnection();
	return tutors;
}
std::string TutorAccount::getName(std::string TutorID) {

	TutorAccount tutor;
	DBConnection db;
	std::string name;

	if (TutorID == "NONE") {
		name = "NONE";
	}
	else {
		db.prepareStatement("SELECT Name FROM tutor WHERE TutorID=?");
		db.stmt->setString(1, TutorID);
		db.QueryResult();
		if (db.res->rowsCount() == 1) {
			while (db.res->next()) {
				name = db.res->getString("Name");
			}
		}
	}
	db.~DBConnection();
	return name;
}
std::string TutorAccount::getDate(std::string TutorID) {

	TutorAccount tutor;
	DBConnection db;
	std::string date;

	if (TutorID == "NONE") {
		date = "N/A";
	}
	else {
		db.prepareStatement("SELECT Available_Tutoring_Date FROM tutor WHERE TutorID=?");
		db.stmt->setString(1, TutorID);
		db.QueryResult();
		if (db.res->rowsCount() == 1) {
			while (db.res->next()) {
				date = db.res->getString("Available_Tutoring_Date");
			}
		}
	}
	db.~DBConnection();
	return date;
}

//std::string TutorAccount::getDate(const std::string& TutorID) {
//
//	std::string date;
//	DBConnection db;
//	db.prepareStatement("SELECT Available_Tutoring_Date FROM tutor WHERE TutorID=? ");
//	if (TutorID == "NONE") {
//		date = "N/A";
//	}
//	else {
//		db.stmt->setString(1, TutorID);
//		db.QueryResult();
//		if (db.res->rowsCount() == 1) {
//			while (db.res->next()) {
//				date = db.res->getString("Available_Tutoring_Date");
//			}
//		}
//	}
//	db.~DBConnection();
//	return date;
//}
TutorAccount::~TutorAccount() {

}
