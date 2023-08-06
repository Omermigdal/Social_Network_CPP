#ifndef ADMIN_EXCEPTION_H
#define ADMIN_EXCEPTION_H
#include<iostream>
#include "Entity.h"

class AdminException
{
protected:
	std::string m_name;
public:
	AdminException(std::string& name) : m_name(name) {}

	virtual void what()const = 0;

};

#endif //ADMIN_EXCEPTION_H


