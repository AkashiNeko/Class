#pragma once

#ifndef __DATECLASS_H__
#define __DATECLASS_H__

#include <iostream>

#include <cstdlib>
#include <cassert>
#include <cstring>

class Date {
public:
	// 构造函数
	Date(int year = 1970, int month = 1, int day = 1);

	// 判断日期合法
	bool isLegal() {
		return _month > 0 && _month <= 12
			&& _day > 0 && _day <= GetDays(_year, _month);
	}

	// cin cout
	friend std::ostream& operator<<(std::ostream& out, const Date& d);
	friend std::istream& operator>>(std::istream& in, Date& d);

	// 判断两个日期是否相等
	// Date == Date
	bool operator==(const Date& d);

	// 比较两个日期的大小
	// Date < Date
	bool operator<(const Date& d) const;
	// Date > Date
	bool operator>(const Date& d) const;
	// Date <= Date
	bool operator<=(const Date& d) const;
	// Date >= Date
	bool operator>=(const Date& d) const;

	// 判断两个日期是否不相等
	// Date != Date
	bool operator!=(const Date& d);

	// 日期加减指定天数
	//  Date += days
	Date& operator+=(int days);
	//  Date -= days
	Date& operator-=(int days);
	// Date + days
	Date operator+(int days);
	// Date - days
	Date operator-(int days);

	// 日期加减一天
	// Date++
	Date operator++(int);
	// ++Date
	Date& operator++();
	// Date--
	Date operator--(int);
	// --Date
	Date& operator--();


	// 取两个日期相差的天数
	// Date - Date
	int operator-(const Date& d);

private:

	// 判断是否为闰年
	inline bool isLeapYear(int year) {
		return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
	}

	// 取指定月份的天数
	inline int GetDays(int year, int month) {
		static int days[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
		if (month == 2 && isLeapYear(year)) {
			return 29;
		}
		else {
			return days[month - 1];
		}
	}

	int _year;
	int _month;
	int _day;
};

#endif