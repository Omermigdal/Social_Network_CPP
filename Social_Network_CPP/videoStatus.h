#ifndef __VIDEO_STATUS_H
#define __VIDEO_STATUS_H

#include "status.h"
class videoStatus : public Status
{

private:
	std::string m_fileName;

public:
	videoStatus(std::string& text, std::string& fileName) : Status(text), m_fileName(fileName) {}
	videoStatus(std::ifstream& inputFile);

	virtual void show() const override;

	virtual void save(std::ofstream& outputFile) const override;


};

#endif //__VIDEO_STATUS_H