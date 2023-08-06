#include "fanPage.h"
#include "user.h"
#include <vector>

using namespace std;


Fanpage::Fanpage(string name) : Entity(name)
{
}


Fanpage::Fanpage(ifstream& inputFile) : Entity(inputFile)
{


}

bool Fanpage::isUserFan(const User* user) const
{
	vector<User*>::const_iterator itr = m_fans.begin();
	vector<User*>::const_iterator itrEnd = m_fans.end();

	if (m_fans.empty() == true) //no fans
		return false;

	itr = find(itr, itrEnd, user);

	if (itr == itrEnd)
		return false;
	else
		return true;
}

bool Fanpage::addFan(const User* _newFan)
{
	if (isUserFan(_newFan) == false)
	{
		m_fans.push_back((User*)_newFan);
		return true;
	}
	else // user is already a fan of this fanapge
	{
		cout << "This user is already a fan of " << m_name << endl;
		return false;

	}
}

bool Fanpage::removeFan(User* _fanToRemove)
{
	vector<User*>::iterator itr = m_fans.begin();
	vector<User*>::iterator itrEnd = m_fans.end();
	vector<User*>::iterator res = find(itr, itrEnd, _fanToRemove);

	if (res == itrEnd) // users are not friends... // change to choosing from users..
		return false;
	else
	{
		m_fans.erase(res);
		return true;
	}
}

void Fanpage::showFans() const
{
	vector<User*>::const_iterator itr = m_fans.begin();
	vector<User*>::const_iterator itrEnd = m_fans.end();

	if (itr == itrEnd)
	{
		cout << m_name << " Has No fans" << endl;;
		return;
	}
	else
	{
		cout << m_name << " fans: " << endl;
		int num = 1;
		for (; itr != itrEnd; ++itr)
		{
			cout << num << ".";
			(*(*itr)).show();
			num++;
		}
	}
}

int Fanpage::getNumOfFans()const
{
	return (int)m_fans.size();
}

User* Fanpage::chooseFan()
{
	int numOfFans = (int)(m_fans.size());
	int choice;
	cout << "Please select the fan:\n" << endl;
	showFans();
	cout << "Choice: ";
	cin >> choice;
	cin.ignore();

	while (choice > numOfFans || choice < 1) // choice exception
	{
		cout << "     ERROR-Invalid choice, please select a User in range." << endl;
		cin >> choice;
		cin.ignore();
	}

	vector<User*>::iterator itr = m_fans.begin();
	while (choice > 1)
	{
		++itr;
		choice--;
	}
	return (*itr);
}

void Fanpage::operator+=(User* newFan)
{
	addFan(newFan);
	newFan->becomeFan(this);
}

bool Fanpage::operator>(Fanpage& other) const
{
	if (m_fans.size() > other.m_fans.size())
	{
		return true;
	}
	else
		return false;

}

bool Fanpage::operator>(User& other) const
{
	if (m_fans.size() > other.getNumOfFriends())
	{
		return true;
	}
	else
		return false;
}

void Fanpage::save(ofstream& outputFile)const  //
{
	int numOfFans = (int)m_fans.size();
	Entity::save(outputFile);
	outputFile.write((const char*)&numOfFans, sizeof(int));

}

void Fanpage::saveFansNames(std::ofstream& outputFile)const
{
	for (auto& currFan : m_fans)
	{
		string currName = currFan->getName();
		int len = (int)(currName.size());
		outputFile.write((const char*)&len, sizeof(int));
		outputFile.write((const char*)currName.c_str(), len);
	}
}
