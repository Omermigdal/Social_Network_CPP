#ifndef __IS_EXIST_H
#define  __IS_EXIST_H
#include "adminExceptions.h"

#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)

class isExistException : public AdminException
{
public:
	isExistException(std::string& name) :AdminException(name) {}

	virtual void what() const override { std::cout << m_name << " already exists" << std::endl; }


};

#endif// __IS_EXIST_H

