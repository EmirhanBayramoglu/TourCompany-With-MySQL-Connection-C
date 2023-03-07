#ifndef TOUR_PACK_H
#define TOUR_PACK_H

#include <iostream>
#include <string>
#include <cstring>
#include <mysql.h>
#include <mysqld_error.h>

using namespace std;


class tourPack
{
	
	public:
		void convert(string cities);
		void setPack(int &day,int &road,string &id);
		void allPacks();
		void deletePack();
		void addingRouta(string packNo, string yer);
		void addingEnterHour(string packNo, string enterhour);
		void addingExitHour(string packNo, string exithour);
		int setPackageNumber();
		void addingCities(string packNo, string rankCities);
		void getPack(string Pack_No);
		
		
	private:	
		char* consult;
		char* sentence;
		string sentence_aux;
		
		int Pack_No;
		char Pack_Name[40];
		string Cities;

		
		MYSQL_RES* res;
		MYSQL_ROW row;
		MYSQL* conn;
	
	
};

#endif
