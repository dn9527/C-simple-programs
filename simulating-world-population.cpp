//Dat Nguyen
//Code::Block
//Simulating the World Population
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

unsigned DaysPerMonth[13] = {0,31,28,31,30,31,30,31,31,30,31,30,31};
const string NAMES[] =
{
    "Anh-Dao","Gia","Sam","Aaron","Michael","Ashley","John","Rocky",
    "Sophia","Emmett","Xuefeng","Richard","Amir","Christopher","Thomas","Viet",
    "Sanjit","Johnny","Ehsan","Tri","Fawzan","Sahil","William",
    "Thuy","Emil","Taeyang","Alvin","Duc Huy","Phudit","Ethan","Dat",
    "Yong Yu","Thai Anh Dong","Peter","Li Yu","Joe","Jiazhi","Edgar","Henry"
};
//*******************************************************************************
class Date
{
    private:
    unsigned int day;
    unsigned int month;
    unsigned int year;
public:
    Date();
    Date(unsigned int, unsigned int, unsigned int);
    void increment();
    bool isA_LeapYear() const;
    void letTimePass();
    void print() const;
    unsigned int getday();
    unsigned int getmonth();
    unsigned int getyear();
};

Date::Date()
{
    time_t now = time(0);
    struct tm* ptr2tm;
    ptr2tm = localtime(&now);

    day = ptr2tm->tm_mday;
    month = ptr2tm->tm_mon+1;
    year = ptr2tm->tm_year+1900;
}

Date TODAY;

Date::Date(unsigned int mm, unsigned int dd, unsigned int yy)
{
    month = mm;
    day = dd;
    year = yy;
    // Make a Y2K correction for a 2-digit year
    if (year < 18) year += 2000;
    else if (year < 100) year += 1900;
}
void Date::increment()
{
    if (isA_LeapYear()) DaysPerMonth[2] = 29;
    else DaysPerMonth[2] = 28;

    day++;

    // check for the end of the month
    if (day > DaysPerMonth[month])    // gone past end of current month?
    {
        month ++;
        day = 1;
    }

    // check for the end of the year
    if (month > 12)
    {
        year ++;
        month = 1;
    }
}

bool Date::isA_LeapYear() const
{
    if (year % 400 == 0) return true;
    else if (year % 100 == 0) return false;
    else if (year % 4 == 0) return true;
    else return false;
}

void Date::letTimePass()
{
    for(int i=0; i < rand()%365+1; i++) increment();
}

void Date::print() const
{
    cout << month << '/' << day << '/' << year%100;
}

unsigned int Date::getday()
{
    return day;
}

unsigned int Date::getmonth()
{
    return month;
}

unsigned int Date::getyear()
{
    return year;
}

//********************************************************************
class Human
{
private:
    string name;
    Date birthday;
    bool isAlive;
public:
    Human(const string& n, const Date& b);
    string getName() {return name;}
    bool getIsAlive() {return isAlive;}
    unsigned short age();
    void die();
    float rollTheDice(unsigned short age) {return static_cast<float>(age)*(rand()%100)/10000.;}
    void print();
};

Human::Human(const string& n, const Date& b)
{
    name = n;
    birthday = b;
    isAlive = true;
}

unsigned short Human::age()
{
    bool flag = true;
    unsigned int days = 0;
    Date temp;
    temp = birthday;
    do
    {
        temp.increment();
        days++;
        if(temp.getday() == TODAY.getday() && temp.getmonth() == TODAY.getmonth() && temp.getyear() == TODAY.getyear()) flag=false;
    }while(flag);
    return static_cast<unsigned short>(days/365.25);
}

void Human::die()
{
    isAlive = false;
}

void Human::print()
{
    cout << name << " was born on ";
    birthday.print();
    cout << " is " << age() << endl;
}
//***********************************************************
class Population
{
private:
    Human** people ;
    short size;
public:
    Population(int);
    ~Population();
    void examinePopulation();
    int getNumberLiving();
    void print();
};

Population::Population(int s)
{
    unsigned int r;
    size = s;
    people = new Human*[size];

    for (int i = 0; i < size; i++)
    {
        Date temp(1,1,18);
        r = rand()%36525;
        for(unsigned int j=0; j<r; j++) temp.increment();
        people[i] = new Human(NAMES[i], temp);
    }
}

Population::~Population(void)
{
  for (int i = 0; i < size; i++)
  {
    //cout << people[i]->getName() << " erased" << endl;
    delete people[i];
  }

  //cout << "The city was gone";
  delete [] people;

}

void Population::examinePopulation(void)
{
    for(int i=0; i<size; i++)
    {
        if(people[i]->rollTheDice(people[i]->age()) > 0.5 && people[i]->getIsAlive())
        {
            people[i]->die();
            TODAY.print();
            cout << " " + people[i]->getName() << " died at the age of " << people[i]->age() << endl;
        }
    }
}

int Population::getNumberLiving(void)
{
    int numberLiving = 0;
    for(int i=0; i<size; i++)
        if(people[i]->getIsAlive()) numberLiving++;
    return numberLiving;
}

void Population::print()
{
    cout << "-----------------------------------------------" << endl;
    cout << "Today is ";
    TODAY.print();
    cout << endl;
    for(int i=0; i< size; i++)
    {
        if(people[i]->getIsAlive()) people[i]->print();
    }
    cout << "-----------------------------------------------" << endl;
}
//**************************************************************************

int main()
{
 const int OriginalPopulationSize = 39;

    srand(time(0));
    Population World(OriginalPopulationSize);
    World.print();

    // let time pass until half of the world's Population dies
    do
    {
        TODAY.letTimePass();
        World.examinePopulation();
    }
    while (World.getNumberLiving() > OriginalPopulationSize/2);

    World.print();

}
