#include "my_date.h"
#include <iostream>
#include <iomanip>
#include <cassert>

const int MyDate::month_day[2][13] = {
		{0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
     	{0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
	};

const int MyDate::year_day[2] = {365, 366};

const std::string MyDate::weekday_name[7] = {"Su", "Mo", "Tu", "We", "Th", "Fr", "Sa"};

const std::string MyDate::month_name[13] = {"", "Jan", "Feb", "Mar", "Apr", "May", "Jun",
	                                        "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};

MyDate::MyDate(uint year /* = 1 */, uint month /* = 1 */, uint day /* = 1 */) {
    assert((year > 0) && (month > 0) && (month <= 12) && (day > 0));
    int leap = is_leap_year(year);
    assert(day <= month_day[leap][month]);
    year_ = year, month_ = month, day_ = day;
}

MyDate::MyDate(const time_t &t) {
	std::string str_time(ctime(&t));
	std::string month = str_time.substr(4, 3);
    std::string day = str_time.substr(8, 2);
	std::string year = str_time.substr(20, str_time.length() - 21);
	year_ = str2int(year), day_ = str2int(day);
	for (int i = 0; i < 13; ++i) {
		if (month_name[i] == month) {
			month_ = i;
		}
	}
}

MyDate::MyDate(const MyDate &rhs)
	: year_(rhs.year_), month_(rhs.month_), day_(rhs.day_) {
	
}

MyDate& MyDate::operator=(const MyDate &rhs) {
	if (this != &rhs) {
		year_ = rhs.year_, month_ = rhs.month_, day_ = rhs.day_;
	}
	return *this;
}

MyDate::~MyDate() {

}

void MyDate::set_year(uint year) {
	assert(year > 0);
	year_ = year;
}

MyDate::uint MyDate::year() const {
	return year_;
}

void MyDate::set_month(uint month) {
	assert((month > 0) && (month <= 12));
	month_ = month;
}

MyDate::uint MyDate::month() const {
	return month_;
}

void MyDate::set_day(uint day) {
	int leap = is_leap_year(year_);
	assert((day > 0) && (day <= month_day[leap][month_]));
	day_ = day;
}

MyDate::uint MyDate::day() const {
	return day_;
}

/*
 * @brief Get this object's weekday.
 * @param no param.
 * @return This function return the weekday of this date.
 *         Su - Sunday, Mo - Monday, Tu - Tuesday, We -Wednesday,
 *         Th - Thursday, Fr - Friday, Sa - Saturday.
 **/
std::string MyDate::Weekday() {
	return weekday_name[weekday(*this)];
}

/*
 * @brief Get the specified date's weekday.
 * @param date [in] The specified date.
 * @return This function return the weekday of this date.
 *         Su - Sunday, Mo - Monday, Tu - Tuesday, We -Wednesday,
 *         Th - Thursday, Fr - Friday, Sa - Saturday.
 **/
std::string MyDate::Weekday(const MyDate &date) {
	return weekday_name[weekday(date)];
}

/*
 * @brief Get the specified date's weekday.
 * @param year [in] The specified year.
 * @param month [in] The specified month.
 * @param day [in] The specified day. By default, it is 1.
 * @return This function return the weekday of this date.
 *         Su - Sunday, Mo - Monday, Tu - Tuesday, We -Wednesday,
 *         Th - Thursday, Fr - Friday, Sa - Saturday.
 **/
std::string MyDate::Weekday(uint year, uint month, uint day /* = 1 */) {
	uint d = weekday(MyDate(year, month, day));
	return weekday_name[d];
}

/*
 * @brief Print a calendar of this object.
 * @param no param.
 * @return This function has no return vaule.
 **/
void MyDate::Kalender() {
     kalender(*this);
}

/*
 * @brief Print a calendar of the specified date
 * @param date [in] The date.
 * @return This function has no return vaule.

 **/
void MyDate::Kalender(const MyDate &date) {
	kalender(date);
}

/*
 * @brief Print a calendar of the specified date
 * @param year [in] The year.
 * @param month [in] The month, by default, it is 1.
 * @return This function has no return vaule.
 **/
void MyDate::Kalender(uint year, uint month /* = 1 */) {
     kalender(MyDate(year, month));
}

// --------------- Private Function ------------------ // 

/*
 * @brief Determine whether a leap year.
 * @param year [in] The year.
 * @return If this year is a leap year, the return is 1.
 *         Otherwise, the return is 0.
 **/
int MyDate::is_leap_year(uint year) {
	assert(year > 0);
    if ((year % 4 == 0) && (year % 100 != 0) ||
		(year % 400 == 0)) {
		return 1;
	}
	return 0;
}

/*
 * @brief Calculation day of the year for the first few days.
 * @param date [in] The date.
 * @return The ruturn is the date in this year's day.
 **/
MyDate::uint MyDate::which_day(const MyDate &date) {
	uint day = 0;
	int leap = is_leap_year(date.year());
	for (int i = 1; i < date.month(); ++i) {
		day += month_day[leap][i];
	}
	day += date.day();
	return day;
}

/*
 * @brief Get the weekday of the date.
 * @param date [in] The date.
 * @return weekday.
 *         The return value is 0, 1, 2, 3, 4, 5 and 6.
 *         0 means Sunday, 1 means Monday, 2 means Tuesday,
 *         3 means Wednesday, 4 menas Thursday, 5 means Friday,
 *         6 means Saturday.
 **/
MyDate::uint MyDate::weekday(const MyDate &date) {
	MyDate orign(1, 1, 7);
	int difference_day = date - orign;
	return (difference_day % 7);
}

/*
 * @brief Print a calendar of the month.
 * @param date [in] The date.
 * @return This function has no return value.
 **/
void MyDate::kalender(const MyDate &date) {
	MyDate t(date);
	t.set_day(1);
	int t_weekday = weekday(t);
	std::cout <<"      " <<month_name[t.month()] <<"  " 
		<<std::setw(4) <<t.year() <<std::endl;
    // display the name of weekday
	for (int i = 0; i < 7; ++i) {
		std::cout <<weekday_name[i] <<" ";
	}
	std::cout <<std::endl;
	// display the day of the month
	// first print space and the print the date
	int line_space = 0;
	for (int i = 0; i < t_weekday * 3; ++i) {
		std::cout <<" ";
		++line_space;
	}
	int leap = t.is_leap_year(t.year());
	int total_day = month_day[leap][t.month()];
	for (int i = 1; i <= total_day; ++i) {
		std::cout <<std::setw(2) <<i <<" ";
		line_space += 3;
		// every line has 21 characters
		if (line_space % 21 == 0 ) {
			std::cout <<std::endl;
		}
	}
    std::cout <<std::endl;
}

int MyDate::str2int(const std::string &str) {
	int sum = 0, i = 0;
	bool is_negative = false;
	if ('-' == str[i]) {
		is_negative = true;
		++i;
	}
	while (i < str.length()) {
		sum *= 10;
		sum += str[i] - '0';
		++i;
	}
	return is_negative ? -sum : sum;
}

// -------------- Operator Overloading --------------- // 

bool operator<(const MyDate &lhs, const MyDate &rhs) {
	return (lhs.year() < rhs.year()) &&
		   (lhs.month() < rhs.month()) &&
		   (lhs.day() < rhs.day());
}

int operator-(const MyDate &lhs, const MyDate &rhs) {
    bool r_big = false;
	MyDate left(lhs), right(rhs);
	if (left < right) {
		MyDate temp(left);
		left = right;
		right = temp;
		r_big = true;
	}
	MyDate::uint left_day = left.which_day(left);
	MyDate::uint right_day = right.which_day(right);
	int difference_day = 0;
	int difference_year = left.year_ - right.year_;
	if (0 == difference_year) {
		difference_day = left_day - right_day;
	} else if (1 == difference_year) {
		int leap = right.is_leap_year(right.year_);
		difference_day = MyDate::year_day[leap] - right_day + left_day;
	} else {
		for (int i = right.year_ + 1; i < left.year_; ++i) {
			int leap = right.is_leap_year(i);
			difference_day += MyDate::year_day[leap];
		}
		int leap = right.is_leap_year(right.year_);
		difference_day += (MyDate::year_day[leap] - right_day + left_day);
	}
	return r_big ? -difference_day : difference_day;
}


