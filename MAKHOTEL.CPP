#include<fstream.h>    //for input-output functions and file handling
#include<conio.h>      //for getch() and clrscr()
#include<stdio.h>      //for gets() and puts()
#include<string.h>     //for string functions(strlen(),strcpy() and strcmp())
#include<stdlib.h>     //for randomize
#include<iomanip.h>    //for setprecision()
#include<ctype.h>      //for isdigit()
#include<process.h>    //for exit()
fstream booking_details; //file object for booking details
fstream member_details;  //file object for member details
class guest              //stores details and functions about number of adults and child
{
	short adult;
	short child;
	public:
	float total;
	void get_num();
	void disp_guest_num() //displays guest num
	{
		cout<<"Number of adults : "<<adult;
		cout<<"\nNumber of children : "<<child;
	}
	void disp_tot_price(float cost,int num)//to display total price
	{
		cout.setf(ios::fixed);
		cout<<setprecision(2)<<"\nTotal Price : $"<<cost*num<<endl;
		total=cost*num;
	}
};
void guest :: get_num()//to get number of adults and child
{
	repeat:
	cout<<"Number of adults (18 years and above) : ";
	while(!(cin>>adult))
	{
		cout<<"Invalid input !\n";
		cout<<"Enter number of adults again : ";
		cin.clear();
		cin.ignore();
	}
	while(adult<0)
	{	cout<<"Number of adults cannot be a negative number !\n";
		cout<<"Enter number of adults again : ";
		while(!(cin>>adult))
		{
			cout<<"Invalid input !\n";
			cout<<"Enter number of adults again : ";
			cin.clear();
			cin.ignore();
		}
	}
	cout<<"Number of children : ";
	while(!(cin>>child))
	{
		cout<<"Invalid input !\n";
		cout<<"Enter number of children again : ";
		cin.clear();
		cin.ignore();
	}
	while(child<0)
	{	cout<<"Number of children cannot be a negative number !\n";
		cout<<"Enter number of children again : ";
		while(!(cin>>child))
		{
			cout<<"Invalid input !\n";
			cout<<"Enter number of children again : ";
			cin.clear();
			cin.ignore();
		}
	}
	int total_num=adult+child;
	if(total_num==0)
	{
		cout<<"Invalid, Please re-enter the number of people! !\n";
		goto repeat;
	}
	while(total_num>6)
	{
		cout<<"We are sorry but you can book a hotel room for only 6 people at a time !\n";
		goto repeat;
	}
}
class member //stores member info and functions related to it
{
	int member_id;
	char member_name[100];
	char member_email[30];
	char member_passport[9];
	char member_password[21];
	public:
	int member_login(int id);
	void get_member_details();
} obj1;
void member :: get_member_details() //stores member details
{
	member_details.open("MEMBERS.DAT",ios::out|ios::app|ios::in|ios::binary);
	cout<<"Hello!\n";
	cout<<"Please enter your ID(It is in numeric format): ";
	while(!(cin>>member_id)) //to check for valid input
	{
		cout<<"Invalid input !\n";
		cout<<"Enter your ID again : ";
		cin.clear();
		cin.ignore();
	}
	while(member_id<1||member_id>99) //to check if id between 0 to 100
	{
		cout<<"Invalid member ID !\n";
		cout<<"Please enter your ID again (1-99) : ";
		while(!(cin>>member_id))
		{
			cout<<"Invalid input !\n";
			cout<<"Enter your ID again : ";
			cin.clear();
			cin.ignore();
		}
	}
	member temp;
	member_details.seekg(0L,ios::beg);
	member_details.read((char*)&temp,sizeof(temp));
	while(!member_details.eof())    //to check if member id is already used
	{
		if(temp.member_id==member_id)
		{
			cout<<"Member ID already taken, enter again : ";
			while(!(cin>>member_id))
			{
				cout<<"Invalid input !\n";
				cout<<"Enter your ID again : ";
				cin.clear();
				cin.ignore();
			}
			while(member_id<1||member_id>99)
			{
				cout<<"Invalid member ID !\n";
				cout<<"Please enter your ID again (1-99) : ";
				while(!(cin>>member_id))
				{
					cout<<"Invalid input !\n";
					cout<<"Enter your ID again : ";
					cin.clear();
					cin.ignore();
				}
			}
			member_details.seekg(0L,ios::beg);
		}
		member_details.read((char*)&temp,sizeof(temp));
	}
	cout<<"Please enter your Name : ";
	gets(member_name);
	while(strcmp(member_name," ")==0||strlen(member_name)==0) //to check for valid input
	{
		cout<<"Invalid name !\n";
		cout<<"Please enter your Name : ";
		gets(member_name);
	}
	cout<<"Please enter your Email : ";
	gets(member_email);
	int check=0;
	for(int i=0;i<strlen(member_email);++i)
		if(member_email[i]=='@')
			check=1;
	while(strcmp(member_email," ")==0||strlen(member_email)==0||check==0) //to check for valid input
	{
		cout<<"Invalid email !\n";
		cout<<"Please enter your Email : ";
		gets(member_email);
		for(int i=0;i<strlen(member_email);++i)
			if(member_email[i]=='@')
				check=1;
	}
	cout<<"Please enter your Passport number : ";
	gets(member_passport);
	while(strcmp(member_passport," ")==0||strlen(member_passport)==0||strcmp(member_passport,"0")==0 || strlen(member_passport)!=9 || isdigit(member_passport[0])!=0 || isdigit(member_passport[8])!=0) //to check for valid input
	{
		cout<<"Invalid passport number !\n";
		cout<<"Please enter your Passport number : ";
		gets(member_passport);
	}
	cout<<"Please enter your Password : ";
	gets(member_password);
	while(strcmp(member_password," ")==0||strlen(member_password)==0)  //to check valid inputs
	{
		cout<<"Invalid password !\n";
		cout<<"Please enter your Password : ";
		gets(member_password);
	}
	cout<<"\nThank you for signing up !\n";
	cout<<"Now you can enjoy a 10% discount of all your bookings !";
	member_details.close();
	member_details.open("MEMBERS.DAT",ios::out|ios::app|ios::in|ios::binary);
	member_details.write((char *)&obj1, sizeof(obj1));//writes the data given in the file
	member_details.close();
	getch();
	clrscr();
}
int member :: member_login(int id)
{
	member_details.open("MEMBERS.DAT",ios::in|ios::ate|ios::binary);
        if(!member_details)
	{
		cout<<"Our hotel has no members at the moment !\n";
		cout<<"To become a member choose the 2nd option !\n";
		return 1;
	} 
	int mem_pos=0;
	char org_password[21],input_password[21],name[100];
	member_details.seekg(0L,ios::beg);
	member_details.read((char *)&obj1, sizeof(obj1));
	while(!member_details.eof())
	{
		if(member_id==id)//if id exists,its password and username is copied
		{
			strcpy(org_password,obj1.member_password);
			strcpy(name,obj1.member_name);
			mem_pos=1;
		}
		member_details.read((char *)&obj1, sizeof(obj1));
	}
	if(mem_pos==0) //if member id doesnt exist
	{
		cout<<"Sorry but you are not a member !\n";
		member_details.close();
		return 0;
	}
	else
	{
		cout<<"Enter the Member Password : ";
		gets(input_password);
		char ch;
		if(strcmp(input_password,org_password)==0)//compares entered password and the real password
		{
			cout<<"Welcome back "<<name<<" !\n";
			member_details.close();
			return 1;
		}
		else
		{
			cout<<"Wrong password!\n";
			member_details.close();
			return 1;
		}
	}
}
class date //stores information and functions about date
{
	short day;
	short month;
	int year;
	public:
	void get_date();
	void show_date()
	{
		cout<<day<<'/'<<month<<'/'<<year;
	}
	friend void check(date &IN,date &OUT);
	friend void promo_out_date(date &IN, date &OUT, int day);
	friend int find_numofdays(date IN, date OUT)//finds number of days
	{
		int num = (OUT.day-IN.day)+(OUT.month-IN.month)*30+(OUT.year-IN.year)*360;
		return num;
	}
	int return_year()
	{
		return year;
	}
	int return_month()
	{
		return month;
	}
	date()
	{
		day=10;
		month=11;
		year=2018;
	}
} CHECK_IN,CHECK_OUT;
void date :: get_date() //to input date
{
	cout<<"Enter the day (DD) : ";
	while(!(cin>>day))  //to check if input is valid
	{
		cout<<"Invalid input !\n";
		cout<<"Enter the day again : ";
		cin.clear();
		cin.ignore();
	}
	while(day<1||day>30)  //to check if input is valid
	{
		cout<<"Please enter a day from 1 to 30 : ";
		while(!(cin>>day))
		{
			cout<<"Invalid input !\n";
			cout<<"Enter the day again : ";
			cin.clear();
			cin.ignore();
		}
	}
	cout<<"Enter the month (MM) : ";
	while(!(cin>>month))  //to check if input is valid
	{
		cout<<"Invalid input !\n";
		cout<<"Enter the month again : ";
		cin.clear();
		cin.ignore();
	}
	while(month<1||month>12)  //to check if input is valid
	{
		cout<<"Please enter a month from 1 to 12 : ";
		while(!(cin>>month))
		{
			cout<<"Invalid input !\n";
			cout<<"Enter the month again : ";
			cin.clear();
			cin.ignore();
		}
	}
	cout<<"Enter the year (YYYY) : ";
	while(!(cin>>year)) //to check if input is valid
	{
		cout<<"Invalid input !\n";
		cout<<"Enter the year again : ";
		cin.clear();
		cin.ignore();
	}
	while(year<2018||year>2021) //to check if input is valid
	{
		cout<<"Please enter a year after 2017 and before 2022 : ";
		while(!(cin>>year))
		{
			cout<<"Invalid input !\n";
			cout<<"Enter the year again : ";
			cin.clear();
			cin.ignore();
		}
	}
}
void check(date &IN, date &OUT)
{
	int check=0;
	while(!check) //to check if check in date is before check out date
	{
		clrscr();
		if(IN.year>OUT.year)
		{
			cout<<"Invalid date !\nEnter the dates again : \n\n";
			cout<<"CHECK IN\n";
			cout<<"--------\n\n";
			IN.get_date();
			cout<<"\n\nCHECK OUT\n";
			cout<<"---------\n\n";
			OUT.get_date();
		}
		else if(IN.year==OUT.year)
		{
			if(IN.month>OUT.month||(IN.month==OUT.month&&IN.day>OUT.day)||(IN.month==OUT.month&&IN.day==OUT.day))
			{
				cout<<"Invalid date !\nEnter the dates again :\n\n";
				cout<<"CHECK IN\n";
				cout<<"--------\n\n";
				IN.get_date();
				cout<<"\n\nCHECK OUT\n";
				cout<<"---------\n\n";
				OUT.get_date();
			}
			else
				check=1;
		}
		else
			check=1;
	}
}
void promo_out_date(date &IN,date &OUT,int day) //sets the date for check out
{
	if(IN.day+day<=30)
	{
		OUT.day=IN.day+day;
		OUT.month=IN.month;
		OUT.year=IN.year;
	}
	else
	{
		OUT.day=IN.day+day-30;
		OUT.month=IN.month+1;
		OUT.year=IN.year;
		if(OUT.month==13)
		{
			OUT.month=1;
			OUT.year++;
		}
	}
}
struct promo //stores information about promotion
{
	int days;
	int room;
	float cost;
} deal[5];
void promo(int num) //to create random promotions
{
	switch(num)
	{
		case 1: cout<<"Premium Room";
			break;
		case 2: cout<<"Deluxe Room";
			break;
		case 3: cout<<"Family Room";
			break;
		case 4: cout<<"Presidential Suite";
			break;
	}
}
class personal : public guest  //stores information and functions related to payment and guest information
{
	char first_name[30];
	char last_name[30];
	long pin_code;
	long long phone_no;
	char card_number[17];
	int doe_month;
	int doe_year;
	char otp[10];
	int ifmember;
	float cost;
	char room[30];
	int num_days;
	public:
	date CHECK_IN,CHECK_OUT;
	void disp_name()
	{
		cout<<"Full Name : "<<first_name<<' '<<last_name;
	}
	void show_details() //shows details
	{
		cout<<"\nCHECK IN : ";
		CHECK_IN.show_date();
		cout<<"\nCHECK OUT : ";
		CHECK_OUT.show_date();
		cout<<"\nNumber of days of stay : "<<return_numofdays();
		cout<<"\nType of Room : ";
		puts(room);
		disp_guest_num();
		cout<<"\nMember : ";
		cout.setf(ios::fixed);
		if(ifmember)
		{
			cout<<"Yes\n";
			cout<<"Discount : 10%\n";
		}
		else
			cout<<"No\n";
		cout<<setprecision(2)<<"Total Price : $"<<total<<endl;
	}
	void enter_details();
	char *return_first_name()
	{
		return first_name;
	}
	char *return_last_name()
	{
		return last_name;
	}
	int return_numofdays()
	{
		return num_days;
	}
	void equate_numofdays(int num)
	{
		num_days=num;
	}
	void store_room(int room_detail);
} PERS;
void personal :: enter_details() //to enter details
{
	char ch;
	int id;
	cout<<"\nEnter your First name : ";
	gets(first_name);
	while(strcmp(first_name," ")==0||strlen(first_name)==0) //to check if input is valid
	{
		cout<<"Invalid first name !\n";
		cout<<"Enter your First name again : ";
		gets(first_name);
	}
	cout<<"Enter your Last name : ";
	gets(last_name);
	while(strcmp(last_name," ")==0||strlen(last_name)==0) //to check if input is valid
	{
		cout<<"Invalid last name !\n";
		cout<<"Enter your Last name again : ";
		gets(last_name);
	}
	cout<<"Enter your Pin code : ";
	while(!(cin>>pin_code)) //to check if input is valid
	{
		cout<<"Invalid input !\n";
		cout<<"Enter your Pin code again : ";
		cin.clear();
		cin.ignore();
	}
	while(pin_code<100000||pin_code>1000000) //to check if input is valid
	{
		cout<<"Enter a valid pincode (6 digis) : ";
		while(!(cin>>pin_code))
		{
			cout<<"Invalid input !\n";
			cout<<"Enter your Pin code again : ";
			cin.clear();
			cin.ignore();
		}
	}
	cout<<"Enter your Phone number : ";
	while(!(cin>>phone_no)) //to check if input is valid
	{
		cout<<"Invalid input !\n";
		cout<<"Enter your Phone number again : ";
		cin.clear();
		cin.ignore();
	}
	while(phone_no<1000000) //to check if input is valid
	{
		cout<<"Invalid number !\n";
		cout<<"Enter your Phone number again : ";
		while(!(cin>>phone_no))
		{
			cout<<"Invalid input !\n";
			cout<<"Enter your Phone number again : ";
			cin.clear();
			cin.ignore();
		}
	}
	cout<<"Are you a member (y/Y for yes, any other character for no) : ";
	cin>>ch;
	ifmember=0;
	if(ch=='y'||ch=='Y')
	{
		cout<<"Enter your Member ID : ";
		while(!(cin>>id))  //to check if input is valid
		{
			cout<<"Invalid input !\n";
			cout<<"Enter your Member ID again : ";
			cin.clear();
			cin.ignore();
		}
		if(obj1.member_login(id))//to check if member,if its true, total cost is reduced by 10%
		{
			ifmember=1;
			total*=0.9;
		}
	}
	cout<<"Enter your Credit/Debit card number : ";
	gets(card_number);
	expired:
	while(strlen(card_number)!=16) //to check if input is valid
	{
		cout<<"Invalid card number !\n";
		cout<<"Enter the card number again (16 digits) : ";
		gets(card_number);
	};
	for(int i=0;i<strlen(card_number);++i)
	{
		if(!isdigit(card_number[i]))
		{
			cout<<"Invalid card number !(only numbers allowed)\n";
			cout<<"Enter the card number again : ";
			gets(card_number);
			goto expired;
		}
	}
	cout<<"Enter the month of expiration of the card (eg:jan is 1,dec is 12) : ";
	while(!(cin>>doe_month))  //to check if input is valid
	{
		cout<<"Invalid input !\n";
		cout<<"Enter the month of expiration of the card again : ";
		cin.clear();
		cin.ignore();
	}
	while(doe_month<1||doe_month>12)
	{
		cout<<"Invalid month !\n";
		cout<<"Enter the month of expiration again : ";
		while(!(cin>>doe_month))
		{
			cout<<"Invalid input !\n";
			cout<<"Enter the month of expiration of the card again : ";
			cin.clear();
			cin.ignore();
		}
	}
	cout<<"Enter the year of expiration of the card (yyyy) : ";
	while(!(cin>>doe_year))   //to check if input is valid
	{
		cout<<"Invalid input !\n";
		cout<<"Enter the year of expiration of the card again : ";
		cin.clear();
		cin.ignore();
	}
	while(doe_year>2036||doe_year<1000)
	{
		cout<<"Invalid expiration year !\n";
		cout<<"Enter the year of expiration again : ";
		while(!(cin>>doe_year))   //to check if input is valid
		{
			cout<<"Invalid input !\n";
			cout<<"Enter the year of expiration of the card again : ";
			cin.clear();
			cin.ignore();
		}
	}
	if(doe_year<CHECK_IN.return_year()||(doe_year==CHECK_IN.return_year()&&doe_month<CHECK_IN.return_month()))
	{
		cout<<"Card already expired !\n";
		cout<<"Enter the card number again : ";
		gets(card_number);
		goto expired;
	}
}
void personal :: store_room(int room_detail)
{
	if(room_detail==1)
		strcpy(room,"Premium Room");
	else if(room_detail==2)
		strcpy(room,"Deluxe Room");
	else if(room_detail==3)
		strcpy(room,"Family Room");
	else
		strcpy(room,"Presidential Suite");
}
void main()
{
	clrscr();
	int choice,room;
	while(1)
	{
		clrscr();
		cout<<"        MM     MM      A      K  K       H   H   OOO  TTTTT  EEEEE  L   \n";
		cout<<"        M M   M M     A A     K K        H   H  O   O   T    E      L   \n";
		cout<<"        M   M   M    AAAAA    KK         HHHHH  O   O   T    EEEEE  L   \n";
		cout<<"        M       M   A     A   K K        H   H  O   O   T    E      L   \n";
		cout<<"        M       M  A       A  K  K       H   H   OOO    T    EEEEE  LLLL\n\n";
		cout<<"1. Know about us\n";
		cout<<"2. Become a member\n";
		cout<<"3. Book a room\n";
		cout<<"4. Promotions\n";
		cout<<"5. Details about your booking\n";
		cout<<"6. How to contact us\n";
		cout<<"7. Details of all the Booking (for employees only)\n";
		cout<<"8. Exit the Booking System\n";
		cout<<"Enter your choice : ";
		while(!(cin>>choice)) //to check if input is valid
		{
			cout<<"Invalid input !\n";
			cout<<"Enter your choice again : ";
			cin.clear();
			cin.ignore();
		}
		while(choice<1||choice>8) //to check if input is valid
		{
			cout<<"Invalid option !";
			cout<<"\nEnter your choice again : ";
			while(!(cin>>choice)) //to check if input is valid
			{
				cout<<"Invalid input !\n";
				cout<<"Enter your choice again : ";
				cin.clear();
				cin.ignore();
			}
		}
		switch(choice)
		{
			case 1: clrscr();
				cout<<"	      		         -|  MAK HOTEL  |-                       \n";
				cout<<"	     -|                  [-_-_-_-_-_-_-_-]                  |-   \n";
				cout<<"	     [-_-_-_-_-]          |             |          [-_-_-_-_-]   \n";
				cout<<"	      | o   o |           [  0   0   0  ]           | o   o |    \n";
				cout<<"	       |     |    -|       |           |       |-    |     |     \n";
				cout<<"	       |     |_-___-___-___-|         |-___-___-___-_|     |     \n";
				cout<<"	       |  o  ]              [    0    ]              [  o  |     \n";
				cout<<"	       |     ]   o   o   o  [ _______ ]  o   o   o   [     | ------\n";
				cout<<"	------ |     ]              [ ||||||| ]              [     |     \n";
				cout<<"	       |     ]              [ ||||||| ]              [     |     \n";
				cout<<"	   _-_-|_____]--------------[_|||||||_]--------------[_____|-_-_ \n" ;
				cout<<"\t  ( (__________------------_____________-------------_________) )\n";
				cout<<"We are a 5 Star Hotel with its own private beach. ";
				cout<<"\nWe have the most happening discotheque in the city. ";
				cout<<"\nWe have 5 unique style restaurants with food cuisine from the different parts of the world. ";
				cout<<"\nAll the rooms are sea facing and offer a panoramic view of the beach incuding \nlovely sight of the sunrise. ";
				cout<<"\nWe are close to the international airport and closer to the main shopping \ndistricts in town. ";
				cout<<"\nWe also boast of a live theatre every weekend evening wherein we have star \ntroupes from across the country who perform to a full house audience. ";
				getch();
				break;
			case 2: clrscr();
				obj1.get_member_details();
				break;
			case 3: mod:
				clrscr();
				int numofdays;
				char wish,modify;
				float cost,total_cost;
				cout<<"CHECK IN\n";
				cout<<"--------\n\n";
				PERS.CHECK_IN.get_date();
				cout<<"\n\nCHECK OUT\n";
				cout<<"---------\n\n";
				PERS.CHECK_OUT.get_date();
				check(PERS.CHECK_IN,PERS.CHECK_OUT);
				numofdays=find_numofdays(PERS.CHECK_IN,PERS.CHECK_OUT);
				PERS.equate_numofdays(numofdays);
				if(PERS.return_numofdays()>10) //if days more than 10, booking isnt allowed
				{
					cout<<"We are sorry but you cannot book a room for more than 10 days !\n";
					cout<<"Please enter the Check-In and Check_Out date again after enterring any character";
					getch();
					goto mod;
				}
				clrscr();
				PERS.get_num();
				clrscr();
				do
				{
					cout<<"Select a room :\n\n";
					cout<<"1. Premier Room\n";
					cout<<"2. Deluxe Room\n";
					cout<<"3. Family Room\n";
					cout<<"4. Presidential Suite\n";
					cout<<"Please enter your choice to see the details about the room : ";
					while(!(cin>>room))
					{
						cout<<"Invalid input !\n";
						cout<<"Enter your choice of room again : ";
						cin.clear();
						cin.ignore();
					}
					while(room<1||room>4)
					{
						cout<<"No such room available !\n";
						cout<<"Enter your choice of room again : ";
						while(!(cin>>room)) //to check if input is valid
						{
							cout<<"Invalid input !\n";
							cout<<"Enter your choice of room again : ";
							cin.clear();
							cin.ignore();
						}
					}
					PERS.store_room(room);
					switch(room)
					{
						case 1: cost=random(471.14-403.14+1)+403.14;
							cout<<"\n32-inch TV, air conditioning, spacious bathroom with shower, tea and coffee\nmaking machine, complimentary 2 bottles mineral water, garden view rooms,\ncomplimentary wi-fi\n\n";
							break;
						case 2: cost=random(571.14-491.17+1)+491.17;
							cout<<"\n49-inch TV, air conditioning, spacious bathroom with bath tub and shower, tea\nand coffee making machine, hair dryer, in-room electronic safe, morning\nnewspaper, minibar, complimentary 2 bottles mineral water, garden view rooms,\ncomplimentary wi-fi\n\n";
							break;
						case 3: cost=random(771.14-693.17+1)+693.17;
							cout<<"\n49-inch TV, air conditioning, extra 2 beds for children, spacious bathroom with bath tub and shower, tea and coffee making machine, hair dryer, in-room\nelectronic safe, ironing board and steam iron, morning newspaper, minibar,\ncomplimentary 2 bottles mineral water, beach view rooms, complimentary wi-fi\n\n";
							break;
						case 4: cost=random(1041.14-891.17+1)+891.17;
							cout<<"\n75-inch TV, individual air conditioning unit, study room with table and\ndedicated internet connection, spacious bathroom with bath tub, shower and\ndressing room, hotel robes, tea and coffee making machine, hair dryer, in-room\nelectronic safe, ironing board and steam iron, morning newspaper, minibar,\ncomplimentary 2 bottles mineral water, beach view rooms with balconies, personalbutler, chef on demand cuisine room service\n\n";
							break;
					}
					cout<<"If you wish to see the details of another room input 'y'/'Y', otherwise any \nother character : ";
					cin>>wish;
					clrscr();
				} while(wish=='y'||wish=='Y');
				clrscr();
				cout<<"\t\t\t\tBooking Details\n";
				cout<<"\t\t\t\t---------------\n\n";
				cout<<"CHECK IN : ";
				PERS.CHECK_IN.show_date();
				cout<<"\n\nCHECK OUT : ";
				PERS.CHECK_OUT.show_date();
				cout<<"\n\n";
				cout<<"Number of days of stay : "<<PERS.return_numofdays()<<endl;
				PERS.disp_guest_num();
				PERS.disp_tot_price(cost,PERS.return_numofdays());
				cout<<"\nDo you wish to modify the above data (y/Y for yes, any other character for no) ?";
				cin>>modify;
				if(modify=='Y'||modify=='y')
					goto mod;
				clrscr();
				cout<<"Personal and Payment Information : \n";
				PERS.enter_details();
				booking_details.open("BOOKING.dat",ios::app|ios::binary);
				booking_details.write((char *)&PERS, sizeof(PERS));
				clrscr();
				cout<<"Your room has been booked !\n";
				cout<<"We will send you an email containing all the details about your booking !\n";
				cout<<"Enjoy your stay at MAK hotel\n";
				booking_details.close();
				getch();
				clrscr();
				break;
			case 4: clrscr();
				randomize();
				int days,promonum;
				float price;
				cout<<"\n\nHOT PROMOS FOR THIS WEEK!!!!\n";
				for(int i=0;i<5;++i)
				{
					cout<<"\nPROMO "<<i+1<<":";
					promonum=random(4)+1;
					promo(promonum);
					deal[i].room=promonum;
					cout<<" for ";
					days=random(4)+2;
					cout<<days;
					deal[i].days=days;
					cout<<" days at $";
					switch(promonum)
					{
						case 1: cost=random(321.14-253.14+1)+253.14;
							break;
						case 2: cost=random(571.14-391.17+1)+391.17;
							break;
						case 3: cost=random(671.14-493.17+1)+493.17;
							break;
						case 4: cost=random(941.14-591.17+1)+591.17;
							break;
					}
					price=cost;
					deal[i].cost=price;
					price*=days;
					cout.setf(ios::fixed);
					cout<<setprecision(2)<<price;
				}
				int promoch;
				cout<<"\n\nTerms and conditions:1)All bookings are non refundable.";
				cout<<"\n                     2)Free morning buffet.";
				cout<<"\n                     3)Extra charges for additional services.";
				cout<<"\n\nDo you want to make use of any of these deals. If yes, enter the appropriate\nnumber, otherwise enter random number : ";
				while(!(cin>>promoch))  //to check if input is valid
				{
					cout<<"Invalid input !\n";
					cout<<"Enter the appropriate or random number again : ";
					cin.clear();
					cin.ignore();
				}
				clrscr();
				if(promoch>=1&&promoch<=5)
				{
					mod1:
					clrscr();
					char wish,modify;
					cout<<"CHECK IN\n";
					cout<<"--------\n\n";
					PERS.CHECK_IN.get_date();
					promo_out_date(PERS.CHECK_IN,PERS.CHECK_OUT,deal[promoch-1].days);
					clrscr();
					PERS.get_num();
					clrscr();
					room=promonum;
					PERS.store_room(room);
					clrscr();
					cout<<"\t\t\t\tBooking Details\n";
					cout<<"\t\t\t\t---------------\n\n";
					cout<<"CHECK IN : ";
					PERS.CHECK_IN.show_date();
					cout<<"\n\nCHECK OUT : ";
					PERS.CHECK_OUT.show_date();
					cout<<"\n\n";
					PERS.disp_guest_num();
					PERS.disp_tot_price(deal[promoch-1].cost,deal[promoch-1].days);
					PERS.equate_numofdays(deal[promoch-1].days);
					cout<<"\nDo you wish to modify the above data (y/Y for yes, any other character for no) ? ";
					cin>>modify;
					if(modify=='Y'||modify=='y')
						goto mod1;
					clrscr();
					cout<<"Personal and Payment Information : \n";
					PERS.enter_details();
					booking_details.open("BOOKING.dat",ios::out|ios::app|ios::binary);
					booking_details.write((char *)&PERS, sizeof(PERS));
					clrscr();
					cout<<"Your room has been booked !\n";
					cout<<"We will send you an email containing all the details about your booking !\n";
					cout<<"Enjoy your stay at MAK hotel\n";
					booking_details.close();
				}
				break;
			case 5: clrscr();
				char first[30],last[30];
				int checkbook=0;
				booking_details.open("BOOKING.dat",ios::in|ios::binary);
				if(!booking_details) //to check if the file is empty
				{
					cout<<"No booking has been made till now !\n";
					cout<<"Please choose option '3' to book a room !\n";
				}
				else
				{
					cout<<"\t\t\tDetails about your Booking\n";
					cout<<"\t\t\t----------------------------------\n\n";
					cout<<"Enter the first name under which the booking was made : ";
					gets(first);
					while(strcmp(first," ")==0||strlen(first)==0) //to check if input is valid
					{
						cout<<"Invalid first name !\n";
						cout<<"Enter the first name again : ";
						gets(first);
					}
					cout<<"Enter the last name : ";
					gets(last);
					while(strcmp(last," ")==0||strlen(last)==0) //to check if input is valid
					{
						cout<<"Invalid last name !\n";
						cout<<"Enter the last name again : ";
						gets(last);
					}
					booking_details.read((char *)&PERS, sizeof(PERS));
					while(!booking_details.eof())   //finds the booking and display details
					{
						if(strcmpi(first,PERS.return_first_name())==0&&strcmpi(last,PERS.return_last_name())==0)
						{
							checkbook=1;
							PERS.show_details();
							getch();
						}
						booking_details.read((char *)&PERS, sizeof(PERS));
					}
					if(checkbook==0)
					{
						cout<<"No booking has been made under that name !\n";
						getch();
					}
				}
				booking_details.close();
				clrscr();
				break;
			case 6: clrscr();
				randomize();
				cout<<"How to contact us :-";
				cout<<"\n\nGet in touch with us";
				cout<<"\n\nFor ticketing or reservations enquiries please call : +91 ";
				cout<<random(9999-1000+1)+1000<<random(999-100+1)+100<<random(999-100+1)+100;
				cout<<"\nReservations/ticketing enquiries email : makreservations@makisthebest.com";
				cout<<"\nOther enquiries email  : makeverything@makisthebest.com";
				cout<<"\nFeedback email : nobadfeedbacksformak@makisthebest.com";
				getch();
				clrscr();
				break;
			case 7: clrscr();
				long ID;
				char password[21];
				cout<<"\nEnter your Employee ID : ";
				while(!(cin>>ID)) //to check if input is valid
				{
					cout<<"Invalid input !\n";
					cout<<"Enter your Employee ID again : ";
					cin.clear();
					cin.ignore();
				}
				cout<<"Enter your password : ";
				gets(password);
				while(strcmp(password," ")==0||strlen(password)==0) //to check if input is valid
				{
					cout<<"Invalid password !\n";
					cout<<"Enter your password again : ";
					gets(password);
				}
				if(strcmp(password,"MAKhotel")==0) //to check if the password entered is correct
				{
					fstream file("TEMP.dat",ios::out|ios::in|ios::trunc|ios::binary);
					booking_details.open("BOOKING.dat",ios::in|ios::out|ios::binary|ios::ate);
					if(!booking_details) //to checck if the file is empty
					{
						cout<<"No booking has been made till now !\n";
					}
					else
					{
						int no=booking_details.tellg()/sizeof(PERS);
						personal *temp=new personal[no];
						booking_details.seekg(0L,ios::beg);
						for(int i=0;!booking_details.eof();++i)
							booking_details.read((char*)&temp[i],sizeof(personal));
						for(i=0;i<no-1;++i)    //sorts the booking details in ascending order using selection sort
						{
							int small=temp[i].total,pos=i;
							for(int j=i+1;j<no;++j)
							{
								if(temp[j].total<small)
								{
									small=temp[j].total;
									pos=j;
								}
							}
							personal temp1=temp[i];
							temp[i]=temp[pos];
							temp[pos]=temp1;
						}
						for(i=0;i<no;++i)
							file.write((char *)&temp[i],sizeof(personal));
						file.seekg(0L,ios::beg);
						file.read((char *)&PERS, sizeof(PERS));
						while(!file.eof()) //displays all the booking information
						{
							clrscr();
							cout<<"\t\t\tDetails about Booking\n";
							cout<<"\t\t\t---------------------\n\n";
							PERS.disp_name();
							PERS.show_details();
							file.read((char *)&PERS, sizeof(PERS));
							cout<<"\nPress any character for the next booking !";
							getch();
						}
						delete temp;
						clrscr();
						cout<<"Have a nice day employee : "<<ID;
					}
					booking_details.close();
					file.close();
				}
				else
					cout<<"Wrong password !\nGood bye.";
				getch();
				break;
			case 8: clrscr();
				cout<<"Thank you for using MAK hotel website !\n";
				cout<<"See you soon\n";
				cout<<"Bye Bye!";
				getch();
				clrscr();
				exit(0);  //exits out of the loop
		}
	}
}