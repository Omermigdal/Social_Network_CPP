#include "Entity.h"
#include "pictureStatus.h"
#include "videoStatus.h"
#include "admin.h"
#include "statusExceptions.h"
using namespace std;



Entity::Entity(ifstream& inputFile)
{
	int nameLen, numOfStatuses;
	char* name;
	inputFile.read((char*)&nameLen, sizeof(int));
	name = new char[nameLen];
	inputFile.read(name, nameLen); // CHECK IF READING BINARYWORKS
	m_name = string(name, nameLen);// string capacity-> read string
	delete[] name;

	inputFile.read((char*)&numOfStatuses, sizeof(int));
	m_statuses.reserve(numOfStatuses);

	//loading statuses
	for (int i = 0; i < numOfStatuses; i++)
	{
		char type[Status::TYPE_LEN + 1];
		inputFile.read(type, Status::TYPE_LEN);
		type[Status::TYPE_LEN] = '\0';

		if (strcmp(type, "pic") == 0)
			m_statuses.push_back(new pictureStatus(inputFile));
		else if (strcmp(type, "vid") == 0)
			m_statuses.push_back(new videoStatus(inputFile));
		else
			m_statuses.push_back(new Status(inputFile));
	}


}

void Entity::show()const
{
	cout << m_name << endl;
}

void Entity::showStatuses(int howMany) const
{
	cout << "\n\n";

	if (m_statuses.empty())
	{
		cout << m_name << " has no statuses";
		return;
	}

	int numOfStatuses = (int)m_statuses.size();

	if (howMany != 0) // showing amount of statuses according to howMany
	{
		if (howMany > numOfStatuses)
		{
			howMany = numOfStatuses;
			cout << m_name << "has only " << numOfStatuses << "statuses, showing them.." << endl;
		}
		for (int i = 0; i < howMany; i++)
		{
			Status* currStatus = m_statuses[i];
			const pictureStatus* pic = dynamic_cast<const pictureStatus*>(currStatus);
			if (pic)
			{
				pic->show();
				continue;
			}

			const videoStatus* vid = dynamic_cast<const videoStatus*>(currStatus);
			if (vid)
			{
				vid->show();
				continue;
			}
			else // text status..
				currStatus->show();
		}
		return;
	}



	// else - showing 
	vector<Status*>::const_iterator itr = m_statuses.begin();
	vector<Status*>::const_iterator itrEnd = m_statuses.end();


	cout << "------------Showing statuses of " << m_name << "-------------" << endl;

	for (; itr != itrEnd; ++itr)
	{
		const pictureStatus* pic = dynamic_cast<const pictureStatus*>(*itr);
		if (pic)
		{
			pic->show();
			continue;
		}
		const videoStatus* vid = dynamic_cast<const videoStatus*>(*itr);
		if (vid)
		{
			vid->show();
			continue;
		}

		else // text status..
			(*itr)->show();
	}
	cout << "-------------------------------------------------------------" << endl;
}

void  Entity::addStatus(Status* toAdd)
{
	m_statuses.push_back(toAdd);
}

void Entity::save(ofstream& outputFile) const
{
	int nameLen = (int)m_name.size();
	int numOfStatuses = (int)m_statuses.size();

	outputFile.write((const char*)&nameLen, sizeof(nameLen)); // wirting 4B name length
	outputFile.write(m_name.c_str(), nameLen);// writing  name
	outputFile.write((const char*)&numOfStatuses, sizeof(int));

	for (auto& status : m_statuses)
		status->save(outputFile);


}


