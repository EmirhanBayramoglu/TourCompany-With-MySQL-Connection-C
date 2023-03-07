#include <iostream>
#include <mysql.h>
#include <mysqld_error.h>

#include "clients.h"
#include "tours.h"
#include "Tour_Pack.h"


using namespace std;


int main() {
	
	string adminN = "mahmut";
	string adminP = "mahmut123";
	string adminName;
	string adminPass;
	int vote = 1;
	int clientChoose = 1;
	string clientName = "";
	tourPack pack;
	clients clint;
	tours tour;
	
	while(vote!=0)
	{
		cout<<"[1] Show Stable Tours"<<endl
			<<"[2] Client Enter"<<endl
			<<"[3] Admin Enter"<<endl
			<<"[0] Exit"<<endl;
		cin>>vote;
			
			if(vote==1)
			{
				tour.getTours();
			}
			
			while(vote==2){
				
				
				cout<<"[1] Giris Yapin"<<endl
					<<"[2] Kayit Ol"<<endl
					<<"[0] Geri Don"<<endl;
				
				cin>>clientChoose;
				
				if(clientChoose==1)
				{
					clientName = clint.Login();
					
					while(clientName != "" ){
						cout<<"Choose your process..."<<endl<<endl;
						
						cout<<"[1] Profile"<<endl
							<<"[2] My Tours"<<endl
							<<"[3] Buy Tour"<<endl
							<<"[4] Create Personal Tour"<<endl
							<<"[5] My Personal Tour"<<endl
							<<"[0] Go Back"<<endl;
						
						cin>>clientChoose;
						
						switch(clientChoose){
							
							case 1: clint.getChossenClint(clientName); break;
							case 2: clint.getMyTours(clientName); break;
							case 3: tour.tourBuying(clientName); break;
							case 4: tour.setPrivateTour(clientName); break;
							case 5: tour.myPrivateTours(clientName); break;
							case 0: vote = 20; clientName=""; break;
							
						}		
					}
				}
				else if(clientChoose==2)
				{
					clint.setClint();
				}
				else if(clientChoose==0)
				{
					vote=20;
				}
			}
			
			if(vote==3){
				
				cout<<"Admin Name: ";
				cin>>adminName;
				cout<<endl<<"Admin password: ";
				cin>>adminPass;
				while(adminN==adminName && adminP==adminPass){
					
					cout<<"[1] Show All Tours"<<endl
						<<"[2] Add Tour"<<endl
						<<"[3] Delete Tour"<<endl
						<<"[4] Show City Packs"<<endl
						<<"[5] Show Clients"<<endl
						<<"[6] Delete Client"<<endl
						<<"[0] Exit"<<endl;
						
						cin>>clientChoose;
						
						switch(clientChoose){
							
							case 1: tour.getTours(); break;
							case 2: tour.differentAddingSystem(); break;
							case 3: tour.deleteTour(); break;
							case 4: pack.allPacks(); break;
							case 5: clint.getClint(); break;
							case 6: clint.deleteClint(); break;
							case 0: vote = 20 ; adminName="" ; adminPass="" ; break;
							
						}
			}	
		}
	}
	return 0;
}	
