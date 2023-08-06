#include <iostream>
#define USER_CHOICE 1
#define EMPTY 0
#define FAN_PAGE_CHOICE 2
#define BIRTHDAY_LENGTH 13
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)
#pragma once
#include "admin.h"
#include "user.h"
#include "fanPage.h"
#include "status.h"
#include "choiceExceptions.h"
#include <sstream>
#include "adminExceptions.h"
#include "userExceptions.h"
#include "birthdayExceptions.h"
#include "isExistException.h"
#include "namesExceptions.h"
#include "statusExceptions.h"
#include "videoStatus.h"
#include "pictureStatus.h"
using namespace std;




void Admin::promptMenu()
{
	bool flag = false;
	int  choice;
	std::cout << "\nwelcome to Facebook!\n";


	while (flag == false)
	{


		cout << "\n\n****************ADMIN MENU*************************\n";
		cout << "       " << ADD_USER << "-------Add a new user to the system \n";
		cout << "       " << ADD_FANPAGE << "-------Add a new fan page to the system\n";
		cout << "       " << ADD_STATUS_TO_ENTITY << "-------Add new status to a friend or a fan page \n";
		cout << "       " << SHOW_ALL_STATUSES << "-------Show all the statuses of a specific friend or a fan page \n";
		cout << "       " << SHOW_LAST_TEN_STATUSES_OF_FRIENDS_OF_USER << "-------Show last 10 statuses of an entitiy (last 10 status from all of his friends) \n";
		cout << "       " << CONNECT << "-------Create friendship between 2  friends \n";
		cout << "       " << DISCONNECT << "-------Disconnet friendshep between 2 friends \n";
		cout << "       " << ADD_FAN_TO_FANPAGE << "-------Add a fan to a fan page \n";
		cout << "       " << REMOVE_FAN_FROM_FANPAGE << "-------Delete a fan from a fan page fans list\n";
		cout << "       " << SHOW_ALL_ENTETIES << "------Show all facebook friends and fan pages\n";
		cout << "       " << SHOW_ALL_CONNECTIONS << "------Show all friends/fans of a specific friend or fan page \n";
		cout << EXIT_SYSTEM << "-exit \n";
		cout << "*******************************************************\n\n";

		cout << "Choice: ";
		cin >> choice;
		cin.ignore();



		switch (choice)
		{
		case ADD_USER:
			addUser();
			break;
		case ADD_FANPAGE:
			addFanpage();
			break;
		case ADD_STATUS_TO_ENTITY:
			addStatusToEntity();
			break;
		case SHOW_ALL_STATUSES:
			showStatuses();
			break;
		case SHOW_LAST_TEN_STATUSES_OF_FRIENDS_OF_USER:
			showLastTenStatuses();
			break;
		case CONNECT:
			connect();
			break;
		case DISCONNECT:
			disconnect();
			break;
		case ADD_FAN_TO_FANPAGE:
			addFanToFanpage();
			break;
		case REMOVE_FAN_FROM_FANPAGE:
			removeFanFromFanpage();
			break;
		case SHOW_ALL_ENTETIES:
			showAllEntities();
			break;
		case SHOW_ALL_CONNECTIONS:
			showAllConnections();
			break;
		case EXIT_SYSTEM:
			cout << "Goodbye!\n";
			flag = true;
			break;
		}// end switch

	}// end while
} // ends prompt

//1
void Admin::addUser()
{

	bool isValid = false;
	while (isValid == false)
	{
		try
		{
			char birthDay[BIRTHDAY_LENGTH];
			string userName = getUserName();
			getBirthday(birthDay);
			m_usersList.push_back(User(userName, birthDay));
		}
		catch (UserExceptions& ue) {
			ue.what();
		}

		catch (AdminException& ae)
		{
			ae.what();
		}
		catch (...)
		{
			cout << "FATAL ERROR !" << endl;
		}
		isValid = true;
	}
}

//2
void Admin::addFanpage()
{
	bool isValid = false;
	while (isValid == false)
	{
		try
		{
			string fanPageName = getFanPageName();
			m_fanPagesList.push_back(Fanpage(fanPageName));
		}
		catch (nameException& ue) {
			ue.what();
		}

		catch (AdminException& ae)
		{
			ae.what();
		}
		catch (...)
		{
			cout << "FATAL ERROR !" << endl;
		}
		isValid = true;
	}
}

//3
void Admin::addStatusToEntity()
{
	string tempName;
	Entity* entity;
	int choice;
	bool isChoiceValid = false;
	bool isValid = false;
	while (isValid == false)
	{

		try
		{
			cout << "Add the  status to:\n 1-user \n 2-fan page: " << endl;
			choice = getChoice(USER_CHOICE, FAN_PAGE_CHOICE);
			switch (choice)
			{
			case 1: // adding a status to a user
				entity = chooseUser();
				entity->addStatus(createStatus());
				break;
			case 2:// adding a status to a fanpage
				entity = chooseFanpage();
				entity->addStatus(createStatus());
				break;
			}
		}
		catch (choiceExceptions& ce)
		{
			ce.what();
		}
		catch (statusExceptions& se)
		{
			se.what();
		}

		catch (...)
		{
			cout << "FATAL ERROR !" << endl;
		}
		isValid = true;
	}

}

//4
void Admin::showStatuses()
{

	int choice;
	bool isValid = false;

	while (isValid == false)
	{
		try
		{
			cout << "Show statuses of:\n 1-user \n 2-fan page: " << endl;
			choice = getChoice(USER_CHOICE, FAN_PAGE_CHOICE);
			switch (choice)
			{
			case 1: // showing user statuses
				chooseUser()->showStatuses();
				break;
			case 2:// showing fanpage statuses
				chooseFanpage()->showStatuses();
				break;
			}
		}
		catch (choiceExceptions& ce)
		{
			ce.what();
		}

		catch (...)
		{
			cout << "FATAL ERROR !" << endl;
		}
		isValid = true;
	}


}

//5
void Admin::showLastTenStatuses()
{
	int numOfUsers = (int)m_usersList.size();
	bool isValid = false;

	while (isValid == false)
	{
		try
		{
			cout << "Choose a user to see 10 statuses fo his friends: " << endl;
			chooseUser()->showLastTenStatusesOfFriends();

		}
		catch (choiceExceptions& ce)
		{
			ce.what();
		}

		catch (...)
		{
			cout << "FATAL ERROR !" << endl;
		}
		isValid = true;
	}
}

//6
void Admin::connect()
{
	bool isValid = false;
	while (isValid == false)
	{

		try {
			cout << "Please select the two users you want to connect: " << endl;
			cout << "First user- ";
			User* user1 = chooseUser();

			cout << "Second user- ";
			User* user2 = chooseUser();

			if (user1->addFriend(user2))
			{
				user2->addFriend(user1);
				cout << "\nConnection was made:\n" << user1->getName() << " <----> " << user2->getName() << endl;
			}
			else
				cout << "\n" << user1->getName() << " and " << user2->getName() << " are already friends..\n";
		}
		catch (choiceExceptions& ce)
		{
			ce.what();
		}
		catch (...)
		{
			cout << "FATAL ERROR !" << endl;
		}
		isValid = true;
	}
}

//7
void Admin::disconnect()
{
	bool isValid = false;
	while (isValid == false)
	{

		try
		{

			cout << "Please select the two users you want to disconnect: " << endl;

			cout << "First user- ";
			User* user1 = chooseUser();

			cout << "Second user- ";
			User* user2 = chooseUser();

			if (user1->removeFriend(user2))
			{
				user2->removeFriend(user1);
				cout << "\nDisconnection was made:\n" << user1->getName() << " X----X " << user2->getName() << endl;
			}
			else
				cout << user1->getName() << " and " << user2->getName() << " are not friends" << endl;
		}
		catch (choiceExceptions& ce)
		{
			ce.what();
		}
		catch (...)
		{
			cout << "FATAL ERROR !" << endl;
		}
		isValid = true;

	}
}


//8
void  Admin::addFanToFanpage()
{
	if (m_fanPagesList.empty())
		cout << "No fanpages in the system" << endl;
	bool isValid = false;
	while (isValid == false)
	{
		try
		{
			cout << "Adding a fan to a fan page" << endl;
			User* fan = chooseUser();
			Fanpage* fanpage = chooseFanpage();
			fanpage->addFan(fan);
			fan->becomeFan(fanpage);
		}
		catch (choiceExceptions& ce)
		{
			ce.what();
		}
		catch (...)
		{
			cout << "FATAL ERROR !" << endl;
		}
		isValid = true;

	}
}

//9
void Admin::removeFanFromFanpage()
{


	bool isValid = false;
	cout << "Pick the fanpage you want to remove a fan from" << endl;
	while (isValid == false)
	{
		try
		{
			Fanpage* fanPage = chooseFanpage();
			int numOfFans = (int)fanPage->getNumOfFans();
			if (numOfFans == EMPTY)
			{
				cout << fanPage->getName() << " has no fans\n";
				return;
			}
			else
			{
				User* fanToRemove = fanPage->chooseFan();
				fanPage->removeFan(fanToRemove);
			}
		}
		catch (choiceExceptions& ce)
		{
			ce.what();
		}
		catch (...)
		{
			cout << "FATAL ERROR !" << endl;
		}
		isValid = true;


	}

}

//10
void Admin::showAllEntities() const
{
	cout << "\n---------ALL ENTETIES IN THE SYSTEM-----------\n" << endl;
	showAllUsers();
	cout << endl;
	showAllFanpages();

}

//11
void Admin::showAllConnections()  // const causes compilation error
{
	int numOfFanpages = (int)m_fanPagesList.size();
	int numOfUsers = (int)m_usersList.size();
	list<User>::const_iterator userItr = m_usersList.begin();
	list<Fanpage>::const_iterator fanPageItr = m_fanPagesList.begin();
	bool isValid = false;
	int choice;
	cout << "Select 1 to see all connection of a certain user or 2 to see all fans of a Fanpage " << endl;

	while (isValid == false)
	{
		try
		{

			choice = getChoice(USER_CHOICE, FAN_PAGE_CHOICE);
			switch (choice)
			{
			case 1:
				chooseUser()->showFriends();
				break;
			case 2:
				chooseFanpage()->showFans();
				break;
			}
		}
		catch (choiceExceptions& ce)
		{
			ce.what();
		}
		catch (...)
		{
			cout << "FATAL ERROR !" << endl;
		}
		isValid = true;
	}
}

void Admin::showAllFanpages() const
{
	if (m_fanPagesList.empty() == true)
	{
		cout << "No Fanpages in the system..." << endl;
		return;
	}

	list<Fanpage>::const_iterator itr = m_fanPagesList.begin();
	list<Fanpage>::const_iterator itrEnd = m_fanPagesList.end();
	cout << "----FANPAGES---" << endl;
	int num = 1;
	for (; itr != itrEnd; ++itr)
	{
		cout << num << ".";
		itr->show();
		num++;
	}
	cout << "----------------" << endl;

}

void Admin::showAllUsers() const
{
	if (m_usersList.empty() == true)
	{
		cout << "No Users in the system..." << endl;
		return;
	}

	list<User>::const_iterator itr = m_usersList.begin();
	list<User>::const_iterator itrEnd = m_usersList.end();
	cout << "~~~~~~ Users ~~~~~~" << endl;
	int num = 1;
	for (; itr != itrEnd; ++itr)
	{
		cout << num << ".";
		itr->show();
		num++;
	}
	cout << "~~~~~~~~~~~~~~~~~~~~" << endl;


}

User* Admin::chooseUser() noexcept(false)
{
	int numOfUsers = (int)m_usersList.size();
	int choice;
	cout << "Please select the User:\n" << endl;
	showAllUsers();

	choice = getChoice(1, numOfUsers);
	list<User>::iterator itr = m_usersList.begin();
	std::advance(itr, choice - 1);
	return &(*itr);

}

Fanpage* Admin::chooseFanpage()
{

	int numOfFanpages = (int)m_fanPagesList.size();
	int choice;
	cout << "Please select the Fanpage:\n" << endl;
	showAllFanpages();

	choice = getChoice(1, numOfFanpages);
	list<Fanpage>::iterator itr = m_fanPagesList.begin();
	std::advance(itr, choice - 1);
	return &(*itr);
}

string Admin::getUserName()
{
	string tempName;
	cout << "Please write the user full name: ";

	getline(std::cin, tempName);
	_flushall();



	if (!(nameException::isNameValid(tempName)))
		throw nameException(tempName);

	if (isUserExist(tempName) == true)
		throw isExistException(tempName);


	return tempName;


}

string Admin::getFanPageName()
{
	string tempName;
	cout << "Please write the fan  page name: ";

	getline(std::cin, tempName);
	_flushall();

	if (!(nameException::isNameValid(tempName)))
		throw nameException(tempName);

	if (isFanpageExist(tempName) == true)
		throw isExistException(tempName);

	return tempName;

}

int Admin::getChoice(int min, int max)
{
	int choice;
	cout << "Choice: ";
	cin >> choice;
	cin.ignore();
	if (!(choice >= min && choice <= max))
		throw choiceExceptions(min, max);
	else
		return choice;



}

void Admin::getBirthday(char* birthDay)
{
	int day;
	int month;
	int year;

	string date;
	string charyear = "year";
	string charmonth = "month";
	string charday = "day";



	cout << "Please write the year the user born: ";
	cin >> year;
	cin.ignore();
	if (!(birthdayException::checkYear(year)))
		throw (birthdayException(year, charyear));


	cout << "Please write the month the user born: ";
	cin >> month;
	if (!(birthdayException::checkMonth(month)))
		throw (birthdayException(month, charmonth));


	cout << "Please write the day the user born: ";
	cin >> day;
	if (!(birthdayException::checkDay(day)))
		throw (birthdayException(day, charday));




	// Add leading zeros if necessary
	if (day < 10)
	{
		date += "0";
	}
	date += to_string(day);
	date += "/";

	if (month < 10)
	{
		date += "0";
	}
	date += to_string(month);
	date += "/";

	date += to_string(year);

	//copying to desired
	std::strcpy(birthDay, date.c_str());



}

bool Admin::isUserExist(string& userName)
{
	if (m_usersList.empty() == false)
	{
		std::list<User>::iterator itr = m_usersList.begin();
		std::list<User>::iterator itrEnd = m_usersList.end();
		for (; itr != itrEnd; ++itr)
		{
			if ((*itr).getName() == userName)
				return true;
		}
	}
	return false;
}

bool Admin::isFanpageExist(string& fanPageName)
{
	if (m_fanPagesList.empty() == false)
	{
		std::list<Fanpage>::iterator itr = m_fanPagesList.begin();
		std::list<Fanpage>::iterator itrEnd = m_fanPagesList.end();
		for (; itr != itrEnd; ++itr)
		{
			if ((*itr).getName() == fanPageName)
				return true;
		}
	}
	return false;
}

void Admin::showAllFanpagesOfUser(User& user) const
{
	cout << user.getName() << "is a fan of: \n";
	user.showAllFanpages();
}



Status* Admin::createStatus() const noexcept(false)
{
	string tempText;
	string tempFileName;
	int choice;
	cout << "Please define the status type:\n\t1 - text\n\t2 - video\n\t3 - picture " << endl;
	choice = getChoice(TEXT, VIDEO);

	cout << "Please write the status text: ";

	getline(std::cin, tempText);
	_flushall();



	if (tempText[0] == '\0')
		throw statusExceptions();

	switch (choice)
	{

	case 1:
		return new Status(tempText);
		break;

	case 2:

		cout << "Please write the video file name : ";
		getline(std::cin, tempFileName);
		_flushall();
		if (tempFileName[0] == '\0')
			throw statusExceptions();
		return new videoStatus(tempText, tempFileName);

		break;
	case 3:
		cout << "Please write the picture file name : ";
		getline(std::cin, tempFileName);
		_flushall();
		if (tempFileName[0] == '\0')
			throw statusExceptions();
		return new pictureStatus(tempText, tempFileName);
		break;
	default: throw statusExceptions();
	}
}


void Admin::save(ofstream& outputFile) const
{
	int numOfUsers = (int)m_usersList.size();
	int numOfFanpages = (int)m_fanPagesList.size();

	outputFile.write((const char*)&numOfUsers, sizeof(int));
	for (auto& currUser : m_usersList)
		currUser.save(outputFile);

	outputFile.write((const char*)&numOfFanpages, sizeof(int));
	for (auto& currFanpage : m_fanPagesList)
		currFanpage.save(outputFile);

	//  saving connections...
	for (auto& currUser : m_usersList)
	{
		currUser.saveFriendsNames(outputFile);
		currUser.saveFanpagesNames(outputFile);
	}

	for (auto& currFanpage : m_fanPagesList)
	{
		currFanpage.saveFansNames(outputFile);
	}

}

Admin::Admin(ifstream& inputFile)
{
	int numOfUsers, numOfFanpages, i;
	int currNumOfFriends, currNumOfFanpages, currNumFans;

	// loading users
	inputFile.read((char*)&numOfUsers, sizeof(int));
	for (i = 0; i < numOfUsers; i++)
	{

		m_usersList.push_back(User(inputFile));

		inputFile.read((char*)&currNumOfFriends, sizeof(int));
		inputFile.read((char*)&currNumOfFanpages, sizeof(int));

		m_usersList.back().setNumOfFriends(currNumOfFriends);
		m_usersList.back().setNumOfFanpages(currNumOfFanpages);
	}

	//loading fanpages
	inputFile.read((char*)&numOfFanpages, sizeof(int));
	for (i = 0; i < numOfFanpages; i++)
	{
		m_fanPagesList.push_back(Fanpage(inputFile));

		inputFile.read((char*)&currNumFans, sizeof(int));
		m_fanPagesList.back().setNumOfFans(currNumFans);
	}

	for (auto& currUser : m_usersList)
	{

		currNumOfFriends = currUser.getFriendsCapacity();
		currNumOfFanpages = currUser.getFanpagesCapacity();

		// loading each user friend
		for (int i = 0; i < currNumOfFriends; i++)
		{
			int len;
			char* friendName;
			inputFile.read((char*)&len, sizeof(int));
			friendName = new char[len];
			inputFile.read(friendName, len);
			string friendStr(friendName, len);
			delete[] friendName;

			for (auto& itr : m_usersList)
			{
				if (itr.getName() == friendStr)
					currUser.addFriend(&itr);
			}
		}


		//loading each user fanpages
		for (int i = 0; i < currNumOfFanpages; i++)
		{
			int len;
			char* fanPageName;
			inputFile.read((char*)&len, sizeof(int));
			fanPageName = new char[len];
			inputFile.read(fanPageName, len);
			string fp_str(fanPageName, len);
			delete[] fanPageName;

			for (auto& itr : m_fanPagesList)
			{
				if (itr.getName() == fp_str)
					currUser.becomeFan(&itr);
			}
		}



	}

	for (auto& currFanpage : m_fanPagesList)
	{
		currNumFans = currFanpage.getFansCapacity();
		for (int i = 0; i < currNumFans; i++)
		{
			int len;
			char* fanName;
			inputFile.read((char*)&len, sizeof(int));
			fanName = new char[len];
			inputFile.read(fanName, len);
			string fan_str(fanName, len);
			delete[] fanName;

			for (auto& itr : m_usersList)
			{
				if (itr.getName() == fan_str)
					currFanpage.addFan(&itr);
			}
		}

	}


}


