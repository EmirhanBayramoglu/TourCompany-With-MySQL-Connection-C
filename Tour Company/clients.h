#ifndef CLIENTS_H
#define CLIENTS_H
 
#include <cstring>
#include <iostream>
#include <mysql.h>
#include <mysqld_error.h>
#include <string>
 
using namespace std;

		

class clients{

	public:
		void getChossenClint(string clientName);
		void getClint();
		void setClint();
		string Login();
		void deleteClint();
		void convertMyTours(string myTours);
		void getMyTours(string clientName);
		
		
		
		
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
