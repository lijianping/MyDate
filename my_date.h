#ifndef _MY_DATE_H_
#define _MY_DATE_H_

#include <string>
#include <ctime>

class MyDate {
public:
	typedef unsigned int uint;
	MyDate(uint year = 1, uint month = 1, uint day = 1);
	MyDate(const time_t &t);
    MyDate(const MyDate &rhs);
	MyDate& operator=(const MyDate &rhs);
	~MyDate();
	inline void set_year(uint year);
	inline uint year() const;
	inline void set_month(uint month);
	inline uint month() const;
	inline void set_day(uint day);
	inline uint day() const;
    std::string Weekday();
	std::string Weekday(const MyDate &date);
	std::string Weekday(uint year, uint month, uint day = 1);
	void Kalender();
	void Kalender(const MyDate &date);
	void Kalender(uint year, uint month = 1);
	friend int operator-(const MyDate &lhs, const MyDate &rhs);

private:
    const static int month_day[2][13];
    const static int year_day[2];
    const static std::string weekday_name[7];
    const static std::string month_name[13];
	
	int is_leap_year(uint year);
	uint which_day(const MyDate &date);
	uint weekday(const MyDate &date);
	void kalender(const MyDate &date);
    int str2int(const std::string &str);

	uint year_;
	uint month_;
	uint day_;
};

#endif
