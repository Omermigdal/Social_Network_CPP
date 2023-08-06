#ifndef __FACEBOOK_H
#define __FACEBOOK_H


#include "fanPage.h"
#include "user.h"
#include "status.h"
#include <list>

enum menu
{
	ADD_USER = 1, ADD_FANPAGE, ADD_STATUS_TO_ENTITY,
	SHOW_ALL_STATUSES, SHOW_LAST_TEN_STATUSES_OF_FRIENDS_OF_USER,
	CONNECT, DISCONNECT, ADD_FAN_TO_FANPAGE, REMOVE_FAN_FROM_FANPAGE, SHOW_ALL_ENTETIES, SHOW_ALL_CONNECTIONS, EXIT_SYSTEM
};


class Admin
{
private:
	std::list<User> m_usersList;
	std::list<Fanpage> m_fanPagesList;
public:
	Admin(std::ifstream& inputFile);

	//managing the basic menu
	void promptMenu();

	//createing new user and adding it to the system 
	void addUser();

	//creating new fan page and adding it to the system
	void addFanpage();


	//creating new status and adding it to a user/fan page (based on your choice)
	void addStatusToEntity();

	// showing the statuses of a spesific entity (user or fan Page)
	void showStatuses();

	// showing last ten statuses of each friend of a given user
	void showLastTenStatuses();


	//coonecting between 2 users (make then a "friends")
	void connect();

	//disconecting 2 user (unfriend them from each other)
	void disconnect();

	//connect between a user and a fan page
	void addFanToFanpage();

	//disconnect a user and a fan page
	void removeFanFromFanpage();

	//show all the user anf fan pages in the system
	void showAllEntities() const;


	//shows all the fanpages of user
	void showAllFanpagesOfUser(User& user) const;


	// show all user friends or fan page fans
	void showAllConnections(); // why cant const


	void showAllFanpages() const;

	void showAllUsers() const;

	User* chooseUser();

	Fanpage* chooseFanpage();

	std::string getUserName()noexcept(false);

	std::string getFanPageName()noexcept(false);

	static int getChoice(int min, int max) noexcept(false);

	void getBirthday(char* birthDay);

	bool isUserExist(std::string& userName);

	bool isFanpageExist(std::string& fanPageName)noexcept(false);


	Status* createStatus() const noexcept(false);


	int getNumOfUsers()const { return (int)m_usersList.size(); }
	int getNumOfFanPages()const { return (int)m_fanPagesList.size(); }

	void save(std::ofstream& outputFile) const;
};




#endif // __FACEBOOK_H






