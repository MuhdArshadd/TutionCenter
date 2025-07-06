#include "Subject.h"

using namespace std;

Subject::Subject() {
	//initialize
	SubjectID = "";
	Name = "";
	AdminID = "";
	Fees = 0;
	Quota = 0;
	TutorID = "";
	Category_Age = 0;
}
Subject::Subject(std::string SubjectID, std::string Name, double Fees, int Quota, int Category_Age, std::string AdminID, std::string TutorID)
{
	this->SubjectID = SubjectID;
	this->Name = Name;
	this->AdminID = AdminID;
	this->Fees = Fees;
	this->TutorID = TutorID;
	this->Quota = Quota;
}

void Subject::insert() {

	DBConnection db;//instantiate

	db.prepareStatement("Insert into subject (SubjectID, Name, Fees, Category_Age, AdminID,TutorID) VALUES (?,?,?,?,?,?)");
	db.stmt->setString(1, SubjectID);
	db.stmt->setString(2, Name);
	db.stmt->setDouble(3, Fees);
	db.stmt->setInt(4, Category_Age);
	db.stmt->setString(5, AdminID);
	if (TutorID.empty()) {
		db.stmt->setNull(6, sql::DataType::VARCHAR);
	}
	else {
		db.stmt->setString(6, TutorID);
	}	db.QueryStatement();
	db.~DBConnection();
}
void Subject::remove() {

	int count;
	bool exists;
	std::string name;
	DBConnection db, db2, db3,db4,db5;
	db.prepareStatement("SELECT * FROM subject WHERE SubjectID=?");
	db.stmt->setString(1, SubjectID);
	db.QueryResult();

	// Check if the result set has at least one row
	exists = (db.res->rowsCount() > 0);
	if (exists == true)
	{

		db3.prepareStatement("SELECT * FROM enrollment WHERE SubjectID=?");
		db3.stmt->setString(1, SubjectID);
		db3.QueryResult();
		if (db3.res->rowsCount() > 0)
		{
			db3.prepareStatement("DELETE FROM enrollment WHERE SubjectID = ?");
			db3.stmt->setString(1, SubjectID);
			db3.QueryStatement();
			db3.~DBConnection();
		}

		try {
			db4.prepareStatement("SELECT Name FROM subject WHERE SubjectID=?");
			db4.stmt->setString(1, SubjectID);
			db4.QueryResult();
			if (db4.res->rowsCount() == 1) {
				db4.res->next();
				name = db4.res->getString("Name");
			}
		}
		catch (sql::SQLException& e) {
			// Handle any SQL exceptions
			std::cerr << "SQL Error: " << e.what() << std::endl;
		}


		//delete the subject
		db.prepareStatement("DELETE FROM subject WHERE SubjectID=?");
		db.stmt->setString(1, SubjectID);
		db.QueryResult();
		if (db.res->rowsCount() == 1)
		{
			db.QueryStatement();
			cout << "\n\nSUBJECT HAS BEEN SUCCESSFULLY REMOVE\n\n";
			db.~DBConnection();
		}

		db5.prepareStatement("SELECT COUNT(Name) AS COUNTER FROM subject WHERE Name=?");
		db5.stmt->setString(1, name);
		db5.QueryResult();
		if (db5.res->next())
		{
			count = db5.res->getInt("COUNTER");
			db5.~DBConnection();

		}
		
		//cannot apply
		if (count == 0) {
			db2.prepareStatement("UPDATE tutor SET Subject_Experties='NONE', Available_Tutoring_Date='0000-00-00' WHERE TutorID=(SELECT TutorID FROM subject WHERE SubjectID=?)");
			db2.stmt->setString(1, SubjectID);
			db2.QueryResult();
			if (db2.res->rowsCount() == 1)
			{
				db2.QueryStatement();
				db2.~DBConnection();
			}
		}

		cout << "\n******SUCCESSFULLY REMOVE*******.\n";
	}
	else
	{
		db.~DBConnection();
		cout << "\nSubject ID entered does not exists in the database.\n";
	}


}
bool Subject::assignedSubject() {

	DBConnection db;
	db.prepareStatement("SELECT Name FROM subject WHERE TutorID IS NULL AND Name=?");
	db.stmt->setString(1, Name);
	db.QueryResult();

	if (db.res->rowsCount() > 0) { // the subject chosen is null and true
		return true;
	}
	else
	{
		return false;
	}
	db.~DBConnection();
}
std::vector<Subject> Subject::listSubject() {

	vector<Subject> subjects;
	DBConnection db;

	db.prepareStatement("SELECT * FROM subject ");
	db.QueryResult();

	while (db.res->next()) {
		Subject subject;
		subject.SubjectID = db.res->getString("SubjectID");
		subject.Name = db.res->getString("Name");
		subject.Fees = db.res->getDouble("Fees");
		subject.Quota = db.res->getInt("Quota");
		subject.Category_Age = db.res->getInt("Category_Age");
		subject.TutorID = db.res->getString("TutorID");

		// To check if there's a tutor that register to this subject or not
		if (!db.res->isNull("TutorID"))
		{
			// if there's is a tutor 
				subject.TutorID = db.res->getString("TutorID");
		}
		else if (db.res->isNull("TutorID"))
		{
			subject.TutorID = "NONE";
		}

		subjects.push_back(subject);
	}
	db.~DBConnection();
	return subjects;
}
std::string Subject::getStatus(std::string StudentID,std::string SubjectID) {

	std::string status;
	DBConnection db;
	db.prepareStatement("SELECT Status FROM enrollment WHERE StudentID=? AND SubjectID=?");
	db.stmt->setString(1, StudentID);
	db.stmt->setString(2, SubjectID);
	db.QueryResult();
	if (db.res->rowsCount() == 1) {
		while (db.res->next()) {
			status = db.res->getString("Status");
		}
	}
	db.~DBConnection();
	return status;
}
std::string Subject::getTutorID(std::string SubjectID) {

	std::string id;
	DBConnection db;
	db.prepareStatement("SELECT TutorID FROM subject WHERE SubjectID=?");
	db.stmt->setString(1, SubjectID);
	db.QueryResult();
	//To check if there's a tutor that register to this subject or not
	
	if (db.res->rowsCount() == 1) {
		while (db.res->next()) {
			id = db.res->getString("TutorID"); // Fetch single value
		}
	}

	db.~DBConnection();
	return id;
}
std::string Subject::getSubjectID(std::string TutorID) {

	std::string id;
	DBConnection db;
	db.prepareStatement("SELECT SubjectID FROM subject WHERE TutorID=?");
	db.stmt->setString(1, TutorID);
	db.QueryResult();
	if (db.res->rowsCount() == 1) {
		if (!db.res->isNull("TutorID")) {
			while (db.res->next()) {
				id = db.res->getString("SubjectID");
			}
		}
		else {
			id = "NONE";
		}

	}
	db.~DBConnection();
	return id;
}
bool Subject::fullSubject(std::string SubjectID)
{
	int quota = 0;
	DBConnection db;
	db.prepareStatement("SELECT Quota FROM subject WHERE SubjectID=?");
	db.stmt->setString(1, SubjectID);
	db.QueryResult();
	if (db.res->rowsCount() == 1) {
		while (db.res->next()) {
			quota = db.res->getInt("Quota");
		}
	}
	if (quota >= 15) // this subject is full
	{
		return true;
	}
	else // subject is not full yet
	{
		return false;
	}
	db.~DBConnection();
}
int Subject::getSubAge(std::string SubjectID)
{
	int age = 0;
	DBConnection db;
	db.prepareStatement("SELECT Category_Age FROM subject WHERE SubjectID=?");
	db.stmt->setString(1, SubjectID);
	db.QueryResult();
	if (db.res->rowsCount() == 1) {
		while (db.res->next()) {
			age = db.res->getInt("Category_Age");
		}
	}
	return age;
	db.~DBConnection();
}
std::string Subject::getSubName(std::string SubjectID)
{
	std::string name;
	DBConnection db;
	db.prepareStatement("SELECT Name FROM subject WHERE SubjectID=?");
	db.stmt->setString(1, SubjectID);
	db.QueryResult();
	if (db.res->rowsCount() == 1) {
		while (db.res->next()) {
			name = db.res->getString("Name");
		}
	}
	return name;
	db.~DBConnection();
}
void Subject::displaySubject(int age)
{
	std::string subjectid, subname, tutorname, tutordate;
	int quota;
	double fees;

	DBConnection db;
	db.prepareStatement("SELECT subject.SubjectID,subject.Name AS SubjectName,subject.Fees,subject.Quota,tutor.Name AS TutorName,tutor.Available_Tutoring_Date FROM subject JOIN tutor ON subject.TutorID = tutor.TutorID WHERE subject.Category_Age=?");
	db.stmt->setInt(1, age);
	db.QueryResult();

	system("cls");
	std::cout << "LIST OF SUBJECT(S)\n*******************************\nList of all subject offered for student age: " << age << "\n\n\n";
	std::cout << "---------------------------------------------------------------------------------------------------------------------------------------" << endl;
	std::cout << "|" << setw(15) << "SubjectID" << "|" << setw(25) << "Name" << "|" << setw(15) << "Fees(RM)" << "|" << setw(18) << "Quota Left" << "|" << setw(35) << "Tutor Name" << "|" << setw(20) << "Lesson Date" << "|" << endl;
	std::cout << "---------------------------------------------------------------------------------------------------------------------------------------" << endl;

	while (db.res->next()) {
		subjectid = db.res->getString("SubjectID");
		subname = db.res->getString("SubjectName");
		fees = db.res->getDouble("Fees");
		quota = db.res->getInt("Quota");
		tutorname = db.res->getString("TutorName");
		tutordate = db.res->getString("Available_Tutoring_Date");

		if (quota == 0 )
		{
			std::cout << "|" << setw(15) << subjectid << "|" << setw(25) << subname << "|" << setw(15) << fees << "|" << setw(19) << "<<FULL>>|" << setw(35) << tutorname << "|" << setw(20) << tutordate << "|" << endl;
		}
		else
			std::cout << "|" << setw(15) << subjectid << "|" << setw(25) << subname << "|" << setw(15) << fees << "|" << setw(15) << quota << "   |" << setw(35) << tutorname << "|" << setw(20) << tutordate << "|" << endl;
	}
	std::cout << "---------------------------------------------------------------------------------------------------------------------------------------" << endl;

	db.~DBConnection();

}
Subject::~Subject() {

}
