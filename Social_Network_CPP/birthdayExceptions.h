#ifndef __BIRTHDAY_EXCEPTIONS_H
#define  __BIRTHDAY_EXCEPTIONS_H
#include <iostream>
#include "userExceptions.h"
enum months {
	Jan, Feb, Mar, Apr, May, Jun, Jul,
	Aug, Sep, Oct, Nov, Dec
};

class birthdayException :public UserExceptions
{
private:
	int m_val;
	std::string m_date;
public:
	birthdayException(int val, std::string& dateType) : m_val(val), m_date(dateType) {}
	virtual void what() override { std::cout << m_val << "is Invalid " << m_date << std::endl; }


	static bool checkDay(int day)
	{
		if (!(day >= 1 && day <= 30))
			return false;
		else
			return true;
	}

	static bool checkMonth(int month)
	{
		if (!(month >= Jan && month <= Feb))
			return false;
		else
			return true;
	}

	static bool checkYear(int year)
	{
		if (!(year >= 1923 && year <= 2023))
			return false;
		else
			return true;
	}
};

#endif //__BIRTHDAY_EXCEPTIONS_H

