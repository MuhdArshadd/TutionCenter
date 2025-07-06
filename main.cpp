//libraries
#include <iostream>
#include <conio.h>
#include <iomanip>
#include <sstream>
#include <vector>
#include <string>
#include <mysql/jdbc.h>
#include <cstring>
#include <regex>
#include <algorithm>
//Header
#include "DBConnection.h"
#include "menu.h"
#include "StudAccount.h"
#include "TutorAccount.h"
#include "Admin.h"
#include "Subject.h"
#include "Payment.h"
#include "Enrollment.h"

using namespace std;

//function header
//registration
void registerMenu();
void registerStudAccount();
void registerTutAccount();
//log in
void loginMenu();
void loginStudent();
void loginTutor();
void loginAdmin();
//home menu for each user
void studhome(StudAccount stud);
void tutorhome(TutorAccount tutor);
void adminhome(Admin admin);
//view profile for student and tutor
StudAccount studprofile(StudAccount stud);
TutorAccount tutorprofile(TutorAccount tutor);
// admin function
void manageUser(Admin admin);
void manageSubject(Admin admin);
//student function
void enrollment(StudAccount stud);
void payment(StudAccount stud);
void feedback(StudAccount stud);
void UnrollSubject(StudAccount stud);
void timeTable(StudAccount stud);
//tutor function
void studentlist(TutorAccount tutor);



int main()
{
	menu mainmenu;
	mainmenu.header = "*******************************************\nWelcome to Tuition Centre Online System!\n*******************************************\n\nPlease choose from the following options:\n";
	mainmenu.addOption("Register");
	mainmenu.addOption("Login");
	mainmenu.addOption("Exit");

	while (1) {
		switch (mainmenu.prompt())
		{
		case 1:
			registerMenu();
			break;
		case 2:
			loginMenu();
			break;
		case 3:
			exit(0);
		default:
			std::cout << "Invalid number. Try again.";
			_getch();
			break;
		}
	}
}

void registerMenu()
{
	menu registerAcc;
	registerAcc.header = "*************************************\nREGISTRATION SECTION\n*************************************\nChoose your category to register.\n";
	registerAcc.addOption("Student");
	registerAcc.addOption("Tutor");
	registerAcc.addOption("Press 3 to back.");

	while (1) {
		switch (registerAcc.prompt())
		{
		case 1:
			registerStudAccount();
			break;
		case 2:
			registerTutAccount();
			break;
		case 3:
			main();
			break;
		default:
			std::cout << "Invalid number. Try again.";
			_getch();
			break;
		}
	}
}
void registerStudAccount()
{
	menu rgStud;
	rgStud.header = "*************************************\nSTUDENT REGISTRATION SECTION\n*************************************\n";
	rgStud.addOption("Student ID (IC NUMBER)");
	rgStud.addOption("Student Password");
	rgStud.addOption("Fullname (BASED ON IC)");
	rgStud.addOption("Phone Number");
	rgStud.addOption("Register");
	rgStud.addOption("Press 6 to go back.\n");

	StudAccount newstudacc;
	std::vector<bool> optionInserted(5, false); // turutan of insertion

	std::regex pattern1("\\d{12}");// Validate the format of the entered Student ID
	std::regex pattern2("^01\\d{8}$"); // validate the format of the entered phone number

	while (1) {

		switch (rgStud.prompt()) {
		case 1:
			
			std::cout << "\nInsert Student ID (IC NUMBER WITHOUT DASH): ";
			std::cin >> newstudacc.StudentID;

			// Check if the Student ID is in the correct format
			if (std::regex_match(newstudacc.StudentID, pattern1)) { // check format
				if (newstudacc.registeredIC() == true) // exist
				{
					std::cout << "\nThis Student ID already registered. Try Again\n";
					_getch();
				}
				else if (newstudacc.registeredIC() == false) // not exist
				{
					newstudacc.Age = newstudacc.setAge();
					if (newstudacc.Age < 16 || newstudacc.Age > 17) { // Check age before registration
						std::cout << "\nSorry. You are not in the age of 16 and 17. Therefore, you cannot register.\n";
						system("pause");
						return;
					}
					else {
						// Update the option value and set it to true
						rgStud.setValue(0, newstudacc.StudentID);
						optionInserted[0] = true;
					}
				}
			}
			else {
				std::cout << "Invalid Student ID format. Please enter a valid 12-digit number without dash. " << std::endl;
				_getch();
			}
		break;
		case 2:
			if (optionInserted[0] == true) {
				std::cout << "\nInsert Student Password:";
				std::cin >> newstudacc.StudentPass;
				rgStud.setValue(1, newstudacc.StudentPass);
				optionInserted[1] = true;
			}
			else {
				std::cout << "Error: Please enter information for Option 1 first.\n";
				_getch();
			}
			break;
		case 3:
			if (optionInserted[1] == true) {
				std::cout << "\nInsert Fullname (BASED ON IC):";
				std::cin.ignore();
				getline(std::cin, newstudacc.Name);
				rgStud.setValue(2, newstudacc.Name);
				optionInserted[2] = true;
			}
			else {
				std::cout << "Error: Please enter information for Option 2 first.\n";
				_getch();
			}
			break;
		case 4:
			if (optionInserted[2] == true) {
				std::cout << "\nInsert Phone Number (e.g. 01######## ): ";
				std::cin >> newstudacc.Phone_Number;
				// Check if the Student ID is in the correct format
				if (std::regex_match(newstudacc.Phone_Number, pattern2)) { // check format
					if (newstudacc.registeredPN() == true) // exist
					{
						std::cout << "\nThis Phone Number already registered. Try Again.\n";
						_getch();
					}
					else if (newstudacc.registeredPN() == false) // not exist
					{
						rgStud.setValue(3, newstudacc.Phone_Number);
						optionInserted[3] = true;
					}
				}
				else {
					std::cout << "Invalid Phone Number. Please enter a valid 10-digit number without dash starting with 01. " << std::endl;
					_getch();
				}
			}
			else {
				std::cout << "Error: Please enter information for Option 3 first.\n";
				_getch();
			}
			break;
		case 5:
			if (optionInserted[3] == true) {
				newstudacc.AdminID = "A12345";
				newstudacc.insert();
				std::cout << "\n\nREGISTRATION IS SUCCESSFULLY COMPLETE.\nREDIRECTING YOU BACK TO MAIN MENU.\n";
				system("pause");
				main();
			}
			else {
				std::cout << "Error: Please enter information for Option 4 first.\n";
				_getch();
			}
			break;
		case 6:
			main();
			break;
		default:
			std::cout << "Invalid number. Try again.";
			_getch();
			break;
		}
	}
}
void registerTutAccount() {

	menu rgTutor;
	rgTutor.header = "*************************************\nTUTOR REGISTRATION SECTION\n*************************************\n";
	rgTutor.addOption("Tutor ID (IC NUMBER)");
	rgTutor.addOption("Tutor Password");
	rgTutor.addOption("Fullname (BASED ON IC)");
	rgTutor.addOption("Phone Number");
	rgTutor.addOption("Subject Experties"); // ***
	rgTutor.addOption("Available Tutoring Date"); // ***
	rgTutor.addOption("Register");
	rgTutor.addOption("Press 8 to go back.\n");

	TutorAccount newtutoracc;
	Subject subject;
	std::vector<Subject> sub = subject.listSubject();
	std::vector<bool> optionInserted(6, false);
	std::vector<string> subName;

	int age = 0;
	bool validName = false;
	bool Unique = false;
	bool valid = false;
	bool occupied = true;
	std::regex pattern1("\\d{12}");// Validate the format of the entered Tutor ID
	std::regex pattern2("^01\\d{8}$"); // validate the format of the entered phone number
	std::regex datePattern("^\\d{4}-\\d{2}-\\d{2}$"); // validate the format of the entered date

	while (1) {

		switch (rgTutor.prompt()) {
		case 1:
			std::cout << "\nInsert Tutor ID (IC NUMBER WITHOUT DASH): ";
			std::cin >> newtutoracc.TutorID;

			// Check if the Student ID is in the correct format
			if (std::regex_match(newtutoracc.TutorID, pattern1)) {
				if (newtutoracc.registeredIC() == true)
				{
					std::cout << "\nThis Tutor ID already registered. Try Again\n";
					_getch();
				}
				else if (newtutoracc.registeredIC() == false)
				{
					age = newtutoracc.setAge();
					if (age <= 19) { // Check age before registration
						std::cout << "\nSorry. Your age is not suitable for tutoring. Therefore, you cannot register.\n";
						system("pause");
						return;
					}
					rgTutor.setValue(0, newtutoracc.TutorID);
					optionInserted[0] = true;
				}
			}
			else
			{
				std::cout << "Invalid Tutor ID format. Please enter a valid 12-digit number without dash: " << std::endl;
				_getch();
			}
			break;
		case 2:
			cin.ignore();
			if (optionInserted[0] == true) {
				std::cout << "\nInsert Tutor Password:";
				getline(std::cin, newtutoracc.TutorPass);
				rgTutor.setValue(1, newtutoracc.TutorPass);
				optionInserted[1] = true;
			}
			else {
				std::cout << "Error: Please enter information for Option 1 first.\n";
				_getch();
			}
			break;
		case 3:
			if (optionInserted[1] == true) {
				std::cout << "\nInsert Fullname (BASED ON IC):";
				getline(std::cin, newtutoracc.Name);
				rgTutor.setValue(2, newtutoracc.Name);
				optionInserted[2] = true;
			}
			else {
				std::cout << "Error: Please enter information for Option 2 first.\n";
				_getch();
			}
			break;
		case 4:
			if (optionInserted[2] == true) {
				std::cout << "\nInsert Phone Number (eg: 019#######) : ";
				std::cin >> newtutoracc.Phone_Number;

				if (std::regex_match(newtutoracc.Phone_Number, pattern2))
				{
					if (newtutoracc.registeredPN() == true)
					{
						std::cout << "\nThis Phone Number already registered. Try Again\n";
						_getch();
					}
					else if (newtutoracc.registeredPN() == false)
					{
						rgTutor.setValue(3, newtutoracc.Phone_Number);
						optionInserted[3] = true;
					}
				}
				else
				{
					std::cout << "Invalid phone number format. Please enter a valid 10-digit number: ";
					_getch();
				}
			}
			else {
				std::cout << "Error: Please enter information for Option 3 first.\n";
				_getch();
			}
			break;
		case 5: // kene enter dulu baru elok like watehel
			if (optionInserted[3] == true) 
			{
				system("cls");
				std::cout << " ****************************\nLIST OF SUBJECT(S)\n *****************************\n\n";
				std::cout << "-------------------------------------------------------------------------\n";
				std::cout << "|" << std::setw(35) << "Subject Name" << "|" << std::setw(35) << "Tutor In Charge" << "|\n";
				std::cout << "-------------------------------------------------------------------------\n";

				for (int i = 0; i < sub.size(); i++) {
					if (sub[i].Category_Age == 16) {
						std::cout << "|" << std::setw(35) << sub[i].Name << "|" << std::setw(35) << sub[i].TutorID << "|\n";
						std::cout << "-------------------------------------------------------------------------\n";

						subName.push_back(sub[i].Name);
					}
				}

				std::cout << "\n\nNOTE : PLEASE CHOOSE FOR NONE TUTOR IN CHARGE ONLY. YOU ALSO WILL BE TEACHING FOR FORM 4 AND FORM 5 STUDENT\n\nInsert Subject Experties ( Please Enter only 1 of the Subject Name ) :";
				cin.ignore();
				do {
					std::cout << "\nSubject Name:";
					getline(std::cin, newtutoracc.Subject_Experties);
					std::transform(newtutoracc.Subject_Experties.begin(), newtutoracc.Subject_Experties.end(), newtutoracc.Subject_Experties.begin(), ::toupper); // convert lowercase to upper case
					subject.TutorID = newtutoracc.TutorID;

					auto it = std::find(subName.begin(), subName.end(), newtutoracc.Subject_Experties);
					if (it != subName.end()) {// found
						subject.Name = newtutoracc.Subject_Experties;
						if (subject.assignedSubject() == true)
						{
							rgTutor.setValue(4, newtutoracc.Subject_Experties);
							optionInserted[4] = true;
							break;
						}
						else if (subject.assignedSubject() == false)
						{
							std::cout << "\n\nSubject Name has a tutor assigned.\n";
							_getch();
						}
					}
					else {
						std::cout << "\n\nSubject Name not found. Try Again.";
						_getch();
					}

				} while (true);
			}
			else {
				std::cout << "error: please enter information for option 4 first.\n";
				_getch();
			}
			break;
		case 6:
			if (optionInserted[4] == true) {
				std::cout << "\nInsert Available Tutoring Date (FORMAT: YYYY-MM-DD):";
				std::cin >> newtutoracc.Available_Tutoring_Date;
				if (std::regex_match(newtutoracc.Available_Tutoring_Date, datePattern)) {
					rgTutor.setValue(5, newtutoracc.Available_Tutoring_Date);
					optionInserted[5] = true;
				}
				else {
					std::cout << "Invalid date format. Please enter the date in YYYY-MM-DD format." << std::endl;
					_getch();
				}
			}
			else {
				std::cout << "Error: Please enter information for Option 5 first.\n";
			}
			break;
		case 7:
			if (optionInserted[5] == true) {
				newtutoracc.AdminID = "A12345";
				newtutoracc.insert();
				std::cout << "\n\nREGISTRATION IS SUCCESSFULLY COMPLETE.\nREDIRECTING YOU BACK TO MAIN MENU.\n";
				system("pause");
				main();
				break;
			}
			else {
				std::cout << "Error: Please enter information for Option 6 first.\n";
				_getch();
				break;
			}
		case 8:
			main();
			break;
		default:
			std::cout << "Invalid number. Try again.";
			break;
		}
	}
}
void loginMenu()
{
	menu loginMenu;
	loginMenu.header = "*************************************\nLOGIN MENU\n*************************************\nChoose your category to login.\n";
	loginMenu.addOption("Student");
	loginMenu.addOption("Tutor");
	loginMenu.addOption("Admin");
	loginMenu.addOption("Press 4 to go back.");

	while (1) {
		switch (loginMenu.prompt())
		{
		case 1:
			loginStudent();
			break;
		case 2:
			loginTutor();
			break;
		case 3:
			loginAdmin();
			break;
		case 4:
			main();
			break;
		default:
			break;
		}
	}
}
void loginStudent()
{
	menu loginStud;
	loginStud.header = "*************************************\nSTUDENT LOGIN SECTION\n*************************************\nFill in the information.\n";
	loginStud.addOption("StudentID");
	loginStud.addOption("Student Password");
	loginStud.addOption("Login");
	loginStud.addOption("Back");

	StudAccount stud;
	std::string hide;
	int i = 0;

	while (1) {
		switch (loginStud.prompt())
		{
		case 1:
			std::cout << "\nInsert Student ID:";
			std::cin >> stud.StudentID;
			loginStud.setValue(0, stud.StudentID);
			break;
		case 2:
			std::cout << "\nInsert Student Password:";
			char ch;
			hide = ""; // reset the display password
			stud.StudentPass = ""; // reset the actual password
			while ((ch = _getch()) != 13) // 13 is the ASCII code for Enter key
			{
				if (ch == '\b') // Check if the input is a backspace
				{
					// Handle backspace: remove the last character from 'StudentPass'
					if (!stud.StudentPass.empty()) {
						stud.StudentPass.pop_back();
						hide.pop_back();
						std::cout << "\b \b"; // Move the cursor back and overwrite with a space
					}
				}
				else {
					stud.StudentPass += ch;
					hide += '*';
					std::cout << '*';
				}
			}
			loginStud.setValue(1, hide);
			break;
		case 3:
			if (stud.login()) {
				std::cout << "\n\nYou Have Logged In!\n\nREDIRECTING YOU TO STUDENT HOME MENU\n";
				system("pause");
				studhome(stud);
			}
			else {
				std::cout << "\nInvalid Login";
				i++;
				if (i > 5)
				{
					std::cout << "\n\n*************IF YOU HAVING TROUBLE FOR THIS LOG IN, CONTACT ADMIN.*************\n\n";
				}
				_getch();
			}
			break;
		case 4:
			loginMenu();
			break;
		default:
			break;
		}
	}
}

void loginTutor()
{
	menu loginTutor;
	loginTutor.header = "*************************************\nTUTOR LOGIN SECTION\n*************************************\nFill in the information.\n";
	loginTutor.addOption("Tutor ID");
	loginTutor.addOption("Tutor Password");
	loginTutor.addOption("Login");
	loginTutor.addOption("Back");

	int i = 0;
	TutorAccount tutor;
	std::string hide;

	while (1) {
		switch (loginTutor.prompt())
		{
		case 1:
			std::cout << "\nInsert Tutor ID:";
			std::cin >> tutor.TutorID;
			loginTutor.setValue(0, tutor.TutorID);
			break;
		case 2:
			std::cout << "\nInsert Tutor Password:";
			char ch;
			hide = ""; // reset the display password
			tutor.TutorPass = ""; // reset the actual password
			while ((ch = _getch()) != 13) // 13 is the ASCII code for Enter key
			{
				if (ch == '\b') // Check if the input is a backspace
				{
					// Handle backspace: remove the last character from 'TutorPass'
					if (!tutor.TutorPass.empty()) {
						tutor.TutorPass.pop_back();
						hide.pop_back();
						std::cout << "\b \b"; // Move the cursor back and overwrite with a space
					}
				}
				else {
					tutor.TutorPass += ch; // store the actual password
					hide += '*'; // store * based on how many character in the password
					std::cout << '*';
				}
			}
			loginTutor.setValue(1, hide); // output the display password containing only * according to how many character in the actual password
			break;
		case 3:
			if (tutor.login()) {
				std::cout << "\n\nYou Have Logged In!\n\nREDIRECTING YOU TO TUTOR HOME MENU\n";
				system("pause");
				tutorhome(tutor);
			}
			else {
				std::cout << "\nInvalid Login";
				i++;
				if (i > 5)
				{
					std::cout << "\n\n*************IF YOU HAVING TROUBLE FOR THIS LOG IN, CONTACT ADMIN.*************\n\n";
				}
				_getch();
			}
			break;
		case 4:
			loginMenu();
			break;
		default:
			break;
		}
	}
}

void loginAdmin()
{
	menu loginAdmin;
	loginAdmin.header = "*************************************\nADMIN LOGIN SECTION\n*************************************\nFill in the information.\n";
	loginAdmin.addOption("Admin ID");
	loginAdmin.addOption("Admin Password");
	loginAdmin.addOption("Login");
	loginAdmin.addOption("Back");

	Admin admin;
	std::string hide;

	while (1) {
		switch (loginAdmin.prompt())
		{
		case 1:
			admin.AdminID = "";
			std::cout << "\nInsert Admin ID:";
			std::cin >> admin.AdminID;
			loginAdmin.setValue(0, admin.AdminID);
			break;
		case 2:
			admin.AdminPass = "";
			std::cout << "\nInsert Admin Password:";
			char ch;
			hide = ""; // reset the display password
			admin.AdminPass = ""; // reset the actual password
			while ((ch = _getch()) != 13) // 13 is the ASCII code for Enter key
			{
				if (ch == '\b') // Check if the input is a backspace
				{
					// Handle backspace: remove the last character from 'StudentPass'
					if (!admin.AdminPass.empty()) {
						admin.AdminPass.pop_back();
						hide.pop_back();
						std::cout << "\b \b"; // Move the cursor back and overwrite with a space
					}
				}
				else {
					admin.AdminPass += ch;
					hide += '*';
					std::cout << '*';
				}
			}

			loginAdmin.setValue(1, hide);
			break;
		case 3:
			if (admin.login()) {
				std::cout << "\n\nYou Have Logged In!\nREDIRECTING YOU TO ADMIN HOME MENU\n";
				system("pause");
				adminhome(admin);
			}
			else {
				std::cout << "\nInvalid Login";
				_getch();
			}
			break;
		case 4:
			loginMenu();
			break;
		default:
			break;
		}
	}
}
void studhome(StudAccount stud) {
	menu studmenu;
	studmenu.header = "*************************************\nSTUDENT HOME MENU\n*************************************\n\n";
	studmenu.addOption("View/Edit Profile");
	studmenu.addOption("View Enrolled Subject");
	studmenu.addOption("Enrollment Subject");
	studmenu.addOption("Fees Payment");
	studmenu.addOption("Make a Feedback");
	studmenu.addOption("Unroll Subject");
	studmenu.addOption("Logout");


	while (1) {
		studmenu.header = "**************************************************\n     Welcome " + stud.Name + "      \n""**************************************************\n\n";
		switch (studmenu.prompt())
		{
		case 1:
			studprofile(stud);
			break;
		case 2:
			timeTable(stud);
			break;
		case 3:
			enrollment(stud);
			break;
		case 4:
			payment(stud);
			break;
		case 5:
			feedback(stud);
			break;
		case 6:
			UnrollSubject(stud);
			break;
		case 7:
			loginStudent();
			break;
		default:
			break;
		}
	}
}

void tutorhome(TutorAccount tutor) {

	menu tutormenu;
	tutormenu.header = "*************************************\nTUTOR HOME MENU\n*************************************\n";
	tutormenu.addOption("View Profile");
	tutormenu.addOption("View Student List & Feedback");
	tutormenu.addOption("Logout");
	while (1) {
		tutormenu.header = "********************************\n     Welcome " + tutor.Name + "\n********************************\n\n";
		switch (tutormenu.prompt())
		{
		case 1:
			tutorprofile(tutor);
			break;
		case 2:
			studentlist(tutor);
			break;
		case 3:
			loginTutor();
			break;
		default:
			break;
		}
	}
}
void adminhome(Admin admin) {

	Enrollment enroll;

	menu adminmenu;
	adminmenu.header = "*************************************\nADMIN HOME MENU\n*************************************\n";
	adminmenu.addOption("User Management");
	adminmenu.addOption("Subject Management");
	adminmenu.addOption("View Feedback of Tutor");
	adminmenu.addOption("Logout");

	std::string tutorID;
	char more = 'y';

	while (1) {
		switch (adminmenu.prompt())
		{
		case 1:
			manageUser(admin);
			break;
		case 2:
			manageSubject(admin);
			break;
		case 3:
			do {
				system("cls");
				std::cout << "*************************************\nVIEW TUTOR FEEDBACK SECTION\n*************************************\n\n";
				std::cout << "Enter TutorID :";
				std::cin >> tutorID;

				enroll.getFeedback(tutorID);

				std::cout << "\n\nView Other Tutor? (Y/N) :";
				std::cin >> more;

			} while (more == 'y' || more == 'Y');
			break;
		case 4:
			loginAdmin();
			break;
		default:
			break;
		}
	}
}

StudAccount studprofile(StudAccount stud) {

	StudAccount temp = stud; // copy the object
	char again;

	menu profileMenu;
	profileMenu.header = "Your profile";
	profileMenu.addOption("Fullname");
	profileMenu.addOption("Phone Number");
	profileMenu.addOption("Edit & Save");
	profileMenu.addOption("Back");

	std::regex pattern2("^01\\d{8}$"); // validate the format of the entered phone number

	while (1) {
		profileMenu.setValue(0, temp.Name);
		profileMenu.setValue(1, temp.Phone_Number);

		switch (profileMenu.prompt())
		{
		case 3:
			std::cout << "Insert Fullname (BASED ON IC):";
			std::cin.ignore();
			getline(std::cin, temp.Name);

			again = 'y';
			do { 
				std::cout << "\nInsert Phone Number (eg: 019#######) : ";
				std::cin >> temp.Phone_Number;
				if (std::regex_match(temp.Phone_Number, pattern2)) { // check format
					if (temp.registeredPN() == true && stud.Phone_Number == temp.Phone_Number) // exist and its dia punya
					{
						break;
					}
					else if (temp.registeredPN() == true && stud.Phone_Number != temp.Phone_Number)
					{
						std::cout << "\nThis Phone Number already registered. Try Again (Y/N):";
						std::cin >> again;
					}
				}
				else {
					std::cout << "Invalid Phone Number. Please enter a valid 10-digit number without dash. Try Again? (Y/N) : " << std::endl;
					std::cin >> again;
				}
			} while (again == 'y' || again == 'Y');

			stud = temp;
			stud.update();
			std::cout << "\n\nSUCCESSFULLY UPDATE INFORMATION\nREDIRECTING YOU BACK TO HOME MENU\n";
			system("pause");
			studhome(stud);
			break;
		case 4:
			return stud;
			break;
		default:
			std::cout << "You can choose options 4 or 5 only.";
			_getch();
			break;
		}
	}
}

TutorAccount tutorprofile(TutorAccount tutor) {

	TutorAccount temp = tutor; // copy the object

	Subject subject;
	std::vector<Subject> sub;
	std::vector<string>subName;

	menu profileMenu;
	profileMenu.header = "Your profile";
	profileMenu.addOption("Fullname");
	profileMenu.addOption("Phone Number");
	profileMenu.addOption("Subject Experties");
	profileMenu.addOption("Available Tutoring Date");
	profileMenu.addOption("Edit profile");
	profileMenu.addOption("Save");
	profileMenu.addOption("Back");

	char again;
	int opt = 0;
	bool hasNewSubject = false;
	std::regex pattern2("^01\\d{8}$"); // validate the format of the entered phone number
	std::regex datePattern("^\\d{4}-\\d{2}-\\d{2}$"); // validate the format of the entered date



	while (1) {
		profileMenu.setValue(0, temp.Name);
		profileMenu.setValue(1, temp.Phone_Number);
		profileMenu.setValue(2, temp.Subject_Experties);
		profileMenu.setValue(3, temp.Available_Tutoring_Date);


		switch (profileMenu.prompt())
		{
		case 5:
			std::cout << "\n\nChoose the number of your profile to edit :";
			std::cin >> opt;
			if (opt == 1)
			{
				std::cout << "Insert Fullname:";
				std::cin.ignore();
				getline(std::cin, temp.Name);
				profileMenu.setValue(0, temp.Name);
			}
			else if (opt == 2)
			{
				again = 'y';
				do {
					std::cout << "\nInsert Phone Number (eg: 019#######) : ";
					std::cin >> temp.Phone_Number;
					if (std::regex_match(temp.Phone_Number, pattern2)) { // check format
						if (temp.registeredPN() == true) // exist
						{
							std::cout << "\nThis Phone Number already registered. Try Again (Y/N) :";
							std::cin >> again;
						}
						else
						{
							profileMenu.setValue(1, temp.Phone_Number);
							break;
						}
					}
					else {
						std::cout << "Invalid Phone Number. Please enter a valid 10-digit number without dash: " << std::endl;
						_getch();
					}
				} while (again == 'y' || again == 'Y');
			}
			else if (opt == 3)
			{
				again = 'y';
				subName = {};
				sub = subject.listSubject();
				if (tutor.Subject_Experties.empty()) //not none string
				{
					system("cls");
					std::cout << "LIST OF SUBJECT(S)\n\n";
					std::cout << std::setw(35) << "Subject Name" << "|" << std::setw(35) << "Tutor In Charge" << "|\n";
					std::cout << std::string(75, '-') << "\n"; // Line separator

					for (int i = 0; i < sub.size(); i++) {
						if (sub[i].Category_Age == 16) {
							std::cout << std::setw(35) << sub[i].Name << "|" << std::setw(35) << sub[i].TutorID << "|\n";
							subName.push_back(sub[i].Name);
						}
					}

					std::cout << "\n\nNOTE : PLEASE CHOOSE FOR NONE TUTOR IN CHARGE ONLY. YOU ALSO WILL BE TEACHING FOR FORM 4 AND FORM 5 STUDENT\n\nInsert Subject Experties ( Please Enter only 1 of the Subject Name ) :";

					do {
						std::cin.ignore();
						std::cin.clear();
						std::cout << "\nSubject Name:";
						getline(std::cin, temp.Subject_Experties);
						std::transform(temp.Subject_Experties.begin(), temp.Subject_Experties.end(), temp.Subject_Experties.begin(), ::toupper);
						subject.TutorID = temp.TutorID;

						auto it = std::find(subName.begin(), subName.end(), temp.Subject_Experties);

						if (it != subName.end()) {// found
							if (subject.assignedSubject() == true)
							{
								profileMenu.setValue(2, temp.Subject_Experties);
								hasNewSubject = true;
								break;
							}
							else if (subject.assignedSubject() == false)
							{
								std::cout << "\n\nSubject Name has a tutor assigned.Try Again (Y/N) :";
								std::cin >> again;
								_getch();
							}
						}
						else {
							std::cout << "\n\nSubject Name not found.\n";
							_getch();
						}

					} while (again == 'y' || again == 'Y');
				}
				else
				{
					std::cout << "\n\nTo change subject experties, please contact admin.\n\n";
					_getch();
				}
			}
			else if (opt == 4)
			{
				if ( !(tutor.Subject_Experties.empty()) || hasNewSubject == true)
				{
					std::cout << "\nInsert Available Tutoring Date (FORMAT: YYYY-MM-DD):";
					std::string date;
					std::cin >> date;
					if (std::regex_match(date, datePattern)) {
						temp.Available_Tutoring_Date = date;
						profileMenu.setValue(3, temp.Available_Tutoring_Date);
					}
					else {
						std::cout << "Invalid date format. Please enter the date in YYYY-MM-DD format." << std::endl;
						_getch();
					}
				}
				else
				{
					std::cout << "\n\nYou dont assign yourself into any of the subject available.\nPlease assign yourself first.\n";
					_getch();
				}
			}
			else
			{
				std::cout << "\n\nYou choose the wrong option.\n\n";
				_getch();
			}
			break;
		case 6:
			tutor = temp;
			tutor.update();
			std::cout << "\n\nSUCCESSFULLY UPDATE INFORMATION\nREDIRECTING YOU BACK TO HOME MENU\n";
			system("pause");
			tutorhome(tutor);
			break;
		case 7:
			return tutor;
			break;
		default:
			std::cout << "You can choose options 5 or 6";
			_getch();
			break;
		}
	}
}

void manageUser(Admin admin) { // hanya boleh remove student yang tak pernah enroll or do payment , especially payment
	menu managemenu;
	managemenu.header = "USER MANAGEMENT SECTION\n*********************\n\nCHOOSE THE CATEGORY BELOW:\n";
	managemenu.addOption("Student");
	managemenu.addOption("Tutor");
	managemenu.addOption("Press 3 to go back.");

	char ans = 'y';
	int opt = 0, act = 0;
	StudAccount stud;
	std::vector<StudAccount> students = stud.listStudent();
	TutorAccount tutor;
	std::vector<TutorAccount> tutors;


	while (1) {

		switch (managemenu.prompt())
		{
		case 1: // student
			do
			{
				system("cls");
				std::cout << "LIST OF STUDENTS\n*******************************\nList of all students:\n\n";
				std::cout << "--------------------------------------------------------------------------------------------------------" << endl;
				std::cout << "|" << setw(13) << "StudentID" << "|" << setw(35) << "Name" << "|" << setw(10) << "Age" << "|" << setw(20) << "Phone Number" << "|" << setw(20) << "Account Status" << "|" << endl << "--------------------------------------------------------------------------------------------------------" << endl;

				for (int i = 0; i < students.size(); i++) {
					std::cout << "|" << setw(13) << students[i].StudentID << "|" << setw(35) << students[i].Name << "|" << setw(10) << students[i].Age << "|" << setw(20) << students[i].Phone_Number << "|" << setw(20) << students[i].AccountStatus << "|" << endl;
					std::cout << "--------------------------------------------------------------------------------------------------------" << endl;
				}

				std::cout << endl;
				std::cout << "Please Choose:\n";
				std::cout << "1.Deactive/Reactive Student Account\n2.Remove student account\n3.Back\n";
				std::cout << "Option :";
				std::cin >> opt;
				if (opt == 1) // deactive or reactive
				{
					std::cout << "\nPlease Choose:\n1.Deactive\n2.Reactive\n";
					std::cout << "Option :";
					std::cin >> act;
					if (act == 1) // deactive
					{
						std::cout << "\n\nEnter StudentID:";
						std::cin >> stud.StudentID;
						if (stud.deactive() == true)
						{
							std::cout << "\n\nSUCCESSFULLY DEACTIVATED\n\n";
							_getch();
							std::cout << "\nDo you wish to continue? (Y/N) : ";
							std::cin >> ans;
						}
						else if(stud.deactive() == false)
						{
							std::cout << "\n\nStudent ID does not exist in the database\n\n";
							_getch();
							std::cout << "\nDo you wish to continue? (Y/N) : ";
							std::cin >> ans;
						}
					}
					else if (act == 2) // reactive
					{
						std::cout << "\n\nEnter StudentID:";
						std::cin >> stud.StudentID;
						if (stud.reactive() == true)
						{
							std::cout << "\n\nSUCCESSFULLY REACTIVATED\n\n";
							_getch();
							std::cout << "\nDo you wish to continue? (Y/N) : ";
							std::cin >> ans;
						}
						else if (stud.reactive() == false)
						{
							std::cout << "\n\nStudent ID does not exist in the database\n\n";
							_getch();
							std::cout << "\nDo you wish to continue? (Y/N) : ";
							std::cin >> ans;
						}
					}
					else
					{
						std::cout << "\nInvalid Option.\nContinue? (Y/N) :";
						std::cin >> ans;
					}
				}
				else if (opt == 2) // remove
				{
					std::cout << "\n\nEnter StudentID:";
					std::cin >> stud.StudentID;
					if (stud.remove() == true)
					{
						std::cout << "\nSUCCESSFULLY DELETE\n\n";
						_getch();
						std::cout << "\nDo you wish to continue? (Y/N) : ";
						std::cin >> ans;
					}
					else if (stud.remove() == false)
					{
						std::cout << "\nStudentID does not exist in the database.\n\n";
						_getch();
						std::cout << "\nDo you wish to continue? (Y/N) : ";
						std::cin >> ans;
					}
				}
				else if (opt == 3) // Go back
				{
					return;
				}
				else
				{
					std::cout << "\n\nInvalid Option\n\n";
					_getch();
				}
			} while (ans == 'Y' || ans == 'y');
			adminhome(admin);
			break;
		case 2: // tutor
			do
			{
				tutors = tutor.listTutor();
				system("cls");
				std::cout << "LIST OF TUTOR(S)/REMOVE\n*******************************\nList of all tutor:\n\n";
				std::cout << "------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
				std::cout << "|" << setw(13) << "TutorID" << "|" << setw(35) << "Name" << "|" << setw(35) << "Subject Experties" << "|" << setw(20) << "Phone Number" << "|" << setw(20) << "Tutoring Date" << "|" << setw(20) << "Account Status" << "|" << endl << "------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;

				for (int i = 0; i < tutors.size(); i++) {
					std::cout << "|" << setw(13) << tutors[i].TutorID << "|" << setw(35) << tutors[i].Name << "|" << setw(35) << tutors[i].Subject_Experties << "|" << setw(20) << tutors[i].Phone_Number << "|" << setw(20) << tutors[i].Available_Tutoring_Date << "|" << setw(20) << tutors[i].AccountStatus << "|" << endl;
					std::cout << "------------------------------------------------------------------------------------------------------------------------------------------------------\n";
				}
				std::cout << endl;
				std::cout << "Please Choose:\n";
				std::cout << "1.Deactive/Reactive Tutor Account\n2.Remove tutor account\n3.Go Back\n";
				std::cout << "Option :";
				std::cin >> opt;
				if (opt == 1) // deactive or reactive
				{
					std::cout << "\nPlease Choose:\n1.Deactive\n2.Reactive\n";
					std::cout << "Option :";
					std::cin >> act;
					if (act == 1) // deactive
					{
						std::cout << "\n\nEnter TutorID:";
						std::cin >> tutor.TutorID;
						if (tutor.deactive() == true)
						{
							std::cout << "\n\nSUCCESSFULLY DEACTIVE\n\n";
							_getch();
							std::cout << "\nDo you wish to continue? (Y/N) : ";
							std::cin >> ans;
						}
						if (tutor.deactive() == false)
						{
							std::cout << "\n\nTutor ID does not exist in database\n\n";
							_getch();
							std::cout << "\nDo you wish to continue? (Y/N) : ";
							std::cin >> ans;
						}
					}
					else if (act == 2) // reactive
					{
						std::cout << "\n\nEnter TutorID:";
						std::cin >> tutor.TutorID;
						if (tutor.reactive() == true)
						{
							std::cout << "\n\nSUCCESSFULLY REACTIVE\n\n";
							_getch();
							std::cout << "\nDo you wish to continue? (Y/N) : ";
							std::cin >> ans;
						}
						if (tutor.deactive() == false)
						{
							std::cout << "\n\nTutor ID does not exist in database\n\n";
							_getch();
							std::cout << "\nDo you wish to continue? (Y/N) : ";
							std::cin >> ans;
						}
					}
					else
					{
						std::cout << "\nInvalid Option.\nContinue? (Y/N) :";
						std::cin >> ans;
					}
				}
				else if (opt == 2) // remove
				{
					std::cout << "\n\nEnter TutorID:";
					std::cin >> tutor.TutorID;
					if (tutor.remove() == true)
					{
						std::cout << "\n\nSUCCESSFULLY REMOVE\n\n";
						_getch();
						std::cout << "\nDo you wish to continue? (Y/N) : ";
						std::cin >> ans;
					}
					if (tutor.remove() == false)
					{
						std::cout << "\n\nTutor ID does not exist in database\n\n";
						_getch();
						std::cout << "\nDo you wish to continue? (Y/N) : ";
						std::cin >> ans;
					}
				}
				else if (opt == 3) // Go back
				{
					return;
				}
				else
				{
					std::cout << "\n\nInvalid Option\n\n";
					_getch();
				}
			} while (ans == 'Y' || ans == 'y');
			adminhome(admin);
			break;
		case 3:
			return;
			break;
		default:
			std::cout << "You can choose options 1 or 2 or 3.";
			_getch();
			break;
		}
	}
}
void manageSubject(Admin admin) {

	menu managesub;
	managesub.header = "SUBJECT MANAGEMENT SECTION\n*********************\n\nPlease choose option below : \n";
	managesub.addOption("Add Subject");
	managesub.addOption("Remove Subject");
	managesub.addOption("Enter 3 to go back.");

	int choice = 0;
	char opt = '0', more ='y', back;
	std::string hold;

	Subject sub;
	std::vector<Subject> subject;
	std::vector<string> subName;
	std::vector<string>subID;

	char conti;
	bool Unique = false;
	bool valid = false;
	bool found = false;
	std::regex pattern3("SB\\d{2}");// Validate the format of the entered subject ID


	while (1) {

		switch (managesub.prompt())
		{
		case 1:
			do {
				subName = {};
				subject = sub.listSubject();
				system("cls");
				std::cout << "ADD SUBJECT SECTION\n*************************\n";
				std::cout << "LIST OF SUBJECT(S)\n*******************************\n\n\n";
				std::cout << "----------------------------------------------------------------------------------------------------------------------------------------------\n";
				std::cout << "|" << setw(10) << "SubjectID" << "|" << setw(35) << "Name" << "|" << setw(20) << "Fees" << "|" << setw(20) << "Quota" << "|" << setw(20) << "Category Age" << "|" << setw(30) << "Tutor In Charge(Tutor ID)" << "|" << endl << "---------------------------------------------------------------------------------------------------------------------------------------------" << endl;

				for (int i = 0; i < subject.size(); i++) {
					std::cout << "|" << setw(10) << subject[i].SubjectID << "|" << setw(35) << subject[i].Name << "|" << setw(20) << subject[i].Fees << "|" << setw(20) << subject[i].Quota << "|" << setw(20) << subject[i].Category_Age << "|" << setw(30) << subject[i].TutorID << "|" << endl;
					std::cout << "----------------------------------------------------------------------------------------------------------------------------------------------\n";
					subName.push_back(subject[i].Name);
					subID.push_back(subject[i].SubjectID);
				}
				std::cout << endl;
				std::cout << "1.Add Subject\n2.Go Back\n";
				std::cout << "Option :";
				std::cin >> opt;
				if (opt == '1') // Add subject
				{
					std::cout << "\n\nNOTE: FOR ONE SUBJECT, IT HAS 2 DIFFERENT AGE WHICH IS FOR 16 AND 17.";

					do {
						std::cout << "\nInsert Subject Name:";
						std::cin.ignore();
						getline(std::cin, sub.Name);
						std::transform(sub.Name.begin(), sub.Name.end(), sub.Name.begin(), ::toupper); // convert lowercase to upper case

						auto it = std::find(subName.begin(), subName.end(), sub.Name);

						if (it != subName.end()) // found meaning already exist
						{
							std::cout << "\nSubject Name already exist. Continue (Y/N) : \n";
							std::cin >> conti;
							if (conti == 'y' || conti == 'Y')
							{
								continue;
							}
							else
							{
								adminhome(admin);
							}
						}
						else // not found , not exists yet
						{
							break;
						}
					} while (true);

					for (int age = 16; age <= 17; age++)
					{
						std::cout << "\nFOR AGE : " << age;

						std::cout << "\nInsert Subject ID (Format : SB## where # is the random number you will enter) :";
						do {
							std::cout << "\nSubject ID: ";
							std::cin >> sub.SubjectID;
							if (std::regex_match(sub.SubjectID, pattern3)) {

								auto it = std::find(subID.begin(), subID.end(), sub.SubjectID);

								if (it != subID.end() || sub.SubjectID == hold) // found meaning already exist
								{
									std::cout << "\nSubject ID already exist. Continue (Y/N) : \n";
									std::cin >> conti;
									if (conti == 'y' || conti == 'Y')
									{
										continue;
									}
									else
									{
										adminhome(admin);
									}
								}
								else // not found , not exists yet
								{
									std::cout << "\nInsert Subject Fees per month : RM";
									std::cin >> sub.Fees;

									sub.Category_Age = age;
									sub.AdminID = admin.AdminID;
									sub.insert();
									std::cout << "\n\nNEW SUBJECT HAS BEEN SUCCESSFULLY ADDED\n\n";
									hold = sub.SubjectID;
									break;
								}
							}
							else {
								std::cout << "\nInvalid SubjectID format. Please enter according to the format.\n";
							}
						} while (true);
					}
					std::cout << "Do you wish to add more? (Y/N) : ";
					std::cin >> more;
				}
				else if (opt == '2')
				{
					return;
				}
				else
				{
					std::cout << "\n\nInvalid Option. Try Again.\n\n";
					_getch();
				}

			} while (more == 'Y' || more == 'y');
			manageSubject(admin);
			break;
		case 2:
			do {
				subject = sub.listSubject();
				system("cls");
				std::cout << "REMOVE SUBJECT SECTION\n*************************\n";
				std::cout << "LIST OF SUBJECT(S)\n*******************************\n\n";
				std::cout << "----------------------------------------------------------------------------------------------------------------------------------------------\n";
				std::cout << "|" << setw(10) << "SubjectID" << "|" << setw(35) << "Name" << "|" << setw(20) << "Fees" << "|" << setw(20) << "Quota" << "|" << setw(20) << "Category Age" << "|" << setw(30) << "Tutor In Charge(Tutor ID)" << "|" << endl << "---------------------------------------------------------------------------------------------------------------------------------------------" << endl;

				for (int i = 0; i < subject.size(); i++) {
					std::cout << "|" << setw(10) << subject[i].SubjectID << "|" << setw(35) << subject[i].Name << "|" << setw(20) << subject[i].Fees << "|" << setw(20) << subject[i].Quota << "|" << setw(20) << subject[i].Category_Age << "|" << setw(30) << subject[i].TutorID << "|" << endl;
					std::cout << "----------------------------------------------------------------------------------------------------------------------------------------------\n";
				}
				std::cout << endl;
				std::cout << "1.Remove Subject\n2.Go Back\n";
				std::cout << "Option :";
				std::cin >> opt;
				if (opt == '1')
				{
					cin.ignore();
					std::cout << "\n\nInsert SubjectID accordingly (refer table) :";
					std::cout << "\nSubject ID : ";
					getline(std::cin, sub.SubjectID);
					std::transform(sub.SubjectID.begin(), sub.SubjectID.end(), sub.SubjectID.begin(), ::toupper); // convert lowercase to upper cas

					sub.remove();
					_getch();
					std::cout << "Do you wish to remove more? (Y/N) : ";
					std::cin >> more;
				}
				else if (opt == '2')
				{
					return;
				}
				else
				{
					std::cout << "\n\nInvalid Option. Try Again.\n\n";
					_getch();
				}

			} while (more == 'Y' || more == 'y');
			manageSubject(admin);
			break;
		case 3:
			adminhome(admin);
			break;
		default:
			std::cout << "You can choose options 1 or 2 or 3.";
			_getch();
			break;
		}
	}
}
void enrollment(StudAccount stud) {

	TutorAccount tutor;
	Subject sub;
	Enrollment enroll;

	std::vector<Subject> subject;
	std::vector<string> choices;
	std::regex pattern3("SB\\d{2}");// Validate the format of the entered subject ID
	std::vector<string> findSubject;
	std::string choice;
	char more = 'y';

	subject = sub.listSubject();
	for (int i = 0; i < subject.size(); i++)
	{
		if (subject[i].Category_Age == 16 && subject[i].TutorID != "NONE" && stud.Age == 16)
		{
			findSubject.push_back(subject[i].SubjectID);
		}
		if (subject[i].Category_Age == 17 && subject[i].TutorID != "NONE" && stud.Age == 17)
		{
			findSubject.push_back(subject[i].SubjectID);
		}
	}
	sub.displaySubject(stud.Age);

	int opt;
	std::cout << "\n\nChoose:\n1.Enroll\n2.Back\nOption:";
	std::cin >> opt;

	if (opt == 1)
	{
		std::cout << "\n\nYOUR AGE IS : " << stud.Age;
		std::cout << "\n\nAFTER YOU DONE CHOOSING A SUBJECT TO ENROLL, YOU CAN ENTER N TO GO TO EDIT SECTION(REMOVE CHOSEN SUBJECT)";
		std::cout << "\n\nPlease enter the SubjectID that you want to enroll into: ";
		choices = {};

		do
		{
			std::vector<bool> validation(4, true); // validation
			std::cin.clear();
			std::cin.ignore();
			std::cout << "\nEnter SubjectID: ";
			std::cin >> choice;
			std::transform(choice.begin(), choice.end(), choice.begin(), ::toupper); // convert lowercase to upper case
			if (std::regex_match(choice, pattern3)) // first check is subject id format
			{
				auto it = std::find(findSubject.begin(), findSubject.end(), choice);

				if (it != findSubject.end()) // found
				{
					if (sub.getSubAge(choice) != stud.Age) // tapi bukan age dia
					{
						validation[0] = false;
						std::cout << "\nThis subject is not the list for " << stud.Age << " years old. Try another.\n";
						_getch();
						std::cout << "Continue? (Y/N) : ";
						std::cin >> more;
					}
				}
				else // not found
				{
					validation[0] = false;
					std::cout << "\nThis subject is not the list for " << stud.Age << " years old. Try another. \n";
					_getch();
					std::cout << "Continue? (Y/N) : ";
					std::cin >> more;
				}

				if (enroll.alreadyEnrolled(stud.StudentID, choice) == true) // check if already enrolled
				{
					validation[1] = false;
					std::cout << "\nYou already enrolled into this subject, Try Another. \n";
					_getch();
					std::cout << "Continue? (Y/N) : ";
					std::cin >> more;
				}
				if (sub.fullSubject(choice) == true && sub.getSubAge(choice) == stud.Age) // check if choice of subject is full , sb02 full and same with age
				{
					validation[2] = false;
					std::cout << "\nThis subject is full, Try Another. \n";
					_getch();
					std::cout << "Continue? (Y/N) : ";
					std::cin >> more;
				}

				bool alreadyChosen = false;
				for (int i = 0; i < choices.size(); i++) // to loop to check if its similar with chosen subject before
				{
					if (choice == choices[i])
					{
						alreadyChosen = true;
						validation[3] = false;
					}
				}
				if (alreadyChosen)
				{
					std::cout << "\nThis subject already chosen previously.\n";
					_getch();
					std::cout << "Continue? (Y/N) : ";
					std::cin >> more;
				}
				if (choices.size() <= 0) // nothing to be compare yet choices is zero
				{
					bool alreadyChosen = false;
					if (!alreadyChosen && std::all_of(validation.begin(), validation.end(), [](bool result) { return result; }))
					{
						choices.push_back(choice);
						std::cout << "\nSubject has added to the list.";
						std::cout << "\nEnroll more subject? (Y/N) :";
						std::cin >> more;
					}
				}
				else if (!alreadyChosen && std::all_of(validation.begin(), validation.end(), [](bool result) { return result; }))
				{
					choices.push_back(choice);
					std::cout << "\nSubject has added to the list.";
					std::cout << "\nEnroll more subject? (Y/N) :";
					std::cin >> more;
				}
			}
			else // wrong format and reset loop
			{
				std::cout << "\nInvalid SubjectID, Try Again\n";
				_getch();
				std::cout << "Continue? (Y/N) : ";
				std::cin >> more;
			}

		} while (more == 'Y' || more == 'y');
		
		if (choices.size() == 0)
		{
			studhome(stud);
		}

		do
		{
			system("cls");
			std::cout << "**************************\nCHOSEN SUBJECT\n**************************\nSubject ID	Subject Name\n";
			if (choices.size() == 0)
			{
				std::cout << "\n\nTHERE ARE NO SUBJECT IDs\n\n";
			}
			for (int i = 0; i < choices.size(); i++)
			{
				std::cout << "" << choices[i] << "		"<< sub.getSubName(choices[i]) << "\n";
			}

			char next;
			std::cout << "\nChoose Option:\n1.Remove Chosen Subject\n2.Proceed to payment(CONFIRM ENROLLMENT)\n3.Cancel/Exit\nInsert Option:";
			std::cin >> next;
			if (next == '1')
			{
				if (choices.size() == 0)
				{
					std::cout << "\n\nYou do not have any subjects to be paid.\n";
					_getch();
					std::cout << "Redirect you home menu.\n";
					system("pause");
					break;
				}

				std::string removeSub;
				std::cout << "\nEnter SubjectID to be remove :";
				std::cin >> removeSub;
				std::transform(removeSub.begin(), removeSub.end(), removeSub.begin(), ::toupper); // convert lowercase to upper case
				auto it = std::find(choices.begin(), choices.end(), removeSub);

				if (it != choices.end() && choices.size() > 0) // found
				{
					choices.erase(it);
					std::cout << "\nSuccesfully remove the chosen SubjectID!";
					_getch();
				}
				else
				{
					std::cout << "\nSubjectID is not in your chosen list. Continue? (Y/N) : ";
					_getch();
				}
			}
			else if (next == '2')
			{
				if (choices.size() > 0)
				{
					enroll.insert(stud.StudentID, choices);
					payment(stud);
					break;
				}
				else
				{
					std::cout << "\n\nYou do not have any chosen subjects.\nRedirect you back to home menu.\n";
					system("pause");
					studhome(stud);
				}
			}		
			else if (next == '3')
			{
				std::cout << "\n\nREDIRECTING YOU BACK TO HOME MENU\n";
				studhome(stud);
			}
			else
			{
				std::cout << "\n\nWrong Input\n\n";
			}
		} while(true);
	}
	else if (opt == 2)
	{
		return;
	}
	else
	{
		std::cout << "Wrong input";
		enrollment(stud);
	}
}

void payment(StudAccount stud) {
		menu manuPayment;
		manuPayment.header = "PAYMENT SECTION\n*********************\n\nPlease choose option below : \n";
		manuPayment.addOption("Pay Now (ONLINE BANKING)");
		manuPayment.addOption("Pay Later");

		Subject sub;
		Payment payment;

		std::string newID;
		std::vector<double> fees;
		std::vector<string> name;
		std::vector<StudAccount> students = stud.listSubjectUnpaid();
		std::vector<Subject> subjects = sub.listSubject();

		int Size = students.size();
		double sum = 0, pay = 0;
		bool found = false;


		while (1) {

			switch (manuPayment.prompt())
			{
			case 1:
				system("cls");
				std::cout << "----------------PAYMENT FOR UNPAID SUBJECT(S)-----------------\n\n";
				for (int i = 0; i < Size; i++) // size of students
				{
					for (int j = 0; j < subjects.size(); j++) // size of subjects
					{
						if (students[i].SubjectID == subjects[j].SubjectID) // if it matches
						{
							fees.push_back(subjects[j].Fees); // this will push back to fees vector so meaning index 0 both unpaid subject id and its fees respectively
							name.push_back(subjects[j].Name);// this will push back to name vector so meaning index 0 both unpaid subject id and its name respectively
						}
					}
				}
				std::cout << "LIST OF SUBJECT(S)\n*******************************\nList of all unpaid subjects:\n\n\n";
				std::cout << "---------------------------------------------------------------------" << endl;
				std::cout << "|" << setw(15) << "SubjectID" << "|" << setw(35) << "Name" << "|" << setw(15) << "Fees" << "|" << endl;
				std::cout << "---------------------------------------------------------------------" << endl;

				for (int i = 0; i < Size; i++) {
					std::cout << "|" << setw(15) << students[i].SubjectID << "|" << setw(35) << name[i] << "|" << setw(15) << fees[i] << "|" << endl;
					std::cout << "---------------------------------------------------------------------" << endl;
					sum += fees[i];
				}

				if (students.size() == 0)
				{
					std::cout << "\nYou have no pending fees.\nRedirecting You back to home.\n";
					system("pause");
					studhome(stud);
				}
				else
				{
					std::cout << "\nTotal Unpaid subject(s):" << Size;
					std::cout << "\nTotal Fees to be paid: RM" << fixed << setprecision(2) << sum;
					std::cout << "\nPayment Method: Online Banking";
					std::cout << "\nEnter your amount of money : RM";
					std::cin >> pay;

					while (pay < sum) {
						std::cout << "Insufficient Amount. Try again: RM";
						std::cin >> pay;
					}
					//payment.PaymentID auto increment
					payment.StudentID = stud.StudentID;
					payment.Total_Subject = Size;
					payment.Total_Fees = sum;
					payment.AdminID = stud.AdminID;
					payment.insert();
					for (int i = 0; i < Size; i++)
						payment.update(students[i].SubjectID);

					std::cout << "\nYour balance will be: RM" << pay - sum;
					std::cout << "\n\nFEES PAYMENT COMPLETE\n" << "REDIRECTING YOU TO HOME PAGE\n";
					system("pause");
					studhome(stud);
				}
				break;
			case 2:
				if (students.size() == 0)
				{
					std::cout << "\nYou have no pending fees.\nRedirecting You back to home.\n";
					system("pause");
					studhome(stud);
				}
				std::cout << "\nPayment status will be pending. You can check the payment status of your enrolled subject on your profile.\n";
				std::cout << "********REDIRECTING BACK TO HOME PAGE***********\n";
				system("pause");
				studhome(stud);
				break;
			default:
				std::cout << "You can choose options 1 or 2 or 3.";
				_getch();
				break;
			}
		}
	}
void feedback(StudAccount stud) {

		Enrollment enroll;

		std::string feed, id;
		char more = 'y', opt;

		std::vector<StudAccount> students = stud.listSubjectEnrolled();

		system("cls");
		std::cout << "********************************************\nLIST OF SUBJECT YOU ENROLLED\n********************************************\n\n";
		std::cout << "|-------------------------|-----------------------------------------|\n";
		std::cout << "| " << std::left << std::setw(24) << "Subject ID" << "|" << std::left << std::setw(41) << "Subject Name" << "|\n";

		std::cout << "|-------------------------|-----------------------------------------|\n";

		if (students.size() == 0) {
			std::cout << "| " << std::left << std::setw(66) << "You currently do not enrolled to any subjects." << "|\n";
			std::cout << "|-------------------------|-----------------------------------------|\n";
			std::cout << "\n\nREDIRECT YOU BACK TO HOME MENU\n";
			system("pause");
			studhome(stud);
		}

		enroll.displayEnrolled(stud.StudentID);
		std::cout << "|-------------------------|-----------------------------------------|\n";
		
		std::cout << "\n\nChoose Option:\n1.Make Feedback.\n2.Back\nInsert Option:";
		std::cin >> opt;
		if (opt == '1')
		{
		std::cout << "Choose which subject you want to make a feedback on by entering the SubjectID: ";

			do {
				std::cout << "\n\nSubjectID: ";
				std::cin >> id;
				std::transform(id.begin(), id.end(), id.begin(), ::toupper); // convert lowercase to upper case
				std::cout << "\n\nFeedback:";
				std::cin.ignore();
				getline(std::cin, feed);

				if (enroll.doFeedback(stud.StudentID, id, feed) == true)
				{
					std::cout << "\n\nThank you for your feedback! Do you wish to make feedback on other Subject? (Y/N) : ";
					std::cin >> more;
				}
				else
				{
					std::cout << "\nYou currently do not enroll to this SubjectID. Continue ? (Y/N) :";
					std::cin >> more;
				}

			} while (more == 'y' || more == 'Y');
			std::cout << "\n\nREDIRECTING YOU BACK TO HOME MENU\n";
			system("pause");
			studhome(stud);
		}
		else if (opt == '2')
		{
			return;
		}
		else
		{
			std::cout << "\n\nWrong Input.\n\n";
			_getch();
			feedback(stud);
		}
}
void UnrollSubject(StudAccount stud) {

	Enrollment enroll;
	std::vector<StudAccount> students;
	std::vector<string> listSubject;

	char opt, more = 'y', confirm;
	std::string id;

	do {
		students = stud.listSubjectEnrolled();
		for (int i = 0; i < students.size(); i++)
			listSubject.push_back(students[i].SubjectID);

		system("cls");
		std::cout << "********************************************\nLIST OF SUBJECT YOU ENROLLED\n********************************************\n\n";
		std::cout << "|-------------------------|-----------------------------------------|\n";
		std::cout << "| " << std::left << std::setw(24) << "Subject ID" << "|" << std::left << std::setw(41) << "Subject Name" << "|\n";

		std::cout << "|-------------------------|-----------------------------------------|\n";

		if (students.size() == 0) {
			std::cout << "| " << std::left << std::setw(66) << "You currently do not enrolled to any subjects." << "|\n";
			std::cout << "|-------------------------|-----------------------------------------|\n";
			std::cout << "\n\nREDIRECT YOU BACK TO HOME MENU\n";
			system("pause");
			studhome(stud);
		}
		else
		{
			enroll.displayEnrolled(stud.StudentID);
			std::cout << "|-------------------------|-----------------------------------------|\n";
		}

		std::cout << "\n\nChoose Option:\n1.Unroll Subject\n2.Back\nInsert Option:";
		std::cin >> opt;
		if (opt == '1')
		{
			std::cout << "Please enter the SubjectID you want to unroll : ";
			std::cin >> id;
			std::transform(id.begin(), id.end(), id.begin(), ::toupper); // convert lowercase to upper case
			auto it = std::find(listSubject.begin(), listSubject.end(), id);

			if (it != listSubject.end()) {// found

				std::cout << "Are you sure you want to unroll this SubjectID " << id << " ? (Y/N) :";
				std::cin >> confirm;
				if (confirm == 'y' || confirm == 'Y')
				{
					enroll.unrollSubject(stud.StudentID, id);
					std::cout << "Do you want to unroll another subject? (Y/N): ";
					std::cin >> more;
				}
			}
			else { // salah eja ke salah format etc
				std::cout << "\n\nSubjectID inserted is not found.";
				_getch();
			}
		}
		else if (opt == '2')
		{
			return;
		}
		else
		{
			std::cout << "\n\nWrong Input.\n";
			_getch();
		}

	} while (more == 'y' || more == 'Y');
}
void timeTable(StudAccount stud) {

	std::vector<StudAccount> students;
	students = stud.listSubjectEnrolled();

	system("cls");
	std::cout << "********************************************\nLIST OF SUBJECT YOU ENROLLED\n********************************************\n\n";
	std::cout << "------------------------------------------------------------------------------------------------------------------------------------------------------------------\n";
	std::cout << "| " << std::left << std::setw(40) << "Subject Name" << "|"
		<< std::setw(25) << " Lesson Date" << "|"
		<< std::setw(25) << "Tutor Name" << "|"
		<< std::setw(25) << "Fees Status" << "|"
		<< std::setw(40) << "Fees Payment Period(DATE)" << "|\n";

	std::cout << "|-----------------------------------------|-------------------------|-------------------------|" << "-------------------------|----------------------------------------|\n";

	if (students.size() == 0) {
		std::cout << "| " << std::left << std::setw(159) << "You currently do not enrolled to any subjects." << "|\n";
	}
	else {
		stud.timeTable();
	}

	std::cout << "------------------------------------------------------------------------------------------------------------------------------------------------------------------\n";
	system("pause");
}
void studentlist(TutorAccount tutor) {

		Enrollment enroll;

		system("cls");
		std::cout << "LIST OF STUDENT(S)\n*******************************\nList of all students enrolled to this subject with feedback:\n\n";
		
		enroll.getFeedback(tutor.TutorID);

		std::cout << "\n\nPress B to back.\n";
		_getch();
		tutorhome(tutor);
	}