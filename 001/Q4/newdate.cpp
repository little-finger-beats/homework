#include <iostream>
#include <string>

#define LEFT_BIT_VAL(v) (!!((1 << 31) & (v)))

class Date {
public:
    Date() {year_ = 0; month_ = 0; day_ = 0; extraDays_ = 0;};
    ~Date() {};
    int setDate(int year, int month, int day);
    int updateDate(int days);
    int getYear();
    int getMonth();
    int getDay();
 
private:
    bool isLeapYear(int year);
    int updateYear(int &days);
    int updateMonth(int &days);
    int updateDay(int &days);
    int getExtraDays();
    int getDaysOfYear(int year);
    int backToFirstDayOfYear();
    int year_;
    int month_;
    int day_;
    int extraDays_;
};

int Date::updateDate(int days)
{
    int daysInYear = 365;
    int years = 0;

    days += extraDays_;
    updateYear(days);
    updateMonth(days); 
    updateDay(days); 
    extraDays_ = 0;

    return 0;
}

int Date::updateDay(int &days)
{
    day_ += days;

    return 0;
}

int Date::updateMonth(int &days)
{
    int days2month = 28;

    if (isLeapYear(year_)) days2month = 29;

    if (days >= 31) {
	month_ += 1;
	days -= 31;
    }
    if (days >= days2month) {
	month_ += 1;
	days -= days2month;
    }
    if (days >= 31) { /* March */
	month_ += 1;
	days -= 31;
    }
    if (days >= 30) { /* April */
	month_ += 1;
	days -= 30;
    }
    if (days >= 31) {
	month_ += 1;
	days -= 31;
    }
    if (days >= 30) { /* June */
	month_ += 1;
	days -= 30;
    }
    if (days >= 31) { /* July */
	month_ += 1;
	days -= 31;
    }
    if (days >= 31) { /* August */
	month_ += 1;
	days -= 31;
    }
    if (days >= 30) { /* September */
	month_ += 1;
	days -= 30;
    }
    if (days >= 31) { /* October */
	month_ += 1;
	days -= 31;
    }
    if (days >= 30) {
	month_ += 1;
	days -= 30;
    }

    return 0; 
}

int Date::updateYear(int &days)
{
    int daysInYear = 365;
    int currentYear = year_;
    int yearNum = 0;

    do {
        daysInYear = getDaysOfYear(currentYear);
	if (daysInYear > days)
	    break;
	yearNum++;
	days -= daysInYear;
    } while(1);
    year_ += yearNum;

    return 0;
}

int Date::getYear()
{
    return year_;
}

int Date::getMonth()
{
    return month_;
}

int Date::getDay()
{
    return day_;
}
    
int Date::getExtraDays()
{
    return extraDays_;
}

int Date::getDaysOfYear(int year)
{
    int days = 365;

    if (isLeapYear(year)) {
	days = 366;
    }
    return days;
}

bool Date::isLeapYear(int year)
{
    bool isLeap = false;

    if (!!(year % 100) && (!(year % 4))) {
	isLeap = true;
    } else if (!(year % 400)) {
	isLeap = true;
    }

    return isLeap;
}

int Date::setDate(int year, int month, int day)
{
    int max = 0;

    if (LEFT_BIT_VAL(year | month | day)) {
	std::cout << "please check your year, month and day, must be more than 0" << std::endl;
	return -1;
    }
    if (!(month > 0 && month < 13)) {
	std::cout << "month error" << std::endl;
	return -1;
    }

    switch(month) {
    case 1:
    case 3:
    case 5:
    case 7:
    case 8:
    case 10:
    case 12:
	max = 31;
	break;
    case 2:
	max = 28;
	if (isLeapYear(year))
	    max = 29;
	break;
    case 4:
    case 6:
    case 9:
    case 11:
	max = 30;
	break;
    default:
	break;
    }
    if (day > max) {
	std::cout << "day error" << std::endl;
	return -1;
    }
   year_ = year;
   month_ = month;
   day_ = day;
   extraDays_ = backToFirstDayOfYear(); 

   return 0;
}

int Date::backToFirstDayOfYear()
{
    int days = day_;

    switch(month_-1) {
    case 12:
	days += 31;
    case 11:
	days += 30;
    case 10:
	days += 31;
    case 9:
	days += 30;
    case 8:
	days += 31;
    case 7:
	days += 31;
    case 6:
	days += 30;
    case 5:
	days += 31;
    case 4:
	days += 30;
    case 3:
	days += 31;
    case 2:
	if (isLeapYear(year_)) {
	    days += 29;
	} else {
	    days += 28;
	}
    case 1:
	days += 31;
    default:
	break;
    }
    month_ = 1;
    day_ = 1; 

    return days;
}

int main(int argc, char **argv)
{
    int year, month, day;
    int days = 0;
    Date d1;

    if (argc != 5) {
	std::cout << "please check your input: <program> <date.year> <date.month> <date.day> <days>" << std::endl;
	return 0;
    }
    year = std::stoi(std::string(argv[1]));
    month = std::stoi(std::string(argv[2]));
    day = std::stoi(std::string(argv[3]));
    days = std::stoi(std::string(argv[4]));
    if (d1.setDate(year, month, day) < 0) {
	std::cout << "please check your date" << std::endl;
	return 0;
    }
    d1.updateDate(days);
    std::cout << std::string("current is ") + std::string(argv[1]) + std::string("-") + std::string(argv[2]) + std::string("-") + std::string(argv[3]);
    std::cout << std::string(", after ") + std::string(argv[4]) + std::string("days");
    std::cout << std::string(", it is ") + std::to_string(d1.getYear()) + std::string("-") + std::to_string(d1.getMonth()) + std::string("-") + std::to_string(d1.getDay()) << std::endl;

    return 0;
}
