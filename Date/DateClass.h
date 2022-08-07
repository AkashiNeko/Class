#pragma once

#ifndef __DATECLASS_H__
#define __DATECLASS_H__

#include <iostream>

#include <cstdlib>
#include <cassert>
#include <cstring>

class Date {
public:
	// ���캯��
	Date(int year = 1970, int month = 1, int day = 1);

	// �ж����ںϷ�
	bool isLegal() {
		return _month > 0 && _month <= 12
			&& _day > 0 && _day <= GetDays(_year, _month);
	}

	// cin cout
	friend std::ostream& operator<<(std::ostream& out, const Date& d);
	friend std::istream& operator>>(std::istream& in, Date& d);

	// �ж����������Ƿ����
	// Date == Date
	bool operator==(const Date& d);

	// �Ƚ��������ڵĴ�С
	// Date < Date
	bool operator<(const Date& d) const;
	// Date > Date
	bool operator>(const Date& d) const;
	// Date <= Date
	bool operator<=(const Date& d) const;
	// Date >= Date
	bool operator>=(const Date& d) const;

	// �ж����������Ƿ����
	// Date != Date
	bool operator!=(const Date& d);

	// ���ڼӼ�ָ������
	//  Date += days
	Date& operator+=(int days);
	//  Date -= days
	Date& operator-=(int days);
	// Date + days
	Date operator+(int days);
	// Date - days
	Date operator-(int days);

	// ���ڼӼ�һ��
	// Date++
	Date operator++(int);
	// ++Date
	Date& operator++();
	// Date--
	Date operator--(int);
	// --Date
	Date& operator--();


	// ȡ����������������
	// Date - Date
	int operator-(const Date& d);

private:

	// �ж��Ƿ�Ϊ����
	inline bool isLeapYear(int year) {
		return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
	}

	// ȡָ���·ݵ�����
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