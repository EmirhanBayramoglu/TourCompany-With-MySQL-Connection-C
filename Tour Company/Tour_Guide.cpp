#include <iostream>
#include <mysql.h>
#include <mysqld_error.h>
#include <sstream>

#include "Tour_Guide.h"

using namespace std;

void Tour_Guide::deleteGuide()
{
	conn = mysql_init(0);
	conn = mysql_real_connect(conn,"localhost","root","baksbani316","school",3306,NULL,0);
	
	int secim;
	cin>>secim;
	
	sentence_aux = "DELETE FROM tourguide where Tour_Guide_Code = '%d';";
				sentence = new char[sentence_aux.length()+1];
				strcpy(sentence, sentence_aux.c_str());
				
				consult = new char[strlen(sentence)+sizeof(int)];
				sprintf(consult,sentence,secim);
}

void Tour_Guide::allGuides()
	{
	conn = mysql_init(0);
	conn = mysql_real_connect(conn,"localhost","root","baksbani316","school",3306,NULL,0);
	if(conn)
	{
		int qstate = mysql_query(conn,"select * from tourguide ");
		if(!qstate)
		{
			res = mysql_store_result(conn);
			while(row = mysql_fetch_row(res))
			{
				cout <<row[0]<<"	"<<row[1]<<"	"<<row[2]<<"	"<<row[3]<<"	"<<row[4]<<"	"<<row[5]<<"	"<<row[6]<<"	"<<row[7]<<endl<<endl;
			}
			
		}
		
	}		
	}
	
void Tour_Guide::setGuide()
	{
		
				conn = mysql_init(0);
				conn = mysql_real_connect(conn,"localhost","root","baksbani316","school",3306,NULL,0);
		
				cout<<"Tour_Guide_Code: ";
				cin>>Tour_Guide_Code;
				cin.ignore(40, '\n');
				
				cout<<"Guide_Name_Surname: ";
				cin.getline(Guide_Name_Surname,40, '\n');
				
				cout<<"Gender: "<<endl<<"[1]Erkek	[2]Kadin"<<endl;
				cin>>Gender;
				
				cout<<"First_Language: ";
				cin>>First_Language;
				
				cout<<"Second_Language: ";
				cin>>Second_Language;
				
				cout<<"Third_Language: ";
				cin>>Third_Language;
				
				cout<<"Fourth_Language: ";
				cin>>Fourth_Language;
				
				sentence_aux = "INSERT INTO tourguide(Tour_Guide_Code, Guide_Name_Surname, Gender, First_Language, Second_Language, Third_Language, Fourth_Language) VALUES('%d','%s','%d','%s','%s','%s','%s')";
				sentence = new char[sentence_aux.length()+1];
				strcpy(sentence, sentence_aux.c_str());
				
				consult = new char[strlen(sentence)+sizeof(int)+sizeof(int)];
				sprintf(consult,sentence,Tour_Guide_Code, Guide_Name_Surname, Gender, First_Language, Second_Language, Third_Language, Fourth_Language);
				
				
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
