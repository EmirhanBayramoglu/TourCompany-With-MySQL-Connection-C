# TourCompany-With-MySQL-Connection-C-
Product store datas on mysql, and can create new tours with you have choosed points (with shortest way). When you create tour first choosen point is your hotel. Tour will go to restaurant according to condition. End of the day tour goes to hotel back.

MySQL Tabels:
-city(City_Code(Decimal),City_Name(Varchar))
-clients(TC_NUmber(Varchar),Name_Surname(Varchar),Phone_Number(Varchar),BirthDate(date),Password(Varchar),My_Tours(Varchar),Private_Tours(Varchar))
-distcities(Name,x,y,bayubrt,bolu,kastamonu,ordu,rize,tokat)(x and y are cordinate, others are cities name, if you want change table as points so work with just cordinates)
-pack(Pack_No,Pack_Name,Cities,tour,enterhour,exithour)
-points(City,Name,type,spendTime,x,y)
-ptour(Pack_Id,Day,Start_Time,NumberOfBus,Price,PersonalLimit)
-tours(Tour_Code,Tour_Name,Start_Date,Finish_Date,Adult_Price,NumberOfCities,Tour_Capacity)
