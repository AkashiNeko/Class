#include "DateClass.h"

Date::Date(int year, int month, int day)
	:_year(year), _month(month), _day(day)
{
	assert(isLegal());
}

// 判断两个日期是否相等
// Date == Date
bool Date::operator==(const Date& d) {
	return _day = d._day && _month == d._month && _year == d._year;
}

// 比较两个日期的大小
// Date < Date
bool Date::operator<(const Date& d) const{
	return _year < d._year
		|| (_year == d._year && _month < d._month)
		|| (_month == d._month && _day < d._day);
}
// Date > Date
bool Date::operator>(const Date& d) const{
	return _year > d._year
		|| (_year == d._year && _month > d._month)
		|| (_month == d._month && _day > d._day);
}
// Date >= Date
bool Date::operator>=(const Date& d) const {
	return !(*this < d);
}
// Date <= Date
bool Date::operator<=(const Date& d) const {
	return !(*this > d);
}

// 判断两个日期是否不相等
// Date != Date
bool Date::operator!=(const Date& d) {
	return _day != d._day || _month != d._month || _year != d._year;
}

// 日期加减指定天数
//  Date += days
Date& Date::operator+=(int days) {
	if (days < 0) {
		return *this -= (-days);
	}
	_day += days;
	int get;
	while ((get = GetDays(_year, _month)) < _day) {
		//日期超过该月最大天数，则跳到下一个月
		++_month;
		_day -= get;
		if (_month == 13) {
			//月份大于12，则跳到下一年
			_month = 1;
			++_year;
		}
	}
	return *this;
}
//  Date -= days
Date& Date::operator-=(int days) {
	if (days < 0) {
		return *this += (-days);
	}
	_day -= days;
	while (_day < 1) {
		//日期小于1，则跳到前一个月
		--_month;
		_day += GetDays(_year, _month);
		if (_month == 0) {
			//月份小于1，则跳到上一年
			_month = 12;
			--_year;
		}
	}
	return *this;
}

// Date + days
Date Date::operator+(int days) {
	Date ret(*this);
	ret += days;
	return ret;
}
// Date - days
Date Date::operator-(int days) {
	Date ret(*this);
	ret -= days;
	return ret;
}

// 日期加减一天
// Date++
Date Date::operator++(int) {
	Date ret(*this);
	*this += 1;
	return ret;
}
// ++Date
Date& Date::operator++() {
	return *this += 1;
}
// Date--
Date Date::operator--(int) {
	Date ret(*this);
	*this -= 1;
	return ret;
}
// --Date
Date& Date::operator--() {
	return *this -= 1;
}

// 取两个日期相差的天数
// Date - Date
int Date::operator-(const Date& d) {
	int count;
	Date temp1(*this);
	Date temp2(d);
	//计算相差日期对应的天数
	count = temp1._day - temp2._day;
	temp1._day = 1;
	temp2._day = 1;
	//计算相差月份对应的天数
	while (temp1._month != temp2._month) {
		--temp1._month;
		if (temp1._month == 0) {
			temp1._month = 12;
			--temp1._year;
		}
		count += GetDays(temp1._year, temp1._month);
	}
	//计算相差年份对应的天数
	if (temp1._month > 2) {
		++temp1._year;
		++temp2._year;
	}
	while (temp1._year > temp2._year) {
		count += isLeapYear(--temp1._year) ? 366 : 365;
	}
	while (temp1._year < temp2._year) {
		count -= isLeapYear(temp1._year++) ? 366 : 365;
	}
	return count;
}

std::ostream& operator<<(std::ostream& out, const Date& d) {
	out << d._year << '-' << d._month << '-' << d._day;
	return out;
}

std::istream& operator>>(std::istream& in, Date& d) {
	in >> d._year >> d._month >> d._day;
	assert(d.isLegal());
	return in;
}