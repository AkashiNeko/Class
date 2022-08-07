#include "DateClass.h"

Date::Date(int year, int month, int day)
	:_year(year), _month(month), _day(day)
{
	assert(isLegal());
}

// �ж����������Ƿ����
// Date == Date
bool Date::operator==(const Date& d) {
	return _day = d._day && _month == d._month && _year == d._year;
}

// �Ƚ��������ڵĴ�С
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

// �ж����������Ƿ����
// Date != Date
bool Date::operator!=(const Date& d) {
	return _day != d._day || _month != d._month || _year != d._year;
}

// ���ڼӼ�ָ������
//  Date += days
Date& Date::operator+=(int days) {
	if (days < 0) {
		return *this -= (-days);
	}
	_day += days;
	int get;
	while ((get = GetDays(_year, _month)) < _day) {
		//���ڳ������������������������һ����
		++_month;
		_day -= get;
		if (_month == 13) {
			//�·ݴ���12����������һ��
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
		//����С��1��������ǰһ����
		--_month;
		_day += GetDays(_year, _month);
		if (_month == 0) {
			//�·�С��1����������һ��
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

// ���ڼӼ�һ��
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

// ȡ����������������
// Date - Date
int Date::operator-(const Date& d) {
	int count;
	Date temp1(*this);
	Date temp2(d);
	//����������ڶ�Ӧ������
	count = temp1._day - temp2._day;
	temp1._day = 1;
	temp2._day = 1;
	//��������·ݶ�Ӧ������
	while (temp1._month != temp2._month) {
		--temp1._month;
		if (temp1._month == 0) {
			temp1._month = 12;
			--temp1._year;
		}
		count += GetDays(temp1._year, temp1._month);
	}
	//���������ݶ�Ӧ������
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