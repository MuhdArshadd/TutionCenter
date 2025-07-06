#include "Enrollment.h"

using namespace std;

Enrollment::Enrollment() {
	//initialize
	StudentID = "";
	SubjectID = "";
	Feedback = "";
	Status = "";
}
Enrollment::Enrollment(std::string StudentID, std::string SubjectID, std::string Feedback, std::string Status)
{
	this->StudentID = StudentID;
	this->SubjectID = SubjectID;
	this->Feedback = Feedback;
	this->Status = Status;
}
void Enrollment::insert(const std::string StudentID,const std::vector<std::string>& subjectID) {

	DBConnection db, db2;

	//process of enrolling the student according to chosen subject
	db.prepareStatement("Insert into enrollment (StudentID, SubjectID) VALUES (?,?)");
	for (int i = 0; i < subjectID.size(); ++i) {
		const std::string& SubjectID = subjectID[i];
		db.stmt->setString(1, StudentID);
		db.stmt->setString(2, SubjectID);
		db.QueryStatement();
	}
	db.~DBConnection();

	//process of adding the quota
	db2.prepareStatement("UPDATE subject SET Quota=Quota+1 WHERE SubjectID=?");
	for (int i = 0; i < subjectID.size(); ++i) {
		const std::string& SubjectID = subjectID[i];
		db2.stmt->setString(1, SubjectID);
		db2.QueryStatement();
	}
	db2.~DBConnection();
}
bool Enrollment::doFeedback(const std::string& StudentID, const std::string& SubjectID, const std::string& Feedback) {
	DBConnection db;

	db.prepareStatement("SELECT * FROM enrollment WHERE SubjectID=? AND StudentID=?");
	db.stmt->setString(1, SubjectID);
	db.stmt->setString(2, StudentID);
	db.QueryResult();
	if (db.res->rowsCount() == 1) {

		db.prepareStatement("UPDATE enrollment SET Feedback=? WHERE SubjectID=? AND StudentID=?");
		db.stmt->setString(1, Feedback);
		db.stmt->setString(2, SubjectID);
		db.stmt->setString(3, StudentID);
		db.QueryStatement();

		return true;
	}
	else
	{
		return false;
	}
	db.~DBConnection();

}
std::vector<Enrollment> Enrollment::enrollmentDetails() {

	Enrollment enroll;
	vector<Enrollment> enrollment;
	DBConnection db;
	db.prepareStatement("SELECT * FROM enrollment");
	db.QueryResult();

	while (db.res->next()) {
		enroll.StudentID = db.res->getString("StudentID");
		enroll.SubjectID = db.res->getString("SubjectID");
		enroll.Feedback = db.res->getString("Feedback");
		enroll.Status = db.res->getString("Status");
		// To check if there's a feedback to this subject or not
		if (!db.res->isNull("Feedback")) // if there's is a status
			enroll.Feedback = db.res->getString("Feedback");
		else // if there's not
			enroll.Feedback = "N/A";

		enrollment.push_back(enroll);
	}
	db.~DBConnection();
	return enrollment;
}
bool Enrollment::alreadyEnrolled(const std::string& StudentID, const std::string& SubjectID)
{
	bool exists;
	bool enrolled;
	DBConnection db;
	db.prepareStatement("SELECT * FROM enrollment WHERE StudentID=? AND SubjectID=?");
	db.stmt->setString(1, StudentID);
	db.stmt->setString(2, SubjectID);
	db.QueryResult();

	exists = (db.res->rowsCount() > 0);
	if (exists == true) 
	{
		enrolled = true;
	}
	else
	{
		enrolled = false;
	}
	db.~DBConnection();
	return enrolled;
}
std::string Enrollment::getFeesPeriod(const std::string& StudentID, const std::string& SubjectID)
{
	std::string date;
	DBConnection db;
	db.prepareStatement("SELECT FeesPeriod FROM enrollment WHERE StudentID=? AND SubjectID=?");
	db.stmt->setString(1, StudentID);
	db.stmt->setString(2, SubjectID);
	db.QueryResult();

	if (db.res->rowsCount() == 1) {
		while (db.res->next()) {
			date = db.res->getString("FeesPeriod");
		}
	}
	db.~DBConnection();
	return date;
}

void Enrollment::getFeedback(const std::string& TutorID)
{

	std::string name, feedback;
	int totalstudents = 0;
	int age16 = 0;
	int age17 = 0;
	int age;

	DBConnection db, db2;
	db2.prepareStatement("SELECT * FROM tutor WHERE TutorID=?");
	db2.stmt->setString(1, TutorID);
	db2.QueryResult();
	if (db2.res->rowsCount() == 1)
	{
		db.prepareStatement("SELECT student.Name, student.Age, enrollment.Feedback FROM student JOIN enrollment ON student.StudentID = enrollment.StudentID WHERE enrollment.SubjectID IN (SELECT SubjectID FROM subject WHERE TutorID=?) ORDER BY student.Age ASC");
		db.stmt->setString(1, TutorID);
		db.QueryResult();

		if (db.res->rowsCount() > 0) {
		std::cout << "--------------------------------------------------------------------------------------------------------------------------------\n";
		std::cout << "|           Name				 |           Age           |                        Feedback		        |\n";
		std::cout << "--------------------------------------------------------------------------------------------------------------------------------\n";

		while (db.res->next()) {
			name = db.res->getString("Name");
			age = db.res->getInt("Age");
			if (age == 16)
			{
				age16++;
			}
			else if (age == 17)
			{
				age17++;
			}
			feedback = db.res->getString("Feedback");

			totalstudents++;

			std::cout << "| " << std::setw(47) << std::left << name << "|" << std::setw(25) << std::left << age << "| " << std::setw(50) << std::left << feedback << "|\n";
		}

		std::cout << "--------------------------------------------------------------------------------------------------------------------------------\n";

		std::cout << "\n\nThe total of students (Age 16) enrolled is : " << age16 << "/15";
		std::cout << "\nThe total of students (Age 17) enrolled is : " << age17 << "/15";
		std::cout << "\nThe total of students under guidance is : " << totalstudents << "/15";

		}
		else
		{
			std::cout << "\nYou do not have any feedback.\n\n";
		}
	}
	else
	{
		std::cout << "\nTutor ID does not exist in the database.\n\n";
	}

	db.~DBConnection();
}

bool Enrollment::unrollSubject(const std::string& StudentID, const std::string& SubjectID) {

	bool exists;
	DBConnection db, db2;
	db.prepareStatement("SELECT * FROM enrollment WHERE StudentID=? AND SubjectID=?");
	db.stmt->setString(1, StudentID);
	db.stmt->setString(2, SubjectID);
	db.QueryResult();

	// Check if the result set has at least one row
	exists = (db.res->rowsCount() > 0);
	if (exists == true)
	{
		//delete the subject
		db.prepareStatement("DELETE FROM enrollment WHERE StudentID=? AND SubjectID=?"); //unroll
		db.stmt->setString(1, StudentID);
		db.stmt->setString(2, SubjectID);
		db.QueryStatement();
		cout << "\n\nUNROLLMENT PROCESS HAS BEEN SUCCESSFULLY COMPLETE\n\n";
		db.~DBConnection();

		//update the tutor
		db2.prepareStatement("UPDATE subject SET Quota = Quota - 1 WHERE SubjectID=?"); // update quota
		db2.stmt->setString(1, SubjectID);
		db2.QueryStatement();
		db2.~DBConnection();
		return true;
	}
	else
	{
		cout << "\nSubjectID is not in the database.\n";
		db.~DBConnection();
		return false;
	}

}
void Enrollment::displayEnrolled(const std::string& StudentID)
{
	std::string subjectid, subjectname;
	DBConnection db;
	db.prepareStatement("SELECT e.SubjectID, s.Name FROM enrollment e JOIN subject s ON e.SubjectID = s.SubjectID WHERE e.StudentID=?");
	db.stmt->setString(1, StudentID);
	db.QueryResult();


	if (db.res->rowsCount() > 0) {
		while (db.res->next()) {
			subjectid = db.res->getString("SubjectID");
			subjectname = db.res->getString("Name");
			std::cout << "| " << std::setw(24) << std::left << subjectid << "|" << std::setw(41) << std::left << subjectname << "|\n";
		}
	}

	db.~DBConnection();
}

Enrollment::~Enrollment() {

}