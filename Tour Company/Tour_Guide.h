#ifndef TOUR_GUIDE_H
#define TOUR_GUIDE_H
 
#include <iostream>
#include <mysql.h>
#include <mysqld_error.h>
#include <sstream>
#include <string>
#include <cmath>
#include <stdexcept>
#include <iomanip>
 
using namespace std;

		

class Tour_Guide{

	public:
		void getGuideInformations(int guideCode);
		void setGuide();
		void allGuides();
		void deleteGuide();
		
		
	private:	
		char* consult;
		char* sentence;
		string sentence_aux;
		
		int Tour_Guide_Code;
		char Guide_Name_Surname[40];
		int Gender;
		char First_Language[25];
		char Second_Language[25];
		char Third_Language[25];
		char Fourth_Language[25];
		

		MYSQL_RES* res;
		MYSQL_ROW row;
		MYSQL* conn;
		
};

#endif
