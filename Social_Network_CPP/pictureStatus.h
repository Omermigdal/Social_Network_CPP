#ifndef __PICTURE_STATUS_H
#define __PICTURE_STATUS_H

#include "status.h"

class pictureStatus : public Status
{
private:
	std::string m_fileName;
public:
	pictureStatus(std::string text, std::string fileName) : Status(text), m_fileName(fileName) {}
	virtual void show() const override;
	pictureStatus(std::ifstream& inputFile);

	virtual void save(std::ofstream& outputFile) const override;

};
#endif // !__PICTURE_STATUS_H
