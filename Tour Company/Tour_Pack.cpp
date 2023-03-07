#include <iostream>
#include <mysql.h>
#include <mysqld_error.h>
#include <sstream>
#include <string>
#include "Tour_Pack.h"
#include "tours.h"

using namespace std;

tours tour;
//packetlerin bilgisini verir
void tourPack::allPacks()
	{
	conn = mysql_init(0);
	conn = mysql_real_connect(conn,"localhost","root","YourPassword","YourSchema",3306,NULL,0);
	if(conn)
	{
		int qstate = mysql_query(conn,"select * from pack ");
		if(!qstate)
		{
			res = mysql_store_result(conn);
			while(row = mysql_fetch_row(res))
			{
				cout <<row[0]<<"	"<<row[1]<<"	"<<row[2]<<endl;
				
			}
			
		}
		
	}		
}

//pack numarasýný otomatik olabilecek en düþük numarayý verir 1 3 4 5 varsa 2 verir
int tourPack::setPackageNumber()
{
	stringstream ss;
	stringstream sss;
	int packNo = 1;
	int keeper;
	conn = mysql_init(0);
	conn = mysql_real_connect(conn,"localhost","root","YourPassword","YourSchema",3306,NULL,0);
	ss<<"SELECT Pack_No FROM pack";
	string query = ss.str();
	const char* q = query.c_str();
	mysql_query(conn,q);
	res = mysql_store_result(conn);
	while(row = mysql_fetch_row(res))
	{
		sss<<row[0];
		sss>>keeper;
		sss.clear();
		if(keeper==packNo){
			packNo++;
		}
		else if(keeper!=packNo){
			return packNo;
		}
	}
	return packNo;
}


void tourPack::getPack(string Pack_No)
{
	int i=1;
	string reflect;
	int count=0;
	int day=1;
	stringstream ss;
	string rankCities;
	string enterhour;
	string exithour;
	string guzergah;
	string senterhour[100];
	string sexithour[100];
	string spoint[100];
	string cities[10];
	conn = mysql_init(0);
	conn = mysql_real_connect(conn,"localhost","root","YourPassword","YourSchema",3306,NULL,0);
	ss<<"SELECT * FROM pack where Pack_No ='"+Pack_No+"'";
	string query = ss.str();
	const char* q = query.c_str();
	mysql_query(conn,q);
	res = mysql_store_result(conn);
	while(row = mysql_fetch_row(res))
	{
		rankCities=row[2];
		guzergah=row[3];
		enterhour=row[4];
		exithour=row[5];
	}
	
	char dizii[rankCities.length()+1];
	strcpy(dizii, rankCities.c_str());
	
	count=0;
	for(int l=0;l<rankCities.length()+1;l++){
		if(dizii[l]!='-')
		{
			reflect = reflect + dizii[l];
		}
		else if(dizii[l]=='-')
		{
			cities[count]=reflect;
			reflect.clear();
			count++;
			i++;
		}	
	}
	
	char centerhour[enterhour.length()+1];
	strcpy(centerhour, enterhour.c_str());
	
	char cexithour[exithour.length()+1];
	strcpy(cexithour, exithour.c_str());
	
	char cpoint[guzergah.length()+1];
	strcpy(cpoint, guzergah.c_str());

	int countreflect =0;
	reflect.clear();
	for(int l=0;l<enterhour.length()+1;l++){
		if(centerhour[l]!='-' && reflect!="/")
		{
			reflect = reflect + centerhour[l];
		}	
		if(centerhour[l]=='-')
		{
			senterhour[countreflect]=reflect;
			reflect.clear();
			countreflect++;
		}
		if(centerhour[l]=='/')
		{
			senterhour[countreflect]=reflect;
			reflect.clear();
			countreflect++;
		}
	}
	cout<<endl;
	reflect.clear();
	countreflect =0;
	for(int l=0;l<exithour.length()+1;l++){
		if(cexithour[l]!='-' && reflect!="/")
		{
			reflect = reflect + cexithour[l];
		}
		if(cexithour[l]=='-')
		{
			sexithour[countreflect]=reflect;
			reflect.clear();
			countreflect++;
		}
		if(cexithour[l]=='/')
		{
			sexithour[countreflect]=reflect;
			reflect.clear();
			countreflect++;
		}
	}
	cout<<endl;
	countreflect =0;
	reflect.clear();
	for(int l=0;l<guzergah.length()+1;l++){
		if(cpoint[l]!='-' && reflect!="/")
		{
			reflect = reflect + cpoint[l];
		}
		if(cpoint[l]=='-')
		{
			spoint[countreflect]=reflect;
			reflect.clear();
			countreflect++;
		}
		if (cpoint[l]=='/')
		{

			spoint[countreflect]=reflect;
			reflect.clear();
			countreflect++;
			
		}
	}
	
	cout<<endl;
	//tüm planý yazdýrýr (þehir adý sonra o þehirde gidilen yerler ve orada kalma süresi)
	int lastCount = 0;
	for(int f=0;f<i;f++){
		cout<<endl<<"		"<<cities[f]<<endl<<endl;
		cout<<"Day		"<<"Loc		"<<"En.H.		"<<"Ex.H."<<endl;
		while(spoint[lastCount]!="/" && lastCount<countreflect)
		{
			cout<<day<<"		"<<spoint[lastCount]<<"		"<<senterhour[lastCount]<<"	-	"<<sexithour[lastCount]<<endl;
			lastCount++;
			if(sexithour[lastCount-1]=="7:00"){
				day++;
			}
		}
		lastCount++;
	}
}

//tur paketi oluþturma
void tourPack::setPack(int &day,int &road,string &id)
{
		stringstream sss;
		conn = mysql_init(0);
		conn = mysql_real_connect(conn,"localhost","root","YourPassword","YourSchema",3306,NULL,0);
		string i = "selam";
		
		string stringpack;
		int packNo;
		packNo=setPackageNumber();
		sss<<packNo;
		sss>>stringpack;
		
		string packName;
		cout<<"packName: ";
		cin>>packName;	

		stringstream ss;
		ss<<"INSERT INTO pack(Pack_No, Pack_Name) VALUES('"+stringpack+"','"+packName+"')";
		string query = ss.str();
		const char* q = query.c_str();
		mysql_query(conn,q);
		
		tour.route(stringpack,day,road);
		id=stringpack;
}

//þehirler içinde gidilecek yerleri string olarak dataBase'e kayýt eder
void tourPack::addingRouta(string packNo, string yer)
{
	conn = mysql_init(0);
	conn = mysql_real_connect(conn,"localhost","root","YourPassword","YourSchema",3306,NULL,0);
	
	stringstream ss;
	ss<<"UPDATE pack SET tour = '"+yer+"' WHERE Pack_No = '"+packNo+"'";
	string query = ss.str();
	const char* q = query.c_str();
	mysql_query(conn,q);
}

//gidilen yerlere giriþ saatleri
void tourPack::addingEnterHour(string packNo, string enterhour)
{
	conn = mysql_init(0);
	conn = mysql_real_connect(conn,"localhost","root","YourPassword","YourSchema",3306,NULL,0);
	
	stringstream ss;
	ss<<"UPDATE pack SET enterhour = '"+enterhour+"' WHERE Pack_No = '"+packNo+"'";
	string query = ss.str();
	const char* q = query.c_str();
	mysql_query(conn,q);
}

//gidilen yerlerden çýkýþ saatleri
void tourPack::addingExitHour(string packNo, string exithour)
{
	conn = mysql_init(0);
	conn = mysql_real_connect(conn,"localhost","root","YourPassword","YourSchema",3306,NULL,0);
	
	stringstream ss;
	ss<<"UPDATE pack SET exithour = '"+exithour+"' WHERE Pack_No = '"+packNo+"'";
	string query = ss.str();
	const char* q = query.c_str();
	mysql_query(conn,q);
}

void tourPack::addingCities(string packNo, string rankCities)
{
	conn = mysql_init(0);
	conn = mysql_real_connect(conn,"localhost","root","YourPassword","YourSchema",3306,NULL,0);
	
	stringstream ss;
	ss<<"UPDATE pack SET Cities = '"+rankCities+"' WHERE Pack_No = '"+packNo+"'";
	string query = ss.str();
	const char* q = query.c_str();
	mysql_query(conn,q);
}
