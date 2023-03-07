#ifndef TOURS_H
#define TOURS_H
 
#include <iostream>
#include <string>
#include <mysql.h>
#include <mysqld_error.h>
#include <cstring>

using namespace std;

		

class tours{

	public:
		void getChossenClint(string tcNumber);
		void getTours();
		void setTour();
		int getClintPassword(int tcNumber);
		void message();
		void deleteTour();
		void differentAddingSystem();
		void where();
		void shortestPath(string cityName,string packNo,string &guzergah,float &hour,string &enterhour,string &exithour,int &road);
		void tourBuying(string clientName);
		string getBuyedTours(string clientName);
		void route(string packNo,int &day,int &road);
		int placesOfCities(string city);
		int placesOfCountry(string cityName);
		void rankOfCities(string &disOfcit, int &i,string &rankCities);
		int setTourNumber();
		string getTourCapacity(string secilenTur);
		void minusCapacity(string secilenTur);
		void setPrivateTour(string clientName);
		void updatePrivateTours(string clientName,string id,string privateTours);
		void getPrivateTours(string clientName,string id);
		void privateTourinfo();
		void convertPrivateTours(string myTours);
		void myPrivateTours(string clientName);
		void convertArray(string allPlaces[40][40],string cityName,int &placeRow,int rrow);
		
		
		
	private:	
		char* consult;
		char* sentence;
		string sentence_aux;
		
		int Tour_Code;
		char Tour_Name[40];
		char Start_Date[11];
		char Finish_Date[11];
		float Adult_Price;
		int NumberOfCities;
		int Tour_Capacity;

		
		MYSQL_RES* res;
		MYSQL_ROW row;
		MYSQL* conn;
		
};

#endif
