#ifndef __USER_H
#define __USER_H
#include <vector>
#include "status.h"
#include "choiceExceptions.h"
#include "isExistException.h"
#include "Entity.h"
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)



using namespace std;
class Fanpage;
class User : public Entity
{
private:
    char m_birthDay[11];
    std::vector<User*> m_friends;
    std::vector<Fanpage*> m_fanPages;

    bool setBirthDay(const char* birthDay);
public:


    User(std::string name, const char* birthDay); // ctor
    User(std::ifstream& inputFile);


    // dtor
    ~User() = default;

    // sets and gets
    const char* getBirthDay() const { return m_birthDay; }

    int getNumOfFriends() const { return (int)m_friends.size(); }


    int getFriendsCapacity() const { return (int)m_friends.capacity(); }
    int getFanpagesCapacity() const { return (int)m_fanPages.capacity(); }


    void setNumOfFriends(int numFriends) { m_friends.reserve(numFriends); }
    void setNumOfFanpages(int numFanpages) { m_fanPages.reserve(numFanpages); }


    //adds the given User to the THIS user friend list
    bool addFriend(User* newFriend);

    bool becomeFan(Fanpage* pageToFan);

    // remove the given User from THIS user friend list

    bool removeFriend(User* friendToRemove);



    bool areFriends(const User* other) const;

    bool isFan(Fanpage* fanPageTocheck) const;


    //operators----------------------------------------------

    bool operator==(const User& other) const;

    User& operator+=(User& _newFriend);// how to const

    User& operator+=(Fanpage& fanPage);

    bool operator>(User& other)  const;
    bool operator<(User& other)  const { return !(*this > other); }


    bool operator>(Fanpage& other)  const;
    bool operator<(Fanpage& other)  const { return !(*this > other); }


    // shows--------------------------------------------------
    //show all the user friends
    void showFriends()  const;

    void showAllFanpages() const;

    //show last ten statuse of user friends
    void showLastTenStatusesOfFriends() const;

    virtual void save(ofstream& outputFile)const override;

    void saveFriendsNames(ofstream& outputFile)const;
    void saveFanpagesNames(ofstream& outputFile)const;



};
#endif // !__USER_H
