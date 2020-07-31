///HOTEL SCHOOLVIEW
///PROJECT DONE BY ABISHEK.S AND AHMED SHAMSUDEEN, class 12-A

#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<fstream>
#define _WIN32_WINNT 0x0500        ///FOR FULL SCREEN VIEWING
#include<windows.h>
#include<dos.h>
#include<conio.h>
#include<bits/stdc++.h>
#include<time.h>
#include<graphics.h>
#include<cstring>

using namespace std;

///CLASS DEFINITIONS.....
///Class customer for storing details of each booking of a customer
class customer {
public:
    char name[50];            ///Name of customer
    char address[250];        ///Address of customer's residence
    int age;                  ///Age of customer as on the date of booking
    int rtype;                ///room type: 1. A.C Deluxe  2. A.C Luxury  3. NON-A.C------THERE ARE 10 ROOMS OF EACH TYPE
    string phno;              ///customer's contact number
    int memb;                 ///number of members
    int laundry;              ///customer's choice for laundry service:1 for YES,0 for NO
    int food;                 ///customer's choice for food service:1 for YES,0 for NO
    int cndate;               ///check-in date dd format
    int cnmonth;              ///check-in month mm format
    int cnyear;               ///check in year  yyyy format
    int codate;               ///check-out date dd format
    int comonth;              ///check-out month mm format
    int coyear;               ///check out year yyyy format
    int nroom;                ///number of rooms booked
	int id;                   ///user identification number
	///Constructors:
	customer(){
        strcpy(name,"\0");
        strcpy(address,"\0");
        age=rtype=cndate=cnmonth=cnyear=codate=comonth=coyear=0;
        phno="";
        food=laundry=memb=0;
        nroom=0;
        id=0;
    }
	///Functions.....
	friend istream&  operator>>(istream&  str,customer&  a) {    ///To input customer details from users.txt file
       char ch;
       str.get(ch);
       if(ch!='\n'&&ch!='\0') str.unget();
       str.getline((char*)&(a.name),50,'\n');
       str.getline((char*)&(a.address),250,'\n');
       str>>a.phno>>a.age>>a.rtype>>a.cndate>>a.cnmonth>>a.cnyear>>a.codate>>a.comonth>>a.coyear>>a.nroom>>a.id>>a.laundry>>a.food>>a.memb;
       return str;

    }
    friend ostream&  operator<<(ostream& str,const customer &a) {    ///To output customer details to users.txt file
       str.write((char*)&(a.name),strlen(a.name));
       str<<'\n';
       str.write((char*)&(a.address),strlen(a.address));
       str<<'\n';
       str<<a.phno<<' '<<a.age<<' '<<a.rtype<<' '<<a.cndate<<' '<<a.cnmonth<<' '<<a.cnyear<<' '<<a.codate<<' '<<a.comonth<<' '<<a.coyear<<' '<<' '<<a.nroom<<' '<<a.id<<' '<<a.laundry<<' '<<a.food<<' '<<' '<<a.memb<<'\n';
       return str;
    }
};

///Class room for storing status of each room
class room{
public:
    int rno;       ///ROOM NO
    char status;   ///'b'-BOOKED    'a'-AVAILABLE(EMPTY)
    customer c;    ///CUSTOMER IN THAT ROOM
};

map<int,room> r;  ///This is to keep track of rooms and their status

///Class hotel to take care of the hotel operations
class hotel:protected room{
protected:
    vector<pair<string,string> > emps;  ///Hotel employee details: user name,password
public:
	///Member Functions-prototypes
	void addemp(string);
	void dsearch();
	void nsearch();
	void addtorecord(customer&);
	void emplogin();
	int  available(int,int,int,int,int,int,int,int);
	int nodays(int,int,int,int,int,int);
	void book();
	double discount(int);
	string encDec(string& , char);
	int full(int,int,int,int,int);
	int genbill(int);
	int genbill(int,int,int,int);
	void homescreen();
	int id();
	void allroom(int);
	void incemps();
	int IsInRange(int,int,int,int,int,int,int,int,int);
	void loginscreen();
	void remodate(int,int,int,int,int,int,int,int);
	void userlogin();
	void usermanage(int);
	void vacate(int);
	void viewdetails(int);
	int iscorrect(int,int,int);
	int iscorrect(int,int,int,int,int,int);
	int  checkdate(int,int,int,int,int,int);
	void adminlogin();
};

///MEMBER FUNCTION DEFINITIONS.....
///Class room member functions
void hotel::allroom(int id=-1){     ///To allot rooms properly each time program is closed and opened again
    for(int i=100;i<=130;i++){
    customer d;
    r[i].status='a';
    r[i].rno=i;
    r[i].c=d;
    }
    fstream fin("rooms.txt",ios::in);
    customer c;
    time_t timer;
    timer=time(NULL);
    struct tm* timers=localtime(&timer);
    int rn;char st;
    ofstream fout;
    int cnt=0;
    cout<<"\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t"<<ctime(&timer);
    cout<<"\n\n\t\t\t\t\tVACATING TODAY(ROOM NUMBERS) : ";
    while(fin>>rn&&fin>>st&&fin>>c){
        if(id!=-1){
        if(c.codate==timers->tm_mday&&c.comonth==timers->tm_mon+1&&c.coyear==timers->tm_year+1900&&c.id==id){
            r[rn].status='a';
            customer d;
            r[rn].c=d;
            r[rn].rno=rn;
        }
        }
        else{
        if(c.codate==timers->tm_mday&&c.comonth==timers->tm_mon+1&&c.coyear==timers->tm_year+1900){
            cout<<rn<<'('<<c.rtype<<")  ";
            cnt++;
            r[rn].status=st;
            r[rn].rno=rn;
            r[rn].c=c;
        }
        else{
            if(c.cndate==timers->tm_mday&&c.cnmonth==timers->tm_mon+1&&c.cnyear==timers->tm_year+1900){
               r[rn].status='a';
               r[rn].rno=rn;
               customer d;
               r[rn].c=d;
            }
            else{
            r[rn].status=st;
            r[rn].rno=rn;
            r[rn].c=c;
            }
        }
        }
    }
    if(cnt==0) cout<<"--NIL--";
    fin.close();
    fin.open("users.txt");
    fout.open("rooms.txt",ios::trunc);
    int i1=100,i2=101,i3=102,j;
    int ct=0;
   cout<<"\n\n\t\t\t\t\tROOM ALLOTMENTS TODAY ";

    while(fin>>c){
        if(c.cndate==timers->tm_mday&&c.cnmonth==timers->tm_mon+1&&c.cnyear==timers->tm_year+1900&&iscorrect(c.cndate,c.cnmonth,c.cnyear)==0){
            int cnt=0;
            if(c.rtype==1) j=i1;
            else if(c.rtype==2) j=i2;
            else if(c.rtype==3) j=i3;
            while(cnt<c.nroom){
            while(r[j].status!='a') {j=j+3;}
            r[j].rno=j;
            r[j].status='b';
            r[j].c=c;
            cnt++;
            }
        }
    }
    for(int i=100;i<=130;i++){
        fout<<r[i].rno<<" "<<r[i].status<<"\n"<<r[i].c<<"\n";
        if(r[i].status=='b'){
            ct++;
            cout<<"\n\t\t\t\t\t"<<r[i].rno<<'('<<r[i].c.rtype<<") "<<"--->"<<' '<<r[i].c.id;
        }
    }
    if(ct==0) cout<<"---NIL---";
    cout<<"\n\n";
    fin.close();
    fout.close();
    if(id!=-1)
    system("pause");
}

int hotel::full(int rtype,int n,int cd ,int cm,int cy){   ///To check if a room of given type is vacant on a given day
     int a=0,b=0,c=0,d=0,rt=0;
     ifstream fin("dates.txt");
     while(!fin.eof()){
        fin>>a>>b>>d>>rt;
        if (a==cd&&b==cm&&d==cy&&rtype==rt)
            c++;
     }
     fin.close();
     if(c+n>10) return 0;
     else return 1;
}

int hotel::iscorrect(int cnd,int cnm,int cny){    ///To check if booking is allowed for the check in date
      time_t timer=time(NULL);
      struct tm new1;
      new1.tm_hour=12;new1.tm_min=2;new1.tm_sec=59;new1.tm_mon=cnm-1;new1.tm_mday=cnd;new1.tm_year=cny-1900;
      double sec=difftime(mktime(&new1),timer);
      if(sec>=0) return 1;
      else return 0;
}

int hotel::iscorrect(int cnd,int cnm,int cny,int cod,int com,int coy){   ///To check if the check in date and check out date are proper in terms of time
      struct tm new1;
      new1.tm_hour=12;new1.tm_min=2;new1.tm_sec=59;new1.tm_mon=cnm-1;new1.tm_mday=cnd;new1.tm_year=cny-1900;
      struct tm new2;
      new2.tm_hour=12;new2.tm_min=2;new2.tm_sec=59;new2.tm_mon=com-1;new2.tm_mday=cod;new2.tm_year=coy-1900;
      double sec=difftime(mktime(&new2),mktime(&new1));
      if(sec>=0) return 1;
      else return 0;
}

int hotel::available(int rtype,int n,int cnd,int cnm,int cny,int cod,int com,int coy){  ///To check if rooms of a given type are available
     int i=cnd , j=cnm,k=cny;                                                           ///for the entered dates
     while(i!=cod || j!=com||k!=coy){
        if(full(rtype,n,i,j,k)==0) return 0;
        if((i==31&&(j==1||j==3||j==5||j==7||j==8||j==10)) || (i==30&&(j==4||j==6||j==9||j==11)) || (i==28&&j==2&&k%4!=0)||(i==29&&j==2&&k%4==0))
           {i=0; j++;}
        else if(i==31&&j==12) {i=0;j=1;k++;}
        i++;
     }
     ofstream fout("dates.txt",ios::app);
     int c=0;
     while(c<n){
        i=cnd;
        j=cnm;
        k=cny;
        while(i!=cod || j!=com||k!=coy){
           fout<<i<<" "<<j<<" "<<k<<" "<<rtype<<"\n";
           if((i==31&&(j==1||j==3||j==5||j==7||j==8||j==10)) || (i==30&&(j==4||j==6||j==9||j==11)) || (i==28&&j==2&&k%4!=0)||(i==29&&j==2&&k%4==0))
              {i=0; j++;}
           else if(i==31&&j==12) {i=0;j=1;k++;}
           i++;
        }
        c++;
     }
     fout.close();
     return 1;
}

int hotel::nodays(int cnd,int cnm,int cny,int cod,int com,int coy){   ///To find number of days between the check in and check out dates
     int i=cnd,j=cnm,k=cny;
     int nodays=0;
     while(i!=cod||j!=com||k!=coy) {
        if((i==31&&(j==1||j==3||j==5||j==7||j==8||j==10)) || (i==30&&(j==4||j==6||j==9||j==11)) || (i==28&&j==2&&k%4!=0)||(i==29&&j==2&&k%4==0))
           {i=0; j++;}
        else if(i==31&&j==12) {i=0;j=1;k++;}
        i++;
        nodays++;
     }
     return nodays;
}

int hotel::checkdate(int cnd,int cnm,int cny,int cod,int com,int coy){   ///To check if the check in date and check out date are proper
    int res=0;
    if(cnd>=1&&cnm>=1&&cnm<=12&&(cnd<=31&&(cnm==1||cnm==3||cnm==5||cnm==7||cnm==8||cnm==10||cnm==12)) ||
       (cnd<=30&&(cnm==4||cnm==6||cnm==9||cnm==11)) || (cnd<=28&&cnm==2&&cny%4!=0)||(cnd<=29&&cnm==2&&cnm%4==0)) res++;
    if(cod>=1&&com>=1&&com<=12&&(cod<=31&&(com==1||com==3||com==5||com==7||com==8||com==10||cnm==12)) ||
       (cod<=30&&(com==4||com==6||com==9||com==11)) || (cod<=28&&com==2&&coy%4!=0)||(cod<=29&&com==2&&com%4==0)) res++;
    return res;
}

double hotel::discount(int l) {   ///To find discount applicable
     if(l==0) return 0;
     else if(l==1) return 3;
     else if(l==2) return 5;
     else if(l<=5&&l>2) return 10;
     else if(l<=10&&l>5) return 15;
     else return 20;
}

void hotel::homescreen() {   ///To display the standard homescreen
     system("COLOR B2");
     cout<<"\n\t\t\t\t\t\t\t*********************************************";
     cout<<"\n\t\t\t\t\t\t\t************ HOTEL SCHOOLVIEW ***************";
     cout<<"\n\t\t\t\t\t\t\t*********************************************";
     cout<<"\n\n\n";
     cout<<"\t\t\t\t\t\t\t\t  KOTTUR GARDENS,\n\n\t\t\t\t\t\t\t\t    KOTTURPURAM,\n\n\t\t\t\t\t\t\t\t  CHENNAI-600024.";
     cout<<"\n\n\n\t\t\t\tOUR HOTEL ALLOWS NO CANCELLATION OF BOOKED ROOMS!!ONLY RESCHEDULING IS ALLOWED!!";
     string a="admin",b="admin";
     pair<string,string> p(a,b);
     emps.push_back(p);
     system("pause");
     loginscreen();
     return;
}

void hotel::loginscreen() {   ///To choose whether we are an employee or customer or ADMIN
     time_t timer;
     timer=time(NULL);
     system("COLOR B2");
     int i=0;
     while(i!=4) {
         system("cls");
         system("COLOR B2");
         cout<<"\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t"<<ctime(&timer);
         cout<<"\n\t\t\t\t\t\t\t*********************************************";
         cout<<"\n\t\t\t\t\t\t\t*************  HOTEL   PAAR  ****************";
         cout<<"\n\t\t\t\t\t\t\t*********************************************";
         cout<<"\n\n\n";
         cout<<"\t\t\t\t\t\tSELECT  : "
             <<"\n\t\t\t\t\t\t\t1.EMPLOYEE Login"
             <<"\n\t\t\t\t\t\t\t2.USER Login"
             <<"\n\t\t\t\t\t\t\t3.ADMIN Login"
             <<"\n\t\t\t\t\t\t\t4.EXIT";
         cin>>i;
         switch(i) {
             case 1:{
                 emplogin();
             }
             break;
             case 2:{
                 userlogin();
             }
             break;
             case 4:{
                 system("cls");
                 system("COLOR 07");
                 time_t timer1;
                 timer1=time(NULL);
                 cout<<"\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t"<<ctime(&timer1)<<"\n\n";
                 cout<<"\n\n\n\n\n\t\t\t\t\t\t-----  |   |  -----  |----  |    |     |    |   -------  |     |     |  |"
                             <<"\n\t\t\t\t\t\t  |    |   |  |   |  |   |  |    |     |    |   |     |  |     |     |  |"
                             <<"\n\t\t\t\t\t\t  |    -----  -----  |   |  |___-      |----|   |     |  |     |     |  |"
                             <<"\n\t\t\t\t\t\t  |    |   |  |   |  |   |  |   -|          |   |     |  |     |     |  |"
                             <<"\n\t\t\t\t\t\t  |    |   |  |   |  |   |  |    |      ----|   -------  -------     *  *";
                delay(500);
                system("color 17");
                delay(500);
                system("color 27");
                delay(500);
                system("COLOR 37");
                delay(500);
                system("color 47");
                delay(500);
                system("color 57");
                delay(500);
                system("color 67");
                delay(500);
                system("color 07");
                delay(500);
            }
            break;
            case 3: {
                system("cls");
                adminlogin();
            }
            break;
            default:
                cout<<"\n\n\t\t\t\t\tENTER CORRECTLY : ";
                delay(2000);
         }
      }
}

void hotel::viewdetails(int id){   ///To view details of a customer
      ifstream fin("users.txt");
      customer c;
      while(!fin.eof()) {
          fin>>c;
          if(c.id==id) break;
      }
      system("cls");
      time_t timer;
      timer=time(NULL);
      system("COLOR B2");
      cout<<"\t\t\t\t\t\t\t\t\t\t"<<ctime(&timer);
      cout<<"\n\t\t\t\t\t\t\t*********************************************";
      cout<<"\n\t\t\t\t\t\t\t*************  HOTEL   PAAR  ****************";
      cout<<"\n\t\t\t\t\t\t\t*********************************************";
      cout<<"\n\n\n\t\t\t\tNAME : ";
      puts(c.name);
      cout<<"\n\t\t\t\tADDRESS : ";
      puts(c.address);
      cout<<"\n\t\t\t\tAGE : "<<c.age<<"\n\t\t\t\tID : "<<c.id<<'\n';
      system("pause");
}

void hotel::userlogin() {
      system("cls");
      time_t timer;
      timer=time(NULL);
      system("COLOR B2");
      cout<<"\t\t\t\t\t\t\t\t\t\t"<<ctime(&timer);
      cout<<"\n\t\t\t\t\t\t\t*********************************************";
      cout<<"\n\t\t\t\t\t\t\t*************  HOTEL   PAAR  ****************";
      cout<<"\n\t\t\t\t\t\t\t*********************************************";
      int k=0,i=1;
      while(i==1){
        cout<<"\n\n\n\t\t\t\t\tEnter your ID : ";
        cin>>k;
        int l=0;
        ifstream fin("users.txt");
        customer c;
        system("cls");
        cout<<"\n\n\n\n\n\n\t\t\t\t\t\tSearching....";
        delay(1000);
        cout<<".";
        delay(1000);
        cout<<"..";
        delay(1000);
        cout<<"..";
        while(fin>>c) {
           if(c.id==k){
               l++;
               break;
           }
        }
        fin.close();
        if(l==0) {
            i=0;
            system("cls");
            cout<<"\n\n\n\t\t\t\t\tNO SUCH RECORD!!Click 1 to enter again 2 to exit";
            while(i!=1&&i!=2){
               cin>>i;
               if (i==2) return;
               else if(i!=1) {
                    system("cls");
                    cout<<"\n\n\n\t\t\t\t\tEnter proper number.....(1 to enter 2 to exit)";
                    delay(2000);
               }
            }
        }
        else{
           int j=0;
           while(j!=4) {
              system("cls");
              system("COLOR B2");
              time_t timer1;
              timer1=time(NULL);
              struct tm* time1=localtime(&timer1);
              system("COLOR B2");
              cout<<"\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t"<<ctime(&timer1);
              cout<<"\n\n\t\t\t\t\t\tWELCOME ";
              puts(c.name);
              cout<<"\n\t\t\t\t\t\tID : "<<c.id;
              fin.open("rooms.txt");
              int rn,cnt=0;
              char st;
              customer d;
              while(fin>>rn&&fin>>st&&fin>>d){
                 if(d.id==c.id) {
                    if(cnt==0)
                       cout<<"\n\t\t\t\t\t\tROOMS ALLOTTED: ";
                    cout<<rn<<'('<<d.rtype<<")  ";
                    cnt++;
                }
              }
              cout<<"\n\n";
              fin.close();
              fin.open("rooms.txt");
              int roo=0;
              cnt=0;
              while(fin>>rn&&fin>>st&&fin>>d){
                if(d.codate==time1->tm_mday&&d.comonth==time1->tm_mon+1&&d.coyear==time1->tm_year+1900&&d.id==c.id) {
                   if(cnt==0) cout<<"\n\t\t\t\t\tROOMS TO BE VACATED: ";
                   cout<<rn<<'('<<d.rtype<<")  ";
                   cnt++;
                }
              }
              if(cnt!=0)
                 cout<<"\n\t\t\t\t\tHOPE YOU ENJOYED YOUR STAY WITH US!!";
              fin.close();
              cout<<"\n\t\t\t\t\t\t\t*********************************************";
              cout<<"\n\t\t\t\t\t\t\t************** USER   PORTAL ****************";
              cout<<"\n\t\t\t\t\t\t\t*********************************************";
              cout<<"\n\n\n";
              cout<<"\t\t\t\tSELECT  :\n ";
              cout<<"\n\n\t\t\t\t1.VIEW DETAILS "
                  <<"\n\t\t\t\t2.VIEW AVAILABLE DISCOUNT "
                  <<"\n\t\t\t\t3.CHECK AVAILABILITY "
                  <<"\n\t\t\t\t4.LOGOUT ";
              cout<<"\n\t\t\t\tENTER YOUR CHOICE.....";
              cin>>j;
              switch(j){
                case 1:{
                    system("cls");
                    viewdetails(c.id);
                }
                break;
                case 2:{
                    system("cls");
                    fin.open("users.txt");
                    int l=0;
                    customer d;
                    while(fin>>d)
                      if(d.id==c.id) l++;
                    fin.close();
                    cout<<"\n\n\t\t\t\tYOU ARE ELIGIBLE FOR A DISCOUNT OF : "<<discount(l)<<"%";
                    system("pause");
                }
                break;
                case 3:{
                    system("cls");
                    int cnd,cnm,com,cod,coy,cny,n,rt;
                    int j=1;
                    while(j==1){
                       cout<<"\n\n\t\t\t\tEnter the check in date,check in month,check in year:";
                       cin>>cnd>>cnm>>cny;
                       cout<<"\n\t\t\t\t\tEnter the check out date,check out month,check out year:";
                       cin>>cod>>com>>coy;
                       if(iscorrect(cnd,cnm,cny)==0||iscorrect(cnd,cnm,cny,cod,com,coy)==0) {
                          system("cls");
                          cout<<"\n\n\n\t\t\t\tCAN'T CHECK AVAILABIITY FOR THE ENTERED DATE!!";
                          cout<<"\n\t\t\t\t\t\tCLICK 1 TO ENTER ANOTHER DATE,ANY OTHER NUMBER TO EXIT";
                          cin>>j;
                       }
                       else j=-1;
                    }
                    if(j!=-1) break;
                    cout<<"\n\t\t\t\tEnter number of rooms required in the selected dates : ";
                    cin>>n;
                    cout<<"\n\t\t\t\tEnter the room type(1. A.C Deluxe  2. A.C Luxury  3. NON-A.C): ";
                    cin>>rt;
                    int k=available(rt,n,cnd,cnm,cny,cod,com,coy);
                    if(k==1) {
                        system("cls");
                        cout<<"\n\n\n\n\t\t\t\tROOMS AVAILABLE IN THE SELECTED DATES!!!HURRY UP AND BOOK FAST!!";
                    }
                    else{
                        system("cls");
                        cout<<"\n\n\n\n\t\t\t\tSORRY!!SELECTED NUMBER OF ROOMS NOT AVAILABLE IN THE SELECTED DATES....\n\n\t\tCHECK FOR AN ALTERNATIVE!!";
                    }
                    cout<<"\n";
                    system("pause");
                }
                break;
                case 4:{
                    system("cls");
                    cout<<"\n\n\n\n\n\n\t\t\t\t\t\t\tLOGGING YOU OUT......";
                    i=-1;
                    delay(1000);
                }
                break;
                default:
                    system("cls");
                    cout<<"\n\n\n\n\t\t\t\tENTER CORRECTLY!!";
                    delay(2000);
            }
           }
          }
        }
    return;
}

string hotel::encDec(string& a,char key) {    ///To encrypt and decrypt the employee password
    string out = a;
    for (int i = 0; i < out.size(); i++)
        out[i] = out[i] ^ key;
    return out;
}

void hotel::addtorecord(customer &c){    ///To add a customer object to file
    ofstream fout("users.txt",ios::app);
    fout<<c;
    fout.close();
}

int hotel::id() {    ///To assign new id for the customer
    int v=1200;
    fstream file("id.txt",ios::in);
    file>>v;
    v++;
    file.close();
    file.open("id.txt",ios::out|ios::trunc);
    file<<v<<"\n";
    file.close();
    return v;
}
    void hotel::adminlogin(){  ///for logging into  the admin account
         int i=-1;
      while(i!=0) {
        system("cls");
        time_t timer;
        timer=time(NULL);
        system("COLOR B2");
        cout<<"\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t"<<ctime(&timer);
        cout<<"\n\t\t\t\t\t\t\t*********************************************";
        cout<<"\n\t\t\t\t\t\t\t*************  HOTEL   PAAR  ****************";
        cout<<"\n\t\t\t\t\t\t\t*********************************************";
        cout<<"\n\n\n";
        string a,b;
        char c;
        cout<<"\n\n\t\t\t\tUSERNAME : ";
        cin>>a;
        cout<<"\n\n\t\t\t\tPASSWORD : ";
        c=_getch();
        while(c!='\r'&&c!=' '&&c!='\n') {
            if(c!='\b'){
            cout<<"*";
            b.push_back(c);
            }
            else if(c=='\b'){cout<<'\b'<<" "<<'\b';b.erase(b.size()-1,1);}
            c=_getch();
        }
        if(a=="admin"&&b=="admin") i=0;
        system("cls");
        if(i!=0){
        cout<<"\n\n\n\n\t\tWRONG USERNAME AND/OR PASSWORD!!!!!DO YOU WANT TO ENTER AGAIN? (1.YES,2.NO) ";
        cin>>i;
        }
        if (i==2) {return;}
      }
      system("cls");
      cout<<"\n\n\n\n\n\n\t\t\t\tPROCEEDING.";
        delay(1000);
        cout<<".";
        delay(1000);
        cout<<"..";
        delay(1000);
        cout<<"..";
      while(i!=3) {
        system("cls");
        system("COLOR B2");
        time_t timer1;
        timer1=time(NULL);
        cout<<"\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t"<<ctime(&timer1);
        cout<<"\n\n\t\t\t\tWELCOME ";
        cout<<"admin";
        cout<<"\n\t\t\t\t\t\t\t*********************************************";
        cout<<"\n\t\t\t\t\t\t\t*************  HOTEL   PAAR  ****************";
        cout<<"\n\t\t\t\t\t\t\t*********************************************";
        cout<<"\n\n\n";
        cout<<"\t\t\t\t\t\tSELECT YOUR CHOICE : "
        <<"\n\t\t\t\t\t\t1.ADD/MODIFY/REMOVE EMPLOYEE"
        <<"\n\t\t\t\t\t\t2.GENERATE REPORT"
        <<"\n\t\t\t\t\t\t3.EXIT";
        cin>>i;
        switch(i){
            case 1: addemp("admin");
            break;
            case 2: {
                system("cls");
                string dt;
                int id,cnt=0;
                double revenue;
                fstream fin("revenue.txt",ios::in);
                fin.get();
                while(getline(fin,dt,'\n')&&fin>>id&&fin>>revenue){
                    cout<<"\n\n\t\t\t\t\tDATE AND TIME OF VACATING: "<<dt<<"\n\t\t\t\t\tID: "<<id<<"\n\t\t\t\t\tAMOUNT: "<<revenue;
                    cnt++;
                    fin.get();
                }
                cout<<dt<<endl;
                if(cnt==0) cout<<"\n\n\t\t\t\t\t\tNO REVENUE UPDATED TILL NOW!!";
                fin.close();
                system("pause");
            }
            break;
            case 3:{
                system("cls");
                cout<<"\n\n\n\t\t\t\t\tLOGGING YOU OUT....";
                delay(500);
                cout<<"...";
                delay(750);
                cout<<"...";
                delay(750);
                cout<<"..";
                delay(500);
            }
            break;
            default:{
                cout<<"\n\n\t\t\t\t\t\tENTER PROPER NUMBER!!";
            }
      }
   }
}

void hotel::emplogin() { ///for logging into employee account
        int i=-1;
        vector<pair<string,string> >::iterator it=emps.begin();
        while(i!=0) {
            system("cls");
            time_t timer;
            timer=time(NULL);
            system("COLOR B2");
            cout<<"\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t"<<ctime(&timer);
            cout<<"\n\t\t\t\t\t\t\t*********************************************";
            cout<<"\n\t\t\t\t\t\t\t*************  HOTEL   PAAR  ****************";
            cout<<"\n\t\t\t\t\t\t\t*********************************************";
            cout<<"\n\n\n";
            string a,b;
            char c;
            cout<<"\n\n\t\t\t\tUSERNAME : ";
            cin>>a;
            cout<<"\n\n\t\t\t\tPASSWORD : ";
            c=_getch();
            while(c!='\r'&&c!=' '&&c!='\n') {
                if(c!='\b'){
                cout<<"*";
                b.push_back(c);
                }
                else if(c=='\b'){cout<<'\b'<<" "<<'\b';b.erase(b.size()-1,1);}
                c=_getch();
            }
            vector<pair<string,string> >::iterator its=emps.begin();
            while(its!=emps.end()){
                if(its->first==a&&its->second==b) {i=0;it=its;}
                its++;
            }
            system("cls");
            if(i!=0){
              cout<<"\n\n\n\n\t\tWRONG USERNAME AND/OR PASSWORD!!!!!DO YOU WANT TO ENTER AGAIN? (1.YES,2.NO) ";
              cin>>i;
            }
            if (i==2) {return;}
        }
        system("cls");
        cout<<"\n\n\n\n\n\n\t\t\t\tPROCEEDING.";
        delay(1000);
        cout<<".";
        delay(1000);
        cout<<"..";
        delay(1000);
        cout<<"..";
        i=0;
        while(i!=8) {
            system("cls");
            system("COLOR B2");
            time_t timer1;
            timer1=time(NULL);
            cout<<"\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t"<<ctime(&timer1);
            cout<<"\n\n\t\t\t\tWELCOME ";
            cout<<it->first;
            cout<<"\n\t\t\t\t\t\t\t*********************************************";
            cout<<"\n\t\t\t\t\t\t\t*************  HOTEL   PAAR  ****************";
            cout<<"\n\t\t\t\t\t\t\t*********************************************";
            cout<<"\n\n\n";
            cout<<"\t\t\t\t\t\tSELECT YOUR CHOICE : "
            <<"\n\t\t\t\t\t\t\t1.BOOK ROOM"
            <<"\n\t\t\t\t\t\t\t2.VACATE ROOM"
            <<"\n\t\t\t\t\t\t\t3.VIEW CUSTOMER DETAILS"
            <<"\n\t\t\t\t\t\t\t4.CHECK AVAILABILITY"
            <<"\n\t\t\t\t\t\t\t5.ADD/MODIFY/REMOVE EMPLOYEE"
            <<"\n\t\t\t\t\t\t\t6.GENERATE BILL"
            <<"\n\t\t\t\t\t\t\t7.RESCHEDULE"
            <<"\n\t\t\t\t\t\t\t8.LOGOUT";
            cin>>i;
            switch(i) {
                case 1:{
                    system("cls");
                    cout<<"\n\n\n\n\n\t\t\t\tPROCEEDING TO BOOKING PORTAL....";
                    delay(1000);
                    cout<<"...";
                    delay(500);
                    cout<<"...";
                    delay(500);
                    book();
                }
                break;
                case 2:{
                    system("cls");
                    cout<<"\n\n\n\n\n\t\t\t\tPLEASE WAIT ...........";
                    delay(2000);
                    system("cls");
                    int id;
                    cout<<"\n\t\t\t\tEnter user id to vacate!!";
                    cin>>id;
                    vacate(id);
                }
                break;
                case 3:{
                    system("cls");
                    int z=0;
                    while(z!=1&&z!=2){
                       cout<<"\n\n\t\t\t\tDATE SEARCH OR NAME SEARCH?(1.DATE SEARCH,2.NAME SEARCH)";
                       cin>>z;
                       system("cls");
                       if(z!=1&&z!=2)
                       cout<<"\n\n\t\t\t\tENTER PROPER DETAILS";
                    }
                    if (z==1) {
                        dsearch();
                    }
                    else {
                        nsearch();
                    }
                }
                break;
                case 4: {
                    system("cls");
                    int cnd,cnm,com,cod,coy,cny,n,rt;
                    int j=1;
                    while(j==1){
                        cout<<"\n\n\t\t\t\tEnter the check in date,check in month,check in year:";
                        cin>>cnd>>cnm>>cny;
                        cout<<"\n\t\t\t\tEnter the check out date,check out month,check out year:";
                        cin>>cod>>com>>coy;
                        if(iscorrect(cnd,cnm,cny)==0||iscorrect(cnd,cnm,cny,cod,com,coy)==0) {
                           system("cls");
                           cout<<"\n\n\n\t\t\t\tCAN'T CHECK AVAILABIITY FOR THE ENTERED DATE!!";
                           cout<<"\n\t\t\t\tCLICK 1 TO ENTER ANOTHER DATE,ANY OTHER NUMBER TO EXIT";
                           cin>>j;
                        }
                        else j=-1;
                        }
                        if(j!=-1) break;
                        cout<<"\n\t\t\t\tEnter number of rooms required in the selected dates : ";
                        cin>>n;
                        cout<<"\n\t\t\t\tEnter the room type(1. A.C Deluxe  2. A.C Luxury  3. NON-A.C): ";
                        cin>>rt;
                        int k=available(rt,n,cnd,cnm,cny,cod,com,coy);
                        if(k==1) {
                            system("cls");
                            cout<<"\n\n\n\n\t\t\t\tROOMS AVAILABLE IN THE SELECTED DATES!!!HURRY UP AND BOOK FAST!!";
                        }
                        else{
                           system("cls");
                           cout<<"\n\n\n\n\t\t\t\tSORRY!!SELECTED NUMBER OF ROOMS NOT AVAILABLE IN THE SELECTED DATES....\n\n\t\tCHECK FOR AN ALTERNATIVE!!";
                        }
                        cout<<"\n";
                        system("pause");
                }
                break;
                case 5: {
                    addemp(it->first);
                }
                break;
                case 6: {
                    system("cls");
                    int checkd=0,checkg=0,id,cod,com,coy;
                    while(checkd==0||checkg==0){
                        cout<<"\n\n\t\t\t\tEnter your ID: ";
                        cin>>id;
                        cout<<"\n\t\t\t\tEnter check out date,month and year: ";
                        cin>>cod>>com>>coy;
                        checkd=1;
                        checkg=1;
                        if(checkdate(cod,com,coy,1,1,2018)!=2){
                            checkd=0;
                            cout<<"\n\t\t\t\tEnter proper dates!!";
                            delay(1500);
                        }
                        checkg=genbill(id,cod,com,coy);
                        if(checkg==0){
                            cout<<"\n\t\t\t\tEnter proper details!!";
                            delay(1500);
                        }
                    }
                }
                break;
                case 7:{
                    usermanage(3);
                }
                break;
                case 8: {
                    system("cls");
                    cout<<"\n\n\n\n\n\n\t\t\t\t\tLOGGING YOU OUT ....";
                    delay(1000);
                    cout<<"...";
                    delay(500);
                    cout<<"...";
                    delay(500);
                    return;
                }
                break;
                default:
                    cout<<"\n\n\t\t\t\t\tENTER CORRECTLY!!";
                    delay(2000);
            }
        }
}

void hotel::addemp(string its) {   ///For adding employee
        system("cls");
        system("COLOR B2");
        cout<<"\n\t\t\t\t\t\t\t\t************************************************";
        cout<<"\n\t\t\t\t\t\t\t\t************* EMPLOYEE   PORTAL ****************";
        cout<<"\n\t\t\t\t\t\t\t\t************************************************";
        cout<<"\n\n\n";
        string nam=its,pass;
        cout<<"\t\t\t\t\tEnter the username : ";
        cin.ignore(1,'\n');
        while(nam==its){
        getline(cin,nam);
        if(nam==its) cout<<"\n\t\t\t\t\tYOU CANT ADD OR MODIFY YOURSELF!!....ENTER PROPER NAME!!";
        }
        int i=0;
        vector<pair<string,string> >::iterator it=emps.begin();
        for (;it!=emps.end();it++){
            if (it->first==nam) {
                while(i!=1 && i!=2 &&i!=3) {
                    if(nam!="admin")
                    {
                        cout<<"\n\t\t\t\t\tThe username exists......click 1 to change password 2 to exit 3 to remove employee";
                        cin>>i;
                    }
                    else{
                        cout<<"\n\t\t\t\t\tYOU CANT MODIFY OR REMOVE ADMIN!!";
                        delay(2000);
                        return;
                    }
                    if(i==1) {cout<<"\n\t\t\t\t\tEnter the new password";cin>>pass;it->second=pass;}
                    else if (i==2) return;
                    else if(i!=3){
                        system("cls");
                        cout<<"\n\n\n\t\t\t\t\tEnter proper number.....";
                        delay(2000);
                        system("cls");
                    }
                }
            }
        }
        if(i==0) {
            cout<<"\n\n\t\t\t\t\tEnter the password : ";
            getline(cin,pass);
            srand(time(NULL));
            char k=rand()%257;
            string tn=encDec(nam,k),tp=encDec(pass,k);
            ofstream fout("emp.txt",ios::app);
            fout<<tn<<' '<<tp<<' '<<k<<'\n';
            emps.push_back(make_pair(nam,pass));
            fout.close();
            cout<<"\n\n\t\t\t\t\tSUCCESSFULLY ADDED EMPLOYEE!!";
            delay(2000);
        }
        else if (i==1) {
            fstream file1("emp.txt",ios::in);
            fstream file2("temp.txt",ios::out);
            string tnam,tpass;
            char tmp,k;
            while(file1>>tnam&&file1>>tpass&&file1>>tmp){
               if (encDec(tnam,tmp)==nam) k=tmp;
               else file2<<tnam<<' '<<tpass<<' '<<tmp<<'\n';
            }
            file2<<encDec(nam,k)<<' '<<encDec(pass,k)<<' '<<k<<'\n';
            file1.close();
            file2.close();
            remove("emp.txt");
            rename("temp.txt","emp.txt");
            for(int i=0;i<emps.size();i++){
                if(emps[i].first==nam) {emps[i].first="";emps[i].second="";}
            }
            cout<<"\n\n\t\t\t\t\tSUCCESSFULLY CHANGED PASSWORD!!";
            delay(2000);
        }
        else if(i==3) {
            fstream file1("emp.txt",ios::in);
            fstream file2("temp.txt",ios::out);
            string tnam,tpass;
            char tmp;
            while(file1>>tnam&&file1>>tpass&&file1>>tmp){
               if (encDec(tnam,tmp)==nam);
               else file2<<tnam<<' '<<tpass<<' '<<tmp<<'\n';
            }
           file1.close();
           file2.close();
           remove("emp.txt");
           rename("temp.txt","emp.txt");
           for(int i=0;i<emps.size();i++){
               if(emps[i].first==nam) {emps[i].first="";emps[i].second="";}
           }
           cout<<"\n\t\t\t\t\tSUCCESSFULLY REMOVED EMPLOYEE!!";
           delay(2000);
        }
}

void hotel::usermanage(int key=1) {   ///To manage bookings
        system("cls");
        system("COLOR B2");
        time_t timer1;
        timer1=time(NULL);
        cout<<"\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t"<<ctime(&timer1);
        cout<<"\n\t\t\t\t\t\t\t**********************************************";
        cout<<"\n\t\t\t\t\t\t\t************* EMPLOYEE PORTAL ****************";
        cout<<"\n\t\t\t\t\t\t\t**********************************************";
        if (key==1) {
            customer c;
            cout<<"\n\t\t\t\tEnter name : ";
            cin.ignore(1,'\n');
            gets(c.name);
            cout<<"\n\t\t\t\tEnter address : ";
            gets(c.address);
            cout<<"\n\t\t\t\tEnter age : ";
            cin>>c.age;
            cout<<"\n\t\t\t\tEnter number of members : ";
            cin>>c.memb;
            cout<<"\n\t\t\t\tDo you want laundry services(RS.50 per day per person)(1 for YES,2 for NO) : ";
            cin>>c.laundry;
            cout<<"\n\t\t\t\tDo you want food services(RS.800 per day per person)(1 for YES,2 for NO) : ";
            cin>>c.food;
            int chumm=1;
            while(chumm==1){
                cout<<"\n\t\t\t\tEnter Contact Number: ";
                cin>>c.phno;
                if(c.phno.length()==8) cout<<"\n\t\t\t\tENTER YOUR PHONE NUMBER WITH PROPER STD CODE: ";
                else if(c.phno.length()!=10&&c.phno.length()!=11){ cout<<"\n\t\t\t\tENTER PROPER PHONE NUMBER....1 to enter again any other number to exit";
                cin>>chumm;}
                else chumm=2;
                if(chumm!=1&&chumm!=2) return;
            }
            cout<<"\n\t\t\t\tEnter Room type (1. A.C Deluxe  2. A.C Luxury  3. NON-A.C) ";
            cin>>c.rtype;
            int j=1,s=1;
          while(j==1||s==1){
            cout<<"\n\t\t\t\tEnter check in date,month,year (DD MM YYYY) : ";
            cin>>c.cndate>>c.cnmonth>>c.cnyear;
            cout<<"\n\t\t\t\tEnter check out date,month,year (DD MM YYYY) : ";
            cin>>c.codate>>c.comonth>>c.coyear;
            if(iscorrect(c.cndate,c.cnmonth,c.cnyear)==0||iscorrect(c.cndate,c.cnmonth,c.cnyear,c.codate,c.comonth,c.coyear)==0||
               checkdate(c.cndate,c.cnmonth,c.cnyear,c.codate,c.comonth,c.coyear)!=2||nodays(c.cndate,c.cnmonth,c.cnyear,c.codate,c.comonth,c.coyear)==0) {
                system("cls");
                cout<<"\n\n\n\t\t\t\tBOOKING NOT ALLOWED FOR THE ENTERED DATE!!";
                cout<<"\n\t\t\t\tCLICK 1 TO ENTER ANOTHER DATE,2 TO EXIT";
                cin>>j;
                if(j==2) return;
            }
            else{
                j=0;
                int chumma=1;
                while(chumma==1){
                   cout<<"\n\n\t\t\t\tEnter number of rooms required : ";
                   cin>>c.nroom;
                   if(c.memb/c.nroom>3) cout<<"\n\n\t\t\t\tRequired rooms not enough according to our policy(A MAXIMUM OF THREE PER ROOM ONLY)!!";
                   else chumma=2;
                }
                int k=available(c.rtype,c.nroom,c.cndate,c.cnmonth,c.cnyear,c.codate,c.comonth,c.coyear);
                if(k==0) {
                    system("cls");
                    cout<<"\n\t\t\t\tSORRY!!ENTERED NUMBER OF ROOMS NOT AVAILABLE IN THE SELECTED DATES AND ROOM TYPE!!";
                    cout<<"\n\t\t\t\tCLICK 1 TO ENTER ANOTHER DATE AND/OR ROOMS,2 TO EXIT";
                    cin>>s;
                    if(s==2) return;
                }
                else if (k==1) {
                    s=0;
                    system("cls");
                    cout<<"\n\n\n\n\t\t\t\tCONGRATULATIONS!!YOUR ROOMS HAVE BEEN BOOKED!!";
                    c.id=id();
                    cout<<"\n\n\t\t\t\tYOUR ID is : "<<c.id;
                    addtorecord(c);
                    system("pause");
                    genbill(c.id,c.codate,c.comonth,c.coyear);
                    cout<<"\n\n";
                }
            }
           }
        }
        else if (key==2) {
            int m=0;
            customer d,c;
            int l=0;
            cout<<"\n\n\t\t\t\tEnter user ID : ";
            while(l==0){
            cin>>m;
            ifstream fin("users.txt");
            while(l==0 && fin>>d){
                if(d.id == m) {c=d;
                l++;}
            }
            fin.close();
            if (l==0) {
                system("cls");
                int i=1;
                cout<<"\n\n\t\t\t\tWRONG USER ID!!TYPE 1 TO ENTER AGAIN AND ANY OTHER NUMBER TO EXIT: ";
                cin>>i;
                if(i!=1) return;
                else
                cout<<"\n\n\n\t\t\t\tENTER CORRECT ID : ";
            }
            }
            system("cls");
            cout<<"\n\n\t\t\t\tEnter age: ";
            cin>>c.age;
            cout<<"\n\t\t\t\tEnter number of members : ";
            cin>>c.memb;
            cout<<"\n\t\t\t\tDo you want laundry services(RS.50 per day per person)(1 for YES,2 for NO) : ";
            cin>>c.laundry;
            cout<<"\n\t\t\t\tDo of days you want food services(RS.800 per day per person)(1 for YES,2 for NO) : ";
            cin>>c.food;
            int chumm=1;
            while(chumm==1){
                c.phno="";
                cout<<"\n\t\t\t\tEnter New Contact Number: ";
                cin>>c.phno;
                if(c.phno.length()==8){ cout<<"\n\t\t\t\tENTER YOUR PHONE NUMBER WITH PROPER STD CODE...PRESS ANY KEY....";}
                else if(c.phno.length()!=10&&c.phno.length()!=11){ cout<<"\n\t\t\t\tENTER PROPER PHONE NUMBER....1 to enter again, any other number to exit";
                cin>>chumm;
                }
                else chumm=2;
                if(chumm!=1&&chumm!=2) return;
            }
            cout<<"\n\n\t\t\t\tEnter room type (1. A.C Deluxe  2. A.C Luxury  3. NON-A.C): ";
            cin>>c.rtype;
            int j = 1,s = 1;
            while(j == 1 || s == 1){
            cout<<"\n\t\t\t\tEnter check in date,month,year (DD MM YYYY) : ";
            cin>>c.cndate>>c.cnmonth>>c.cnyear;
            cout<<"\n\t\t\t\tEnter check out date,month,year (DD MM YYYY) : ";
            cin>>c.codate>>c.comonth>>c.coyear;
            if(iscorrect(c.cndate,c.cnmonth,c.cnyear)==0||iscorrect(c.cndate,c.cnmonth,c.cnyear,c.codate,c.comonth,c.coyear)==0||
               checkdate(c.cndate,c.cnmonth,c.cnyear,c.codate,c.comonth,c.coyear)!=2||nodays(c.cndate,c.cnmonth,c.cnyear,c.codate,c.comonth,c.coyear)==0) {
                system("cls");
                cout<<"\n\n\n\t\t\t\tBOOKING NOT ALLOWED FOR ENTERED DATES!!!";
                cout<<"\n\n\n\t\t\t\tCLICK 1 TO ENTER ANOTHER DATE,2 TO EXIT";
                cin>>j;
                if(j==2) return;
            }
            else{
                j=0;
                int chumma=1;
                while(chumma==1){
                   cout<<"\n\n\t\t\t\tEnter number of rooms required : ";
                   cin>>c.nroom;
                   if(c.memb/c.nroom>3) cout<<"\n\n\t\t\t\tRequired rooms not enough according to our policy(A MAXIMUM OF THREE PER ROOM ONLY)!!";
                   else chumma=2;
                }
                int k=available(c.rtype,c.nroom,c.cndate,c.cnmonth,c.cnyear,c.codate,c.comonth,c.coyear);
                if(k==0) {
                    system("cls");
                    cout<<"\n\t\t\t\tSORRY!!ENTERED NUMBER OF ROOMS NOT AVAILABLE IN THE SELECTED DATES AND ROOM TYPE!!";
                    cout<<"\n\t\t\t\tCLICK 1 TO ENTER ANOTHER DATE AND/OR ROOMS,2 TO EXIT";
                    cin>>s;
                    if(s==2) return;
                }
                else if (k==1) {
                    s=0;
                    system("cls");
                    cout<<"\n\n\n\n\t\t\t\tCONGRATULATIONS!!YOUR ROOMS HAVE BEEN BOOKED!!";
                    cout<<"\n\t\t\t\tYou are eligible for discount of "<<discount(l)<<"%"<<"(as of now)"<<endl;
                    addtorecord(c);
                    system("pause");
                    genbill(c.id,c.codate,c.comonth,c.coyear);
                }
            }
          }
        }
        else if(key==3) {
            int cnd1,cnm1,cod1,com1,cnd2,cnm2,cod2,com2,cny1,cny2,coy1,coy2,n1=0,n2,i=0,j=0;
            system("cls");
            system("COLOR B2");
            time_t timer1;
            timer1=time(NULL);
            cout<<"\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t"<<ctime(&timer1);
            cout<<"\n\t\t\t\t\t\t\t**********************************************";
            cout<<"\n\t\t\t\t\t\t\t************* EMPLOYEE PORTAL ****************";
            cout<<"\n\t\t\t\t\t\t\t**********************************************";

            int m=0;
                fstream fin;
                customer d,c;
                int l=0;
                cout<<"\n\n\t\t\t\tEnter user ID : ";
                while(l==0){
                cin>>m;
                fin.open("users.txt",ios::in);
                while(l==0&&fin>>d){
                    if(d.id==m) {c=d;l++;}
                }
                if (l==0) {
                    system("cls");
                    int i=1;
                    cout<<"\n\n\t\t\t\tWRONG USER ID!!TYPE 1 TO ENTER AGAIN AND ANY OTHER NUMBER TO EXIT: ";
                    cin>>i;
                    if(i!=1) return;
                    else
                    cout<<"\n\n\n\t\t\t\tENTER CORRECT ID : ";
                }
                fin.close();
                }
            j=1;
          while(j==1){
          cout<<"\n\n\t\t\t\tEnter your current check in date,month and year (DD MM YYYY) : ";
          cin>>cnd1>>cnm1>>cny1;
          cout<<"\n\n\t\t\t\tEnter the current check out date,month and year (DD MM YYYY) : ";
          cin>>cod1>>com1>>coy1;
          if(iscorrect(cnd1,cnm1,cny1)==0||iscorrect(cnd1,cnm1,cny1,cod1,com1,coy1)==0||
             checkdate(cnd1,cnm1,cny1,cod1,com1,coy1)!=2||nodays(cnd1,cnm1,cny1,cod1,com1,coy1)==0) {
                system("cls");
                cout<<"\n\n\n\t\t\t\tRESCHEDULING NOT ALLOWED FOR ENTERED DATES!!!";
                cout<<"\n\n\n\t\t\t\tCLICK 1 TO ENTER ANOTHER DATE,2 TO EXIT";
                cin>>j;
                if(j==2) return;
          }
          else j=0;
          }
          fin.open("users.txt");
          while(fin>>c&&(c.cndate!=cnd1||c.cnmonth!=cnm1||c.cnyear!=cny1||c.codate!=cod1||c.comonth!=com1||c.coyear!=coy1||c.id!=m));
          fin.close();
          int kj=1;j=1;
          int rt=0;
          while(kj==1||j==1){
          cout<<"\n\n\t\t\t\tEnter the required check in date,month and year (DD MM YYYY) : ";
          cin>>cnd2>>cnm2>>cny2;
          cout<<"\n\n\t\t\t\tEnter the required check out date,month and year (DD MM YYYY) : ";
          cin>>cod2>>com2>>coy2;
          if(iscorrect(cnd2,cnm2,cny2)==0||iscorrect(cnd2,cnm2,cny2,cod2,com2,coy2)==0||checkdate(cnd2,cnm2,cny2,cod2,com2,coy2)!=2||
             nodays(cnd2,cnm2,cny2,cod2,com2,coy2)==0) {
                system("cls");
                cout<<"\n\n\n\t\t\t\tRESCHEDULING NOT ALLOWED FOR ENTERED DATES!!";
                cout<<"\n\n\n\t\t\t\tCLICK 1 TO ENTER ANOTHER DATE,2 TO EXIT";
                cin>>kj;
                if(kj==2) return;
          }
          else{
          kj=0;
          n2=c.nroom+2;
          int cc=1,memb;
          while(cc==1){
          cout<<"\n\t\t\t\tEnter number of members : ";
          cin>>memb;
          if(memb>c.memb) cout<<"Enter a proper number(less than or equal to what you have given earlier!!)";
          else cc++;
          }
          cout<<"\n\t\t\t\tDo you want laundry services(RS.50 per day per person)(1 for YES,2 for NO) : ";
          cin>>c.laundry;
          cout<<"\n\t\t\t\tDo you want food services(RS.800 per day per person)(1 for YES,2 for NO) : ";
          cin>>c.food;
          while(c.nroom<n2){
            cout<<"\n\n\t\t\t\tNumber of rooms you want to reschedule : ";
            cin>>n2;
            if(c.nroom<n2) cout<<"\n\t\t\t\tENTER A PROPER NUMBER(LESS THAN OR EQUAL TO THE NUMBER OF ROOMS YOU HAVE ALREADY BOOKED!!";
            else if(c.memb/c.nroom>3) cout<<"\n\t\t\t\tENTERED NUMBER OF ROOMS NOT ENOUGH ACCORDING TO OUR POLICY(A MAXIMUM OF THREE PER ROOM ONLY)!!";
          }
          n1=c.nroom;
          cout<<"\n\n\t\t\t\tEnter the room type you want to choose (1. A.C Deluxe  2. A.C Luxury  3. NON-A.C):";
          cin>>rt;
          int ii=cnd2 , ji=cnm2,ki=cny2,cot=1;
          while((ii!=cod2 || ji!=com2||ki!=coy2)&&cot!=0){
            int isin=IsInRange(ii,ji,ki,cnd1,cnm1,cny1,cod1,com1,coy1),num=n2;
            if(isin==1&&rt==c.rtype);
            else if(full(rt,n2,ii,ji,ki)==0) {cot=0;}
            if((ii==31&&(ji==1||ji==3||ji==5||ji==7||ji==8||ji==10)) || (ii==30&&(ji==4||ji==6||ji==9||ji==11)) ||
                (ii==28&&ji==2&&ki%4!=0)||(ii==29&&ji==2&&ki%4==0))
               {ii=0; ji++;}
            else if(ii==31&&ji==12) {ii=0;ji=1;ki++;}
            ii++;
          }
          if(cot==1) {
                i=1;
                remodate(c.rtype,n2,cnd1,cnm1,cny1,cod1,com1,coy1);
                available(rt,n2,cnd2,cnm2,cny2,cod2,com2,coy2);
          }
          else i=0;
          if(i==0){
            cout<<"\n\n\t\t\t\tSorry rooms are not available in that date for the room type!!";
            cout<<"\n\n\t\t\t\tEnter 1 to enter again and 2 to exit";
            cin>>j;
            if(j==2) return;
          }
          else{j=0;}
          }
          }
          if(i==1) {
              customer f;
              fstream file1("users.txt",ios::in);
              fstream file2("temp.txt",ios::out|ios::app);
              while(file1>>f){
                if (f.cndate==cnd1&&f.cnmonth==cnm1&&f.cnyear==cny1&&f.coyear==coy1&&f.codate==cod1&&f.comonth==com1&&f.id==m);
                else file2<<f;
              }

             file1.close();
             file2.close();
             remove("users.txt");
             rename("temp.txt","users.txt");
             f=c;
             f.nroom=n1-n2;
             ofstream fout("users.txt",ios::app);
             fout<<f;
             fout.close();
             f.cndate=cnd2;
             f.cnmonth=cnm2;
             f.codate=cod2;
             f.comonth=com2;
             f.cnyear=cny2;
             f.coyear=coy2;
             f.nroom=n2;
             f.rtype=rt;
             addtorecord(f);
             cout<<"\n\n\t\t\t\tyour booking dates have been changed successfully!!";
             system("pause");
             genbill(f.id,f.codate,f.comonth,f.coyear);
        }
   }
}


void hotel::incemps() {   ///To include employees
       ifstream fin("emp.txt");
       while(!fin.eof()) {
          string a,b;
          char k;
          fin>>a>>b>>k;
          emps.push_back(make_pair(encDec(a,k),encDec(b,k)));
       }
       fin.close();
}

void hotel::book(){  ///To book rooms
        system("cls");
        system("COLOR B2");
        time_t timer1;
        timer1=time(NULL);
        cout<<"\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t"<<ctime(&timer1);
        cout<<"\n\t\t\t\t\t\t\t*********************************************";
        cout<<"\n\t\t\t\t\t\t\t************* BOOKING PORTAL ****************";
        cout<<"\n\t\t\t\t\t\t\t*********************************************";
        cout<<"\n\n\n";
        int i=0;
        while(i!=1&&i!=2){
        cout<<"\t\tDo you have an user ID? (1 for YES 2 for NO) ";
        cin>>i;
        if(i==2) {
            usermanage(1);
            i= 2;
        }
        else if (i==1) {
            usermanage(2);
            i= 1;
        }
        else {
            system("cls");
            cout<<"\n\n\t\t\t\t\tPLEASE CHOOSE SUITABLY.......";
        }
        }
}

void hotel::remodate(int rtype,int n,int cnd,int cnm,int cny,int cod,int com,int coy) {   ///To remove given set of date
      fstream file1("dates.txt",ios::in);
      fstream file2("temp.txt",ios::out);
      int i=0,j=0,k=0,rt=0;
      map<pair<int,pair<int,int> >,int > c;
      file1>>i>>j>>k>>rt;
      while(!file1.eof()){
        if(IsInRange(i,j,k,cnd,cnm,cny,cod,com,coy)==1&&rtype==rt) {
            pair<int,pair<int,int> >temp;
            temp.first=i;
            temp.second.first=j;
            temp.second.second=k;
            if(c.count(temp)==0) c[temp]=1;
            else if(c[temp]<n&&c.count(temp)==1){
               c[temp]++;
            }
            else file2<<i<<" "<<j<<" "<<k<<" "<<rt<<'\n';
        }
        else file2<<i<<" "<<j<<" "<<k<<" "<<rt<<'\n';
        file1>>i>>j>>k>>rt;
     }
     file1.close();
     file2.close();
     remove("dates.txt");
     rename("temp.txt","dates.txt");
}

int hotel::genbill(int id,int cod,int com,int coy){    ///To generate bill
        fstream file("users.txt",ios::in);
        vector<customer> c;
        customer d;
        while(file>>d){
            if(d.id==id&&d.codate==cod&&d.comonth==com&&d.coyear==coy){c.push_back(d);}
        }
        file.close();
        if(c.size()==0) return 0;
        time_t timer;
        timer=time(NULL);
        struct tm* timers=localtime(&timer);
        system("cls");
        cout<<"\n\n\n\n\n\n\t\t\t\t\t\tPROCEEDING.";
        cout<<"...";
        delay(500);
        cout<<"...";
        delay(500);
        cout<<"...";
        delay(500);
        system("cls");
        system("color F0");
        cout<<"\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t"<<ctime(&timer);
        cout<<"\t\t\tUSER  ID :   "<<id<<endl;
        cout<<"\n-------------------------------------------------------------------------------------------------------------------------"
            <<"-----------------------------------------------";
        cout<<"\n\t\t\t\t\t\t\t   **********@@@@@@@   HOTEL   PAAR  @@@@@@@**********";
        cout<<"\n-------------------------------------------------------------------------------------------------------------------------"
            <<"-----------------------------------------------";
        cout<<"\n  S.NO                           \t\t\t      TITLE                                                           \t\t\tAMOUNT                ";
        cout<<"\n-------------------------------------------------------------------------------------------------------------------------"
            <<"-----------------------------------------------";
        cout<<"\n-------------------------------------------------------------------------------------------------------------------------"
            <<"-----------------------------------------------";
        file.open("users.txt",ios::in);
        int coun=0;
        while(file>>d)
           if(d.id==id) coun++;
        file.close();
        int disc=discount(coun-c.size());
        string a="LUXURY AC ",b=" DELUXE AC ",e="NON AC ";
        for(long int i=0;i<c.size();i++){
            double billamt;
            cout<<"\n\n    "<<i+1<<".\t\t\t\t\t   ";
            if(c[i].rtype==1){
                cout<<a;
                billamt=2000;
            }
            else if(c[i].rtype==2){
                cout<<b;
                billamt=2500;
            }
            else {
                cout<<e;
                billamt=1500;
            }
            cout<<"   x"<<c[i].nroom;
            int nod=nodays(c[i].cndate,c[i].cnmonth,c[i].cnyear,c[i].codate,c[i].comonth,c[i].coyear);
            billamt*=c[i].nroom;
            billamt*=nod;
            cout<<"               \t       \t\t\t\t                                 "<<billamt;
            double laundry=0;
            if(c[i].laundry!=2)
               laundry=50*nod*c[i].memb;
            else laundry=0;
            billamt+=laundry;  ///base fare:50 per day per member
            cout<<"\n\t\t\t\t\t   LAUNDRY CHARGES                   \t \t\t\t\t                                 "<<laundry;
            double food=0;
            if(c[i].food!=2)
                food=800*c[i].memb*nod;
            else food=0;
            billamt+=food;  ///base fare:800 per day per member
            cout<<"\n\t\t\t\t\t   FOOD CHARGES                            \t       \t \t\t\t                         "<<food;
            cout<<"\n\n";
            cout<<"\n--------------------------------------------------------------------------------------------------------"
                <<"----------------------------------------------------------------";
            double gst=0.12*billamt;
            cout<<"\n                                   \t\t\t\t\t\t                                              TOTAL AMOUNT: "<<"     "<<billamt;
            cout<<"\n                                   \t\t\t\t\t\t                                              DISCOUNT: "<<disc<<"%"<<"       "
                <<disc/100.0*billamt;
            cout<<"\n                                    \t\t\t\t\t\t                                              GST : "<<"12%"<<"          "<<gst;
            billamt=billamt-(disc/100.0*billamt)+gst;
            cout<<"\n\n                                        \t\t\t\t\t\t                                      NET AMOUNT: "<<"       "<<billamt;
            cout<<"\n\n-------------------------------------------------------------------------------------------------------"
                <<"-----------------------------------------------------------------";
            delay(1000);
        }
        cout<<"\n\n\n\n\n";
        system("pause");
        system("cls");
  }
  int hotel::genbill(int id){
        ifstream fin("users.txt");
        vector<customer> c;
        customer d;
        time_t timer;
        timer=time(NULL);
        struct tm* timers=localtime(&timer);
        while(fin>>d){
            if(id==d.id&&d.codate==timers->tm_mday&&d.comonth==timers->tm_mon+1&&d.coyear==timers->tm_year+1900) c.push_back(d);
        }
        fin.close();
        fin.open("rooms.txt");
        int rn,countt=0;char st;
        while(fin>>rn&&fin>>st&&fin>>d){
            if(id==d.id&&id==d.id&&d.codate==timers->tm_mday&&d.comonth==timers->tm_mon+1&&d.coyear==timers->tm_year+1900) countt++;
        }
        if(c.size()==0){
            return 0;
        }
        else if(countt==0){
            return -1;
        }
        else {
            system("cls");
            cout<<"\n\n\n\n\n\n\t\t\t\t\t\tPROCEEDING.";
            cout<<"...";
            delay(500);
            cout<<"...";
            delay(500);
            cout<<"...";
            delay(500);
            system("cls");
            system("color F0");
            cout<<"\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t"<<ctime(&timer);
            cout<<"\t\t\tUSER  ID :   "<<id<<endl;
            cout<<"\n-------------------------------------------------------------------------------------------------------------------------"
                <<"-----------------------------------------------";
            cout<<"\n\t\t\t\t\t\t\t   **********@@@@@@@   HOTEL   PAAR  @@@@@@@**********";
            cout<<"\n-------------------------------------------------------------------------------------------------------------------------"
                <<"-----------------------------------------------";
            cout<<"\n  S.NO                           \t\t\t      TITLE                                                           \t\t\tAMOUNT                ";
            cout<<"\n-------------------------------------------------------------------------------------------------------------------------"
                <<"-----------------------------------------------";
            cout<<"\n-------------------------------------------------------------------------------------------------------------------------"
                <<"-----------------------------------------------";
            fin.open("users.txt");
            int coun=0;
            while(fin>>d)
                if(d.id==id) coun++;
            fin.close();
            double payamt=0;
            int disc=discount(coun-c.size());
            string a="LUXURY AC ",b="DELUXE AC ",e="NON AC ";
            for(long int i=0;i<c.size();i++){
                double billamt;
                cout<<"\n\n    "<<i+1<<".\t\t\t\t\t   ";
                if(c[i].rtype==1){
                    cout<<a;
                    billamt=2000;
                }
                else if(c[i].rtype==2){
                    cout<<b;
                    billamt=2500;
                }
                else {
                    cout<<e;
                    billamt=1500;
                }
                cout<<"   x"<<c[i].nroom;
                int nod=nodays(c[i].cndate,c[i].cnmonth,c[i].cnyear,c[i].codate,c[i].comonth,c[i].coyear);
                billamt*=c[i].nroom;
                billamt*=nod;
                cout<<"               \t       \t\t\t\t                                 "<<billamt;
                double laundry=0;
                if(c[i].laundry!=2)
                   laundry=50*nod*c[i].memb;
                else laundry=0;
                billamt+=laundry; ///base fare:50 per day per member
                cout<<"\n\t\t\t\t\t   LAUNDRY CHARGES                   \t \t\t\t\t                                 "<<laundry;
                double food=0;
                if(c[i].food!=2)
                   food=800*c[i].memb*nod;
                else food=0;
                billamt+=food; ///base fare:800 per day per member
                cout<<"\n\t\t\t\t\t   FOOD CHARGES                            \t       \t \t\t\t                         "<<food;
                cout<<"\n\n";
                cout<<"\n-----------------------------------------------------------------------------------------------------------------------"
                    <<"-------------------------------------------------";
                double gst=0.12*billamt;
                cout<<"\n                                   \t\t\t\t\t\t                                              TOTAL AMOUNT: "<<"     "<<billamt;
                cout<<"\n                                   \t\t\t\t\t\t                                              DISCOUNT: "<<disc<<"%"<<"       "
                    <<disc/100.0*billamt;
                cout<<"\n                                    \t\t\t\t\t\t                                              GST : "<<"12%"<<"          "<<gst;
                billamt=billamt-(disc/100.0*billamt)+gst;
                cout<<"\n\n                                        \t\t\t\t\t\t                                      NET AMOUNT: "<<"       "<<billamt;
                cout<<"\n\n-----------------------------------------------------------------------------------------------------------------------"
                    <<"-------------------------------------------------";
                delay(1000);
                payamt+=billamt;
      }
      cout<<"\n\n\n\t\t\t\t\t\t\tAMOUNT TO BE PAID BY YOU:     "<<payamt;
      ofstream fout("revenue.txt",ios::app);
      fout<<ctime(&timer)<<id<<" "<<payamt<<"\n";
      fout.close();
    }
    cout<<"\n\n\n\n\n";
    system("pause");
    system("cls");
    return 1;
}

void hotel::vacate(int id){  ///To vacate room and generating bill
       system("cls");
       fstream fin("users.txt",ios::in);
       customer c;
       time_t timer;
       timer=time(NULL);
       struct tm* timers=localtime(&timer);
       int cd=0,ci=0;
       while(fin>>c&&cd==0){
          if(c.codate==timers->tm_mday&&c.comonth==timers->tm_mon+1&&c.coyear==timers->tm_year+1900&&c.id==id){
             ci=genbill(id);
             system("cls");
             system("color 07");
             cout<<"\n\n\n\n\n\t\t\t\t\t\t\t\t\tTHANK YOU!!!\n\n\n\n\t\t\t\t\t\t\t\t\tVISIT AGAIN!!!";
             delay(500);
             system("color 17");
             delay(500);
             system("color 27");
             delay(500);
             system("COLOR 37");
             delay(500);
             system("color 47");
             delay(500);
             system("color 57");
             delay(500);
             system("color 67");
             delay(500);
             system("color 07");
             delay(1000);
             cd++;
             remodate(c.rtype,c.nroom,c.cndate,c.cnmonth,c.cnyear,c.codate,c.comonth,c.coyear);
          }
       }
       if(cd==0) cout<<"\n\n\t\t\t\tVACATING A ROOM CAN BE DONE ONLY ON THE CHECK OUT DATES!!";
       else if(ci==-1) cout<<"\n\n\t\t\t\tALREADY VACATED!!";
       fin.close();
       delay(1000);
       allroom(id);
}

int hotel::IsInRange(int m,int n,int o,int cnd,int cnm,int cny,int cod,int com,int coy) {  ///To check if a given date is in a set of dates
     int i=cnd , j=cnm,k=cny,ct=0;
     while((i!=cod || j!=com||k!=coy)&&(i!=m||j!=n||k!=o)){
        if((i==31&&(j==1||j==3||j==5||j==7||j==8||j==10)) || (i==30&&(j==4||j==6||j==9||j==11)) || (i==28&&j==2&&k%4!=0)||(i==29&&j==2&&k%4==0))
           {i=0; j++;}
        else if(i==31&&j==12){i=0;j=1;k++;}
        i++;
     }
     if(i==cod&&j==com) return 0;
     else return 1;
}

void hotel::dsearch(){   ///To search details based on date
    int da,m,y;
    ifstream fin("users.txt");
    customer d; int co=0,ch=1;
    while(ch==1){
     system("cls");
     int chec=1;
     while(chec==1){
     cout<<"\n\t\t\t\tENTER THE DATE,MONTH AND YEAR TO CHECK";
     cin>>da>>m>>y;
     chec=2;
     if(checkdate(da,m,y,1,1,2018)!=2) {cout<<"\n\t\t\t\tENTER PROPER DETAILS!!";chec=1;}
     }
     system("cls");
     cout<< "\n\n\t\t\t\tLIST OF ALL RECORDS ON GIVEN DATE: ";
    while(fin>>d&&!fin.eof()){
        if((d.cndate==da && d.cnmonth==m&&d.cnyear==y)){
          cout<<"\n\n\t\t\t\tCHECKED IN......";
          cout<<"\n\t\t\t\t\t\tNAME: "<<d.name
              <<"\n\t\t\t\t\t\tID: "<<d.id
              <<"\n\t\t\t\t\t\tADDRESS: "<<d.address
              <<"\n\t\t\t\t\t\tAGE: "<<d.age
              <<"\n\t\t\t\t\t\tPHONE NUMBER: "<<d.phno
              <<"\n\t\t\t\t\t\tCHECK IN DATE: "<<d.cndate<<"/"<<d.cnmonth<<"/"<<d.cnyear
              <<"\n\t\t\t\t\t\tCHECK OUT DATE: "<<d.codate<<"/"<<d.comonth<<"/"<<d.coyear
              <<"\n\t\t\t\t\t\tROOM TYPE: "<<d.rtype
              <<"\n\t\t\t\t\t\tNO OF ROOMS: "<<d.nroom;
              co++;
              ch=2;
         delay(1000);
        }
        if((d.codate==da&&d.comonth==m&&d.coyear==y)){
          cout<<"\n\n\t\t\t\tCHECKED OUT.....";
          cout<<"\n\t\t\t\t\t\tNAME: "<<d.name
              <<"\n\t\t\t\t\t\tID: "<<d.id
              <<"\n\t\t\t\t\t\tADDRESS: "<<d.address
              <<"\n\t\t\t\t\t\tAGE: "<<d.age
              <<"\n\t\t\t\t\t\tPHONE NUMBER: "<<d.phno
              <<"\n\t\t\t\t\t\tCHECK IN DATE: "<<d.cndate<<"/"<<d.cnmonth<<"/"<<d.cnyear
              <<"\n\t\t\t\t\t\tCHECK OUT DATE: "<<d.codate<<"/"<<d.comonth<<"/"<<d.coyear
              <<"\n\t\t\t\t\t\tROOM TYPE: "<<d.rtype
              <<"\n\t\t\t\t\t\tNO OF ROOMS: "<<d.nroom;
              co++;
              ch=2;
         delay(1000);
        }
        if(IsInRange(da,m,y,d.cndate,d.cnmonth,d.cnyear,d.codate,d.comonth,d.coyear)==1){
          cout<<"\n\n\t\t\t\tSTAYED.....";
          cout<<"\n\t\t\t\t\t\tNAME: "<<d.name
              <<"\n\t\t\t\t\t\tID: "<<d.id
              <<"\n\t\t\t\t\t\tADDRESS: "<<d.address
              <<"\n\t\t\t\t\t\tAGE: "<<d.age
              <<"\n\t\t\t\t\t\tPHONE NUMBER: "<<d.phno
              <<"\n\t\t\t\t\t\tCHECK IN DATE: "<<d.cndate<<"/"<<d.cnmonth<<"/"<<d.cnyear
              <<"\n\t\t\t\t\t\tCHECK OUT DATE: "<<d.codate<<"/"<<d.comonth<<"/"<<d.coyear
              <<"\n\t\t\t\t\t\tROOM TYPE: "<<d.rtype
              <<"\n\t\t\t\t\t\tNO OF ROOMS: "<<d.nroom;
              co++;
              ch=2;
          delay(1000);
        }
    }
    if(co==0){
          cout<<"\n\t\t\t\t\t\tNO RECORDS FOUND...";
          cout<<"\n\t\t\t\t\tENTER 1 TO ENTER ANOTHER DATE,ENTER 2 TO EXIT";
          cin>>ch;
          if(ch==2) return;
    }
   }
   system("pause");
    fin.close();
}


void hotel::nsearch(){   ///To search details based on name
     ifstream fin("users.txt");
     customer d;
     char n[50];
     int ch=1,co=0;
     while(ch==1){
        system("cls");
        cout<<"\n\n\t\t\t\t\tENTER NAME TO SEARCH: ";
        cin.ignore(1,'\n');
        cin.getline(n,50,'\n');
        system("cls");
        cout<< "\n\n\t\t\t\tLIST OF ALL RECORDS: ";
        while(fin>>d){
          if(strcmpi(d.name,n)==0){
            cout<<"\n\t\t\t\t\t\tNAME: "<<d.name
              <<"\n\t\t\t\t\t\tID: "<<d.id
              <<"\n\t\t\t\t\t\tADDRESS: "<<d.address
              <<"\n\t\t\t\t\t\tAGE: "<<d.age
              <<"\n\t\t\t\t\t\tPHONE NUMBER: "<<d.phno
              <<"\n\t\t\t\t\t\tCHECK IN DATE: "<<d.cndate<<"/"<<d.cnmonth<<"/"<<d.cnyear
              <<"\n\t\t\t\t\t\tCHECK OUT DATE: "<<d.codate<<"/"<<d.comonth<<"/"<<d.coyear
              <<"\n\t\t\t\t\t\tROOM TYPE: "<<d.rtype
              <<"\n\t\t\t\t\t\tNO OF ROOMS: "<<d.nroom;
              co++;
              ch=2;
              delay(1000);
              cout<<"\n\n";
            }
        }
        if(co==0){
            cout<<"\n\n\t\t\t\t\tNO RECORDS FOUND";
            cout<<"\n\t\t\t\t1. TO ENTER ANOTHER NAME,2. TO EXIT";
            cin>>ch;
            if(ch==2) return;
        }
     }
     fin.close();
     system("pause");
 }


///MAIN FUNCTION.....
int main() {
    system("mode con COLS=700");
    ShowWindow(GetConsoleWindow(),SW_MAXIMIZE);
    SendMessage(GetConsoleWindow(),WM_SYSKEYDOWN,VK_RETURN,0x20000000);
    hotel h;
    h.allroom();
    h.incemps();
    h.homescreen();
}


