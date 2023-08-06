#include "status.h"
#include <typeinfo>
#include <iostream>
#include <windows.h>  
using namespace std;


Status::Status(const string& text) : m_text(text)
{
	time_t rawtime;
	time(&rawtime);
	strcpy(m_date, ctime(&rawtime));
}


Status::Status(ifstream& inputFile)
{
	int textLen;
	char* text;
	inputFile.read((char*)&m_date, DATE_LEN - 1);
	m_date[DATE_LEN - 1] = '\0';
	inputFile.read((char*)&textLen, sizeof(int));
	text = new char[textLen];

	inputFile.read(text, textLen);
	m_text = string(text, textLen);
	delete[] text;
}

void Status::show() const
{
	cout << m_text << endl;
	cout << "Date: " << m_date << "\n" << endl;
}

bool Status::operator==(Status& other) const
{
	if (typeid(*this).name() != typeid(other).name()) // checking if the kind of the status is the same
		return false;

	if (m_text == other.m_text)
	{
		return true;
	}
	else
	{
		return false;
	}

}

bool  Status::operator!=(Status& other) const
{
	return !(*this == other);
}


void Status::save(ofstream& outputFile) const
{
	int textLen = (int)m_text.size();
	saveType(outputFile);
	outputFile.write((const char*)m_date, DATE_LEN - 1);// saves without \n
	outputFile.write((const char*)&textLen, sizeof(int));
	outputFile.write((const char*)m_text.c_str(), textLen);

}

void Status::saveType(ofstream& outputFile) const
{
	char type[TYPE_LEN];
	strncpy(type, typeid(*this).name() + 6, TYPE_LEN);
	outputFile.write((const char*)type, TYPE_LEN); //saving "Sta"/"pic"/"vid" class videoStatus
}
