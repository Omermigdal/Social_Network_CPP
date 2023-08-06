#ifndef __NAMES_EXCEPTIONS_H
#define  __NAMES_EXCEPTIONS_H

#include <string>
#include <iostream>
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)
#include "userExceptions.h"
class nameException : public UserExceptions
{
private:
	std::string m_name;
public:

	nameException(std::string& name) :m_name(name) {}
	static bool isNameValid(std::string& name);
	virtual void what() override { std::cout << m_name << " is not a valid name!" << std::endl; }
};
#endif __NAMES_EXCEPTIONS_H

