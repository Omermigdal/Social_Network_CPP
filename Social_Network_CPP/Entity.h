#ifndef __ENTITY_H
#define __ENTITY_H

#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)
#include <iostream>
#include <fstream>
#include <vector>

#include "status.h"

class Entity
{
protected:
	std::string m_name;
	std::vector<Status*> m_statuses;
public:

	Entity(std::string& name) :m_name(name) {};
	Entity(std::ifstream& inputFile);



	virtual ~Entity() {};

	virtual  void show() const;

	const std::string& getName()const { return m_name; };

	void addStatus(Status* toAdd) noexcept(false);

	void  showStatuses(int howMany = 0)const;

	virtual void save(std::ofstream& outputFile) const;



};




#endif 


//!__ENTITY_H
