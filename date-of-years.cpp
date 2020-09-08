//Dat Nguyen
//Code::Block
//Date and time
#include <iostream>
#include <iomanip>
#include <ctime>
#include <string>
#include <cstdlib>
#include <cmath>
using namespace std;

int DaysPerMonth[13] = {0,31,28,31,30,31,30,31,31,30,31,30,31};
const string months[13] = {"0", "January", "February", "March", "April", "May", "June",
                                "July", "August", "September", "October", "November", "December"};
//************************************************************************************************
class Date
{
private:
    int day;
    int month;
    int year;
public:
    Date();
    Date(unsigned int, unsigned int, unsigned int);
    Date(string);
    bool isA_LeapYear() const;
    Date& operator++();
    Date& operator--();
    Date operator+(const int&) const;
    friend Date operator+(const int&, const Date&);
    Date operator-(const int&) const;
    friend int operator-(const Date&, const Date&);
    void operator!() const;
    friend ostream& operator<<(ostream&, const Date&);
    friend bool operator>(const Date&, const Date&);
    friend bool operator<(const Date&, const Date&);
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

Date::Date(unsigned int mm, unsigned int dd, unsigned int yy) : day(dd), month(mm), year(yy)
{
    if (year < 50) year += 2000;
    else if (year < 100) year += 1900;
}

Date::Date(string s)
{
    month = atoi(s.substr(0,2).c_str());
    day = atoi(s.substr(3,4).c_str());
    year = atoi(s.substr(6,7).c_str());
    if (year < 50) year += 2000;
    else if (year < 100) year += 1900;
}

bool Date::isA_LeapYear() const
{
    if (year % 400 == 0) return true;
    else if (year % 100 == 0) return false;
    else if (year % 4 == 0) return true;
    else return false;
}

Date& Date::operator++()
{
    if(isA_LeapYear()) DaysPerMonth[2] = 29;
    else DaysPerMonth[2] = 28;
    day++; //do increment 1 day
    if (day > DaysPerMonth[month])
    {
        month++;
        day = 1;
    }

    if (month > 12)
    {
        year++;
        month = 1;
    }

    return *this;
}

Date& Date::operator--()
{
    if(isA_LeapYear()) DaysPerMonth[2] = 29;
    else DaysPerMonth[2] = 28;
    day--; //do decrement 1 day
    if (day == 0)
    {
        month--;
        day = DaysPerMonth[month];
    }

    if (month == 0)
    {
        year--;
        month = 12;
        day = 31;
    }

    return *this;
}

Date Date::operator+(const int& n) const
{
    Date temp = *this;
    for(int i=0; i < n; i++) ++temp;
    return temp;
}

Date Date::operator-(const int& n) const
{
    Date temp = *this;
    for(int i=0; i<n; i++) --temp;
    return temp;
}

void Date::operator!() const
{
    cout << months[(*this).month] << ' ' << (*this).day << ", " << (*this).year << endl;
}
//************************************************************************************************
int main()
{
    // Constructors
    Date today;
    Date feb2815(2,28,15);
    Date feb2800("02-28-00");
    Date NewYearsDay("01/01/18");

    // Increment and decrement operators
    cout << today << endl;
    ++today;
    cout << today << endl;
    --today;
    cout << today << endl << endl;

    cout << feb2815 << endl;
    cout << ++feb2815 << endl;
    cout << --feb2815 << endl << endl;

    cout << feb2800 << endl;
    cout << ++feb2800 << endl;
    cout << --feb2800 << endl << endl;

    cout << NewYearsDay << endl;
    --NewYearsDay;
    cout << NewYearsDay << endl;
    ++NewYearsDay;
    cout << NewYearsDay << endl << endl;

    // Test plus operators
    cout << "30 days from now: " << today + 30 << endl;
    cout << "one hundred days from now: " << 100 + today << endl << endl;

    // Test minus operators
    Date twentyYearsAgo = today - static_cast<int>(round(20 * 365.25));
    Date final("12/11/17");
    cout << "Days until the final = " << final - today << endl;

    // Test the ! operator
    cout << "Today is ";
    !today;
    cout << "Twenty years ago was ";
    !twentyYearsAgo;
    cout << endl;

    // Test logic operators
    cout << boolalpha;
    cout << feb2800 << " < " << NewYearsDay << " ? " << (feb2800 < NewYearsDay) << endl;
    cout << feb2815 << " < " << NewYearsDay << " ? " << (feb2815 < NewYearsDay) << endl;
    cout << feb2815 << " > " << NewYearsDay << " ? " << (feb2815 > NewYearsDay) << endl;
}

ostream& operator<<(ostream& out, const Date& date)
{
    out << setfill('0');
    out << setw(2) << date.month << '/' << setw(2) << date.day << '/' << date.year;
    return out;
}

Date operator+(const int& n, const Date& date)
{
    Date temp = date;
    for(int i=0; i<n; i++) ++temp;
    return temp;
}

int operator-(const Date& d1, const Date& d2)
{
    Date temp = d2;
    int days = 0;
    bool match = false;
    do
    {
        ++temp;
        days++;
        if(temp.day == d1.day && temp.month == d1.month && temp.year == d1.year)
            match = true;
    }while(!match);

    return days;
}

bool operator>(const Date& d1, const Date& d2)
{
    if(d1.year > d2.year) return true;
    else if(d1.year < d2.year) return false;
    else
    {
        if(d1.month > d2.month) return true;
        else if(d1.month < d2.month) return false;
        else
        {
            if(d1.day > d2.day) return true;
            else return false;
        }
    }
}

bool operator<(const Date& d1, const Date& d2)
{
    if(d1.year < d2.year) return true;
    else if(d1.year > d2.year) return false;
    else
    {
        if(d1.month < d2.month) return true;
        else if(d1.month > d2.month) return false;
        else
        {
            if(d1.day < d2.day) return true;
            else return false;
        }
    }
}
