#include "pictureStatus.h"
#include <iostream>
#include <fstream>
using namespace std;



pictureStatus::pictureStatus(ifstream& inputFile) :Status(inputFile)
{

	int fileNameLen;
	char* fileName;

	inputFile.read((char*)&fileNameLen, sizeof(int));
	fileName = new char[fileNameLen];
	inputFile.read(fileName, fileNameLen); // CHECK IF READING BINARYWORKS
	m_fileName = string(fileName, fileNameLen);
	delete[] fileName;
}



void pictureStatus::show() const
{
	int color = rand() % 12;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
	cout << "--------------------PICTURE--------------------" << endl;
	Status::show();
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	system("start picture.jpg");

}

void pictureStatus::save(ofstream& outputFile) const
{
	int fileNameLen = (int)m_fileName.size();
	Status::save(outputFile);
	outputFile.write((const char*)&fileNameLen, sizeof(int));
	outputFile.write((const char*)m_fileName.c_str(), fileNameLen);
}

