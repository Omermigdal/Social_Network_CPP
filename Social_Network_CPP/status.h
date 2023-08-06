#ifndef __STATUS_H
#define __STATUS_H

#include <ctime>
#include <string>
#include <fstream>
#include <typeinfo>
#include <windows.h>

#define _CRT_SECURE_NO_WARNINGS
#define DATE_LEN 25
#pragma warning(disable:4996)


enum  statusType { TEXT = 1, PICTURE, VIDEO };

class Status
{
public:
	static const int TYPE_LEN = 3;
protected:
	char m_date[DATE_LEN];
	std::string m_text;

public:


	//constructor
	Status(const std::string& text);

	Status(std::ifstream& inputFile);

	//show a spesific status content and Date
	virtual void show() const;

	const char* getDate() { return m_date; }
	std::string& getContent() { return m_text; }

	// checks if statuses are the same
	bool operator==(Status& other) const;

	// checks if statuses are not the same
	bool operator!=(Status& other) const;

	//virtual void load(ifstream& inputFile);

	virtual void save(std::ofstream& outputFile) const;

	void saveType(std::ofstream& outputFile) const;

};
#endif //__STATUS_H
