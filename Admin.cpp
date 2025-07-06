#include "Admin.h"

using namespace std;

Admin::Admin() {
	AdminID = "";
	AdminPass = "";
}
Admin::Admin(std::string AdminID, std::string AdminPass) {
	this->AdminID = AdminID;
	this->AdminPass = AdminPass;
}
bool Admin::login() {

	DBConnection db;
	db.prepareStatement("SELECT * FROM admin WHERE AdminID=? AND AdminPass=?");
	db.stmt->setString(1, AdminID);
	db.stmt->setString(2, AdminPass);
	db.QueryResult();
	if (db.res->rowsCount() == 1) {
		while (db.res->next()) {
			AdminID = db.res->getString("AdminID");
			AdminPass = db.res->getString("AdminPass");
		}
		db.~DBConnection();
		return true;
	}
	else {

		db.~DBConnection();
		return false;
	}
}
Admin::~Admin() {

}