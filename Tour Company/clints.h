#ifndef CLINTS_H
#define CLINTS_H
 
#include <iostream>
#include <mysql.h>
#include <mysqld_error.h>
 
using namespace std;

		

class clints{

	public:
		void getChossenClint(string musteriName);
		void getClint();
		void setClint();
		string Login();
		void deleteClint();
		void convertMyTours(string myTours);
		void getMyTours(string musteriName);
		
		
		
		
	private:	
		char* consult;
		char* sentence;
		string sentence_aux;
		
		char TC_Number[15];
		char Name_Surname[40];
		char Phone_Number[11];
		char Password[15];
		char BirthDate[11];

		MYSQL_RES* res;
		MYSQL_ROW row;
		MYSQL* conn;
		
};

#endif
