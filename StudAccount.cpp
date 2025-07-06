#include "StudAccount.h"

using namespace std;

StudAccount::StudAccount() {
	//initialize
	StudentID = "";
	StudentPass = "";
	Name = "";
	Age = 0;
	Phone_Number = "";
	AdminID = "";
	SubjectID = "";
	AccountStatus = "";
}
StudAccount::StudAccount(std::string StudentID, std::string StudentPass, std::string Name, int Age, std::string Phone_Number, std::string AdminID, std::string SubjectID,std::string AccountStatus)
{
	this->StudentID = StudentID;
	this->StudentPass = StudentPass;
	this->Name = Name;
	this->Age = Age;
	this->Phone_Number = Phone_Number;
	this->AdminID = AdminID;
	this->SubjectID = SubjectID;
	this->AccountStatus = AccountStatus;
}
bool StudAccount::login() {

	DBConnection db;
	db.prepareStatement("SELECT * FROM student WHERE StudentID=? AND StudentPass=? AND AccountStatus='ACTIVE'");
	db.stmt->setString(1, StudentID);
	db.stmt->setString(2, StudentPass);
	db.QueryResult();
	if (db.res->rowsCount() == 1) {
		while (db.res->next()) {
			StudentID = db.res->getString("StudentID");
			StudentPass = db.res->getString("StudentPass");
			Name = db.res->getString("Name");
			Age = db.res->getInt("Age");
			Phone_Number = db.res->getString("Phone_Number");
			AdminID = db.res->getString("AdminID");
		}
		db.~DBConnection();
		return true;
	}
	else { // DEACTIVE
		db.~DBConnection();
		return false;
	}
}
void StudAccount::insert() {

	DBConnection db;//instantiate
	db.prepareStatement("Insert into student (StudentID, StudentPass, Name, Age, Phone_Number, AdminID) VALUES (?,?,?,?,?,?)");
	db.stmt->setString(1, StudentID);
	db.stmt->setString(2, StudentPass);
	db.stmt->setString(3, Name);
	db.stmt->setInt(4, Age);
	db.stmt->setString(5, Phone_Number);
	db.stmt->setString(6, AdminID);
	db.QueryStatement();
	db.~DBConnection();
}
void StudAccount::update() {

	DBConnection db;
	db.prepareStatement("UPDATE student SET Name=?, Phone_Number=? WHERE StudentID=?");
	db.stmt->setString(1, Name);
	db.stmt->setString(2, Phone_Number);
	db.stmt->setString(3, StudentID);
	db.QueryStatement();
	db.~DBConnection();
}
bool StudAccount::remove() {
	bool exists;
	DBConnection db;

	db.prepareStatement("SELECT * FROM student WHERE StudentID=?");
	db.stmt->setString(1, StudentID);
	db.QueryResult();

	// Check if the result set has at least one row
	exists = (db.res->rowsCount() == 1);

	if (exists) {
		// Start a transaction (if supported by your database)
		try {
			// Update subjects
			db.prepareStatement("UPDATE subject SET Quota = Quota - 1 WHERE SubjectID IN (SELECT SubjectID FROM enrollment WHERE StudentID=?)");
			db.stmt->setString(1, StudentID);
			db.QueryStatement();

			// Delete enrollment records
			db.prepareStatement("DELETE FROM enrollment WHERE StudentID=?");
			db.stmt->setString(1, StudentID);
			db.QueryStatement();

			// Delete student record
			db.prepareStatement("DELETE FROM student WHERE StudentID=?");
			db.stmt->setString(1, StudentID);
			db.QueryStatement();

		}
		catch (std::exception& e) {
			// Handle exceptions
			std::cerr << "Error: " << e.what() << std::endl;

			return false;
		}
	}

	return exists;
}

bool StudAccount::deactive() {

	bool exists;
	DBConnection db;
	db.prepareStatement("SELECT * FROM student WHERE StudentID=?");
	db.stmt->setString(1, StudentID);
	db.QueryResult();

	// Check if the result set has at least one row
	exists = (db.res->rowsCount() == 1);
	if (exists == true)
	{
		db.prepareStatement("UPDATE student SET AccountStatus='DEACTIVATED' WHERE StudentID=?");
		db.stmt->setString(1, StudentID);
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
bool StudAccount::reactive() {

	bool exists;
	DBConnection db;
	db.prepareStatement("SELECT * FROM student WHERE StudentID=?");
	db.stmt->setString(1, StudentID);
	db.QueryResult();

	// Check if the result set has at least one row
	exists = (db.res->rowsCount() == 1);
	if (exists == true)
	{
		db.prepareStatement("UPDATE student SET AccountStatus='ACTIVE' WHERE StudentID=?");
		db.stmt->setString(1, StudentID);
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
int StudAccount::setAge() {
	std::string YOB;
	int YOBdigit, Year, age;

	YOB = StudentID.substr(0, 2);//031220140753 to string , Extract the YOB (03)
	YOBdigit = stoi(YOB); // YOB in integer

	time_t now = time(0);// Get the current time as a time_t object
	tm localTime;// Convert the time_t object to a tm struct using localtime_s
	localtime_s(&localTime, &now);  // Use localtime_s for thread safety
	std::stringstream ss;// Format the date using std::put_time
	ss << std::put_time(&localTime, "%Y-%m-%d"); // YYYY-MM-DD format
	std::string todaysDate = ss.str();
	std::string year = todaysDate.substr(2, 2); // extract the YEAR (24)
    Year = stoi(year); // convert 24 of string to digit

	age = Year - YOBdigit;
	return age;
}
bool StudAccount::registeredIC() {

	DBConnection db;
	db.prepareStatement("SELECT StudentID FROM student WHERE StudentID=?");
	db.stmt->setString(1, StudentID);
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
bool StudAccount::registeredPN(){

	DBConnection db;
	db.prepareStatement("SELECT Phone_Number FROM student WHERE Phone_Number=?");
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
vector<StudAccount> StudAccount::listStudent() {

	vector<StudAccount> students;
	DBConnection db;
	db.prepareStatement("SELECT * FROM student");
	db.QueryResult();

	if (db.res->rowsCount() > 0) {
		while (db.res->next()) {
			StudAccount student;
			student.StudentID = db.res->getString("StudentID");
			student.StudentPass = db.res->getString("StudentPass");
			student.Name = db.res->getString("Name");
			student.Age = db.res->getInt("Age");
			student.Phone_Number = db.res->getString("Phone_Number");
			student.AccountStatus = db.res->getString("AccountStatus");

			students.push_back(student);
		}
	}

	db.~DBConnection();
	return students;
}
vector<StudAccount> StudAccount::listSubjectEnrolled() {

	StudAccount student;
	vector<StudAccount> subjects;
	DBConnection db;
	db.prepareStatement("SELECT SubjectID FROM enrollment WHERE StudentID=? ");
	db.stmt->setString(1, StudentID);
	db.QueryResult();

	if (db.res->rowsCount() >= 1) {
		while (db.res->next()) {
			student.SubjectID = db.res->getString("SubjectID");
			subjects.push_back(student);
		}
	}

	db.~DBConnection();
	return subjects;
}
void StudAccount::timeTable() {
	try {
		DBConnection db;
		db.prepareStatement("SELECT subject.Name AS SubjectName, tutor.Name AS TutorName, tutor.Available_Tutoring_Date, enrollment.Status, enrollment.FeesPeriod FROM enrollment JOIN subject ON enrollment.SubjectID = subject.SubjectID LEFT JOIN tutor ON subject.TutorID = tutor.TutorID WHERE enrollment.StudentID =?");
		db.stmt->setString(1, StudentID);
		db.QueryResult();

		if (db.res->rowsCount() > 0) {
			while (db.res->next()) {
				std::string subjectName = db.res->getString("SubjectName");
				std::string tutorName = db.res->isNull("TutorName") ? "N/A" : db.res->getString("TutorName");
				std::string tutorDate = db.res->isNull("Available_Tutoring_Date") ? "N/A" : db.res->getString("Available_Tutoring_Date");
				std::string enrollmentStatus = db.res->isNull("Status") ? "N/A" : db.res->getString("Status");
				std::string feesPeriod = db.res->isNull("FeesPeriod") ? "N/A" : db.res->getString("FeesPeriod");

				std::cout << "| " << std::setw(40) << std::left << subjectName << "| " << std::setw(24) << std::left << tutorDate << "| " << std::setw(24) << std::left << tutorName << "| " << std::setw(24) << std::left << enrollmentStatus << "| " << std::setw(39) << std::left << feesPeriod << "|" << std::endl;
			}
		}
	}
	catch (const sql::SQLException& e) {
		std::cerr << "SQL Exception: " << e.what() << std::endl;
	}
	// Destructor will be automatically called when 'db' goes out of scope.
}
vector<StudAccount> StudAccount::listSubjectUnpaid() {

	StudAccount sub;
	vector<StudAccount> subjectIDs;
	DBConnection db;
	db.prepareStatement("SELECT SubjectID FROM enrollment WHERE Status='UNPAID' AND StudentID=?");
	db.stmt->setString(1, StudentID);
	db.QueryResult();
	if (db.res->rowsCount() > 0) {
		while (db.res->next()) {
			sub.SubjectID = db.res->getString("SubjectID");
			subjectIDs.push_back(sub);
		}
	}
	db.~DBConnection();
	return subjectIDs;
}
StudAccount::~StudAccount() {

}
