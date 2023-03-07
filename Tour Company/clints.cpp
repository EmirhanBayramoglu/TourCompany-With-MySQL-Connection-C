#include <iostream>
#include <mysql.h>
#include <mysqld_error.h>
#include <sstream>

#include "clints.h"
#include "tours.h"

using namespace std;

	void clints::getMyTours(string musteriName)
	{
		conn = mysql_init(0);
		conn = mysql_real_connect(conn,"localhost","root","baksbani316","school",3306,NULL,0);
		string myTours;
		stringstream ss;
	
		ss<<"SELECT My_Tours FROM clints where Name_Surname = '"+musteriName+"'";
		string query = ss.str();
		const char* q = query.c_str();
		mysql_query(conn,q);
		res = mysql_store_result(conn);
			while(row = mysql_fetch_row(res))
			{
				myTours = row[0];
				
			}
		convertMyTours(myTours);
	}
	
	void clints::convertMyTours(string myTours)
	{
		conn = mysql_init(0);
		conn = mysql_real_connect(conn,"localhost","root","baksbani316","school",3306,NULL,0);
		stringstream ss;
		
		string reflect;
		
		char dizi[myTours.length()+1];
		strcpy(dizi, myTours.c_str());
		
		for(int i=0;i<myTours.length()+1;i++){
			if(dizi[i]!='-')
			{
				reflect = reflect + dizi[i];
			}
			else if(dizi[i]=='-')
			{
					int qstate = mysql_query(conn,"select * from tours ");
				if(!qstate)
				{
					res = mysql_store_result(conn);
					while(row = mysql_fetch_row(res))
					{
						if(row[0] == reflect)
							cout <<row[0]<<"		"<<row[1]<<"		"<<row[2]<<"		"<<row[3]<<"		"<<row[4]<<"		"<<row[5]<<"		"<<row[6]<<endl<<endl;
					}	
				}
				reflect.clear();
			}
		}
	}
		
	void clints::deleteClint()
	{
		conn = mysql_init(0);
		conn = mysql_real_connect(conn,"localhost","root","baksbani316","school",3306,NULL,0);
		string tcNumber;
		stringstream ss;
		cout<<"Silmek istediginiz kisinin TC_Number giriniz..."<<endl;
		cin>>tcNumber;
		ss<<"DELETE FROM clints where TC_Number ='"+tcNumber+"'";
		string query = ss.str();
		const char* q = query.c_str();
		mysql_query(conn,q);
	}

	void clints::getClint()
	{
	conn = mysql_init(0);
	conn = mysql_real_connect(conn,"localhost","root","baksbani316","school",3306,NULL,0);
	if(conn)
	{
		int qstate = mysql_query(conn,"select * from clints ");
		if(!qstate)
		{
			res = mysql_store_result(conn);
			while(row = mysql_fetch_row(res)){
				cout <<row[0]<<"	"<<row[1]<<"	"<<row[2]<<"	"<<row[3]<<"	"<<row[4]<<endl<<endl;
			}
	}
		
	}		
	}
	
	void clints::getChossenClint(string musteriName)
	{
		
	conn = mysql_init(0);
	conn = mysql_real_connect(conn,"localhost","root","baksbani316","school",3306,NULL,0);
	if(conn)
	{
		int qstate = mysql_query(conn,"select * from clints ");
		if(!qstate)
		{
			res = mysql_store_result(conn);
			while(row = mysql_fetch_row(res))
			{
				if(row[1] == musteriName)
				cout <<row[0]<<"	"<<row[1]<<"	"<<row[2]<<"	"<<row[3]<<"	"<<row[4]<<endl<<endl;
			}	
		}		
	}
			
	}
	
	
	string clints::Login()
	{
		cout<<"Name_Surname: ";
		cin.ignore(40, '\n');
		cin.getline(Name_Surname,40, '\n');
		string nameSurname = Name_Surname;
		cin.ignore(40, '\n');
		
		
		cout<<endl<<"Password: ";
		cin.getline(Password,15, '\n');
		string password = Password;
		cin.ignore(15, '\n');
		
		int correctName = 0;
		
		conn = mysql_init(0);
		conn = mysql_real_connect(conn,"localhost","root","baksbani316","school",3306,NULL,0);
		if(conn)
		{
			int qstate = mysql_query(conn,"select * from clints ");
			if(!qstate)
			{
				res = mysql_store_result(conn);
				while(row = mysql_fetch_row(res))
				{
					if(row[1]==nameSurname)
					{
						if(row[4]==password)
						{
							cout<<"Giris Basarili"<<endl;
				
							return nameSurname;
							
						}
						else{
							cout<<"Parola Yanlis"<<endl;
							
							return "";
						}
						correctName = 1;	
					}
					
				}
				if(correctName == 0)
					{
						cout<<"Girdiginiz Name_Surname ait uyelik bulunmamaktadir..."<<endl;
						
						return "";
					}
				
			}
		
	}	
	}
	
	void clints::setClint()
	{
		
				conn = mysql_init(0);
				conn = mysql_real_connect(conn,"localhost","root","baksbani316","school",3306,NULL,0);
		
				cout<<"TC_Number: ";
				cin>>TC_Number;
				cin.ignore(12, '\n');
				
				cout<<"Name_Surname: ";
				cin.getline(Name_Surname,40, '\n');
				cin.ignore(40, '\n');
				
				cout<<"Phone_Number";
				cin.getline(Phone_Number,11, '\n');
				cin.ignore(11, '\n');
				
				cout<<"BirthDate: ";
				cin.getline(BirthDate,11, '\n');
				cin.ignore(11, '\n');
				
				cout<<"Password: ";
				cin.getline(Password,15, '\n');
				cin.ignore(15, '\n');
				
				sentence_aux = "INSERT INTO clints(TC_Number, Name_Surname, Phone_Number, BirthDate, Password) VALUES('%s','%s','%s','%s','%s')";
				sentence = new char[sentence_aux.length()+1];
				strcpy(sentence, sentence_aux.c_str());
				
				consult = new char[strlen(sentence)+strlen(BirthDate)];
				sprintf(consult,sentence,TC_Number,Name_Surname,Phone_Number,BirthDate,Password);
				
				
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
