#include <iostream>

#define LEFT_BIT_VAL(v) (!!((1 << 31) & (v)))

class Date {
public:
    Date() {year_ = 0; month_ = 0; day_ = 0; extraDays_ = 0;};
    ~Date() {};
    uint64_t calcDays(Date &date);
    int setDate(int year, int month, int day);
    int getYear();
    int getExtraDays();
private:
    bool isLeapYear(int year);
    uint64_t getDaysOfYear(int year);
    uint64_t backToFirstDayOfYear();
    int year_;
    int month_;
    int day_;
    uint64_t extraDays_;
};

int Date::getYear()
{
    return year_;
}
    
int Date::getExtraDays()
{
    return extraDays_;
}

uint64_t Date::calcDays(Date &date)
{
    int year = date.getYear();
    int maxYear = year;
    int minYear = maxYear;
    uint64_t days = 0;
    uint64_t extraDays = date.getExtraDays();

    if (year_ > maxYear) maxYear = year_;
    if (year_ < minYear) minYear = year_;

    for (int i = minYear; i < maxYear; i++)
	days += getDaysOfYear(i);
    if (year_ == year) {
	days += (extraDays_ > extraDays) ? (extraDays_ - extraDays) : (extraDays - extraDays_);
    } else if (year_ < year) {
	days += extraDays - extraDays_;
    } else {
	days += extraDays_ - extraDays;
    }

    return days;
}

uint64_t Date::getDaysOfYear(int year)
{
    uint64_t days = 365;

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

uint64_t Date::backToFirstDayOfYear()
{
    uint64_t days = uint64_t(day_);

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
    uint64_t daysdiff;
    Date d1, d2;

    if (argc != 7) {
	std::cout << "please check your input: <program> <date1.year> <date1.month> <date1.day> <date2.year> <date2.month> <date2.day>" << std::endl;
	return 0;
    }
    year = std::stoi(std::string(argv[1]));
    month = std::stoi(std::string(argv[2]));
    day = std::stoi(std::string(argv[3]));
    if (d1.setDate(year, month, day) < 0) {
	std::cout << "please check your date1" << std::endl;
	return 0;
    }

    year = std::stoi(std::string(argv[4]));
    month = std::stoi(std::string(argv[5]));
    day = std::stoi(std::string(argv[6]));
    if (d2.setDate(year, month, day) < 0) {
	std::cout << "please check your date2" << std::endl;
	return 0;
    }

    daysdiff = d2.calcDays(d1);
    std::cout << "days between d1 and d2 is " << daysdiff << std::endl;

    return 0;
}
