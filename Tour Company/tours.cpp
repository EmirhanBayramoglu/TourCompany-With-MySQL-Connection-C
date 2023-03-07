#include <iostream>
#include <mysql.h>
#include <mysqld_error.h>
#include <sstream>
#include <string>
#include <cmath>
#include <stdexcept>
#include <iomanip>


#include "clients.h"
#include "tours.h"
#include "Tour_Pack.h"

using namespace std;
tourPack pack;

//client can see own buyyed standart tours
string tours::getBuyedTours(string clientName)
{
	conn = mysql_init(0);
	conn = mysql_real_connect(conn,"localhost","root","YourPassword","YourSchema",3306,NULL,0);
	string secilenTur;
	string buyedTours;
	getTours();
	cout<<endl<<"Enter the tour code of tour that you want to buy.."<<endl;
	cin>>secilenTur;
	
	minusCapacity(secilenTur);
	
	stringstream ss;
	
	ss<<"SELECT My_Tours FROM clients where Name_Surname = '"+clientName+"'";
	string query = ss.str();
	const char* q = query.c_str();
	mysql_query(conn,q);
	res = mysql_store_result(conn);
		while(row = mysql_fetch_row(res))
		{
			buyedTours = row[0];
		}
		buyedTours = buyedTours +secilenTur+"-";
		
		return buyedTours;
}

//buyying tour for clients
void tours::tourBuying(string clientName)
{
	conn = mysql_init(0);
	conn = mysql_real_connect(conn,"localhost","root","YourPassword","YourSchema",3306,NULL,0);
	string buyedTours;
	stringstream ss;
	buyedTours = getBuyedTours(clientName);
	ss<<"UPDATE clients SET My_Tours='"+buyedTours+"' where Name_Surname = '"+clientName+"'";
	string query = ss.str();
	const char* q = query.c_str();
	mysql_query(conn,q);	
	
}

//creating private tour
void tours::setPrivateTour(string clientName)
{
	conn = mysql_init(0);
	conn = mysql_real_connect(conn,"localhost","root","YourPassword","YourSchema",3306,NULL,0);
	string syol,sprice,sday,sperson,sbus;
	stringstream sss;
	int personLimit;
	int road = 0;
	float price;
	int day=1;
	string id;
	
	
	string startDate;
	cout<<"Start_Date: ";
	cin>>startDate;
	
	int NumberOfBus;
	cout<<endl<<"Number Of Bus:";
	cin>>NumberOfBus;
	
	pack.setPack(day,road,id);
	
	price = ((road/2) + (5000*day)) * NumberOfBus;
	
	personLimit = NumberOfBus * 45;
	
	sss<<NumberOfBus;
	sss>>sbus;
	sss.clear();
	
	sss<<personLimit;
	sss>>sperson;
	sss.clear();
	
	sss<<price;
	sss>>sprice;
	sss.clear();
	
	sss<<day;
	sss>>sday;
	sss.clear();
	
	
	stringstream ss;
	ss<<"INSERT INTO ptours(Pack_Id, Day, Start_Time, NumberOfBus, Price, PersonLimit) VALUES('"+id+"','"+sday+"','"+startDate+"','"+sbus+"','"+sprice+"','"+sperson+"')";
	string query = ss.str();
	const char* q = query.c_str();
	mysql_query(conn,q);
	
	getPrivateTours(clientName,id);
	
}

//after buyying private tour your datas will be updated
void tours::updatePrivateTours(string clientName,string id,string privateTours)
{
	conn = mysql_init(0);
	conn = mysql_real_connect(conn,"localhost","root","YourPassword","YourSchema",3306,NULL,0);
	
	stringstream ss;
	ss<<"UPDATE clients SET Private_Tours='"+privateTours+"' where Name_Surname = '"+clientName+"'";
	string query = ss.str();
	const char* q = query.c_str();
	mysql_query(conn,q);
	
}


void tours::getPrivateTours(string clientName,string id)
{
	conn = mysql_init(0);
	conn = mysql_real_connect(conn,"localhost","root","YourPassword","YourSchema",3306,NULL,0);
	
	string privateTours;
	
	stringstream ss;
	ss<<"SELECT Private_Tours FROM clients where Name_Surname = '"+clientName+"'";
	string query = ss.str();
	const char* q = query.c_str();
	mysql_query(conn,q);
	res = mysql_store_result(conn);
	while(row = mysql_fetch_row(res))
	{
		privateTours = row[0];
	}
	privateTours = privateTours + id +"-";
	updatePrivateTours(clientName,id,privateTours);
}


string tours::getTourCapacity(string secilenTur)
{
	conn = mysql_init(0);
	conn = mysql_real_connect(conn,"localhost","root","YourPassword","YourSchema",3306,NULL,0);
	
	string tourCapacity;
	stringstream ss;
	ss<<"SELECT * FROM tours where Tour_Code = '"+secilenTur+"'";
	string query = ss.str();
	const char* q = query.c_str();
	mysql_query(conn,q);
	res = mysql_store_result(conn);
		while(row = mysql_fetch_row(res))
		{
			tourCapacity = row[6];
		}
		return tourCapacity;
}

void tours::minusCapacity(string secilenTur)
{
	conn = mysql_init(0);
	conn = mysql_real_connect(conn,"localhost","root","YourPassword","YourSchema",3306,NULL,0);
	
	stringstream ss;
	string changedForm;
	int tourCapacity;
	ss<<getTourCapacity(secilenTur);
	ss>>tourCapacity;
	tourCapacity--;
	ss.clear();
	ss<<tourCapacity;
	ss>>changedForm;
	ss.clear();
	
	
	stringstream sss;
	sss<<"UPDATE tours SET Tour_Capacity = '"+changedForm+"' WHERE Tour_Code = '"+secilenTur+"'";
	string query = sss.str();
	const char* q = query.c_str();
	mysql_query(conn,q);
	
}

//found and set different tour number for new tours
int tours::setTourNumber()
{
	stringstream ss;
	stringstream sss;
	int TourNumber = 1000;
	int keeper;
	conn = mysql_init(0);
	conn = mysql_real_connect(conn,"localhost","root","YourPassword","YourSchema",3306,NULL,0);
	ss<<"SELECT Tour_Code FROM tours";
	string query = ss.str();
	const char* q = query.c_str();
	mysql_query(conn,q);
	res = mysql_store_result(conn);
	while(row = mysql_fetch_row(res))
	{
		sss<<row[0];
		sss>>keeper;
		sss.clear();
		if(keeper==TourNumber){
			TourNumber++;
		}
		else if(keeper!=TourNumber){
			return TourNumber;
		}
	}
	return TourNumber;
}

void tours::differentAddingSystem()
{
		conn = mysql_init(0);
		conn = mysql_real_connect(conn,"localhost","root","YourPassword","YourSchema",3306,NULL,0);
				
				string tourCode;
				stringstream sss;
				sss<<setTourNumber();
				sss>>tourCode;
				sss.clear();

				string tourName;
				cout<<"Tour_Name: ";
				cin>>tourName;
				
				string startDate;
				cout<<"Start_Date";
				cin>>startDate;
				
				string finishDate;
				cout<<"Finish_Date";
				cin>>finishDate;
				
				string adultPrice;
				cout<<"Adult_Price: ";
				cin>>adultPrice;
				
				string numberOfCities;
				cout<<"NumberOfCities: ";
				cin>>numberOfCities;
				
				string tourCapacity;
				cout<<"Tour_Capacity: ";
				cin>>tourCapacity;
		
		
		stringstream ss;
		ss<<"INSERT INTO tours(Tour_Code, Tour_Name, Start_Date, Finish_Date, Adult_Price, NumberOfCities, Tour_Capacity) VALUES('"+tourCode+"','"+tourName+"','"+startDate+"','"+finishDate+"','"+adultPrice+"','"+numberOfCities+"','"+tourCapacity+"')";
		string query = ss.str();
		const char* q = query.c_str();
		mysql_query(conn,q);
}

void tours::deleteTour()
{
	conn = mysql_init(0);
	conn = mysql_real_connect(conn,"localhost","root","YourPassword","YourSchema",3306,NULL,0);
	string tourCode;
	stringstream ss;
	cout<<"Enter the Tour_Code of tour that you want to delete..."<<endl;
	cin>>tourCode;
	ss<<"DELETE FROM tours where Tour_Code ='"+tourCode+"'";
	string query = ss.str();
	const char* q = query.c_str();
	mysql_query(conn,q);
}

//show tour acording to tour code
void tours::where(){
	
	conn = mysql_init(0);
	conn = mysql_real_connect(conn,"localhost","root","YourPassword","YourSchema",3306,NULL,0);
	
	string code;
	cin>>code;
	stringstream ss;

	ss<<"SELECT * FROM tours where Tour_Code ='"+code+"'";
	string query = ss.str();
	const char* q = query.c_str();
	mysql_query(conn,q);
	
	res = mysql_store_result(conn);
			while(row = mysql_fetch_row(res))
			{
				cout <<row[0]<<"		"<<row[1]<<"		"<<row[2]<<"		"<<row[3]<<"		"<<row[4]<<"		"<<row[5]<<"		"<<row[6]<<endl<<endl;
			}
		
}

//show all tours
void tours::getTours()
{
	conn = mysql_init(0);
	conn = mysql_real_connect(conn,"localhost","root","YourPassword","YourSchema",3306,NULL,0);
	if(conn)
	{
		int qstate = mysql_query(conn,"select * from tours ");
		if(!qstate)
		{
			res = mysql_store_result(conn);
			while(row = mysql_fetch_row(res))
			{
				cout <<row[0]<<"		"<<row[1]<<"		"<<row[2]<<"		"<<row[3]<<"		"<<row[4]<<"		"<<row[5]<<"		"<<row[6]<<endl<<endl;
			}
		}
		
	}		
}

//show personal tours information on your own
void tours::myPrivateTours(string clientName)
{
	
		conn = mysql_init(0);
		conn = mysql_real_connect(conn,"localhost","root","YourPassword","YourSchema",3306,NULL,0);
		string myTours;
		stringstream ss;
	
		ss<<"SELECT Private_Tours FROM clients where Name_Surname = '"+clientName+"'";
		string query = ss.str();
		const char* q = query.c_str();
		mysql_query(conn,q);
		res = mysql_store_result(conn);
			while(row = mysql_fetch_row(res))
			{
				myTours = row[0];
				
			}
		convertPrivateTours(myTours);
		privateTourinfo();
	
}

//show personal tours on your own
void tours::convertPrivateTours(string myTours)
{
	conn = mysql_init(0);
	conn = mysql_real_connect(conn,"localhost","root","YourPassword","YourSchema",3306,NULL,0);
	stringstream ss;
	
	string reflect;
	
	char dizi[myTours.length()+1];
	strcpy(dizi, myTours.c_str());
	cout <<"Pack_Id"<<"		"<<"Day"<<"		"<<"Start_Time"<<"	"<<"NumberOfBus"<<"		"<<"Price"<<"		"<<"PersonLimit"<<"		"<<endl<<endl;
	for(int i=0;i<myTours.length()+1;i++){
		if(dizi[i]!='-')
		{
			reflect = reflect + dizi[i];
		}
		else if(dizi[i]=='-')
		{
				int qstate = mysql_query(conn,"select * from ptours ");
				
			if(!qstate)
			{
				res = mysql_store_result(conn);
				while(row = mysql_fetch_row(res))
				{
					if(row[0] == reflect)
						cout <<row[0]<<"		"<<row[1]<<"		"<<row[2]<<"		"<<row[3]<<"		"<<row[4]<<"		"<<row[5]<<"		"<<endl<<endl;
				}	
			}
			reflect.clear();
		}
	}
}

//show personal tours information on your own
void tours::privateTourinfo()
{
	
	string cities[10];
	string senterhour[100];
	string sexithour[100];
	string spoint[100];
	string id;
	int i=0;
	int day=1;
	int count =0;
	string rankCities;
	string guzergah;
	string enterhour;
	string exithour;
	string reflect;
	
	conn = mysql_init(0);
	conn = mysql_real_connect(conn,"localhost","root","YourPassword","YourSchema",3306,NULL,0);
	cout<<"Bilgisini istedigin paketin Pack_No girin..."<<endl;
	
	cin>>id;
	stringstream ss;
	
	

	ss<<"SELECT * FROM pack where Pack_No ='"+id+"'";
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

void tours::setTour()
{
	
	conn = mysql_init(0);
	conn = mysql_real_connect(conn,"localhost","root","YourPassword","YourSchema",3306,NULL,0);

	cout<<"Tour_Code: ";
	cin>>Tour_Code;
	cin.ignore(40, '\n');
	
	cout<<"Tour_Name: ";
	cin.getline(Tour_Name,40, '\n');
	
	cout<<"Start_Date";
	cin.getline(Start_Date,11, '\n');
	
	cout<<"Finish_Date: ";
	cin.getline(Finish_Date,11, '\n');
	
	cout<<"Adult_Price: ";
	cin>>Adult_Price;
	
	cout<<"NumberOfCities: ";
	cin>>NumberOfCities;
	
	cout<<"Tour_Capacity: ";
	cin>>Tour_Capacity;
	
	sentence_aux = "INSERT INTO tours(Tour_Code, Tour_Name, Start_Date, Finish_Date, Adult_Price, NumberOfCities, Tour_Capacity) VALUES('%d','%s','%s','%s','%f','%d','%d')";
	sentence = new char[sentence_aux.length()+1];
	strcpy(sentence, sentence_aux.c_str());
	
	consult = new char[strlen(sentence)+strlen(Start_Date)+strlen(Finish_Date)+sizeof(float)+sizeof(int)+sizeof(int)+sizeof(int)];
	sprintf(consult,sentence,Tour_Code, Tour_Name, Start_Date, Finish_Date, Adult_Price, NumberOfCities, Tour_Capacity);
	
	
	//Make our attempt
	
	if(mysql_ping(conn))
	{
		cout<<"ERROR: Imposible to connect."<<endl;
		cout<<mysql_error(conn)<<endl;
	}
	if(mysql_query(conn,consult))
	{
		cout<<"ERROR: "<<mysql_error(conn)<<endl;
		rewind(stdin);
		getchar();
	}
	else
	{
		cout<<"Info added correctly."<<endl;
	}
	mysql_store_result(conn);
}

//find how many point are there certain city
int tours::placesOfCities(string cityName)
{
	//database tablosundaki satýr sayýsýný bulma fonksiyonu
	conn = mysql_init(0);
	conn = mysql_real_connect(conn,"localhost","root","YourPassword","YourSchema",3306,NULL,0);
	int rrow = 0;
	stringstream ssa;
	ssa<<"SELECT * FROM points WHERE City = '"+cityName+"'";
	string query = ssa.str();
	const char* q = query.c_str();
	mysql_query(conn,q);
	res = mysql_store_result(conn);
	cout<<endl<<endl;
	while(row = mysql_fetch_row(res))
	{	
	 rrow++;
	}
	return rrow;
}

int tours::placesOfCountry(string cityName)
{
	//database tablosundaki satýr sayýsýný bulma fonksiyonu
	conn = mysql_init(0);
	conn = mysql_real_connect(conn,"localhost","root","YourPassword","YourSchema",3306,NULL,0);
	int rrow = 0;
	stringstream ssa;
	ssa<<"SELECT * FROM "+cityName+"";
	string query = ssa.str();
	const char* q = query.c_str();
	mysql_query(conn,q);
	res = mysql_store_result(conn);
	cout<<endl<<endl;
	while(row = mysql_fetch_row(res))
	{	
	 rrow++;
	}
	
	return rrow;
}

//arrangement cities according to optimum distance
void tours::rankOfCities(string &disOfcit, int &i,string &rankCities)
{	
	string city;
	string cities[6];
	int match=0;
	
	//distcities tablosundaki satýr sayýsýný alma
	int satira = placesOfCountry(" distcities");
	string allPlaces[rrow][rrow+3];
	int placeRow = 0;
	float distance;
	float shortestWay;
	int tablePosition;
	stringstream ss;
	
	string vote;
	string instant;
	conn = mysql_init(0);
	conn = mysql_real_connect(conn,"localhost","root","YourPassword","YourSchema",3306,NULL,0);	
	
	ss<<"SELECT * FROM distcities";
	string query = ss.str();
	const char* q = query.c_str();
	mysql_query(conn,q);
	res = mysql_store_result(conn);
	//dataBase bilgilerini array'e aktarma
	while(row = mysql_fetch_row(res))
	{
		for(int i=0;i<satira + 3;i++){
			allPlaces[placeRow][i]=row[i];
		}
		placeRow++;
		
	}
	
	//gidilecek þehileri seçme
	cout<<"Kastamonu	Bolu	Bayburt		Ordu	Rize	Tokat"<<endl<<endl;
	while(city!="0")
	{
		cout<<"Tura eklemek istediginiz sehrin adini giriniz...(bitirmek icin 0 giriniz)"<<endl;
		cin>>city;
		match=0;
		for(int c=0;c<satira;c++){
				if(allPlaces[c][0]==city){
					break;
				}
				else if(c==satira-1){
					cout<<"Lutfen listedeki yerleri seciniz..."<<endl;
					match = 1;
				}
			}
			for(int c=0;c<satira;c++){
				if(cities[c]==city){
					cout<<"Daha once secilen bir yer secdiniz..."<<endl;
					match = 1;
				}
			}
			if(match==0 && city!="0"){
				cities[i]=city;
				i++;
			}	
	}
	i++;
	//array bilgilerini yazdýrma
	for(int p =0;p<satira;p++)
	{
		for(int k =0;k<satira + 3;k++)
		{
			cout<<allPlaces[p][k]<<"		";
		}
		cout<<endl;
	}
	string tour[40];
	ss.clear();
	instant = cities[0];
	cities[0].clear();
	//þehirleri gidiþ sýrasýna göre sýralama (ilk yazýlan city baþlangýç þehri)(286-329)
	rankCities= rankCities + instant + "-";
	for(int f = 0 ; f<i-2; f++)
	{
		
		shortestWay=99999;
		tablePosition = 1;
		
		for(int m = 0 ; m < placeRow ; m++){
			if(allPlaces[m][0]==instant){
				break;
			}
			tablePosition++;
		}
		tablePosition=tablePosition+2;
		stringstream sss;
		
		for(int t = 0;t<placeRow;t++)
		{
			for(int y = 0;y<i;y++)
			{
				if(allPlaces[t][0] == cities[y])
				{	
					sss.clear();
					sss<<allPlaces[t][tablePosition];
					sss>>distance;
					if(distance<shortestWay && distance != 0)
					{
						vote=allPlaces[t][tablePosition];
						shortestWay=distance;
						instant = cities[y];
					}	
				}
				distance = 0;	
			}
		}
		rankCities= rankCities + instant + "-";
		disOfcit= disOfcit + vote + "-";
		for(int l=0 ; l<i ; l++)
		{
			if(cities[l]==instant){
				cities[l].clear();
			}
		}
	}
}

void tours::route(string packNo,int &day,int &road)
{
	string enterhour;
	string exithour;
	string guzergah;
	string city;
	string rankCities;
	
	float citdis=0;
	int i=0;
	day=1;
	float hour;
	
	cout<<"Baslangic saati giriniz..."<<endl;
	cin>>hour;
	string distances[10];
	string cities[10];
	string senterhour[100];
	string sexithour[100];
	string spoint[100];
	
	
	string disOfcit;
	//þehirleri sýralama ve mesafeleri kayýt etme fonksiyonu
	rankOfCities(disOfcit,i,rankCities);
	string reflect;
	stringstream ss;
	//sýra sýra þehirler arasýnda eklenecek süreleri diziye aktarma (357-372)
	char dizi[disOfcit.length()+1];
	strcpy(dizi, disOfcit.c_str());
	
	int count=0;
	for(int l=0;l<disOfcit.length()+1;l++){
		if(dizi[l]!='-')
		{
			reflect = reflect + dizi[l];
		}
		else if(dizi[l]=='-')
		{
			distances[count]=reflect;
			reflect.clear();
			count++;
		}	
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
		}	
	}
	//seçilen þehirlere gidip oralarda shortestPath hesaplayýp sonraki þehirle aradaki mesafeyi hesaplama en sonda ise string bilgileri dataBase'e yazdýrma
	for(int k=0;k<i-1;k++)
	{
		city=cities[k];
		if(k==0){
			city.erase(0,1);
		}
		shortestPath(city,packNo,guzergah,hour,enterhour,exithour,road);
		
		ss.clear();
		ss<<distances[k];
		ss>>citdis;
		hour = hour + (citdis/10);
		road= road + hour;
		if(k==i-2){
			pack.addingRouta(packNo, guzergah);
			pack.addingEnterHour(packNo, enterhour);
			pack.addingExitHour(packNo, exithour);
			pack.addingCities(packNo,rankCities);
		}
		citdis=0;	
	}
	//string haline olan bilgileri önce char dizisine sonra string arraye aktarma (408-480)
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

//creating an array according to choosen city's points 
void tours::convertArray(string allPlaces[40][40],string cityName,int &placeRow,int rrow)
{
	
	string alinanBilgiler[40][40];
	conn = mysql_init(0);
	conn = mysql_real_connect(conn,"localhost","root","YourPassword","YourSchema",3306,NULL,0);
	stringstream ss;
	ss<<"SELECT * FROM points WHERE City = '"+cityName+"'";
	string query = ss.str();
	const char* q = query.c_str();
	mysql_query(conn,q);
	res = mysql_store_result(conn);
	
	while(row = mysql_fetch_row(res))
	{
		for(int p=0;p<6;p++)
		{
			alinanBilgiler[placeRow][p]=row[p];
		}
		//cout<<place;
		placeRow++;
		
	}

	stringstream ssX;
	stringstream ssY;
	stringstream ssSonuc;
	int fromX;
	int fromY;
	int toX;
	int toY;
	int dist;
	for(int i=0;i<placeRow;i++)
	{
		ssX.clear();
		ssY.clear();
		ssSonuc.clear();
		ssX<<alinanBilgiler[i][4];
		ssX>>fromX;
		ssY<<alinanBilgiler[i][5];
		ssY>>fromY;
		allPlaces[i][0]=alinanBilgiler[i][0];
		allPlaces[i][1]=alinanBilgiler[i][1];
		allPlaces[i][2]=alinanBilgiler[i][2];
		allPlaces[i][3]=alinanBilgiler[i][3];
		allPlaces[i][4]=alinanBilgiler[i][4];
		allPlaces[i][5]=alinanBilgiler[i][5];
		for(int k=0;k<placeRow;k++)
		{
			/**/
			ssX.clear();
			ssY.clear();
			ssX<<alinanBilgiler[k][4];
			ssX>>toX;
			ssY<<alinanBilgiler[k][5];
			ssY>>toY;
			dist = hypot(fromX-toX,fromY-toY);
			ssSonuc<<dist;
			ssSonuc>>allPlaces[i][k+6];
			ssSonuc.clear();
		}
	}
}

	
void tours::shortestPath(string cityName,string packNo,string &guzergah,float &hour,string &enterhour,string &exithour,int &road)
{	
	int match = 0;
	int bos = 0;
	int daily=0;
	// cityName tablosundaki satýr sayýsýný alma
	int rrow = placesOfCities(cityName);
	stringstream ss;
	string allPlaces[40][40];
	int enterhours[200];
	int exithours[200];
	enterhours[0] = hour;
	int placeRow = 0;
	
	convertArray(allPlaces,cityName,placeRow,rrow);
	
			//Array yazdýrma
			for(int i =0;i<rrow;i++)
			{
				for(int k =0;k<rrow + 6;k++)
				{
					cout<<allPlaces[i][k]<<"	";
				}
				cout<<endl;
			}
			
		string foodplace;
		float distance;
		float shortestWay;
		ss.clear();
		string vote;
		string instant;
		int sira=0;
		stringstream sss;
		string secilenYerler[40];
		//Sorun yaþamamak için seçilenYerler arrayini temizleme
		for(int i=0;i<40;i++){
			secilenYerler[i].clear();
		}
		//Þehirdeki gidilecek yerleri seçme
		while(vote != "0")
		{
			match = 0;
			cout<<"Gitmek istediginiz yeri yazin...(bitirmek icin 0 giriniz)"<<endl;
			cin>>vote;
			//seçimin uygunluðu kontrol edilir
			for(int c=0;c<40;c++){
				if(allPlaces[c][1]==vote){
					break;
				}
				else if(c==39){
					cout<<"Lutfen listedeki yerleri seciniz..."<<endl;
					match = 1;
				}
			}
			for(int c=0;c<40;c++){
				if(secilenYerler[c]==vote){
					cout<<"Daha once secilen bir yer secdiniz..."<<endl;
					match = 1;
				}
			}
			if(match==0){
			secilenYerler[sira]=vote;
			sira++;	
			}	
		}
		string tour[40];
		//Ýlk seçilen yer instant olarak belirleniyor
		instant = secilenYerler[0];
		tour[0]=instant;
		int tablePosition;
		secilenYerler[0].clear();
		int placement = 1;
		
		//Ýþlemlere baþlama (566-731)
		for(int i = 0 ; i<sira && bos==0 ; i++)
		{
			shortestWay=99999;
			tablePosition = 1;
			//instant bulunduðu yerdeki geçirilen zaman saate eklenir ve instant noktanýn diðer noktalara olan uzaklýðýnýn bulunduðu kolonun numarasýný bulur 
			for(int m = 0 ; m < placeRow ; m++){
				distance = 0;
				if(allPlaces[m][1]==instant && instant!=tour[0]){
					sss.clear();
					sss<<allPlaces[m][3];
					sss>>distance;
					hour = hour + distance;
					exithours[placement-1] = hour;
				}
				if(allPlaces[m][1]==instant){
					exithours[placement-1] = hour;
					break;
				}
				tablePosition++;
			}
			tablePosition=tablePosition+5;
			//Saat 17'yi geçtiyse otele geri dönecek (588-629)
			if(1020<hour){
					//en son bulunduðu yer ile otel arasýndaki mesafeyi zamana çeavirip saate ekleme
					for(int t = 0;t<placeRow;t++)
					{
							if(allPlaces[t][1]==tour[0])
							{	
								sss.clear();
								sss<<allPlaces[t][tablePosition];
								sss>>distance;
								hour= hour + (distance/10);
								road = road + hour ;
							}
					}
				
				instant=tour[0];
				daily=0;
				tour[placement] = instant;
				enterhours[placement] = hour;
				exithours[placement] = 420;
				placement++;
				i--;
				hour=420;
				sira++;
				tablePosition = 1;
				//Sabah otelden çýkýþ saatini ayarlama ve diðer noktalarýn otele uzaklýðýnýn kolon sýrasý
				for(int m = 0 ; m < placeRow ; m++){
					distance = 0;
					
					if(allPlaces[m][1]==instant){
						exithours[placement-1] = hour;
						break;
					}
					tablePosition++;
				}
				tablePosition=tablePosition+5;
			}
			
			
			//bulunduðu noktaya en yakýn diðer seçilen noktalardan en yakýnýný bulma (633-649)
			for(int t = 0;t<placeRow;t++)
			{
				for(int y = 0;y<placeRow;y++)
				{
					if(allPlaces[t][1]==secilenYerler[y])
					{	
						sss.clear();
						sss<<allPlaces[t][tablePosition];
						sss>>distance;
						if(distance<shortestWay && distance != 0 && allPlaces[t][2]=="yer")
						{
							shortestWay=distance;
							instant = secilenYerler[y];
						}	
					}
					distance = 0;	
				}
				
			}
			//Çýkan en yakýn yerin mesafesini 10 a bölüp süreyi genel saate ekleme 
			if(shortestWay<3000){
				hour = hour + (shortestWay/10);
				road = road + hour ;
			}
				
			//Yeni gelinen noktanýn baþlangýç süresi
			enterhours[placement] = hour;
			daily++;
			
			//gidilen yere tekrar gidilmesin diye gidilen yeri seçilen yerler arrayinden siliyoruz
			for(int l=0 ; l<sira+4 ; l++)
			{
				if(secilenYerler[l]==instant){
					secilenYerler[l]="";
				}
			}
			shortestWay=99999;
			tour[placement]=instant;
			placement++;
			
			tablePosition = 1;
			
			//Saat 14 ü geçmediyse ve o gün içinde 3 yere gidildiyse en yakýn foodplace yerine gidlir (673-713)
			if(daily==3 && hour<=840)
			{
				for(int m = 0 ; m < placeRow ; m++)
				{
					if(allPlaces[m][1]==instant)
					{
						distance = 0;
						sss.clear();
						sss<<allPlaces[m][3];
						sss>>distance;
						hour = hour + distance;
						exithours[placement-1] = hour;
						break;
					}
				tablePosition++;
				}
				tablePosition=tablePosition+5;
			
				distance = 0;
				for(int h = 0; h < placeRow; h++)
				{
					if(distance<shortestWay && allPlaces[h][2]=="foodplace"){
						sss.clear();
						sss<<allPlaces[h][tablePosition];
						sss>>distance;

						if(distance<shortestWay && distance != 0)
						{
							shortestWay=distance;
							instant = allPlaces[h][1];
						}
					}
					distance = 0 ;
				}

				foodplace=instant;
				tour[placement]=instant;
				if(shortestWay<3000)
				hour = hour + (shortestWay/10);
				road = road + hour ;
				enterhours[placement] = hour;
				placement++;
				sira++;
			}
		//seçilen yerlerin bitip bitmediðini kontrol etme (715-729)
		bos=0;
		for(int k=0;k<sira;k++){
		if(secilenYerler[k]=="")
		{
			bos++;
		}
		}
		if(bos==sira)
		{
			
		}
		else
		{
			bos=0;
		}
	cout<<instant<<endl;	
	}
		//tüm seçilen yerler gezilince eðer anlýk konum otel deðilse otele dönme ve saat 17'yi geçtiyse saati 7'ye ayarlar (733-769)
		if(instant!=tour[0]){
			tablePosition = 1;
			for(int m = 0 ; m < placeRow ; m++)
				{
					if(allPlaces[m][1]==instant)
					{
						distance = 0;
						sss.clear();
						sss<<allPlaces[m][3];
						sss>>distance;
						hour = hour + distance;
						exithours[placement-1] = hour;
						break;
					}
				tablePosition++;
				}
				tablePosition=tablePosition+5;
					for(int t = 0;t<placeRow;t++)
					{
							if(allPlaces[t][1]==tour[0])
							{	
								sss.clear();
								sss<<allPlaces[t][tablePosition];
								sss>>distance;
								hour= hour + (distance/10);
								road = road + hour ;
							}
					}
				
				instant=tour[0];
				tour[placement] = instant;
				enterhours[placement] = hour;
				if(1020<hour)
				{
					hour=420;
				}
				exithours[placement] = hour;
			}
		
		string yer;
		float tableHour;
		string shour;
		string smin;
		stringstream ssss;
		//güzergah exithour ve enterhour deðiþkenlerini ayarlar ve o þehirdeki gezi bilgisini yazdýrýr (777-790)
		for(int c=0;c<sira+1;c++){
			ssss.clear();
			ssss<<enterhours[c]/60<<":"<<setfill('0')<<setw(2)<<enterhours[c]%60;
			ssss>>shour;
			cout<<enterhours[c]/60<<":"<<setfill('0')<<setw(2)<<enterhours[c]%60<<"	-	";
			cout<<exithours[c]/60<<":"<<setfill('0')<<setw(2)<<exithours[c]%60<<"	"<<tour[c]<<endl;
			guzergah = guzergah + tour[c] + "-" ;
			enterhour = enterhour + shour + "-";
			
			ssss.clear();
			ssss<<exithours[c]/60<<":"<<setfill('0')<<setw(2)<<exithours[c]%60;
			ssss>>shour;
			exithour = exithour + shour + "-";
		}
		//her þehir sonunda bilgilerin sonuna "/" ekleme
		guzergah = guzergah+"/";
		enterhour = enterhour+"/";
		exithour = exithour+"/";	
	cout<<endl;
}
