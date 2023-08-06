#include "videoStatus.h"
#include <iostream>
using namespace std;


videoStatus::videoStatus(ifstream& inputFile) :Status(inputFile)
{
	int fileNameLen;
	char* fileName;

	inputFile.read((char*)&fileNameLen, sizeof(int));
	fileName = new char[fileNameLen];
	inputFile.read(fileName, fileNameLen); // CHECK IF READING BINARYWORKS
	m_fileName = string(fileName, fileNameLen);
	delete[] fileName;

}

void videoStatus::show() const
{
	int color = rand() % 12;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
	cout << "--------------------VIDEO--------------------" << endl;
	Status::show();
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	system("start myvideo.mov");
}


void videoStatus::save(ofstream& outputFile) const
{
	int fileNameLen = (int)m_fileName.size();
	Status::save(outputFile);
	outputFile.write((const char*)&fileNameLen, sizeof(int));
	outputFile.write((const char*)m_fileName.c_str(), fileNameLen);
}