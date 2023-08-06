#include "user.h"
#include "fanPage.h"
#include <fstream>
using namespace std;
#define B_DAY_LEN 10


User::User(string name, const char* birthDay) :Entity(name)
{
	setBirthDay(birthDay);
}

User::User(ifstream& inputFile) : Entity(inputFile)
{
	inputFile.read((char*)&m_birthDay, B_DAY_LEN);
	m_birthDay[B_DAY_LEN] = '\0';
}

bool User::setBirthDay(const char* birthDay)
{
	strcpy(m_birthDay, birthDay);

	return true;
}


void User::showFriends() const
{
	cout << m_name << " friends: " << endl;
	int i = 1;
	vector<User*>::const_iterator itr = m_friends.begin();
	vector<User*>::const_iterator itrEnd = m_friends.end();
	for (; itr != itrEnd; ++itr, ++i)
	{
		cout << i << ".";
		(*itr)->show();
	}

}

bool User::addFriend(User* _newFriend)
{

	if (areFriends(_newFriend) == true)
	{
		return false;
	}
	else
	{
		m_friends.push_back(_newFriend);
		return true; //new friends added
	}

}

bool User::becomeFan(Fanpage* pageToFan) {

	if (isFan(pageToFan) == true)
	{
		return false;
	}
	else
	{
		m_fanPages.push_back(pageToFan);
		return true;
	}

}

bool User::removeFriend(User* friendToRemove)
{
	if (m_friends.empty() || friendToRemove->m_friends.empty()) // users are not friends for sure
		return false;

	vector<User*>::iterator itr = m_friends.begin();
	vector<User*>::iterator itrEnd = m_friends.end();

	vector<User*>::iterator res = find(itr, itrEnd, friendToRemove);

	if (res == itrEnd) // users are not friends... 
		return false;

	else
	{
		m_friends.erase(res);
		return true;
	}

}

void User::showLastTenStatusesOfFriends() const
{
	cout << "\n\n";


	if (m_friends.empty() == true)
	{
		cout << m_name << " Currently has no friends." << endl;
		return;
	}

	// user has friends
	cout << "------------Last 10 statuses of " << m_name << "'s friends-------------" << endl;

	vector<User*>::const_iterator itr = m_friends.begin();
	vector<User*>::const_iterator itrEnd = m_friends.end();

	for (; itr != itrEnd; ++itr)
	{
		(*itr)->showStatuses(10);
	}

}

bool User::areFriends(const User* other) const
{
	if ((other->m_friends.empty() == true) || (this->m_friends.empty() == true))
		return false;


	vector<User*>::const_iterator itr = m_friends.begin();
	vector<User*>::const_iterator itrEnd = m_friends.end();


	if (other == *(itrEnd - 1))
		return true; // users are already friends...

	itr = find(m_friends.begin(), m_friends.end(), other); // making sure they are not friend


	if (itr == itrEnd) // not friends
		return false;

	// passing all that, users are friends
	return true;

}


bool User::isFan(Fanpage* fanPageTocheck) const
{
	if (m_fanPages.empty() == true)
	{
		return false;
	}
	else {
		vector<Fanpage*>::const_iterator itr = m_fanPages.begin();
		vector<Fanpage*>::const_iterator itrEnd = m_fanPages.end();

		itr = find(m_fanPages.begin(), m_fanPages.end(), fanPageTocheck);

		if (itr == itrEnd)
		{					// user is not a fan of the given fan page
			return false;
		}
		else {
			return true;

		}
	}

}

bool User::operator==(const User& other) const
{
	if (m_name == other.getName())
		return true;
	else
		return false;
}

User& User::operator+=(User& _newFriend)// how to const
{
	if (&(_newFriend) == this)
	{
		return *this;// thrrow cant be friend of yourself!
	}
	addFriend(&_newFriend);
	_newFriend.addFriend(this);
	return *this;
}

User& User::operator+=(Fanpage& fanPage)
{
	this->becomeFan(&fanPage);
	fanPage.addFan(this);

	return *this;


}

bool User::operator>(User& other)  const
{
	if (m_friends.size() > other.m_friends.size())
	{
		return true;
	}
	else
		return false;

}

bool User::operator>(Fanpage& other)  const
{
	if (m_friends.size() > other.getNumOfFans())
	{
		return true;
	}
	else
		return false;
}

void User::showAllFanpages() const
{
	for (auto& pFanpage : m_fanPages)
		pFanpage->show();

}

void User::save(ofstream& outputFile)const  // saving fanpage name -> fans-> statuses
{
	int numOfFanpages = (int)m_fanPages.size();
	int numOfFriends = (int)m_friends.size();

	Entity::save(outputFile);
	outputFile.write((const char*)m_birthDay, B_DAY_LEN);// writing bday

	outputFile.write((const char*)&numOfFriends, sizeof(int));
	outputFile.write((const char*)&numOfFanpages, sizeof(int));


}

void User::saveFriendsNames(ofstream& outputFile)const
{
	for (auto& currFriend : m_friends)
	{
		int len = (int)(currFriend->m_name.size());
		outputFile.write((const char*)&len, sizeof(int));
		outputFile.write((const char*)currFriend->m_name.c_str(), len);
	}
}

void User::saveFanpagesNames(ofstream& outputFile)const
{
	for (auto& currFanpage : m_fanPages)
	{
		string currName = currFanpage->getName();
		int len = (int)(currName.size());
		outputFile.write((const char*)&len, sizeof(int));
		outputFile.write((const char*)currName.c_str(), len);
	}
}

